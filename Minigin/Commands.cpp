#include "MiniginPCH.h"
#include "Commands.h"

Command::~Command()
{
	//std::cout << "Command Destructor\n";
}

void Command::Execute()
{
	m_Function();
}
