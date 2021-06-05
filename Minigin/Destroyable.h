#pragma once
class Destroyable
{
public:
	//------CONSTRUCTOR/DESTRUCTOR------
	Destroyable();
	virtual ~Destroyable() = default;

	//------COPY CONSTRUCTORS------
	Destroyable(const Destroyable&) = default;
	Destroyable(Destroyable&&) = default;
	//------ASSIGNMENT OPERATORS------
	Destroyable& operator=(const Destroyable&) = default;
	Destroyable& operator=(Destroyable&&) = default;

	//------PUBLIC FUNCTIONS------
	void MarkForDelete() { m_IsMarkedForDelete = true; };
	[[nodiscard]] bool IsMarkedForDelete() const { return m_IsMarkedForDelete; };

protected:
	//------PROTECTED VARIABLES------
	bool m_IsMarkedForDelete;

};

