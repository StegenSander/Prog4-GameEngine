#include "MiniginPCH.h"
#include "Commands.h"
#include "GameObject.h"
#include "BaseComponent.h"
#include "HealthComponent.h"

Command::~Command()
{
	std::cout << "Command Destructor\n";
}

void Command::Execute()
{
	m_Function();
}
