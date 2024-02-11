#pragma once

#include <fstream>
#include <string>
#include <vector>
#include <iostream>

#include "Board.h"
#include "Mouse.h"
#include "Cat.h"

using std::vector;
using std::string;
using std::ifstream;
using std::cout;

const char CAT = '^';
const char WALL = '#';
const char MOUSE = '%';
const char EMPTY = ' ';
const char CHEESE = '*';
const char GIFT = '$';
const char DOOR = 'D';
const char KEY = 'F';
const char BLOCKED = 'N';

enum direction_t {D_UP,D_DOWN,D_LEFT,D_RIGHT};

class Board {
public:

	Board(ifstream& file);
	
	
	Location getMouseLocation() const;

	vector<string> getBoard() const;
	char getUpperItem(Location current) const;
	char getBeneathItem(Location current) const;
	char getLeftItem(Location current) const;
	char getRightItem(Location current) const;

	void updateCatInBoard(direction_t direction,Cat&,int,char);
	
	void updateMouseInBoard(direction_t direction);
	void printBoard() const;
	int countCheesePieces() const;
	void grantKeyToMouse();

	vector<Cat> getAllCats() const;
	void resetMouse();
	void resetCats();
	void resetBoard();
	void removeCat();
	void putBackFromCat();

private:

	vector<string> m_board;
	int m_colSize;
	int m_rowSize;
	Mouse m_mouse;
	vector<Cat> m_cats; 
	
	void processLevel(ifstream& file);
	Location getInitialMouseLocation() const;
	vector<Location> getInitialCatsLocations() const;
		
};