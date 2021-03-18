#include "MiniginPCH.h"
#include "Commands.h"
#include "GameObject.h"
#include "BaseComponent.h"
#include "HealthComponent.h"

void Command::Execute()
{
	m_Function();
}
