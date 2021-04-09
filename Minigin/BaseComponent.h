#pragma once

#include "GameObject.h"
#include "Destroyable.h"

class BaseComponent
	: public Destroyable
{
public:
	//------CONSTRUCTOR/DESTRUCTOR------
	BaseComponent()= default;
	virtual ~BaseComponent();
	
	//------PUBLIC FUNCTIONS------
	virtual void Update() = 0;
	virtual void Render() {};
	dae::GameObject* GetGameObject() const { return m_pGameObject; };


	friend void dae::GameObject::AddComponent(const std::shared_ptr<BaseComponent>& pComponent);

	//------PUBLIC VARIABLES------
protected:
	//------PROTECTED FUNCTIONS------

	//------PROTECTED VARIABLES------
	dae::GameObject* m_pGameObject{};
private:
	//------PRIVATE FUNCTIONS------

	//------PRIVATE VARIABLES------	
};
