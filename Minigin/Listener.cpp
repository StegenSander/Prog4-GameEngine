#include "MiniginPCH.h"
#include "Listener.h"
#include "StaticObserver.h"
#include "Subject.h"

Listener::Listener(Subject* subject)
	:m_Subject {subject}
{
	m_Subject->AddListener(this);
}

Listener::~Listener()
{
	m_Subject->RemoveListener(this);
}

