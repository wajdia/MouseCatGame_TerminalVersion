#include "Board.h"

Board::Board(ifstream& level)
{
	processLevel(level);
	m_mouse = Mouse(getInitialMouseLocation());
	vector<Location> catLocations = getInitialCatsLocations();
	for (int i = 0; i < catLocations.size(); i++)
	{
		m_cats.push_back(Cat(catLocations[i]));
	}
}
Location Board::getMouseLocation() const
{
	return m_mouse.getLocation();
}

//======================================
// find the mouse in the board
// return its location probably for first run
Location Board::getInitialMouseLocation() const
{
	for (int i = 0; i < m_rowSize; i++)
	{
		for (int j = 0; j < m_colSize; j++)
		{
			if (m_board[i][j] == MOUSE)
			{
				return Location(i, j);
			}
		}
	}
	return Location();
}

//=====================================
// find the cat in the board
// return its location
vector<Location> Board::getInitialCatsLocations() const
{
	vector<Location> catLocations;

	for (int i = 0; i < m_rowSize; i++)
	{
		for (int j = 0; j < m_colSize; j++)
		{
			if (m_board[i][j] == CAT)
			{
				catLocations.push_back(Location(i, j));
			}
		}
	}
	return catLocations;
}

//======================================
// returns the board as vector of strings 
vector<string> Board::getBoard() const
{
	return m_board;
}

//======================================
// returns the the upper item related to the current
char Board::getUpperItem(Location current) const
{
	if (current.row <= 0)
	{
		return BLOCKED;
	}
	else
	{
		return m_board[current.row-1][current.col];
	}
}

//======================================
// returns the the beneath item related to the current
char Board::getBeneathItem(Location current) const
{
	if (current.row >= m_rowSize - 1)
	{
		return BLOCKED;
	}
	
	else
	{
		return m_board[current.row+1][current.col];
	}
}

//======================================
// returns the the left item related to the current
char Board::getLeftItem(Location current) const
{
	if (current.col <= 0)
	{
		return BLOCKED;
	}
	else
	{
		return m_board[current.row][current.col-1];
	}
}

//======================================
// returns the the right item related to the current
char Board::getRightItem(Location current) const
{
	if (current.col >= m_colSize - 1)
	{
		return BLOCKED;
	}
	else
	{
		return m_board[current.row][current.col+1];
	}
}

//======================================
// getting the level file and represent it into the 
// vector of strings
void Board::processLevel(ifstream& level)
{
	level >> m_rowSize >> m_colSize;
	
	for (auto line = string(); getline(level, line);)
	{
		if (line.size() != 0)
		{
			m_board.push_back(line);
		}
		
	}
}

//======================================
// gets direction to move then:
// checks if the move is legal - update the board and moves the mouse object
// else do nothing and returns flase
void Board::updateMouseInBoard(direction_t direction)
{
	Location currentLocation = getMouseLocation();
	switch (direction)
	{
	case D_UP:
		
		m_board[currentLocation.row][currentLocation.col] = EMPTY;
		m_board[currentLocation.row - 1][currentLocation.col] = MOUSE;
		m_mouse.moveUp();
			
		break;

	case D_DOWN:	
		m_board[currentLocation.row][currentLocation.col] = EMPTY;
		m_board[currentLocation.row + 1][currentLocation.col] = MOUSE;
		m_mouse.moveDown();

		break;

	case D_LEFT:
		m_board[currentLocation.row][currentLocation.col] = EMPTY;
		m_board[currentLocation.row][currentLocation.col - 1] = MOUSE;
		m_mouse.moveLeft();

		break;
				
	case D_RIGHT:
		m_board[currentLocation.row][currentLocation.col] = EMPTY;
		m_board[currentLocation.row][currentLocation.col + 1] = MOUSE;
		m_mouse.moveRight();

		break;

	default:
		break;

	}
}

