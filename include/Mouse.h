#pragma once

#include <Location.h>

class Mouse {
public:
	Mouse();
	Mouse(Location);
	
	void resetLocation();
	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();
	Location getLocation() const;
	Location getInitLocation() const;
	bool hasKey() const;
	void grantKey();

private:
	bool m_hasKey;
	Location m_location;
	Location m_initLocation;

};