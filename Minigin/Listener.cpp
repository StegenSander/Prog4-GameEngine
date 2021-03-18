#include "MiniginPCH.h"
#include "Listener.h"
#include "StaticObserver.h"

Listener::Listener()
{
	StaticObserver::GetInstance().AddListener(this);
}

Listener::~Listener()
{
	StaticObserver::GetInstance().RemoveListener(this);
}

