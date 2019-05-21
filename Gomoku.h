#pragma once
//author:	Shizhe Zeng	1750145
#include <string>
#include <vector>
#include "Board.h"

class Gomoku {

private:
	int boardSize;
	int x1;
	int y1;
	int goBoard[20][20];
	int moves;
	bool refresh = false;
	bool show = false;


public:
	Gomoku(int size = 15); 
	
	void StartGame();
	void NextMoveScore();
	int AiMove();
	
	void DrawAiThinking(); 

	void showThinking(bool tf);
	void refreshConsole(bool tf);
	
	void Clear();
	void CleanBoard();
	void draw();
	
	int WinsGame(int i0, int j0);

	int WinsGame5Piece(int i0, int j0);
	int WinsGame4Piece(int i0, int j0);
	int WinsGame3Piece(int i0, int j0);
	int WinsGame2Piece(int i0, int j0);
	
	

};