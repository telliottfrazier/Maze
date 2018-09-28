//Author: Elliott Frazier
//Date: 1/15/2018

#include<iostream>
#include"maze.h"
#include<iostream>
using std::cout;
using std::cin;
using std::endl;

void main() {
	char input;
	
	//Menu
	cout << "Welcome!" << endl << "Navigate to 'E' to win." << endl << "Press the 'Esc' key to give up." << endl << "enter 'C' to continue: ";
	cin >> input;

	if (input == 'C' || input == 'c')
	{
		system("CLS");
		maze AmazeING;
		if (AmazeING.playMaze())
		{
			system("CLS");
			cout << "CONGRATULATIONS, YOU WIN!" << endl;
		}
		else
		{
			system("CLS");
			cout << "Game Over" << endl;
		}
	}
	else
	{
		cout << "Thanks for stopping by!" << endl;
	}

}





