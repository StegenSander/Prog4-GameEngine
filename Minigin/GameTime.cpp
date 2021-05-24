#include "MiniginPCH.h"
#include "GameTime.h"

GameTime::GameTime()
	:m_LastTimePoint(std::chrono::steady_clock::now())
{
	
}

void GameTime::Update()
{
	const std::chrono::steady_clock::time_point currentTime = std::chrono::steady_clock::now();
	m_DeltaTime = std::chrono::duration<float>(currentTime - m_LastTimePoint).count();
	m_LastTimePoint = currentTime;
}

void GameTime::SetTargetFPS(int FPS)
{
	m_MsPerFrame =1.f / float(FPS) * 1000;
}


