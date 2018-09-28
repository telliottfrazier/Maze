//Author: Elliott Frazier
//Date: 1/15/2018

#include<stack>
#include<iostream>
#include<cstdlib>
#include<ctime>
#include<windows.h>
#include "maze.h"

using std::cout;
using std::endl;
using std::stack;

const char WALL = (char)219;
const char PATH = ' ';
const char START = 'S';
const char DESTINATION = 'E';
const char PLAYER = 'P';
const int DEFAULT_COLOR = 7;
const int PLAYER_COLOR = 14;
const int START_COLOR = 160;
const int DESTINATION_COLOR = 207;

stack<coordinates> locations;

maze::maze()
{	
	fillMaze();
	getStartingPoint();
	locations.push(currentLocation);

	while (!locations.empty())
	{
		digPath(locations.top());
		locations.pop();
	}
	getDestinationPoint();
}

maze::~maze()
{}

bool maze::playMaze()
{
	printMaze();
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	int row = startLocation.row;
	int column = startLocation.col;
	int key = getKey();
	COORD newCoord = { column, row };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), newCoord);
	while (key != VK_ESCAPE) {

		//Key Left
		if (key == VK_LEFT && grid[row][column-1] != WALL) {
			column--;
			COORD newCoord = { column, row };
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), newCoord);
			if (newCoord.Y == endLocation.row && newCoord.X == endLocation.col)
			{
				return true;
			}
			//Set Player Color
			SetConsoleTextAttribute(hConsole, PLAYER_COLOR);
			cout << PLAYER;

			newCoord.X += 1;
			if (newCoord.Y != startLocation.row || newCoord.X != startLocation.col) 
			{
				SetConsoleTextAttribute(hConsole, DEFAULT_COLOR);
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), newCoord);
				cout << PATH;
			}
		}

		//Key Right
		else if (key == VK_RIGHT && grid[row][column+1] != WALL) {
			column++;
			COORD newCoord = { column, row };
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), newCoord);
			if (newCoord.Y == endLocation.row && newCoord.X == endLocation.col)
			{
				return true;
			}
			//Set Player Color
			SetConsoleTextAttribute(hConsole, PLAYER_COLOR);
			cout << PLAYER;

			newCoord.X -= 1;
			if (newCoord.Y != startLocation.row || newCoord.X != startLocation.col) 
			{
				SetConsoleTextAttribute(hConsole, DEFAULT_COLOR);
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), newCoord);
				cout << PATH;
			}
		}

		//Key Up
		else if (key == VK_UP && grid[row-1][column] != WALL) {
			row--;
			COORD newCoord = { column, row };
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), newCoord);
			if (newCoord.Y == endLocation.row && newCoord.X == endLocation.col)
			{
				return true;
			}
			//Set Player Color
			SetConsoleTextAttribute(hConsole, PLAYER_COLOR);
			cout << PLAYER;

			newCoord.Y += 1;
			if (newCoord.Y != startLocation.row || newCoord.X != startLocation.col) 
			{
				SetConsoleTextAttribute(hConsole, DEFAULT_COLOR);
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), newCoord);
				cout << PATH;
			}
		}

		//Key Down
		else if (key == VK_DOWN && grid[row+1][column] != WALL) {
			row++;
			COORD newCoord = { column, row };
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), newCoord);
			if (newCoord.Y == endLocation.row && newCoord.X == endLocation.col)
			{
				return true;
			}
			//Set Player Color
			SetConsoleTextAttribute(hConsole, PLAYER_COLOR);
			cout << PLAYER;
			newCoord.Y -= 1;
			if (newCoord.Y != startLocation.row || newCoord.X != startLocation.col) 
			{
				SetConsoleTextAttribute(hConsole, DEFAULT_COLOR);
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), newCoord);
				cout << PATH;
			}
		}
		key = getKey();
	}	return false;
}

