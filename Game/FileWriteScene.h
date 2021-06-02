#pragma once
#include "Scene.h"
namespace dae {
	class GameObject;
}
class FileWriteScene
	: public dae::Scene
{
public:
	FileWriteScene();
	void Initialise() override;
};

