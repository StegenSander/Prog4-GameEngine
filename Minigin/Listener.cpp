#include "MiniginPCH.h"
#include "Listener.h"
#include "Subject.h"

Listener::Listener(const std::weak_ptr<Subject>& subject)
	:m_Subject {subject}
{
	m_Subject.lock()->AddListener(this);
}

Listener::~Listener()
{
	if (!m_Subject.expired())
	{
		m_Subject.lock()->RemoveListener(this);
	}
}

