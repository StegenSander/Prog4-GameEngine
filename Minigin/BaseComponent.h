#pragma once
namespace dae
{
	class GameObject;
}
class BaseComponent
{
public:
	//------CONSTRUCTOR/DESTRUCTOR------
	BaseComponent(dae::GameObject* pGameObject);
	virtual ~BaseComponent() = default;
	
	//------PUBLIC FUNCTIONS------
	virtual void Update() = 0;
	dae::GameObject* GetGameObject() const { return  m_pGameObject; };
	void PushComponentToGameObject();

	//------PUBLIC VARIABLES------
protected:
	//------PROTECTED FUNCTIONS------

	//------PROTECTED VARIABLES------
	dae::GameObject* m_pGameObject = nullptr;
private:
	//------PRIVATE FUNCTIONS------

	//------PRIVATE VARIABLES------	
};
