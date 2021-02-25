#include "MiniginPCH.h"
#include "ListenerComponent.h"

ListenerComponent::ListenerComponent()
{
	Observer::GetInstance().AddListener(this);
}

ListenerComponent::~ListenerComponent()
{
	Observer::GetInstance().RemoveListener(this);
}
