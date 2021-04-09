#include "MiniginPCH.h"
#include "SDLSoundSystem.h"
namespace SDLSound {
#include "../3rdParty/SDL2_audio/audio.c"
}
#include <functional>


SDLSoundSystem::SDLSoundSystem(int volume)
	: m_MusicVolume(volume)
	, m_EffectVolume(volume)
	, m_IsRunning {true}
	, m_IsPaused { false}
{
	SDLSound::initAudio();
	m_ThisThread = std::thread (std::bind(&SDLSoundSystem::HandleQueue, this));
}

SDLSoundSystem::~SDLSoundSystem()
{
	m_IsRunning = false;
	m_ThisThread.join();

	for (auto& pair : m_AudioMap)
	{
		delete pair.second;
	}
	SDLSound::endAudio();
}

void SDLSoundSystem::PlayMusic(const std::string& filePath)
{
	std::unique_lock<std::mutex> lock{ m_DataProtectionMutex };
	AddToQueue(filePath, AudioType::Music);
}

void SDLSoundSystem::PlayEffect(const std::string& filePath)
{
	std::unique_lock<std::mutex> lock{ m_DataProtectionMutex };
	AddToQueue(filePath, AudioType::Effect);
}

void SDLSoundSystem::AddToQueue(const std::string& filePath, AudioType audioType)
{
	if (m_AudioMap.find(filePath) == m_AudioMap.end())
	{
		SDLSound::Audio* effect = SDLSound::createAudio(filePath.c_str(), 1, m_EffectVolume);
		if (!effect)
		{
			std::cout << "Audio with path: " << filePath << " could not be loaded\n";
			return;
		}
		m_AudioMap[filePath] = effect;
	}

	m_AudioQueue.push(AudioData( m_AudioMap[filePath],audioType));
}

void SDLSoundSystem::HandleQueue()
{
	while (m_IsRunning)
	{
		while (m_AudioQueue.size() > 0 && !m_IsPaused)
		{
			m_DataProtectionMutex.lock();
				AudioData data = m_AudioQueue.front();
				m_AudioQueue.pop();
			m_DataProtectionMutex.unlock();

			switch (data.audioType)
			{
			case AudioType::Effect:
				SDLSound::playSoundFromMemory(data.pAudio, m_EffectVolume);
				break;
			case AudioType::Music:
				SDLSound::playMusicFromMemory(data.pAudio, m_MusicVolume);
				break;
			}
		}

		//TODO: Find a way to sleep the thread until it has something to do again
	}
}

void SDLSoundSystem::SetPause(bool isPaused)
{
	m_IsPaused = isPaused;
	if (isPaused)
	{
		SDLSound::pauseAudio();
	}
	else
	{
		SDLSound::unpauseAudio();
	}
}

void SDLSoundSystem::SetMusicVolume(int volume)
{
	m_MusicVolume = volume;
}

void SDLSoundSystem::SetEffectVolume(int volume)
{
	m_EffectVolume = volume;
}

int SDLSoundSystem::GetMusicVolume()
{
	return m_MusicVolume;
}

int SDLSoundSystem::GetEffectVolume()
{
	return m_EffectVolume;
}
