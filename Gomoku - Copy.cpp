//author:	Shizhe Zeng	1750145

#include "Gomoku.h"
#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

Board board; //the Ai thinking score board
//constructor
Gomoku::Gomoku(int size) {
	x1 = 0;
	y1 = 0;
	moves = 0;
	boardSize = size;
	int goBoard[30][30];

	int i = 0;
	int j = 0;
	for (i = 0; i < boardSize; i++)	{
		for (j = 0; j < boardSize; j++)	{
			goBoard[i][j] = 0;
		}
	}
}

//
void Gomoku::StartGame() {
	moves = 0;
	int xCor, yCor;
	int quit = 1;
	Gomoku::Clear();
	Gomoku::CleanBoard();
	while (quit != 0) {
		Gomoku::draw();
		
		cout << "Please enter X Y coordinate, seperated by space:";
		cin >> xCor;
		cin >> yCor;

		x1 = xCor - 1;
		y1 = yCor - 1;

		if (xCor > boardSize || yCor >boardSize){
			string quitMidGame;
			cout << "Do you want to quit the game? (Y/N):";
			cin >> quitMidGame;
			if (quitMidGame.find("Y") != string::npos || quitMidGame.find("y") != string::npos)
				quit = 0;
			else continue;
		}
		else if (x1 < boardSize && x1 >= 0 && y1 < boardSize && y1 >= 0){
			if (goBoard[y1][x1] == 1 || goBoard[y1][x1] == 2){
				cout << "Can't put piece there!" << endl;
			}
			else{   
				goBoard[y1][x1] = 1;
				moves++;
				if (refresh) system("CLS");
				cout << moves << ": Player (x,y): (" << xCor << "," << yCor << ")\n";
				if (Gomoku::WinsGame5Piece(y1, x1) == 0 )	{                                 
					Gomoku::Clear();
					Gomoku::NextMoveScore();
					if (show) Gomoku::DrawAiThinking();  //diable to hide
					if (Gomoku::AiMove() == 1){
						Gomoku::draw();
						cout << "====================================================\n"
							  <<"==                  You Lost!                     ==\n" 
							 << "====================================================" << endl;
						quit = 0;
					}
				}
				else {
					Gomoku::draw();
					cout << "====================================================\n"
					   	 << "==                   You Win!                     ==\n"
						 << "====================================================" << endl;
					quit = 0;
					return;
				}
			}
		}
		else{
			cout << "Smething went wrong!" << endl;
		}
		
		if (moves >= 100)
		{
			quit = 0;
			Gomoku::draw();
			cout << "Let's call it a draw!" << endl;
		}
	}
}

void Gomoku::showThinking(bool tf) {
	show = tf;
}

void Gomoku::refreshConsole(bool tf) {
	refresh = tf;
}

void Gomoku::draw() {
	int row;
	cout << " ";
	for (int i = 0; i < boardSize; i++) {
		cout << setw(3) << i+1;
	}
	cout << endl;
	for (int i = 0; i < boardSize; i++) {
		row = i + 1;
		cout << setw(2) << row;
		for (int j = 0; j < boardSize; j++) {
			
			if (goBoard[i][j] == 0) {
				
					cout << " - ";
				
			}
			if (goBoard[i][j] == 1) {
				
					cout << " X ";
				
			}
			if (goBoard[i][j] == 2) {
				
					cout << " O ";
				
			}
		}
		cout << "\n";
	}
}

void Gomoku::DrawAiThinking(){
	cout << "   ";
	for (int i = 0; i < boardSize; i++) {
		cout << setw(3) << i + 1;
	}
	cout << endl;
	for (int i = 0; i < boardSize; i++)	{
		cout << setw(3) <<i+1;
		for (int j = 0; j < boardSize; j++)		{
			if (board(i, j) == 0)
				cout << setw(3) << " ";
			else 
				cout << setw(3) << board(i, j);
		}
		cout << endl;
	}
	cout << " ";
	for (int n = 0; n < boardSize; n++) {
		cout << "---";
	} 
	cout << endl;
}

