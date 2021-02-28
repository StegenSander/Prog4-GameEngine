#pragma once
#include "GameObject.h"

class BaseComponent
{
public:
	//------CONSTRUCTOR/DESTRUCTOR------
	BaseComponent()= default;
	virtual ~BaseComponent()
	{
		std::cout << "Component deleted\n";
	}
	;
	
	//------PUBLIC FUNCTIONS------
	virtual void Update() = 0;
	virtual void Render() {};
	dae::GameObject* GetGameObject() const { return m_pGameObject; };

	bool IsMarkedForDelete() const { return m_IsMarkedForDelete; };
	void Delete() { m_IsMarkedForDelete = true; };


	friend void dae::GameObject::AddComponent(const std::shared_ptr<BaseComponent>& pComponent);

	//------PUBLIC VARIABLES------
protected:
	//------PROTECTED FUNCTIONS------

	//------PROTECTED VARIABLES------
	dae::GameObject* m_pGameObject{};
	bool m_IsMarkedForDelete = false;
private:
	//------PRIVATE FUNCTIONS------

	//------PRIVATE VARIABLES------	
};
