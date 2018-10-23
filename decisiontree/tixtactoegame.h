#pragma once

#include <string>
#include <vector>
using namespace std;


class tictactoe
{
public:
	tictactoe();
	tictactoe(int s);
	tictactoe(char board[10][10], int size);
	tictactoe move(int x,int y, char c);
	void set(int x, int y, char c);
	char winner();
	void print();
	void valid();
	int validmoves();
	int validmovex(int i);
	int validmovey(int i);
	char getside();
private:
	short int size;
	char board[10][10];
	char moves[100][3];
	vector<int> x;
	vector<int> y;
	char side;
};

