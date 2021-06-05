#pragma once
#include <chrono>
#include "Singleton.h"
class GameTime : public dae::Singleton<GameTime>
{
public:
	//------CONSTRUCTOR/DESTRUCTOR------
	~GameTime() = default;

	//------COPY CONSTRUCTORS------
	GameTime(const GameTime&) = delete;
	GameTime(GameTime&&) = delete;
	//------ASSIGNMENT OPERATORS------
	GameTime operator=(const GameTime&) = delete;
	GameTime& operator=(GameTime&&) = delete;

	//------PUBLIC FUNCTIONS------
	void Update();
	void SetTargetFPS(int FPS);

	//------PUBLIC GETTERS------
	[[nodiscard]] float GetDeltaTime() const {return m_DeltaTime;};
	[[nodiscard]] float GetFPS() const { return 1 / m_DeltaTime; };
	[[nodiscard]] float GetMsPerFrame() const { return m_MsPerFrame; };
	[[nodiscard]] std::chrono::time_point<std::chrono::steady_clock> GetLatestTime() const { return m_LastTimePoint; };

	//------PUBLIC VARIABLES------	
private:
	//------PRIVATE FUNCTIONS------
	GameTime();

	friend class dae::Singleton<GameTime>;
	//------PRIVATE VARIABLES------
	std::chrono::time_point<std::chrono::steady_clock> m_LastTimePoint;

	float m_DeltaTime{};

	float m_MsPerFrame = 16; //16 for 60 fps, 33 for 30 fps
};