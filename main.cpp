//author:	Shizhe Zeng	1750145
#include <cstdlib>
#include <iostream>
#include <string>
#include "Gomoku.h"

using namespace std;


void printInfo() {
	cout << "===========================================================================\n"
		<< "> Players alternate turns placing a stone of their color on an\n"
		<< "  empty intersection. The winner is the first player to form an  \n"
		<< "  unbroken chain of five stones horizontally, vertically, or diagonally. \n"
		<< "> player input as 'X', computer as 'O' " << endl;
}

int main()
{
	char input = 'A';
	cout << "===========================================================================\n"
		<< "                   Welcome to the Simple Gomoku game!\n"
		<< "===========================================================================\n"
		<< "   Gomoku, also called Five in a Row, is an abstract strategy board game.\n"
		<< "     It is traditionally played with Go pieces (black and white stones)\n"
		<< "        on a Go board, using 15¡Á15 of the 19¡Á19 grid intersections.\n"
		<< "===========================================================================\n";
	while (input != 'Q' && input != 'q') {
		cout << "===========================================================================\n"
			<< ">> Enter 'S' to start game; 'I' for more info; 'Q': ";

		Gomoku game = Gomoku();
		game.showThinking(true);
		game.refreshConsole(false);
		cin >> input;
		switch (input) {
		case 'S':
			cout << "Game Start!" << endl;
			game.StartGame();	
			break;
		case 's':
			cout << "Game Start!" << endl;
			game.StartGame();
			break;
		case 'I':
			printInfo();
			break;
		case 'i':
			printInfo();
			break;
		
		case 'Q':
			break;
		case 'q':
			break;
		default: 
			cout << "Wrong input, please try again.\n";
			break;
		}
	}
	cout << "Thanks for playing!";
	return 0;
}