void Gomoku::Clear(){
	board();
}

void Gomoku::CleanBoard() {
	for (int i = 0; i < boardSize; i++) {
		for (int j = 0; j < boardSize; j++) {
			goBoard[i][j] = 0;
		}
	}
}

//Ai stuff
void Gomoku::NextMoveScore() {
	int i, j;
	
	for (i = 0; i < boardSize; i++) {
		for (j = 0; j < boardSize; j++) {
			int a = 0, b = 0, c = 0, x = 0, y = 0, z = 0;
			if (goBoard[i][j] != 1 && goBoard[i][j] != 2) {
				//Ai
				goBoard[i][j] = 2;

				if (Gomoku::WinsGame5Piece(i, j) >= 1) {
					board(i, j, board(i, j) + 500);//WinsGame5Piece(i, j)*
					
				}
				if (Gomoku::WinsGame4Piece(i, j) >= 1) {
					board(i, j, board(i, j) + WinsGame4Piece(i, j) * (27-9));//WinsGame4Piece(i, j)*
					a = WinsGame4Piece(i, j) * 18;
				}
				if (Gomoku::WinsGame3Piece(i, j) >= 1) {
					board(i, j, board(i, j) + WinsGame3Piece(i, j) * (9));//WinsGame3Piece(i, j)*
					b = WinsGame3Piece(i, j) * 9;
				}
				if (Gomoku::WinsGame2Piece(i, j) >= 1) {
					board(i, j, board(i, j) + 3); //WinsGame3Piece(i, j)*
					c = 3;
				}

				goBoard[i][j] = 0;
				//reset

				//player
				goBoard[i][j] = 1;

				if (Gomoku::WinsGame5Piece(i, j) >= 1) {
					board(i, j, board(i, j) + (72-18));//WinsGame5Piece(i, j)*
				}
				if (Gomoku::WinsGame4Piece(i, j) >= 1) {
					board(i, j, board(i, j) + WinsGame4Piece(i, j) * (18-6));//WinsGame4Piece(i, j)*  10
					x = WinsGame4Piece(i, j) * 12;
				}
				if (Gomoku::WinsGame3Piece(i, j) >= 1) {
					board(i, j, board(i, j) + WinsGame3Piece(i, j) * (6));//WinsGame3Piece(i, j)*   4
					y = WinsGame3Piece(i, j) * 6;
				}
				if (Gomoku::WinsGame2Piece(i, j) >= 1) {
					board(i, j, board(i, j) + 2); //WinsGame2Piece(i, j)/2 * 
					z = 2;
				}

				goBoard[i][j] = 0;
				//reset
			}
			else
				board(i, j, -99);
			if (board(i, j) > 0) cout << "(" << j+1 << "," << i+1 << "): " << a << "," << b << "," << c << "|" << x << "," << y << "," << z << "=" << board(i, j) <<endl;
		}
	}
	for (int i=0; i < boardSize; i++) {
		board(i, 0, board(i, 0) - 36);
		board(i, boardSize-1, board(i, boardSize-1) - 36);
	}
	for (int j = 0; j < boardSize; j++) {
		board(0, j, board(0, j) - 36);
		board(boardSize-1, j, board(boardSize-1, j) - 36);
	}
	board(boardSize - 1, boardSize - 1, board(boardSize - 1, boardSize - 1) + 36);
	board(0, 0, board(0, 0) + 36);
	board(0, boardSize - 1, board(0, boardSize - 1) + 36);
	board(boardSize - 1, 0, board(boardSize - 1, 0) + 36);

	for (int i = 1; i < boardSize-1; i++) {
		board(i, 1, board(i, 1) - 2);
		board(i, boardSize - 2, board(i, boardSize - 2) - 2);
	}
	for (int j = 2; j < boardSize-2; j++) {
		board(1, j, board(1, j) - 2);
		board(boardSize - 2, j, board(boardSize - 2, j) - 2);
	}
	
	//board(5, 6, -5); // 7,6
}

