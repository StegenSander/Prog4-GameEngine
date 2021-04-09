#pragma once
#include "BaseComponent.h"
#include "Subject.h"
class SubjectComponent final
	: public BaseComponent
	, public Subject
{
public:
	SubjectComponent() = default;
	~SubjectComponent() = default;
};

