#include "MiniginPCH.h"
#include "PlayerListenerComponent.h"

PlayerListenerComponent::PlayerListenerComponent()
	:ListenerComponent()
{
}

void PlayerListenerComponent::Notify(EventType type, EventData* eventData)
{
	if (eventData->Sender == m_pGameObject)
	{
		if (type == EventType::PlayerDamage)
		{
			PlayerDamageData* damageData = static_cast<PlayerDamageData*>(eventData);
			std::cout << "Remaining lives: " << damageData->RemainingHealth << std::endl;
		}

		if (type == EventType::PlayerDied)
		{
			std::cout << "PlayerDied\n";
		}
	}
}
