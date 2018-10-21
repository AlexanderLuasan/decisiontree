#include <iostream>
#include "tixtactoegame.h"
#include <vector>
#include <string>
#include <ios>
#include <fstream>
using namespace std;

class tree
{
public:
	tree(tictactoe g, char side,int move);
	void print(int max);
	bool iswinner;
	int getlose();
private:
	int bestmove;
	int indent;
	tictactoe game;
	vector<tree> tolocation;
	char side;
	int wins;
	int ties;
	int loses;

};


int main() {
	int s;
	char team;
	int dep;
	cout << "working" << endl;
	cout << "input size of game: " << flush;
	cin >> s;
	cout << "team to maximaze for x/o: " << flush;
	cin >> team;
	cout << "out depth(9): "<<flush;
	cin >> dep;
	char choice;
	cout << "intial board setup Y/N: " << flush;
	cin >> choice;
	tictactoe game(s);
	
	char input;
	if (choice == 'y') {
		cout << "e is empty" << endl;
		for (int i = 0; i < s; i++) {
			cout << "row" << i << ": ";
			for (int ii = 0; ii < s; ii++) {
				cin >> input;
				game.set(ii, i, input);
			}

		}
	}




	game.print();
	ofstream ofs;
	ofs.open("moves.txt", ios::out);
	ofs.close();

	tree test=tree(game, team,0);
	test.print(dep+1);

	system("pause");
	return 0;
}

tree::tree(tictactoe g, char s,int m)
{
	loses = 0;
	indent = m;
	game = g;
	game.valid();
	side = s;
	iswinner = false;
	bestmove = -1;
	if (game.winner() == 'e') {
		//cout << endl;
		if (game.getside() == s) {
			for (int i = 0; i < game.validmoves(); i++) {
				//print
				for (int ii = 0; ii < m; ii++) {
					//cout << "\t";
				}
				//cout << game.validmovex(i) << game.validmovey(i) << game.getside();
				tolocation.push_back(tree(game.move(game.validmovex(i), game.validmovey(i), game.getside()), s, m + 1));
				loses += tolocation[i].getlose();
				if (tolocation[i].iswinner) {
					iswinner = true;
					loses = 0;
					bestmove = i;
					break;
				}

			}
		}
		else {
			
			for (int i = 0; i < game.validmoves(); i++) {
				//print
				for (int ii = 0; ii < m; ii++) {
					//cout << "\t";
				}
				//cout << game.validmovex(i) << game.validmovey(i) << game.getside();
				tolocation.push_back(tree(game.move(game.validmovex(i), game.validmovey(i), game.getside()), s, m + 1));
				loses += tolocation[i].getlose();
			}

			iswinner = true;
			for (int i = 0; i < tolocation.size(); i++) {
				if (tolocation[i].iswinner == false) {
					iswinner = false;
					break;
				}
			}
			if (tolocation.size() == 0) {
				iswinner = false;//stalemate is lose
			}

		}
	}
	else if(game.winner()==s){
		iswinner = true;
		//cout << "->W" << endl;
	}
	else {
		iswinner = false;
		loses = 1;
		//cout << "->L" << endl;
	}

	


}

void tree::print(int max)
{
	if (indent < max) {
		if (bestmove != -1) {
			ofstream out("moves.txt", ios_base::app);
			for (int ii = 0; ii < indent; ii++) {
				out << "\t";
			}
			out << game.validmovex(bestmove) << game.validmovey(bestmove) << game.getside() << tolocation[bestmove].iswinner << "L:" << tolocation[bestmove].getlose() << "\n";
			out.close();
			tolocation[bestmove].print(max);
		}
		else {


			for (int i = 0; i < tolocation.size(); i++) {
				ofstream out("moves.txt", ios_base::app);
				//print
				for (int ii = 0; ii < indent; ii++) {
					out << "\t";
				}
				out << game.validmovex(i) << game.validmovey(i) << game.getside() << tolocation[i].iswinner << "L:" << tolocation[i].loses << "\n";
				out.close();
				tolocation[i].print(max);
			}
		}
	}
	


}

int tree::getlose()
{
	return loses;
}
