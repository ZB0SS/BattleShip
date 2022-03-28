#include<iostream>
#include <map>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int charToInt(char c) {
    string holder;
    holder.push_back(c);
    return stoi(holder);
}

bool checkIfPosIsFilled(map<char, vector<char>> board, char x, int y) {
    char val = board[x][y];
    if (val == 'X') {
        return true;
    }
    return false;
}

void printBoard(map<char, vector<char>>  board) {
    cout << "\t    0  1  2  3  4  5  6  7  8  9" << endl;
    for (auto pair : board) {
        cout << "\t" << pair.first << " - ";
        for (auto space : pair.second) {
            cout << space << "  ";
        }
        cout << endl << endl;
    }
}

auto createBoard(bool print){
    map<char, vector<char>> board;
    vector<char> row = {'*', '*', '*', '*', '*', '*', '*', '*', '*', '*'};
    board.insert(pair<char, vector<char>>('A', row));
    board.insert(pair<char, vector<char>>('B', row));
    board.insert(pair<char, vector<char>>('C', row));
    board.insert(pair<char, vector<char>>('D', row));
    board.insert(pair<char, vector<char>>('E', row));
    board.insert(pair<char, vector<char>>('F', row));
    board.insert(pair<char, vector<char>>('G', row));
    board.insert(pair<char, vector<char>>('H', row));
    board.insert(pair<char, vector<char>>('I', row));
    board.insert(pair<char, vector<char>>('J', row));
    if (print) {
        printBoard(board);
    }
    return board;
}

string askUserForPos() {
    string input;
    cout << "What position would you like to bomb?: ";
    cin >> input;
    return input;
}

auto placeBoats(map<char, vector<char>> board) {
    // 2, 3, 3, 4, 5
    vector<int> boats = {2, 3, 3, 4, 5};
    for (int boat: boats) {
        string startingPlace;
        string endPlace;
        cout << "Where would you like to place your " << boat << " unit boat" << endl;
        cin >> startingPlace;
        cout << "Where would you like to place the end of your boat?" << endl;
        cin >> endPlace;
        // Letters are the same F3 F4 F5
        if (startingPlace[0] == endPlace[0]) {

            // F5 F1
            int start = charToInt(startingPlace[1]);
            int end = charToInt(endPlace[1]);

            if (start > end) {
                int holder = start;
                start = end;
                end = holder;
            }

            //J6 J7 J8 J9
            if (abs(start - end) + 1 != boat) {
                cout << "Not enough units provided";
                exit(0);
            }
            int looped = 0;
            bool c = true;
            for (int i = start; i <= end; i++) {
                if (c) {
                    if (!checkIfPosIsFilled(board, startingPlace[0], i)) {
                        board[startingPlace[0]][i] = 'X';
                    }
                    else {
                        cout << "Boat overlaps with another boat";
                        exit(0);
                    }

                }
                looped++;
                if (looped == boat) {
                    c = false;
                }
            } // Numbers are the same letters are diffrent
        } else if (endPlace[1] == startingPlace[1]) {

            // TODO Check if letter is in the key
            const int num = charToInt(startingPlace[1]);
            char startLetter = startingPlace[0];
            char endLetter = endPlace[0];
            map<char, int> key = {
                    {'A', 1},
                    {'B', 2},
                    {'C', 3},
                    {'D', 4},
                    {'E', 5},
                    {'F', 6},
                    {'G', 7},
                    {'H', 8},
                    {'I', 9},
                    {'J', 10}
            };
            map<int, char> reversedKeyMap = {};
            for (auto p: key) {
                reversedKeyMap.insert(pair<int, char>(p.second, p.first));
            }
            int startVal = key[startLetter];
            int endVal = key[endLetter];

            if (startVal > endVal) {
                int holder = startVal;
                startVal = endVal;
                endVal = holder;
            }

            // Correct Amount Of Units
            if (abs(startVal - endVal) + 1 == boat) {
                for (int i = startVal; i <= endVal; i++) {
                    if (!checkIfPosIsFilled(board, reversedKeyMap[i], num)) {
                        board[reversedKeyMap[i]][num] = 'X';
                    } else {
                        cout << "Boat overlaps with another boat";
                        exit(0);
                    }

                }
            }
            else {
                cout << "Too many units or too less units provided" << endl;
                exit(0);
            }

        }
        printBoard(board);
    }
    return board;
}

map<char, vector<char>> bombBoard(map<char, vector<char>> boardToBomb, map<char, vector<char>> displayBoard) {
    string holder;
    bool missed = false;
    while (!missed) {
        string input;
        printBoard(displayBoard);
        cout << "Type the coords you would like to bomb: ";
        cin >> input;
        char letter = input[0];
        int row = charToInt(input[1]);
        if (displayBoard[letter][row] == 'x' || displayBoard[letter][row] == '-') {
            cout << "Bomb somewhere else" << endl;
            continue;
        }
        if (boardToBomb[letter][row] == 'X') {
            displayBoard[letter][row] = 'x';
        } else {
            displayBoard[letter][row] = '-';
            printBoard(displayBoard);
            cout << "Other players turn press any key: ";
            cin >> holder;
            cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";

            missed = true;
        }
    }
    return displayBoard;
}

int checkBombs(map<char, vector<char>> board) {
    int bombs = 0;
    for (pair<char, vector<char>> p  : board) {
        for (char i : p.second) {
            if(i == 'x') {
                bombs ++;
            }
        }
    }
    return bombs;
}

    int main() {
        string holder;
        map<char, vector<char>> firstBoard = createBoard(true);

        firstBoard = placeBoats(firstBoard);
        cout << "Type any key for the second player to begin: ";
        cin >> holder;
        cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
        map<char, vector<char>> secondBoard = createBoard(true);
        secondBoard = placeBoats(secondBoard);

        cout << "Press any key to begin the game (p1) ";
        cin >> holder;
        cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";

        map<char, vector<char>> firstEnemyBoard = createBoard(false);
        map<char, vector<char>> secondEnemyBoard = createBoard(false);

        bool gameOver = false;
        int p = 1;
        int firstBombs = 0;
        int secondBombs = 0;
        while (!gameOver) {
            // player 1
            if (p % 2 == 1) {
                firstEnemyBoard = bombBoard(secondBoard, firstEnemyBoard);
                firstBombs = checkBombs(firstEnemyBoard);
                if (firstBombs >= 17) {
                    cout << "Player 1 wins!";
                    gameOver = true;
                }
            } else {
                secondEnemyBoard = bombBoard(firstBoard, secondEnemyBoard);
                secondBombs = checkBombs(secondEnemyBoard);
                if (secondBombs >= 17) {
                    cout << "Player 2 wins!";
                    gameOver = true;
                }
            }
            p++;
        }
        return 0;
    }


/*      1 2 3 4 5 6 7 8 9 10
    A   x x x x x x x x x x
    B   x x x x x x x x x x
    C   x x x x x x x x x x
    D   x x x x x x x x x x
    E   x x x x x x x x x x
    F   x x x x x x x x x x
    G   x x x x x x x x x x
    H   x x x x x x x x x x
    I   x x x x x x x x x x
*/