int Gomoku::AiMove(){
	int maxy = 0, maxx = 0, maxScore = -99;
	for (int c = 0; c < boardSize; c++)	{
		for (int r = 0; r < boardSize; r++)	{
			if (goBoard[c][r] != 1 && goBoard[c][r] != 2)
			{
				if (maxScore < board(c, r))
				{
					maxScore = board(c, r);
					maxy = c;
					maxx = r;
				}
			}
		}
	}
	goBoard[maxy][maxx] = 2;
	cout << moves << ": Ai (x,y): (" << maxx+1 << "," << maxy+1 << ")\n";
	if (Gomoku::WinsGame5Piece(maxy, maxx) >= 1)
		return 1;
	return 0;
}

//Evaluation
int Gomoku::WinsGame(int i0, int j0) {
	int i, j;

	i = i0;
	j = j0 - 3;
	if (j < 0)	j = 0;
	while ((j <= j0))	{
		if ((goBoard[i][j] == goBoard[i0][j0]) 
			&& (goBoard[i][j + 1] == goBoard[i0][j0]) 
			&& (goBoard[i][j + 2] == goBoard[i0][j0]) 
			&& (goBoard[i][j + 3] == goBoard[i0][j0]))
			return 1;
		j++;
	}
	
	j = j0;
	i = i0 - 3;
	if (i < 0)	i = 0;
	while (i <= i0)	{
		if ((goBoard[i][j] == goBoard[i0][j0]) 
			&& (goBoard[i + 1][j] == goBoard[i0][j0]) 
			&& (goBoard[i + 2][j] == goBoard[i0][j0]) 
			&& (goBoard[i + 3][j] == goBoard[i0][j0]))
			return 1;
		i++;
	}

	j = j0 - 3;
	i = i0 - 3;
	while (i < 0 || j < 0)	{
		j++;	i++;
	}
	while ((i <= i0) && (j <= j0))	{
		if ((goBoard[i][j] == goBoard[i0][j0]) 
			&& (goBoard[i + 1][j + 1] == goBoard[i0][j0]) 
			&& (goBoard[i + 2][j + 2] == goBoard[i0][j0]) 
			&& (goBoard[i + 3][j + 3] == goBoard[i0][j0]))
			return 1;
		j++;
		i++;
	}
	
	j = j0 + 3;
	i = i0 - 3;
	if (i < 0)		i = 0;
	while (j < 0 || i < 0)	{
		j--;i++;
	}
	while ((i <= i0) && (j >= j0) && (j >= 3))	{
		if ((goBoard[i][j] == goBoard[i0][j0]) 
			&& (goBoard[i + 1][j - 1] == goBoard[i0][j0]) 
			&& (goBoard[i + 2][j - 2] == goBoard[i0][j0]) 
			&& (goBoard[i + 3][j - 3] == goBoard[i0][j0]))
			return 1;
		j--;
		i++;
	}
	return 0;
}

