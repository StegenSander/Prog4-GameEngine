#pragma once
#include "SoundSystemInterface.h"
class NullSoundSystem final : public SoundSystemInterface
{
public:
	//------PUBLIC FUNCTIONS------
	void PlayMusic(const std::string& ) override {};
	void PlayEffect(const std::string& ) override {};
	void SetPause(bool ) override {};
	void SetMusicVolume(int ) override {};
	void SetEffectVolume(int ) override {};
	int GetMusicVolume() override { return -1; };
	int GetEffectVolume() override { return -1; };
};

