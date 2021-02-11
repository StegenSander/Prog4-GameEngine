#pragma once
#include "GameObject.h"

class BaseComponent
{
public:
	//------CONSTRUCTOR/DESTRUCTOR------
	BaseComponent()= default;
	virtual ~BaseComponent() = default;
	
	//------PUBLIC FUNCTIONS------
	virtual void Update() = 0;
	dae::GameObject* GetGameObject() const { return  m_pGameObject; };


	friend void dae::GameObject::AddComponent(BaseComponent* pComponent);

	//------PUBLIC VARIABLES------
protected:
	//------PROTECTED FUNCTIONS------

	//------PROTECTED VARIABLES------
	dae::GameObject* m_pGameObject = nullptr;
private:
	//------PRIVATE FUNCTIONS------

	//------PRIVATE VARIABLES------	
};