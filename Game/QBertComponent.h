#pragma once
#include <BaseComponent.h>

class LevelNavigatorComponent;
class QBertComponent:
	public BaseComponent 
{
public:
	//------CONSTRUCTOR/DESTRUCTOR------
	QBertComponent();
	virtual ~QBertComponent();

	//------COPY CONSTRUCTORS------
	QBertComponent(const QBertComponent&) = delete;
	QBertComponent(QBertComponent&&) = delete;
	//------ASSIGNMENT OPERATORS------
	QBertComponent operator=(const QBertComponent&) = delete;
	QBertComponent& operator=(QBertComponent&&) = delete;

	//------PUBLIC FUNCTIONS------

	//------PUBLIC VARIABLES------
protected:
	//------PROTECTED FUNCTIONS------

	//------PROTECTED VARIABLES------	
private:
	//------PRIVATE FUNCTIONS------

	//------PRIVATE VARIABLES------	
};

