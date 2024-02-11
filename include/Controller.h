#pragma once

#include <iostream>
#include <conio.h>

#include"Board.h"
#include "io.h"

const int DEF_LIVES = 3;
const int DIJKSTRA_OPTIONS = 4;		// 4 optin of movement
const int ALIVE_CATS_FACTOR = 5;	//Bonus on alive cats

class Controller {
public:
	Controller();
	void run();

private:
	int m_levels;
	int m_currLevel;
	string m_playlist;
	int m_score;
	int m_lives;
	int m_keysObtained;
	int m_cheeseEaten;
	int m_totalCheese;
	int m_gifts;

	void handleSpecialKey(Board& b);
	void printGameStatus(Board& b) const;
	void updateItems(char item);
	bool mouseToValidLocation(char nextItem) const;
	bool catToValidLocation(char nextItem) const;
	void printUpdatedBoard(char nextItem,Board& board);
	vector<ifstream> openPlaylistFiles(const string& filename);
	
	void moveCat(std::vector<std::pair<int, int>> mini_dest ,
		Board& gameBoard, Cat& cat,int index);
	void printCurrentBoard(Board&) const;
};
