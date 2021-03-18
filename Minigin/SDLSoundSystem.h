#pragma once
#include "SoundSystemInterface.h"
namespace SDLSound {
#include "../3rdParty/SDL2_audio/audio.h"
}
#include <map>


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
protected:
	//------PROTECTED FUNCTIONS------

	//------PROTECTED VARIABLES------	
private:
	//------PRIVATE FUNCTIONS------

	//------PRIVATE VARIABLES------	
	int m_EffectVolume;
	int m_MusicVolume;
	std::map<std::string, SDLSound::Audio*> m_AudioMap{};
};
