#include "Mouse.h"

//Ctors
Mouse::Mouse(Location loc)
{
	m_hasKey = false;
	m_initLocation = m_location = loc;
}

Mouse::Mouse()
{
	m_hasKey = false;
	m_location = m_initLocation = Location();
}

//======================================
void Mouse::resetLocation()
{
	m_location = m_initLocation;
}
//======================================
void Mouse::moveLeft()
{
	m_location.col--;
}
//======================================
void Mouse::moveRight()
{
	m_location.col++;
}
//======================================
void Mouse::moveUp()
{
	m_location.row--;
}
//======================================
void Mouse::moveDown()
{
	m_location.row++;
}
//======================================
Location Mouse::getLocation() const
{
	return m_location;
}
//======================================
// gets initial location
Location Mouse::getInitLocation() const 
{
	return m_initLocation;
}
//======================================
bool Mouse::hasKey() const
{
	return m_hasKey;
}
//======================================
void Mouse::grantKey()
{
	m_hasKey = true;
}
