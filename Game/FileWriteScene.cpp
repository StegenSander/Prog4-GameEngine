#include "MiniginPCH.h"
#include "FileWriteScene.h"
#include "LevelLoader.h"

FileWriteScene::FileWriteScene()
	: Scene("FileWriteScene")
{
}

void FileWriteScene::Initialise()
{
	std::string filePath{"../Data/-----.bin"};

	{
		GameRules gameRules;
		gameRules.AmountOfColorChanges = 1;
		gameRules.Revertible = true;

		LevelData levelData;
		levelData.LevelSize = 7; //7
		levelData.RowOfDiscs = 6;
		levelData.LevelPosition = { 260,-50,0 };

		QBertData qbertData;
		qbertData.Lives = 3;
		qbertData.TimeBetweenMoves = 0.3f;

		EntityData slickAndSameData;
		slickAndSameData.MaxEntitiesAlive = 2;
		slickAndSameData.MinSpawnDuration = 9;
		slickAndSameData.MaxSpawnDuration = 12;
		slickAndSameData.TimeBetweenMoves = 0.5f;

		EntityData uggAndWrongwayData;
		uggAndWrongwayData.MaxEntitiesAlive = 2;
		uggAndWrongwayData.MinSpawnDuration = 10;
		uggAndWrongwayData.MaxSpawnDuration = 15;
		uggAndWrongwayData.TimeBetweenMoves = 1.f;

		EntityData coilyData;
		coilyData.MaxEntitiesAlive = 1; //1
		coilyData.MinSpawnDuration = 8; //10
		coilyData.MaxSpawnDuration = 13; //15
		coilyData.TimeBetweenMoves = 1.f;

		LevelLoader::WriteLevel(filePath,gameRules, levelData, qbertData, slickAndSameData, uggAndWrongwayData, coilyData);
	}

	GameRules gameRules{};
	LevelData levelData{};
	QBertData qbertData{};
	EntityData slickAndSameData{};
	EntityData uggAndWrongwayData{};
	EntityData coilyData{};
	LevelLoader::LoadLevel(filePath,gameRules, levelData, qbertData, slickAndSameData, uggAndWrongwayData, coilyData);
}
