#include "MiniginPCH.h"
#include "LevelLoader.h"
#include "BinaryWriter.h"
#include "BinaryReader.h"

void LevelLoader::LoadLevel(const std::string& filePath
	, GameRules& gameRules
	, LevelData& levelData
	, QBertData& qbertData
	, EntityData& slickAndSamData
	, EntityData& uggAndWrongwayData
	, EntityData& coilyData)
{
	BinaryReader binReader{};
	binReader.openFile(filePath);

	//GameRules
	binReader.Read(gameRules.AmountOfColorChanges);
	binReader.Read(gameRules.Revertible);

	//LevelData
	binReader.Read(levelData.LevelSize);
	binReader.Read(levelData.RowOfDiscs);
	binReader.Read(levelData.LevelPosition.x);
	binReader.Read(levelData.LevelPosition.y);
	binReader.Read(levelData.LevelPosition.z);

	//QbertData
	 binReader.Read(qbertData.Lives);
	 binReader.Read(qbertData.TimeBetweenMoves);

	//Slick and Sam
	 binReader.Read(slickAndSamData.MaxEntitiesAlive);
	 binReader.Read(slickAndSamData.MinSpawnDuration);
	 binReader.Read(slickAndSamData.MaxSpawnDuration);
	 binReader.Read(slickAndSamData.TimeBetweenMoves);

	//ugg and Wrongway
	 binReader.Read(uggAndWrongwayData.MaxEntitiesAlive);
	 binReader.Read(uggAndWrongwayData.MinSpawnDuration);
	 binReader.Read(uggAndWrongwayData.MaxSpawnDuration);
	 binReader.Read(uggAndWrongwayData.TimeBetweenMoves);

	//Coily
	 binReader.Read(coilyData.MaxEntitiesAlive);
	 binReader.Read(coilyData.MinSpawnDuration);
	 binReader.Read(coilyData.MaxSpawnDuration);
	 binReader.Read(coilyData.TimeBetweenMoves);
	 binReader.closeFile();
}

void LevelLoader::WriteLevel(const std::string& filePath
	, const GameRules& gameRules
	, const LevelData& levelData
	, const QBertData& qbertData
	, const EntityData& slickAndSamData
	, const EntityData& uggAndWrongwayData
	, const EntityData& coilyData)
{
	BinaryWriter binWriter{};
	binWriter.openFile(filePath);

	//GameRules
	binWriter.Write(gameRules.AmountOfColorChanges);
	binWriter.Write(gameRules.Revertible);

	//LevelData
	binWriter.Write(levelData.LevelSize);
	binWriter.Write(levelData.RowOfDiscs);
	binWriter.Write(levelData.LevelPosition.x);
	binWriter.Write(levelData.LevelPosition.y);
	binWriter.Write(levelData.LevelPosition.z);

	//QbertData
	binWriter.Write(qbertData.Lives);
	binWriter.Write(qbertData.TimeBetweenMoves);

	//Slick and Sam
	binWriter.Write(slickAndSamData.MaxEntitiesAlive);
	binWriter.Write(slickAndSamData.MinSpawnDuration);
	binWriter.Write(slickAndSamData.MaxSpawnDuration);
	binWriter.Write(slickAndSamData.TimeBetweenMoves);

	//ugg and Wrongway
	binWriter.Write(uggAndWrongwayData.MaxEntitiesAlive);
	binWriter.Write(uggAndWrongwayData.MinSpawnDuration);
	binWriter.Write(uggAndWrongwayData.MaxSpawnDuration);
	binWriter.Write(uggAndWrongwayData.TimeBetweenMoves);

	//Coily
	binWriter.Write(coilyData.MaxEntitiesAlive);
	binWriter.Write(coilyData.MinSpawnDuration);
	binWriter.Write(coilyData.MaxSpawnDuration);
	binWriter.Write(coilyData.TimeBetweenMoves);
	binWriter.closeFile();
}
