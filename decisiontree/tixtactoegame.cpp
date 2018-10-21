#include "tixtactoegame.h"
#include <iostream>
using namespace std;
tictactoe::tictactoe()
{

}

tictactoe::tictactoe(int s)
{
	size = s;
	for (int i = 0; i < s; i++) {
		for (int ii = 0; ii < s; ii++) {
			board[i][ii] = 'e';
		}
	}
}

tictactoe::tictactoe(char b[10][10], int s)
{
	size = s;
	for (int i = 0; i < s; i++) {
		for (int ii = 0; ii < s; ii++) {
			board[i][ii] = b[i][ii];
		}
	}
}

tictactoe tictactoe::move(int x, int y, char c)
{
	char s = c;
	tictactoe end;
	end = tictactoe(board, size);
	end.set(x, y, s);
	return end;
}


void tictactoe::set(int x, int y, char c)
{
	board[y][x] = c;
}

char tictactoe::winner()
{
	char in;
	bool complet;
	for (int c = 0; c < size; c++) {
		in = board[0][c];
		if (in != 'e') {
			complet = true;
			for (int r = 0; r < size; r++) {
				if (board[r][c] != in) {
					complet = false;
					break;
				}
			}
			if (complet) {
				return in;
			}
		}
	}

	for (int r = 0; r < size; r++) {
		in = board[r][0];
		if (in != 'e') {
			complet = true;
			for (int c = 0; c < size; c++) {
				if (board[r][c] != in) {
					complet = false;
					break;
				}
			}
			if (complet) {
				return in;
			}
		}
	}
	//diagonal
	in = board[0][0];
	complet = true;
	for (int i = 0; i < size; i++) {
		if (board[i][i] != in) {
			complet = false;
			break;
		}
	}
	if (complet) {
		return in;
	}

	in = board[0][size-1];
	complet = true;
	for (int i = 0; i < size; i++) {
		if (board[i][size-1-i] != in) {
			complet = false;
			break;
		}
	}
	if (complet) {
		return in;
	}

	return 'e';

}

void tictactoe::print()
{
	cout << endl;
	for (int i = 0; i < size; i++) {
		for (int ii = 0; ii < size; ii++) {
			cout << board[i][ii] << " ";
		}
		cout << endl;
	}

}

void tictactoe::valid()
{
	
	int countx = 0;
	int counto = 0;

	for (int i = 0; i < size; i++) {
		for (int ii = 0; ii < size; ii++) {
			if (board[i][ii] == 'x') {
				countx += 1;
			}
			else if (board[i][ii] == 'o') {
				counto += 1;
			}
			else {

			}
		}
	}

	if (countx > counto) {
		side = 'o';
	}
	else {
		side = 'x';
	}
	char move[3];


	for (int i = 0; i < size; i++) {
		for (int ii = 0; ii < size; ii++) {
			if (board[i][ii] == 'e') {
				x.push_back(ii);
				y.push_back(i);
				


				
			}
		}
	}
	

	return;
}

int tictactoe::validmoves()
{
	return x.size();
}

int tictactoe::validmovex(int i)
{
	return x[i];
}

int tictactoe::validmovey(int i)
{
	return y[i];
}

char tictactoe::getside()
{
	return side;
}
