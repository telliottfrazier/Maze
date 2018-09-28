#pragma once
//Author: Elliott Frazier
//Date: 1/15/2018
const int ROWS = 19;
const int COLS = 29;

struct coordinates
{
	int row;
	int col;
};

class maze
{
public:
	maze();
	~maze();
	void printMaze();
	bool playMaze();
private:
	int getKey();
	char grid[ROWS][COLS];
	void fillMaze();
	void getStartingPoint();
	void getDestinationPoint();
	void digPath(coordinates);
	bool checkPath(coordinates);
	coordinates currentLocation;
	coordinates endLocation;
	coordinates startLocation;
};


