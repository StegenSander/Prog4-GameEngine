#pragma once
#include "SoundSystemInterface.h"
#include "NullSoundSystem.h"

class ServiceLocator final
{
public:
	static void SetSoundSystem(SoundSystemInterface* soundSystem) { m_SoundSystem = soundSystem; };
	static SoundSystemInterface* GetSoundSystem() {
		if (m_SoundSystem) return m_SoundSystem; else return m_DefaultSoundSystem;
	};
private:
	static SoundSystemInterface* m_SoundSystem;
	static NullSoundSystem* m_DefaultSoundSystem;
};
