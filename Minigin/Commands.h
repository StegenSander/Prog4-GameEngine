#pragma once
#include <iostream>
class Command
{
public:
	//------CONSTRUCTOR/DESTRUCTOR------
	Command() = default;
	virtual ~Command() = default;

	virtual void Execute() = 0;
};

class CommandFire final: public Command
{
public:
	CommandFire() : Command() {}
	~CommandFire() = default;

	void Execute() override
	{
		std::cout << "Fire\n";
	}
};

class CommandDuck final : public Command
{
public:
	CommandDuck() : Command() {}
	~CommandDuck() = default;

	void Execute() override
	{
		std::cout << "Duck\n";
	}
};

class CommandJump final : public Command
{
public:
	CommandJump() : Command() {}
	~CommandJump() = default;

	void Execute() override
	{
		std::cout << "Jump\n";
	}
};

class CommandFart final : public Command
{
public:
	CommandFart() : Command() {}
	~CommandFart() = default;

	void Execute() override
	{
		std::cout << "Fart\n";
	}
};

