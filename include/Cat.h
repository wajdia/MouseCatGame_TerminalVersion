#pragma once

#include <Location.h>
#include <vector>
#include <algorithm>
#include <iostream>

class Cat {
public:
	Cat();
	Cat(Location);

	void resetLocation();
	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();
	Location getLocation() const;
	Location getInitLocation() const;
	char getItemSteppedOn() const;
	void setItemSteppedOn(char item);

	std::vector<std::pair<int, int>> 
		chaseMouse(const Location& mouseLocation)const;

private:
	char m_itemSteppedOn;
	Location m_location;
	Location m_initLocation;
	double distance(const Location&, const Location&) const;
};