#pragma once
#include <iostream>
#include <functional>

class Command
{
public:
	//------CONSTRUCTOR/DESTRUCTOR------
	Command(std::function<void()> function)
		: m_Function{ function } {}

	virtual ~Command() = default;

	virtual void Execute()
	{
		m_Function();
	}

private:
	std::function<void()> m_Function;
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
