#include "MiniginPCH.h"
#include "LoggerSoundSystem.h"

void LoggerSoundSystem::PlayMusic(const std::string&)
{
	std::cout << "LoggerSoundSystem: Play music\n";
}

void LoggerSoundSystem::PlayEffect(const std::string&)
{
	std::cout << "LoggerSoundSystem: Play effect\n";
}

void LoggerSoundSystem::SetPause(bool isPaused)
{
	std::cout << "LoggerSoundSystem: Set paused to " << isPaused<<"\n";
}

void LoggerSoundSystem::SetMusicVolume(int volume)
{
	std::cout << "LoggerSoundSystem: Set music volume to "<< volume << "\n";
}

void LoggerSoundSystem::SetEffectVolume(int volume)
{
	std::cout << "LoggerSoundSystem: Set effect volume to " << volume << "\n";
}

int LoggerSoundSystem::GetMusicVolume()
{
	std::cout << "LoggerSoundSystem: Get music volume\n";
	return 0;
}

int LoggerSoundSystem::GetEffectVolume()
{
	std::cout << "LoggerSoundSystem: Get music volume\n";
	return 0;
}