// N>S; W>E; WN>ES; S>N  5 piece to end point
int Gomoku::WinsGame5Piece(int i0, int j0) {
	int i, j, count = 0;
	i = i0;
	j = j0 - 4;
	if (j < 0) j = 0;
	while ((j <= j0)) {		// N>S
		if ((goBoard[i][j] == goBoard[i0][j0])
			&& (goBoard[i][j + 1] == goBoard[i0][j0])
			&& (goBoard[i][j + 2] == goBoard[i0][j0])
			&& (goBoard[i][j + 3] == goBoard[i0][j0])
			&& (goBoard[i][j + 4] == goBoard[i0][j0]))
			count++;
			//return 1;
		j++;
	}
	
	j = j0;
	i = i0 - 4;
	if (i < 0) i = 0;
	while ((i <= i0)) {		// W>E
		if ((goBoard[i][j] == goBoard[i0][j0]) 
			&& (goBoard[i + 1][j] == goBoard[i0][j0]) 
			&& (goBoard[i + 2][j] == goBoard[i0][j0]) 
			&& (goBoard[i + 3][j] == goBoard[i0][j0]) 
			&& (goBoard[i + 4][j] == goBoard[i0][j0]))
			count++;
			//return 1;
		i++;
	}
	// (5,6) < (1,2)
	j = j0 - 4;
	i = i0 - 4;
	while (i < 0 || j < 0)	{
		i++; j++;
	}
	//if(i<0) i=0; if(j<0) j=0;
	while ((i <= i0) && (j <= j0)) 	{	// WN>ES
		if ((goBoard[i][j] == goBoard[i0][j0]) 
			&& (goBoard[i + 1][j + 1] == goBoard[i0][j0]) 
			&& (goBoard[i + 2][j + 2] == goBoard[i0][j0]) 
			&& (goBoard[i + 3][j + 3] == goBoard[i0][j0]) 
			&& (goBoard[i + 4][j + 4] == goBoard[i0][j0]))
			count++; 
			//return 1;
		j++;
		i++;
	}

	j = j0 + 4;
	i = i0 - 4;
	while (i < 0){
		i++; j--;
	}
	//if(i<0) i=0; //
	while ((i <= i0) && (j >= j0) && (j >= 4))	{	// S>N
		if ((goBoard[i][j] == goBoard[i0][j0]) 
			&& (goBoard[i + 1][j - 1] == goBoard[i0][j0]) 
			&& (goBoard[i + 2][j - 2] == goBoard[i0][j0]) 
			&& (goBoard[i + 3][j - 3] == goBoard[i0][j0]) 
			&& (goBoard[i + 4][j - 4] == goBoard[i0][j0]))
			count++;
			//return 1;
		j--;
		i++;
	}
	return count;
}

// N>S; W>E; WN>ES; S>N  4 piece to end point
int Gomoku::WinsGame4Piece(int i0, int j0) {
	int i, j, count = 0;

	i = i0;
	j = j0 - 3;
	if (j < 0)	j = 0;
	while ((j <= j0)) {
		if ((goBoard[i][j] == goBoard[i0][j0])
			&& (goBoard[i][j + 1] == goBoard[i0][j0])
			&& (goBoard[i][j + 2] == goBoard[i0][j0])
			&& (goBoard[i][j + 3] == goBoard[i0][j0]))
			count++;
			//return 1;
		j++;
	}

	j = j0;
	i = i0 - 3;
	if (i < 0)	i = 0;
	while ((i <= i0)) {
		if ((goBoard[i][j] == goBoard[i0][j0])
			&& (goBoard[i + 1][j] == goBoard[i0][j0])
			&& (goBoard[i + 2][j] == goBoard[i0][j0])
			&& (goBoard[i + 3][j] == goBoard[i0][j0]))
			count++;
			//return 1;
		i++;
	}

	j = j0 - 3;
	i = i0 - 3;
	while (j < 0 || i < 0) {
		i++; j++;
	}
	while ((i <= i0) && (j <= j0)) {
		if ((goBoard[i][j] == goBoard[i0][j0])
			&& (goBoard[i + 1][j + 1] == goBoard[i0][j0])
			&& (goBoard[i + 2][j + 2] == goBoard[i0][j0])
			&& (goBoard[i + 3][j + 3] == goBoard[i0][j0]))
			count++;
			//return 1;
		j++;
		i++;
	}

	j = j0 + 3;
	i = i0 - 3;
	while (i < 0) {
		i++; j--;
	}
	while ((i <= i0) && (j >= j0) && (j >= 3)) {
		if ((goBoard[i][j] == goBoard[i0][j0])
			&& (goBoard[i + 1][j - 1] == goBoard[i0][j0])
			&& (goBoard[i + 2][j - 2] == goBoard[i0][j0])
			&& (goBoard[i + 3][j - 3] == goBoard[i0][j0]))
			count++;
			//return 1;
		j--;
		i++;
	}
	return count;
}

