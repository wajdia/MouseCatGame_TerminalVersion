#include "Controller.h"
#include <cstdlib>

using std::vector;
using std::string;
using std::ifstream;
using std::cout;

// Ctor
Controller::Controller() 
{
	m_levels = 1;
    m_currLevel = 1;
    m_score = 0;
    m_cheeseEaten = 0;
    m_lives = DEF_LIVES;
    m_totalCheese = 0;
    m_keysObtained = 0;
    m_gifts = 0;
    m_playlist = "Playlist.txt";
}

//======================================
// main function to run the game
void Controller::run()
{

    vector<ifstream> allLevels = openPlaylistFiles(m_playlist);
    
    int i = 0;
    bool levelFinished = true;      //supposing level 0 is finished
    
    // loop for moving from one level to other
    while(m_lives >0 && levelFinished && i<allLevels.size())
    {
        Board gameBoard = Board(allLevels[i]);
        m_totalCheese = gameBoard.countCheesePieces();
        int firstRun = 1;
        levelFinished = false;
        
        vector<Cat> cats = gameBoard.getAllCats();

        //loop for getting the input
	    do
	    {
            if (firstRun==1)
            {
                system("cls");
                printCurrentBoard(gameBoard);
                firstRun = -1;
            }

            const auto c = _getch();

            switch (c)
            {
            case 0:
            case Keys::SPECIAL_KEY:
                handleSpecialKey(gameBoard);
                break;
            default:
                break;
            }

            if (m_keysObtained > 0)
            {
                gameBoard.grantKeyToMouse();
            }

            if (m_totalCheese == m_cheeseEaten)
            {
                levelFinished = true;
            }

            if (m_gifts > 0 && cats.size()>0)
            {
                gameBoard.putBackFromCat();
                cats.pop_back();
                gameBoard.removeCat();
                
                printCurrentBoard(gameBoard);
                m_gifts--;
            }
            
            //check if the mouse went to a cat
            if (!levelFinished)
            {
                Location mouseLocation = gameBoard.getMouseLocation();
                bool mouseCaught = false;

                // check if cats caught the mouse after his move
                for (int j = 0; j < cats.size(); j++)
                {
                    if (cats[j].getLocation().col == mouseLocation.col &&
                        cats[j].getLocation().row == mouseLocation.row)
                    {
                        mouseCaught = true;
                    }
                }

                if (!mouseCaught)
                {
                    // move the cats if the mouse is free
                    for (int j = 0; j < cats.size(); j++)
                    {
                        moveCat(cats[j].chaseMouse(mouseLocation), gameBoard, cats[j], j);
                    }

                    // check if cats caught the mouse after their move
                    for (int j = 0; j < cats.size(); j++)
                    {
                        if (cats[j].getLocation().col == mouseLocation.col &&
                            cats[j].getLocation().row == mouseLocation.row)
                        {
                            mouseCaught = true;
                        }
                    }
                }

                // reset locations of cats and mouse
                if (mouseCaught)
                {
                    for (int j = 0; j < cats.size(); j++)
                    {
                        cats[j].resetLocation();
                        cats[j].setItemSteppedOn(' ');
                    }
                    gameBoard.resetCats();
                    gameBoard.resetMouse();
                    gameBoard.resetBoard();

                    m_lives--;

                    printCurrentBoard(gameBoard);
                }
            }
		
	    } while (m_lives >0 && !levelFinished);

        // moving from one level to another
        i++;
        m_cheeseEaten = 0;
        m_keysObtained = 0;
        m_currLevel++;
        m_score += 25;
        m_gifts = 0;
        m_score += ALIVE_CATS_FACTOR*cats.size();

    }
}
//=============================
// handle keyboard input
void Controller::handleSpecialKey(Board& gameBoard)
{
    char nextItem;
    bool playerTurnEnded = false;
    while (!playerTurnEnded)
    {
        const auto c = _getch();
        switch (c)
        {
        case SpecialKeys::UP:
            nextItem = gameBoard.getUpperItem(gameBoard.getMouseLocation());
            if (mouseToValidLocation(nextItem))
            {
                gameBoard.updateMouseInBoard(D_UP);
                printUpdatedBoard(nextItem, gameBoard);
                playerTurnEnded = true;
            }
            break;

        case SpecialKeys::DOWN:
            nextItem = gameBoard.getBeneathItem(gameBoard.getMouseLocation());
            if (mouseToValidLocation(nextItem))
            {
                gameBoard.updateMouseInBoard(D_DOWN);
                printUpdatedBoard(nextItem, gameBoard);
                playerTurnEnded = true;
            }
            break;

        case SpecialKeys::LEFT:
            nextItem = gameBoard.getLeftItem(gameBoard.getMouseLocation());
            if (mouseToValidLocation(nextItem))
            {
                gameBoard.updateMouseInBoard(D_LEFT);
                printUpdatedBoard(nextItem, gameBoard);
                playerTurnEnded = true;
            }
            break;

        case SpecialKeys::RIGHT:
            nextItem = gameBoard.getRightItem(gameBoard.getMouseLocation());
            if (mouseToValidLocation(nextItem))
            {
                gameBoard.updateMouseInBoard(D_RIGHT);
                printUpdatedBoard(nextItem, gameBoard);
                playerTurnEnded = true;
            }
            break;

        case SpecialKeys::SPACE:
            playerTurnEnded = true;
            break;
        default:
            break;
        }
    }
}

