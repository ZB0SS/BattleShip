#include<iostream>
#include <map>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

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

auto createBoard(){
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

    printBoard(board);
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
    vector<int> boats = {2, 3};
    for (int boat : boats) {
        string startingPlace;
        string endPlace;
        cout << "Where would you like to place your " << boat << " unit boat" << endl;
        cin >> startingPlace;
        cout << "Where would you like to place the end of your boat?" << endl;
        cin >> endPlace;

        if (startingPlace[0] == endPlace[0]) {
            // Letters are the same F3 F4 F5

            string holder;
            // convert char -> string -> int
            holder.push_back(startingPlace[1]);
            int start = stoi(holder);
            holder.clear();
            holder.push_back(endPlace[1]);
            int end = stoi(holder);

            int looped = 0;
            bool c = true;
            for (int i = start;  i <= end; i++) {
                if (c) {
                    board[startingPlace[0]][i] = 'X';
                }
                looped ++;
                if (looped == boat) {
                    c = false;
                }
            }
        }
        else if (endPlace[1] == startingPlace[1]) {
            // Numbers are the same
        }

    }
    return board;
}
int main() {
    vector<char> yPositions = {'A', 'B', 'C', 'D', 'E', 'G', 'H', 'I'};
    map<char, vector<char>> firstBoard = createBoard();
    // Get the location
//    string input = askUserForPos();
//    string numInput;
//    char yPos = input[0];
//    numInput.push_back(input[1]);
//    int xPos = stoi(numInput);
//    firstBoard[yPos][xPos] = 'X';
    firstBoard = placeBoats(firstBoard);
    printBoard(firstBoard);

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
