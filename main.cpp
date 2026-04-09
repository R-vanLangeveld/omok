#include <iostream>
#include <initializer_list>
#include <iomanip>
#include <cmath>
#include <fstream>
#include <string>
#include "game.h"

using namespace std;

int main() {
	// Class and variable setup
	Game gameplay;
	string winner = "e";
	bool paused = false;
	string omok[15][15];
	string playerInfo[2][3] = {{"e", "Player 1", "eeeee"}, {"L", "Player 2", "LLLLL"}};
	gameplay.LoadGameBoard(omok, playerInfo);
	gameplay.setPlayer1sInfo(playerInfo);

	// The gameplay Loop
	while (winner != playerInfo[0][1] && winner != playerInfo[1][1] && paused != true) {
		int row = 20, column = 20;
		// Prints the board guide, displays the board, and checks and prints who's turn it is
		cout << "Board guide: \"e\" is an empty space, " << playerInfo[0][0] << " is where " << playerInfo[0][1] << "'s piece is, and " << playerInfo[1][0] << " is where " << playerInfo[1][1] << "'s piece is" << endl;
		gameplay.printBoard(omok);
		string turn = gameplay.DecideTurn(omok, playerInfo);
		cout << turn << "'s turn\n";

		// Calls getRow() and getColumn() until that spot on the board is an "e"
		while (omok[row][column] != "e") {
			row = gameplay.getRow();
			column = gameplay.getColumn();
		}

		// Changes that spot on the board to that player's piece
		if (omok[row][column] == "e" && turn == playerInfo[0][1]) {
			omok[row][column] = playerInfo[0][0];
		} else if (omok[row][column] == "e" && turn == playerInfo[1][1]) {
			omok[row][column] = playerInfo[1][0];
		}

		// Checks if anyone has won
		if (gameplay.hasSomeoneWon(omok, playerInfo) == "e") {
			string save = "e";
			cout << endl;
			gameplay.printBoard(omok);
			cout << turn << "'s turn\nChoose a row between 1 and 15: " << row + 1 << "\nChoose a column between 1 and 15: " << column + 1 << endl;

			// Asks if the user wants to Save & Quit or Continue Playing
			do {
				cout << "Save & Quit or Continue Playing? (S/C): ";
				cin >> save;
			} while (save.compare("S") != 0 && save.compare("C") != 0 && save.compare("s") != 0 && save.compare("c") != 0);

			// Sets paused to true if the user chose to Save & Quit
			if (save == "S" || save == "s") {
				paused = true;
				cout << "Ending the game session." << endl;
			} else {
				cout << "Continuing the game session." << endl;
			}
		}

		// Checks if the user decided not to Save & Quit and sets the winner
		if (paused != true) {
			winner = gameplay.hasSomeoneWon(omok, playerInfo);
		}
	}

	// Checks if a player won or if the game was paused.
	if (winner == playerInfo[0][1] || winner == playerInfo[1][1]) {
		// Prints the winning player, displays the board, and creates a new board
		cout << winner << " Wins!!\nDisplaying the Winning Board" << endl;
		gameplay.printBoard(omok);
		cout << "Creating and saving a new board." << endl;
		for (int z = 0; z < 15; z++) {
			for (int x = 0; x < 15; x++) {
				omok[z][x] = "e";
			}
		}
	} else if (paused == true) {
		// displays the current board and prints "Saving your game."
		cout << "Current Board" << endl;
		gameplay.printBoard(omok);
		cout << "Saving your game." << endl;
	}
	// Saves the board
	gameplay.saveGame(omok);

	return 0;
}