// N>S; W>E; WN>ES; S>N  3 piece to end point
int Gomoku::WinsGame3Piece(int i0, int j0) {
	int i, j, count = 0;
	
	i = i0;
	j = j0 - 2;
	if (j < 0)	j = 0;
	while ((j <= j0))	{	
		if ((goBoard[i][j] == goBoard[i0][j0]) 
			&& (goBoard[i][j + 1] == goBoard[i0][j0]) 
			&& (goBoard[i][j + 2] == goBoard[i0][j0]))
			count++;
			//return 1;
		j++;
	}
	
	j = j0;
	i = i0 - 2;
	if (i < 0)	i = 0;
	while ((i <= i0))	{
		if ((goBoard[i][j] == goBoard[i0][j0]) 
			&& (goBoard[i + 1][j] == goBoard[i0][j0]) 
			&& (goBoard[i + 2][j] == goBoard[i0][j0]))
			count++;
			//return 1;
		i++;
	}
	
	j = j0 - 2;
	i = i0 - 2;
	while (i < 0 || j < 0)	{
		i++;	j++;
	}
	while ((i <= i0) && (j <= j0))	{
		if ((goBoard[i][j] == goBoard[i0][j0]) 
			&& (goBoard[i + 1][j + 1] == goBoard[i0][j0]) 
			&& (goBoard[i + 2][j + 2] == goBoard[i0][j0]))
			count++;
			//return 1;
		j++;
		i++;
	}
	
	j = j0 + 2;
	i = i0 - 2;
	while (j < 0 || i < 0)	{
		i++; j--;
	}
	while ((i <= i0) && (j >= j0) && (j >= 2))	{
		if ((goBoard[i][j] == goBoard[i0][j0]) 
			&& (goBoard[i + 1][j - 1] == goBoard[i0][j0]) 
			&& (goBoard[i + 2][j - 2] == goBoard[i0][j0]))
			count++;
			//return 1;
		j--;
		i++;
	}
	return count;
}

// N>S; W>E; WN>ES; S>N  2 piece to end point
int Gomoku::WinsGame2Piece(int i0, int j0) {
	int i, j, count = 0;
	
	i = i0;
	j = j0 - 1;
	if (j < 0)	j = 0;
	while ((j <= j0)){
		if ((goBoard[i][j] == goBoard[i0][j0]) 
			&& (goBoard[i][j + 1] == goBoard[i0][j0]))
			count++;
			//return 1;
		j++;
	}
	
	j = j0;
	i = i0 - 1;
	if (i < 0)	i = 0;
	while ((i <= i0))	{
		if ((goBoard[i][j] == goBoard[i0][j0]) 
			&& (goBoard[i + 1][j] == goBoard[i0][j0]))
			count++;
			//return 1;
		i++;
	}
	
	j = j0 - 1;
	i = i0 - 1;
	while (i < 0 || j < 0)	{
		i++;j++;
	}
	while ((i <= i0) && (i <= boardSize) && (j <= j0) && (j <= boardSize))	{
		if ((goBoard[i][j] == goBoard[i0][j0]) 
			&& (goBoard[i + 1][j + 1] == goBoard[i0][j0]))
			count++;
			//return 1;
		j++;
		i++;
	}
	
	j = j0 + 1; //if(i<0) i=0;
	i = i0 - 1;
	while (i < 0)	{
		j--;	i++;
	}
	while ((i <= i0) && (i <= boardSize) && (j >= j0) && (j >= 1))	{
		if ((goBoard[i][j] == goBoard[i0][j0]) 
			&& (goBoard[i + 1][j - 1] == goBoard[i0][j0]))
			count++;
			//return 1;
		j--;
		i++;
	}
	return count;
}
