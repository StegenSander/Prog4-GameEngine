#include "MiniginPCH.h"
#include "ServiceLocator.h"
SoundSystemInterface* ServiceLocator::m_SoundSystem{ nullptr };
NullSoundSystem* ServiceLocator::m_DefaultSoundSystem = new NullSoundSystem{};