//======================================
//print board   
void Board::printBoard() const
{
	int i = 0;
	while (i<m_rowSize && !m_board[i].empty())
	{
		cout << m_board[i] << "\n";
		i++;
	}
}

//======================================
// count cheese pieces
int Board::countCheesePieces() const
{
	int counter = 0;
	for (int i = 0; i < m_rowSize; i++)
	{
		for (int j = 0; j < m_colSize; j++)
		{
			if (m_board[i][j] == CHEESE)
			{
				counter++;
			}
		}
	}
	return counter;
}

//======================================
// grant key to the mouse
void Board::grantKeyToMouse()
{
	m_mouse.grantKey();
}

//========================================
vector<Cat> Board::getAllCats() const
{
	return m_cats;
}

//========================================
//update cat in board, taking care that cats can step on items
void Board::updateCatInBoard(direction_t direction,Cat& catToMove,int index,char nextItem)
{
	char previousItem = catToMove.getItemSteppedOn();
	Location currentLocation = catToMove.getLocation();
	switch (direction)
	{
	case D_UP:

		m_board[currentLocation.row][currentLocation.col] = previousItem;
		m_board[currentLocation.row - 1][currentLocation.col] = CAT;
		catToMove.moveUp();
		m_cats[index].moveUp();
		m_cats[index].setItemSteppedOn(nextItem);

		break;

	case D_DOWN:
		m_board[currentLocation.row][currentLocation.col] = previousItem;
		m_board[currentLocation.row + 1][currentLocation.col] = CAT;
		catToMove.moveDown();
		m_cats[index].moveDown();
		m_cats[index].setItemSteppedOn(nextItem);
		break;

	case D_LEFT:
		m_board[currentLocation.row][currentLocation.col] = previousItem;
		m_board[currentLocation.row][currentLocation.col - 1] = CAT;
		catToMove.moveLeft();
		m_cats[index].moveLeft();
		m_cats[index].setItemSteppedOn(nextItem);

		break;

	case D_RIGHT:
		m_board[currentLocation.row][currentLocation.col] = previousItem;
		m_board[currentLocation.row][currentLocation.col + 1] = CAT;
		catToMove.moveRight();
		m_cats[index].moveRight();
		m_cats[index].setItemSteppedOn(nextItem);

		break;

	default:
		break;

	}
}
//======================================
void Board::resetMouse()
{
	m_mouse.resetLocation();
}
//======================================
void Board::resetCats()
{
	for (int i = 0; i < m_cats.size(); i++)
	{
		m_board[m_cats[i].getLocation().row][m_cats[i].getLocation().col] =
			m_cats[i].getItemSteppedOn();
		m_cats[i].resetLocation();
		m_cats[i].setItemSteppedOn(' ');
	}
}//======================================
void Board::resetBoard()
{
	for (int i = 0; i < m_rowSize; i++)
	{
		for (int j = 0; j < m_colSize; j++)
		{
			if (m_board[i][j] == CAT || m_board[i][j] == MOUSE )
			{
				m_board[i][j] = ' ';
			}
			
		}
	}
	m_board[m_mouse.getLocation().row][m_mouse.getLocation().col] = MOUSE;

	for (int i = 0; i < m_cats.size(); i++)
	{
		m_board[m_cats[i].getLocation().row][m_cats[i].getLocation().col] = CAT;
	}
}
//======================================
void Board::removeCat()
{
	m_board[m_cats[m_cats.size()-1].getLocation().row]
		[m_cats[m_cats.size() - 1].getLocation().col] = 
		m_cats[m_cats.size() - 1].getItemSteppedOn();
	m_cats.pop_back();
}
//======================================
// get back the item the cat stepped on
void Board::putBackFromCat()
{
	m_board[m_cats[m_cats.size() - 1].getLocation().row]
		[m_cats[m_cats.size() - 1].getLocation().col] = m_cats[m_cats.size() - 1].getItemSteppedOn();
		
}