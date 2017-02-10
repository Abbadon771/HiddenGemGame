
/*
* Author:	Sean Orme
*			UALR
*
* Date:		August 17, 2016
*
* File:		hmwk0.cpp
*
* Purpose:	The purpose of this homework is to review Programming I topics covering
*           standard input/output, types, declaration, selection constructs, loop
*           constructs, and functions using a very simple interactive environment.
*/

#include<string>
#include<iostream>
#include<ctime>
#include <random>

using namespace std;

//Array constants
enum { EMPTY, CURRENT, HISTORY, JEWEL };
const int Nboard = 6;
bool history = true;
int board[Nboard][Nboard];

//GUI Functions
void clearConsole();
void pauseConsole();
void splashScreen();
void displayGameState(int[Nboard][Nboard], string);
void displayGameDone(int[Nboard][Nboard], int, int, string);
char getAction();

//Engine Functions
void initGame(int[Nboard][Nboard], int&, int&, int&, int&);
void changeGameState(char, int[Nboard][Nboard], int&, int&);
bool gameIsNotDone(int, int, int, int);


int main() {

	srand((unsigned)time(0));

	//State variables
	char action;
	int posX, posY, secretX, secretY;

	//Splash Screen
	clearConsole();
	splashScreen();

	posX = 4;
	posY = 4;
	initGame(board, posX, posY, secretX, secretY);

	do {
		//Display Game State
		clearConsole();
		displayGameState(board, "Current Search History");

		//Collect Player Action
		action = getAction();

		//Update Game State
		changeGameState(action, board, posX, posY);

		//Check Game Termination
	} while (gameIsNotDone(posX, posY, secretX, secretY));

	//Display Termination Game State
	displayGameDone(board, secretX, secretY, "YOU FOUND THE HIDDEN JEWEL!");
	pauseConsole();
	return 0;
}

void clearConsole() {
	system("cls");
}

void pauseConsole() {
	system("PAUSE");
}

void splashScreen() {
	cout << "HIDDEN JEWEL!" << endl;
	cout << endl;
	cout << "James Norcross (2015)" << endl;
	cout << "CPSC 2377, Game Programming, Homework 0" << endl;
	cout << "UALR, Computer Science Dept." << endl;
	cout << endl;
	cout << "INSTRUCTIONS:" << endl;
	cout << endl;
	cout << "Find the hidden jewel to win the game!" << endl;
	cout << endl;
	cout << "        (North)          " << endl;
	cout << "           w             " << endl;
	cout << "           |             " << endl;
	cout << "(West) a --+-- d (East)  " << endl;
	cout << "           |             " << endl;
	cout << "           s             " << endl;
	cout << "        (South)          " << endl;
	cout << endl;
	cout << "Select 'h' to toggle history." << endl;
	cout << endl;
	pauseConsole();
}

void displayGameState(int board[Nboard][Nboard], string message) {
	cout << "+------+" << endl;
	for (int i = 0; i < 6; i++)
	{
		cout << "|";
		for (int j = 0; j < 6; j++)
		{
			switch (board[i][j])
			{
			case EMPTY:
				cout << " ";
				break;
			case CURRENT:
				cout << "x";
				break;
			case HISTORY:
				if (history == true)
				{
					cout << "o";
				}
				else
				{
					cout << " ";
				}
				break;
			case JEWEL:
				cout << "J";
				break;
			}

		}
		cout << "|";
		cout << endl;
	}
	cout << "+------+" << endl;
	cout << message << endl;
}

void displayGameDone(int board[Nboard][Nboard], int secretX, int secretY, string message) {
	board[secretY][secretX] = JEWEL;
	switch (board[secretY][secretX])
	{
	case EMPTY:
		cout << " ";
		break;
	case CURRENT:
		cout << "x";
		break;
	case HISTORY:
		if (history == true)
		{
			cout << "o";
		}
		else
		{
			cout << " ";
		}
		break;
	case JEWEL:
		cout << "J";
		break;
	}
	displayGameState(board, message);
}

char getAction() {

	char action;
	cout << "enter directional key (w = up, s = down, a = left, d = right):";
	cin >> action;
	return action;

}

void initGame(int board[Nboard][Nboard], int& posX, int& posY, int& secretX, int& secretY) {

	random_device rdev;
	default_random_engine e(rdev());
	uniform_int_distribution<int> d(0, Nboard - 1);
	secretX = d(e);
	secretY = d(e);
	posX = 5;
	posY = 5;
	if ((secretX == posX) || (secretY == posY))
	{
		while ((secretX != posX) || (secretY != posY))
		{
			secretX = d(e);
			secretY = d(e);
		}
	}
	board[posY][posX] = CURRENT;
	board[secretY][secretX] = 0;
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			if (i != posY && j != posX && i != secretY && j != secretX)
			{
				board[i][j] = EMPTY;
			}
		}
	}

}

void changeGameState(char action, int board[Nboard][Nboard], int& posX, int& posY) {
	if (action == 'w')
	{
		board[posY][posX] = HISTORY;
		posY = posY - 1;
		board[posY][posX] = CURRENT;
	}
	else if (action == 's')
	{
		board[posY][posX] = HISTORY;
		posY = posY + 1;
		board[posY][posX] = CURRENT;
	}
	else if (action == 'a')
	{
		board[posY][posX] = HISTORY;
		posX = posX - 1;
		board[posY][posX] = CURRENT;
	}
	else if (action == 'd')
	{
		board[posY][posX] = HISTORY;
		posX = posX + 1;
		board[posY][posX] = CURRENT;
	}
	else if (action == 'h')
	{
		if (history == true)
		{
			history = false;
		}
		else 
		{
			history = true;
		}
	}
	else
	{
		cout << "Invalid key command" << endl;
	}
	
}


bool gameIsNotDone(int posX, int posY, int secretX, int secretY) {

	if ((posX != secretX) || (posY != secretY))
	{
		return(true);
	}
	else
	{
		return(false); //This is a placehold to make the program compile!
	}
}