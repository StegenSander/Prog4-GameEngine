#pragma once
#include "DataStructures.h"
class LevelLoader
{
public:
	//------CONSTRUCTOR/DESTRUCTOR------
	virtual ~LevelLoader() {};

	//------COPY CONSTRUCTORS------
	LevelLoader(const LevelLoader&) = delete;
	LevelLoader(LevelLoader&&) = delete;
	//------ASSIGNMENT OPERATORS------
	LevelLoader operator=(const LevelLoader&) = delete;
	LevelLoader& operator=(LevelLoader&&) = delete;

	//------PUBLIC FUNCTIONS------
	static void LoadLevel(const std::string& filePath
		, GameRules& gameRules
		,LevelData& levelData
		,QBertData& qbertData
		,EntityData& slickAndSamData
		,EntityData& uggAndWrongwayData
		,EntityData& coilyData);
	static void WriteLevel(const std::string& filePath
		, const GameRules& gameRules
		, const LevelData& levelData
		, const QBertData& qbertData
		, const EntityData& slickAndSamData
		, const EntityData& uggAndWrongwayData
		, const EntityData& coilyData);

	//------PUBLIC VARIABLES------
protected:
	//------PROTECTED FUNCTIONS------

	//------PROTECTED VARIABLES------	
private:
	//------PRIVATE FUNCTIONS------
	LevelLoader();

	//------PRIVATE VARIABLES------	
};
