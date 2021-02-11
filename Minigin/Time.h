#pragma once
#include <chrono>
#include "Singleton.h"
class Time : public dae::Singleton<Time>
{
public:
	//------CONSTRUCTOR/DESTRUCTOR------
	Time();
	~Time() = default;

	//------COPY CONSTRUCTORS------
	Time(const Time&) = delete;
	Time(Time&&) = delete;
	//------ASSIGNMENT OPERATORS------
	Time operator=(const Time&) = delete;
	Time& operator=(Time&&) = delete;

	//------PUBLIC FUNCTIONS------
	void Update();
	void SetTargetFPS(int FPS);

	//------PUBLIC GETTERS------
	float GetDeltaTime() const {return m_DeltaTime;};
	float GetFPS() const { return 1 / m_DeltaTime; };
	float GetMsPerFrame() const { return m_MsPerFrame; };
	std::chrono::time_point<std::chrono::steady_clock> GetLatestTime() const { return m_LastTimePoint; };

	//------PUBLIC VARIABLES------
protected:
	//------PROTECTED FUNCTIONS------

	//------PROTECTED VARIABLES------	
private:
	//------PRIVATE FUNCTIONS------

	//------PRIVATE VARIABLES------
	std::chrono::time_point<std::chrono::steady_clock> m_LastTimePoint;

	float m_DeltaTime{};

	float m_MsPerFrame = 33; //16 for 60 fps, 33 for 30 fps
};