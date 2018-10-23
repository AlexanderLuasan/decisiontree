#include <iostream>
#include "tixtactoegame.h"
#include <vector>
#include <string>
#include <ios>
#include <fstream>
#include <thread>
#include <future>
using namespace std;

class tree
{
public:
	tree();
	tree(tictactoe g, char side,int move);
	string print(int max);
	int getlose();
	bool iswinner;
private:
	int bestmove;
	int indent;
	tictactoe game;
	vector<tree> tolocation;
	char side;
	int loses;

};


tree multi(tictactoe g, char side, int move);


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

	game.valid();

	ofstream ofs;
	ofs.open("moves.txt", ios::out);
	ofs.close();
	for (int j = 0; j < s/2;j++) {
		future<tree> ret[10];
		for (int i = 0; i < s*2; i++) {
			tictactoe t = game.move(game.validmovex((j*s)+i), game.validmovey((j*s)+i), game.getside());
			ret[i] = async(&multi, t, team, 0);
		}
		cout << "writting" << endl;
		
		
		ofs.open("moves.txt", ios::app);
		for (int i = 0; i < s*2; i++) {
			tree temp = ret[i].get();
			ofs << game.validmovex((j*s) + i) << game.validmovey((j*s) + i) << game.getside() << "L:" << temp.getlose() << "\n";
			ofs << temp.print(dep).c_str();
			cout << "done" << endl;
		}
		ofs.close();
	}
	
	system("pause");
	return 0;
}


tree::tree()
{

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
				//cout << game.validmovex(i) << game.validmovey(i) << game.getside();
				tree temp = tree(game.move(game.validmovex(i), game.validmovey(i), game.getside()), s, m + 1);
				tolocation.push_back(temp);
				loses += tolocation[i].getlose();
				if (tolocation[i].iswinner) {
					iswinner = true;
					loses = 0;
					bestmove = 0;
					tolocation.clear();
					tolocation.push_back(temp);
					break;
				}

			}
			
			if (tolocation.size() > 0) {
				int minlose = tolocation[0].getlose();
				int minpos = 0;
				for (int i = 0; i < tolocation.size(); i++) {
					
					if (minlose > tolocation[i].getlose()) {
						minlose = tolocation[i].getlose();
						minpos = i;
					}
				}
				tree temp = tolocation[minpos];
				tolocation.clear();
				tolocation.push_back(temp);
				bestmove = 0;
			}

		}
		else {
			
			for (int i = 0; i < game.validmoves(); i++) {

				//print
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

string tree::print(int max)
{
	char buf[11];
	string end="";
	if (indent < max) {
		if (bestmove != -1) {
			for (int ii = 0; ii < indent+1; ii++) {
				end+="\t";
			}
			sprintf_s(buf, "%ld", game.validmovex(bestmove));
			end += buf;
			
			sprintf_s(buf, "%ld", game.validmovey(bestmove));
			end += buf;
			end += game.getside();
			end += "L:";
			sprintf_s(buf, "%ld", tolocation[bestmove].getlose());
			end += buf;
			end += "\n";
			end += tolocation[bestmove].print(max);
		}
		else {


			for (int i = 0; i < tolocation.size(); i++) {
				//print
				for (int ii = 0; ii < indent+1; ii++) {
					end += "\t";
				}
				sprintf_s(buf, "%ld", game.validmovex(i));
				end += buf;

				sprintf_s(buf, "%ld", game.validmovey(i));
				end += buf;
				end += game.getside();
				end += "L:";
				sprintf_s(buf, "%ld", tolocation[i].getlose());
				end += buf;
				end += "\n";
				end += tolocation[i].print(max);
			}
		}
	}
	

	return end;
}

int tree::getlose()
{
	return loses;
}

tree multi(tictactoe g, char side, int move)
{
	return tree(g,side,move);
}
