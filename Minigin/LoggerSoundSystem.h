#pragma once
#include "SoundSystemInterface.h"
class LoggerSoundSystem final : public SoundSystemInterface
{
public:
	//------CONSTRUCTOR/DESTRUCTOR------
	LoggerSoundSystem() = default;
	~LoggerSoundSystem() = default;

	//------COPY CONSTRUCTORS------
	LoggerSoundSystem(const LoggerSoundSystem&) = delete;
	LoggerSoundSystem(LoggerSoundSystem&&) = delete;
	//------ASSIGNMENT OPERATORS------
	LoggerSoundSystem operator=(const LoggerSoundSystem&) = delete;
	LoggerSoundSystem& operator=(LoggerSoundSystem&&) = delete;

	//------PUBLIC FUNCTIONS------
	void PlayMusic(const std::string& filePath) override;
	void PlayEffect(const std::string& filePath) override;
	void SetPause(bool isPaused) override;
	void SetMusicVolume(int volume) override;
	void SetEffectVolume(int volume) override;
	int GetMusicVolume() override;
	int GetEffectVolume() override;
};

