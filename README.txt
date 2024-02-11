Cat & Mouse

Written by: Wajdi Aweida ID: 300571650, Razi Shibli: 324259555

--------------------
General information:
--------------------
In this game the cats try to catch the mouse to prevent him from
collecting cheese piecies.

The game consists of 5 levels going from easy to hard levels.

The levels can be modified by editing Playlist.txt file and adding/
editing levels.(Do not forget to make required change in CMake file)
Note that levels 4,5 can hardly be passed without losing a life so play wisley.

The palyer has 3 lives in the game. 

Pay attention: the game is HIGHLY addictive.

------
Files:
------
Cat.h
Cat header file

Cat.cpp
Implementation of Cat class

Mouse.h
Mouse header file

Mouse.cpp
Implementation of Mouse class

Board.h
Board header file

Board.cpp
Implementation of Board class

Controller.h
Controller header file

Controller.cpp
Implementation of Controller class

main.cpp
Runs the game by calling Controller run() function

Playlist.txt
Contains list of the files representing levels
(can be modified)

Files represnting the 5 levels(can be modified)
Level1.txt
Level2.txt
Level3.txt
Level4.txt
Level5.txt

----------------
Data structures:
----------------
string: used to represent the rows of a text file
to manage the objects in the game.

vector: used to make vector of files represnting the levels,
and vector representing the cats in the game
also used a vector of pairs made to calculate and prioritize the 
decision of moving the cats

pair: used to make a vector of pairs represent the direction and
the distance betewen the cat and the mouse.

2D array of chars: representing the game board.

-----------
Algorithms:
-----------
The chaseMouse function in the Cat class calculates the cat's movement
towards a mouse, employing a method inspired by Dijkstra's algorithm.
This approach focuses on evaluating and comparing distances as costs.
The function initiates by retrieving the cat's current location.
Subsequently, it constructs a vector of pairs named mini_dist.
Each pair in this vector comprises the distance to the mouse from a
potential next position (left, right, down, up) and an associated
direction index (0 for left, 1 for right, 2 for down, 3 for up).

Crucially, after determining these distance-cost pairs, the function
sorts the mini_dist vector in ascending order based on these
distances, effectively organizing the movements from the least to
the most costly. This sorted list thus prioritizes moves that are
closer to the mouse, aligning with the strategy of minimizing
distance in the pursuit, akin to the principles of Dijkstra's
algorithm.

-----------
Design:
-----------
The design of the game relies on a central principle: the primary
object, denoted as the "Controller," assumes control over all game
behavior and other objects. To facilitate this control, a dedicated object
named the "Board" is introduced to manage both game data and other objects
present on the game board.

While the static objects within the game are represented as chars,
their utility extends beyond mere visual elements. They play a pivotal
role in various operations, influencing the behavior of these objects
when consumed or when other entities interact with them.

The cornerstone of the game comprises two principal characters: the Mouse
and the Cat. These objects are central to the gameplay, each contributing
distinct dynamics to the overall experience. The interplay of these
characters, coupled with the orchestrated management of the game board and
its objects by the Controller, forms the core architecture of the game,
fostering an engaging and interactive gaming environment.


-----------
Known bugs:
-----------
Fortunately, known bugs are solved. Devil are the unknown.
 
------------
Other notes:
------------
