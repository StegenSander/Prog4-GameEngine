#include "MiniginPCH.h"
#include "SDLSoundSystem.h"
namespace SDLSound {
#include "../3rdParty/SDL2_audio/audio.c"
}


SDLSoundSystem::SDLSoundSystem(int volume)
	: m_MusicVolume(volume)
	, m_EffectVolume(volume)
{
	SDLSound::initAudio();
}

SDLSoundSystem::~SDLSoundSystem()
{
	SDLSound::endAudio();
}

void SDLSoundSystem::PlayMusic(const std::string& filePath)
{
	if (m_AudioMap.find(filePath) ==  m_AudioMap.end())
	{
		SDLSound::Audio* music = SDLSound::createAudio(filePath.c_str(), 1, m_MusicVolume);
		if (!music)
		{
			std::cout << "Audio with path: " << filePath << " could not be loaded\n";
			return;
		}
		m_AudioMap[filePath] = music;
	}

	SDLSound::playMusicFromMemory(m_AudioMap[filePath], m_MusicVolume);
}

void SDLSoundSystem::PlayEffect(const std::string& filePath)
{
	if (m_AudioMap.find(filePath) == m_AudioMap.end())
	{
		SDLSound::Audio* effect = SDLSound::createAudio(filePath.c_str(), 1, m_MusicVolume);
		if (!effect)
		{
			std::cout << "Audio with path: " << filePath << " could not be loaded\n";
			return;
		}
		m_AudioMap[filePath] = effect;
	}

	SDLSound::playSoundFromMemory(m_AudioMap[filePath], m_MusicVolume);
}

void SDLSoundSystem::SetPause(bool isPaused)
{
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