//======================================
// print the status of the game
void Controller::printGameStatus(Board& b) const
{
    cout << "\n--------------------------------\n" <<
        "Level:" << m_currLevel << "\t| Lives:" << m_lives <<
        "\t| Score:" << m_score <<"\nkeys: " << m_keysObtained <<
        "\t|Eaten: " << m_cheeseEaten << " from " << m_totalCheese <<
        " peices of cheese \n";
}

//======================================
// update game items and score
void Controller::updateItems(char item)
{
    switch (item)
    {
    case CHEESE:
        m_score += 10;
        m_cheeseEaten++;
        break;

    case GIFT:
        m_score += 5;
        m_gifts++;
        break;

    case DOOR:
        m_score += 2;
        m_keysObtained--;
        break;

    case KEY:
        m_keysObtained++;
        break;

    default:
        break;
    }
}
//======================================
// checks is the mouse is going to make a valid move
bool Controller::mouseToValidLocation(char nextItem) const
{
    if (nextItem == WALL || nextItem == BLOCKED)
    {
        return false;
    }
    else
    {
        if (nextItem == DOOR && m_keysObtained==0)
        {
            return false;
        }
        else
        {
            return true;
        }
    }
}

//======================================
// checks if the cat is going to make a valid move
bool Controller::catToValidLocation(char nextItem) const
{
    if (nextItem == WALL || nextItem == BLOCKED || nextItem == DOOR)
    {
        return false;
    }
    else
    {
        return true;
    }

}

//=====================================
// print after mouse move
void Controller::printUpdatedBoard(char nextItem,Board& gameBoard)
{
    updateItems(nextItem);
    gameBoard.printBoard();
    printGameStatus(gameBoard);
    Screen::resetLocation();
}

//======================================
//open playlist file
vector<ifstream> Controller::openPlaylistFiles(const string& filename) 
{
    vector<ifstream> fileVector;
    ifstream file(filename);

    //checkif the file is open successfully
    if (!file.is_open()) 
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        return fileVector;  
    }

    string line;
    while (getline(file, line)) 
    {
        ifstream individualFile(line);
        fileVector.push_back(move(individualFile));
    }

    return fileVector;
}

//======================================
//move each cat depending on Dijkstra algorothim which implemented
// in Cat class
void Controller::moveCat(std::vector<std::pair<int, int>> mini_dest,
    Board& gameBoard, Cat& cat,int index)
{
    char nextItem;
    bool moved = false;
    for (int j = 0; j < DIJKSTRA_OPTIONS; j++)
    {
        switch (mini_dest[j].second)
        {
        case 0:
            nextItem = gameBoard.getLeftItem(cat.getLocation());
            if (catToValidLocation(nextItem))
            {
                moved = true;
                gameBoard.updateCatInBoard(D_LEFT ,cat,index,nextItem);
                cat.setItemSteppedOn(nextItem);                   
                printCurrentBoard(gameBoard);
            }
            break;

        case 1:
            nextItem = gameBoard.getRightItem(cat.getLocation());
            if (catToValidLocation(nextItem))
            {
                moved = true;
                gameBoard.updateCatInBoard(D_RIGHT, cat,index,nextItem);
                cat.setItemSteppedOn(nextItem);
                printCurrentBoard(gameBoard);
            }
            break;

        case 2:
            nextItem = gameBoard.getBeneathItem(cat.getLocation());
            if (catToValidLocation(nextItem))
            {
                moved = true; 
                gameBoard.updateCatInBoard(D_DOWN,cat,index,nextItem);
                cat.setItemSteppedOn(nextItem);
                printCurrentBoard(gameBoard);
            }
            break;

        case 3:
            nextItem = gameBoard.getUpperItem(cat.getLocation());
            if (catToValidLocation(nextItem))
            {
                moved = true;
                gameBoard.updateCatInBoard(D_UP, cat,index,nextItem);
                cat.setItemSteppedOn(nextItem);    
                printCurrentBoard(gameBoard);
            }
            break;

        default:
            break;
        }

        if (moved)
        {
            moved = false;
            break;
        }
    }
}
//=====================================
// print current board
void Controller::printCurrentBoard(Board& gameBoard) const
{
    gameBoard.printBoard();
    printGameStatus(gameBoard);
    Screen::resetLocation();
}