void maze::digPath(coordinates diglocation)
{
	//check for possible moves
	bool moveExists = false;

	//Check North
	coordinates north = diglocation;
	north.row -= 2;
	//moveExists = checkPath(north); <- condense code to this
	if (checkPath(north))
	{
		moveExists = true;
	}

	//Check South
	coordinates south = diglocation;
	south.row += 2;
	if (checkPath(south))
	{
		moveExists = true;
	}

	//Check East
	coordinates east = diglocation;
	east.col += 2;
	if (checkPath(east))
	{
		moveExists = true;
	}

	//Check West
	coordinates west = diglocation;
	west.col -= 2;
	if (checkPath(west))
	{
		moveExists = true;
	}

	//Dig path if move exists
	if (moveExists) {
		//random number is assigned to 'digID' and then matches it's number with condition statement for direction to dig if possible
		int digID;
		bool moved = false;
		while (!moved)
		{
			digID = 1 + rand() % 4;

			//Dig North
			if (digID == 1 && checkPath(north))
			{
				locations.push(north);
				grid[north.row][north.col] = PATH;
				grid[north.row + 1][north.col] = PATH;
				moved = true;
			}
			//Dig South
			else if (digID == 2 && checkPath(south))
			{
				locations.push(south);
				grid[south.row][south.col] = PATH;
				grid[south.row - 1][south.col] = PATH;
				moved = true;
			}
			//Dig East
			else if (digID == 3 && checkPath(east))
			{
				locations.push(east);
				grid[east.row][east.col] = PATH;
				grid[east.row][east.col - 1] = PATH;
				moved = true;
			}
			//Dig West
			else if (digID == 4 && checkPath(west))
			{
				locations.push(west);
				grid[west.row][west.col] = PATH;
				grid[west.row][west.col + 1] = PATH;
				moved = true;
			}

		}
		digPath(locations.top());
	}
}

void maze::printMaze()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	for (int currentRow = 0; currentRow < ROWS; currentRow++)
	{
		for (int currentColumn = 0; currentColumn < COLS; currentColumn++)
		{
			//colors the start and destination points
			if (currentRow == startLocation.row && currentColumn == startLocation.col)
			{
				SetConsoleTextAttribute(hConsole, START_COLOR);
				cout << grid[currentRow][currentColumn];
				SetConsoleTextAttribute(hConsole, DEFAULT_COLOR);
			}
			else if (currentRow == endLocation.row && currentColumn == endLocation.col)
			{
				SetConsoleTextAttribute(hConsole, DESTINATION_COLOR);
				cout << grid[currentRow][currentColumn];
				SetConsoleTextAttribute(hConsole, DEFAULT_COLOR);
			}
			else
			{
				cout << grid[currentRow][currentColumn];
			}
		}
		cout << endl;
	}
}

void maze::fillMaze()
{
	//fill maze with walls
	for (int curRow = 0; curRow < ROWS; curRow++)
	{
		for (int curCol = 0; curCol < COLS; curCol++)
		{
			grid[curRow][curCol] = WALL;
		}
	}
}

bool maze::checkPath(coordinates testDig)
{
	bool result = true;
	//prevents overwriting walls and start points
	if (grid[testDig.row][testDig.col] == PATH || grid[testDig.row][testDig.col] == START)
	{
		result = false;
	}
	//keeps path in bounds
	else if (testDig.row <= 0 || testDig.col <= 0)
	{
		result = false;
	}
	else if (testDig.row >= ROWS - 1 || testDig.col >= COLS - 1)
	{
		result = false;
	}

	return result;
}

void maze::getStartingPoint()
{
	//generate row location
	srand(static_cast<unsigned int>(time(0)));
	currentLocation.row = (1 + rand() % (ROWS - 2));
	while (currentLocation.row % 2 == 0)
	{
		currentLocation.row = (1 + rand() % (ROWS - 2));
	}
	//generate column location
	currentLocation.col = (1 + rand() % (COLS - 2));
	while (currentLocation.col % 2 == 0)
	{
		currentLocation.col = (1 + rand() % (COLS - 2));
	}
	
	//Marks the start of maze
	grid[currentLocation.row][currentLocation.col] = START;
	startLocation = currentLocation;
}

void maze::getDestinationPoint()
{
	srand(static_cast<unsigned int>(time(0)));
	do {
		//generate column location
		endLocation.row = (1 + rand() % (ROWS - 2));
		while (endLocation.row % 2 == 0)
		{
			endLocation.row = (1 + rand() % (ROWS - 2));
		}
		//generate column location
		endLocation.col = (1 + rand() % (COLS - 2));
		while (endLocation.col % 2 == 0)
		{
			endLocation.col = (1 + rand() % (COLS - 2));
		}
	} while (grid[endLocation.row][endLocation.col] != PATH);
	//prints destination
	grid[endLocation.row][endLocation.col] = DESTINATION;

}

int maze::getKey() {
	int result = 0;
	while (result == 0)
	{
		short MAX_SHORT = 0x7FFF; //111111111111111
		if (GetAsyncKeyState(VK_LEFT) & MAX_SHORT) {
			result = VK_LEFT;
		}
		else if (GetAsyncKeyState(VK_UP) & MAX_SHORT) {
			result = VK_UP;
		}
		else if (GetAsyncKeyState(VK_RIGHT) & MAX_SHORT) {
			result = VK_RIGHT;
		}
		else if (GetAsyncKeyState(VK_DOWN) & MAX_SHORT) {
			result = VK_DOWN;
		}
		else if (GetAsyncKeyState(VK_ESCAPE) & MAX_SHORT) {
			result = VK_ESCAPE;
		}
	}
	return result;

}