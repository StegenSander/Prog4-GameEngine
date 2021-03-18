#pragma once
#include <iostream>
#include <functional>

class BaseComponent;

class Command
{
public:
	//------CONSTRUCTOR/DESTRUCTOR------
	Command(std::function<void()> function,void* identifier)
		: m_Function{ function }
		, m_Identifier{ identifier }
	{}

	virtual ~Command() = default;

	virtual void Execute();
	virtual void* GetTarget() { return m_Identifier; };

	void Delete() { m_IsMarkedForDelete = true; };
	bool IsMarkedForDelete() { return m_IsMarkedForDelete; };

private:
	std::function<void()> m_Function;
	void* m_Identifier;
	bool m_IsMarkedForDelete{ false };
};


/*Disabling a warning
* Warning is visual studio not understanding what's happend
* 'unreferenced local function has been removed'
* precompiler things this function will never be called
* but is wrong since we're working with function pointer
*/
#pragma warning(push)
#pragma warning (disable:4505)
namespace Commands {

	static void Spawn()
	{
		std::cout << "Spawn\n";
	}


}
#pragma warning(pop)
