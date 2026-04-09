#include <iostream>
#include <initializer_list>
#include <iomanip>
#include <cmath>
#include <string>
#include <vector>

using namespace std;

class Game {
	private:
		
	public:
		// Prints some information about the game and the rules of the game
		Game() {
			cout << "Omok is a two player game that is similar to connect four.\nThe game is played on a board with a 15x15 grid.\nPieces can be placed anywhere on the board if that spot is empty.\nTo win a player must align 5 pieces horizontally, vertically or diagonally.\nThere are three different colors for the pieces: Lead, Gold, and Copper." << endl;
		};

		// Attempts to load the game board and sets Player 1's piece color and win condition or creates a new game board if the file isn't found
		void LoadGameBoard(string omok[15][15], string playerInfo[2][3]) {
			ifstream SaveFile("C://windows/temp/omoksavefile.txt");

			// Checks if SaveFile exists or not
			if (SaveFile) {
				// Extracts the board from SaveFile
				cout << "File found, Loading board" << endl;
				for (int z = 0; z < 15; z++) {
					for (int x = 0; x < 15; x++) {
						SaveFile >> omok[z][x];
					}
				}

				// Checks each spot on the board for which piece color Player 1 chose and sets Player 1's piece color and win condition
				for (int z = 0; z < 15; z++) {
					for (int x = 0; x < 15; x++) {
						if (omok[z][x] == "G") {
							playerInfo[0][0] = "G";
							playerInfo[0][2] = "GGGGG";
						} else if (omok[z][x] == "C") {
							playerInfo[0][0] = "C";
							playerInfo[0][2] = "CCCCC";
						}
					}
				}
				SaveFile.close();
			} else {
				// Informs the user that the file couldn't be found and that it will create a new board, and creates a new board
				cout << "Error: file not found\nCreating new board" << endl;
				for (int z = 0; z < 15; z++) {
					for (int x = 0; x < 15; x++) {
						omok[z][x] = "e";
					}
				}
			}
		}

		// Sets Player 1's piece color and win condition from user input
		void setPlayer1sInfo(string playerInfo[2][3]) {
			// p1PC = player1PieceColor, wC = winConditions
			string p1PC;
			vector<string> wC = {"GGGGG", "CCCCC"};

			// Asks what color Player 1 wants to be while the input is invalid
			while (playerInfo[0][0] == "e" && playerInfo[0][2] == "eeeee") {
				cout << "Player 1 choose your piece color: Gold or Copper (G/C): ";
				cin >> p1PC;

				// Sets Player 1's piece color to "G" and win condition to "GGGGG" if the input was "G" or "g"
				if (p1PC == "G" || p1PC == "g") {
					playerInfo[0][0] = "G";
					playerInfo[0][2] = wC.at(0);

				// Sets Player 1's piece color to "C" and win condition to "CCCCC" if the input was "C" or "c"
				} else if (p1PC == "C" || p1PC == "c") {
					playerInfo[0][0] = "C";
					playerInfo[0][2] = wC.at(1);
				}
			}
		}

		// Prints the game board
		void printBoard(const string omok[15][15]) {
			for (int z = 0; z < 15; z++) {
				for (int x = 0; x < 15; x++) {
					cout << omok[z][x] << "  ";
				}
				cout << "\n";
			}
		}

		// Checks if Player 1 has more pieces than Player 2 and returns the appropriate player
		string DecideTurn(string omok[15][15], string playerInfo[2][3]) {
			// p1sPC = player1PieceCount, p2sPC = player2PieceCount
			int p1sPC = 0, p2sPC = 0;

			// Checks each spot on the board and adds 1 to either p1sPC or p2sPC
			for (int z = 0; z < 15; z++) {
				for (int x = 0; x < 15; x++) {
					if (omok[z][x] == playerInfo[0][0]) {
						p1sPC += 1;
					} else if (omok[z][x] == playerInfo[1][0]) {
						p2sPC += 1;
					}
				}
			}

			// Checks if p1sPC is higher than p2sPC and returns the appropriate player
			if (p1sPC > p2sPC) {
				return playerInfo[1][1];
			} else {
				return playerInfo[0][1];
			}
		}

