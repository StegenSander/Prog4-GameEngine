#pragma once
#include "SoundSystemInterface.h"
#include <map>
#include <queue>
#include <thread>
#include <mutex>
namespace SDLSound {
#include "../3rdParty/SDL2_audio/audio.h"
}


class SDLSoundSystem final : public SoundSystemInterface
{
public:
	//------CONSTRUCTOR/DESTRUCTOR------
	SDLSoundSystem(int volume = 100);
	~SDLSoundSystem();

	//------COPY CONSTRUCTORS------
	SDLSoundSystem(const SDLSoundSystem&) = delete;
	SDLSoundSystem(SDLSoundSystem&&) = delete;
	//------ASSIGNMENT OPERATORS------
	SDLSoundSystem operator=(const SDLSoundSystem&) = delete;
	SDLSoundSystem& operator=(SDLSoundSystem&&) = delete;

	//------PUBLIC FUNCTIONS------
	void PlayMusic(const std::string& filePath) override;
	void PlayEffect(const std::string& filePath) override;
	void SetPause(bool isPaused) override;
	void SetMusicVolume(int volume) override;
	void SetEffectVolume(int volume) override;
	int GetMusicVolume() override;
	int GetEffectVolume() override;

	//------PUBLIC VARIABLES------
private:
	enum class AudioType
	{
		Music,
		Effect,
	};
	struct AudioData
	{
		SDLSound::Audio* pAudio;
		AudioType audioType;
		AudioData(SDLSound::Audio* audio, AudioType type)
			: pAudio{audio}
			, audioType{type} 
		{}
	};

	//------PRIVATE FUNCTIONS------
	void HandleQueue();
	void AddToQueue(const std::string& filePath, AudioType audioType);

	//------PRIVATE VARIABLES------	
	int m_EffectVolume;
	int m_MusicVolume;
	bool m_IsPaused;
	std::map<std::string, SDLSound::Audio*> m_AudioMap{};

	std::queue<AudioData> m_AudioQueue{};
	bool m_IsRunning;

	std::thread m_ThisThread{};
	std::mutex m_DataProtectionMutex{};
	std::mutex m_ThreadSleepMutex{};
};
