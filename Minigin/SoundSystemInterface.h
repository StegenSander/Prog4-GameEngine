#pragma once
#include <string>
class SoundSystemInterface
{
public:
	//------CONSTRUCTOR/DESTRUCTOR------
	SoundSystemInterface() = default;
	virtual ~SoundSystemInterface() = default;

	//------COPY CONSTRUCTORS------
	SoundSystemInterface(const SoundSystemInterface&) = delete;
	SoundSystemInterface(SoundSystemInterface&&) = delete;
	//------ASSIGNMENT OPERATORS------
	SoundSystemInterface operator=(const SoundSystemInterface&) = delete;
	SoundSystemInterface& operator=(SoundSystemInterface&&) = delete;

	//------PUBLIC FUNCTIONS------
	virtual void PlayMusic(const std::string& filePath) = 0;
	virtual void PlayEffect(const std::string& filePath) = 0;
	virtual void SetPause(bool isPaused) = 0;
	virtual void SetMusicVolume(int m_Volume) = 0;
	virtual void SetEffectVolume(int m_Volume) = 0;
	virtual int GetMusicVolume() = 0;
	virtual int GetEffectVolume() = 0;
};

