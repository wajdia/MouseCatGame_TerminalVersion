#include "Cat.h"

// Ctors
Cat::Cat()
{
	m_location = m_initLocation = Location();
	m_itemSteppedOn = ' ';
}
//======================================
Cat::Cat(Location loc)
{
	m_initLocation = m_location = loc;
	m_itemSteppedOn = ' ';
}
//======================================
void Cat::resetLocation()
{
	m_location = m_initLocation;
}
//======================================
void Cat::moveLeft()
{
	m_location.col--;
}
//======================================
void Cat::moveRight()
{
	m_location.col++;
}
//======================================
void Cat::moveUp()
{
	m_location.row--;
}
//======================================
void Cat::moveDown()
{
	m_location.row++;

}
//======================================
Location Cat::getLocation() const
{
	return m_location;
}
//======================================
Location Cat::getInitLocation() const
{
	return m_initLocation;
}
//======================================
char Cat::getItemSteppedOn() const
{
	return m_itemSteppedOn;
}
//======================================
void Cat::setItemSteppedOn(char item)
{
	if (item != '^')
	{
		m_itemSteppedOn = item;
	}
}

//======================================
// chase the mouse inspired by Dijkstra algorithm
//returns a vector of pairs to take move decision in controller
std::vector<std::pair<int,int>> 
	Cat::chaseMouse(const Location& mouseLocation) const
{
	Location currentLocation = getLocation();
	
	std::vector<std::pair<int, int>> mini_dist = {
	 { distance (mouseLocation, 
		 {getLocation().row, getLocation().col-1}) , 0} // left
	 
		 ,{distance(mouseLocation, 
		 { getLocation().row, getLocation().col+1}) , 1} // right
	 
		,{distance(mouseLocation, 
		 { getLocation().row+1 ,getLocation().col}) , 2} // Down
	 
		,{distance(mouseLocation, 
		 { getLocation().row-1 ,getLocation().col}) , 3} }; // Up

	int size = mini_dist.size();
	
	std::sort(mini_dist.begin(),
		mini_dist.end(), std::less<std::pair<int, int>>());

	return mini_dist;
}
//======================================
// enable the smart cat to calculate distance between two locs
double Cat::distance(const Location& v1, const Location& v2) const
{
	return std::hypot(v1.col - v2.col, v1.row - v2.row);
}