		// Gets a row number from the user
		int getRow() {
			int row;
			// Continually asks the user to input a number that if the input is greater than 15 or less than 1
			do {
				cout << "Choose a row between 1 and 15: ";
				cin >> row;
			} while (row < 1 || row > 15);

			// Returns the inputted number
			return row - 1;
		}

		// Gets a column number from the user
		int getColumn() {
			int column;
			// Continually asks the user to input a number that if the input is greater than 15 or less than 1
			do {
				cout << "Choose a column between 1 and 15: ";
				cin >> column;
			} while (column < 1 || column > 15);

			// Returns the inputted number
			return column - 1;
		}

		// Checks if a player's win condition has been met and returns the winner or "e"
		string hasSomeoneWon(const string omok[15][15], string playerInfo[2][3]) {
			// winner is "e" by default
			string winner = "e";
			// hArray = horizontalArray, vArray = verticalArray, dRArray = diagonalRightArray, dLArray = diagonalLeftArray
			string hArray[15];
			string vArray[15];
			string dRArray[21] = {
				omok[10][0] + omok[11][1] + omok[12][2] + omok[13][3] + omok[14][4],
				omok[9][0] + omok[10][1] + omok[11][2] + omok[12][3] + omok[13][4] + omok[14][5],
				omok[8][0] + omok[9][1] + omok[10][2] + omok[11][3] + omok[12][4] + omok[13][5] + omok[14][6],
				omok[7][0] + omok[8][1] + omok[9][2] + omok[10][3] + omok[11][4] + omok[12][5] + omok[13][6] + omok[14][7],
				omok[6][0] + omok[7][1] + omok[8][2] + omok[9][3] + omok[10][4] + omok[11][5] + omok[12][6] + omok[13][7] + omok[14][8],
				omok[5][0] + omok[6][1] + omok[7][2] + omok[8][3] + omok[9][4] + omok[10][5] + omok[11][6] + omok[12][7] + omok[13][8] + omok[14][9],
				omok[4][0] + omok[5][1] + omok[6][2] + omok[7][3] + omok[8][4] + omok[9][5] + omok[10][6] + omok[11][7] + omok[12][8] + omok[13][9] + omok[14][10],
				omok[3][0] + omok[4][1] + omok[5][2] + omok[6][3] + omok[7][4] + omok[8][5] + omok[9][6] + omok[10][7] + omok[11][8] + omok[12][9] + omok[13][10] + omok[14][11],
				omok[2][0] + omok[3][1] + omok[4][2] + omok[5][3] + omok[6][4] + omok[7][5] + omok[8][6] + omok[9][7] + omok[10][8] + omok[11][9] + omok[12][10] + omok[13][11] + omok[14][12],
				omok[1][0] + omok[2][1] + omok[3][2] + omok[4][3] + omok[5][4] + omok[6][5] + omok[7][6] + omok[8][7] + omok[9][8] + omok[10][9] + omok[11][10] + omok[12][11] + omok[13][12] + omok[14][13],
				omok[0][0] + omok[1][1] + omok[2][2] + omok[3][3] + omok[4][4] + omok[5][5] + omok[6][6] + omok[7][7] + omok[8][8] + omok[9][9] + omok[10][10] + omok[11][11] + omok[12][12] + omok[13][13] + omok[14][14],
				omok[0][1] + omok[1][2] + omok[2][3] + omok[3][4] + omok[4][5] + omok[5][6] + omok[6][7] + omok[7][8] + omok[8][9] + omok[9][10] + omok[10][11] + omok[11][12] + omok[12][13] + omok[13][14],
				omok[0][2] + omok[1][3] + omok[2][4] + omok[3][5] + omok[4][6] + omok[5][7] + omok[6][8] + omok[7][9] + omok[8][10] + omok[9][11] + omok[10][12] + omok[11][13] + omok[12][14],
				omok[0][3] + omok[1][4] + omok[2][5] + omok[3][6] + omok[4][7] + omok[5][8] + omok[6][9] + omok[7][10] + omok[8][11] + omok[9][12] + omok[10][13] + omok[11][14],
				omok[0][4] + omok[1][5] + omok[2][6] + omok[3][7] + omok[4][8] + omok[5][9] + omok[6][10] + omok[7][11] + omok[8][12] + omok[9][13] + omok[10][14],
				omok[0][5] + omok[1][6] + omok[2][7] + omok[3][8] + omok[4][9] + omok[5][10] + omok[6][11] + omok[7][12] + omok[8][13] + omok[9][14],
				omok[0][6] + omok[1][7] + omok[2][8] + omok[3][9] + omok[4][10] + omok[5][11] + omok[6][12] + omok[7][13] + omok[8][14],
				omok[0][7] + omok[1][8] + omok[2][9] + omok[3][10] + omok[4][11] + omok[5][12] + omok[6][13] + omok[7][14],
				omok[0][8] + omok[1][9] + omok[2][10] + omok[3][11] + omok[4][12] + omok[5][13] + omok[6][14],
				omok[0][9] + omok[1][10] + omok[2][11] + omok[3][12] + omok[4][13] + omok[5][14],
				omok[0][10] + omok[1][11] + omok[2][12] + omok[3][13] + omok[4][14]
			};
			string dLArray[21] = {
				omok[0][4] + omok[1][3] + omok[2][2] + omok[3][1] + omok[4][0],
				omok[0][5] + omok[1][4] + omok[2][3] + omok[3][2] + omok[4][1] + omok[5][0],
				omok[0][6] + omok[1][5] + omok[2][4] + omok[3][3] + omok[4][2] + omok[5][1] + omok[6][0],
				omok[0][7] + omok[1][6] + omok[2][5] + omok[3][4] + omok[4][3] + omok[5][2] + omok[6][1] + omok[7][0],
				omok[0][8] + omok[1][7] + omok[2][6] + omok[3][5] + omok[4][4] + omok[5][3] + omok[6][2] + omok[7][1] + omok[8][0],
				omok[0][9] + omok[1][8] + omok[2][7] + omok[3][6] + omok[4][5] + omok[5][4] + omok[6][3] + omok[7][2] + omok[8][1] + omok[9][0],
				omok[0][10] + omok[1][9] + omok[2][8] + omok[3][7] + omok[4][6] + omok[5][5] + omok[6][4] + omok[7][3] + omok[8][2] + omok[9][1] + omok[10][0],
				omok[0][11] + omok[1][10] + omok[2][9] + omok[3][8] + omok[4][7] + omok[5][6] + omok[6][5] + omok[7][4] + omok[8][3] + omok[9][2] + omok[10][1] + omok[11][0],
				omok[0][12] + omok[1][11] + omok[2][10] + omok[3][9] + omok[4][8] + omok[5][7] + omok[6][6] + omok[7][5] + omok[8][4] + omok[9][3] + omok[10][2] + omok[11][1] + omok[12][0],
				omok[0][13] + omok[1][12] + omok[2][11] + omok[3][10] + omok[4][9] + omok[5][8] + omok[6][7] + omok[7][6] + omok[8][5] + omok[9][4] + omok[10][3] + omok[11][2] + omok[12][1] + omok[13][0],
				omok[0][14] + omok[1][13] + omok[2][12] + omok[3][11] + omok[4][10] + omok[5][9] + omok[6][8] + omok[7][7] + omok[8][6] + omok[9][5] + omok[10][4] + omok[11][3] + omok[12][2] + omok[13][1] + omok[14][0],
				omok[1][14] + omok[2][13] + omok[3][12] + omok[4][11] + omok[5][10] + omok[6][9] + omok[7][8] + omok[8][7] + omok[9][6] + omok[10][5] + omok[11][4] + omok[12][3] + omok[13][2] + omok[14][1],
				omok[2][14] + omok[3][13] + omok[4][12] + omok[5][11] + omok[6][10] + omok[7][9] + omok[8][8] + omok[9][7] + omok[10][6] + omok[11][5] + omok[12][4] + omok[13][3] + omok[14][2],
				omok[3][14] + omok[4][13] + omok[5][12] + omok[6][11] + omok[7][10] + omok[8][9] + omok[9][8] + omok[10][7] + omok[11][6] + omok[12][5] + omok[13][4] + omok[14][3],
				omok[4][14] + omok[5][13] + omok[6][12] + omok[7][11] + omok[8][10] + omok[9][9] + omok[10][8] + omok[11][7] + omok[12][6] + omok[13][5] + omok[14][4],
				omok[5][14] + omok[6][13] + omok[7][12] + omok[8][11] + omok[9][10] + omok[10][9] + omok[11][8] + omok[12][7] + omok[13][6] + omok[14][5],
				omok[6][14] + omok[7][13] + omok[8][12] + omok[9][11] + omok[10][10] + omok[11][9] + omok[12][8] + omok[13][7] + omok[14][6],
				omok[7][14] + omok[8][13] + omok[9][12] + omok[10][11] + omok[11][10] + omok[12][9] + omok[13][8] + omok[14][7],
				omok[8][14] + omok[9][13] + omok[10][12] + omok[11][11] + omok[12][10] + omok[13][9] + omok[14][8],
				omok[9][14] + omok[10][13] + omok[11][12] + omok[12][11] + omok[13][10] + omok[14][9],
				omok[10][14] + omok[11][13] + omok[12][12] + omok[13][11] + omok[14][10]
			};
			
			/* Numbers for if I decide to change the method of adding letters to the diagonalArrays to use for loops
			dRArray: (z= 10 9 8 7 6 5 4 3 2 1 (0 x11); x> 4 5 6 7 8 9 10 11 12 13 (14 x11); z++), (x= (0 x11) 1 2 3 4 5 6 7 8 9 10; z> (14 x11) 13 12 11 10 9 8 7 6 5 4; x++)
			dLArray: (z= (0 x11) 1 2 3 4 5 6 7 8 9 10; z> 4 5 6 7 8 9 10 11 12 13 (14 x11); z++), (x= 4 5 6 7 8 9 10 11 12 13 (14 x11); x< (0 x11) 1 2 3 4 5 6 7 8 9 10; x--) */

			// Adds each letter from each row of omok to a string and adds that string to an array
			for (int z = 0; z < 15; z++) {
				string horizontal = "";
				for (int x = 0; x < 15; x++) {
					horizontal.append(omok[z][x]);
				}
				hArray[z] = horizontal;
			}

			// Adds each letter from each column of omok to a string and adds that string to an array
			for (int x = 0; x < 15; x++) {
				string vertical = "";
				for (int z = 0; z < 15; z++) {
					vertical.append(omok[z][x]);
				}
				vArray[x] = vertical;
			}

			// Checks the horizontal and vertical arrays for a win condition
			for (int i = 0; i < 15; i++) {
				if (vArray[i].find(playerInfo[0][2]) != string::npos || hArray[i].find(playerInfo[0][2]) != string::npos) {
					// Sets winner to "Player 1"
					winner = playerInfo[0][1];
				} else if (hArray[i].find(playerInfo[1][2]) != string::npos || vArray[i].find(playerInfo[1][2]) != string::npos) {
					// Sets winner to "Player 2"
					winner = playerInfo[1][1];
				}
			}

			// Checks the diagonal arrays for a win condition
			for (int i = 0; i < 21; i++) {
				if (dRArray[i].find(playerInfo[0][2]) != string::npos || dLArray[i].find(playerInfo[0][2]) != string::npos) {
					// Sets winner to "Player 1"
					winner = playerInfo[0][1];
				} else if (dLArray[i].find(playerInfo[1][2]) != string::npos || dRArray[i].find(playerInfo[1][2]) != string::npos) {
					// Sets winner to "Player 2"
					winner = playerInfo[1][1];
				}
			}

			// Returns winner
			return winner;
		}

		// Attempts to save the game board and tells the user where the file is
		void saveGame(string omok[15][15]) {
			ofstream SaveFile("C://windows/temp/omoksavefile.txt");

			if (SaveFile.is_open()) {
				// Saves the game board
				for (int z = 0; z < 15; z++) {
					for (int x = 0; x < 14; x++) {
						SaveFile << omok[z][x] << " ";
					}
					SaveFile << omok[z][14] << "\n";
				}
				SaveFile.close();

				// Informs the user of the successful save and where to fine the file
				cout << "Your board has been successfully saved.\nYour save file is at \"C://windows/temp/omoksavefile.txt\"\nYour save file will be deleted if you clear your temp folder" << endl;
			} else {
				// Informs the user of a failed save
				cout << "Errror: board failed to save." << endl;
			}
		}
};