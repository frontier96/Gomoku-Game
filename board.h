#pragma once
//author:	Shizhe Zeng	1750145
class Board {
private:
	int Data[15][15];
	
public:
	Board();

	int operator()(const int nCol, const int nRow);  //operator()
	void operator()(const int nCol, const int nRow, int value);  //operator()
	void operator()(); //operator()();

};