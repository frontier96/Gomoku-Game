//author:	Shizhe Zeng	1750145

#include <iostream>
#include "Board.h"
using namespace std;

Board::Board() {
	for (int nCol = 0; nCol < 15; nCol++)
		for (int nRow = 0; nRow < 15; nRow++)
			Data[nRow][nCol] = 0;
}

int Board::operator()(const int nCol, const int nRow){
	return Data[nRow][nCol];
}

void Board::operator()(const int nCol, const int nRow, int value){
	Data[nRow][nCol] = value;
}


void Board::operator()(){
	// reset all elements of the Array to 0
	for (int nCol = 0; nCol < 15; nCol++)
		for (int nRow = 0; nRow < 15; nRow++)
			Data[nRow][nCol] = 0;
}
