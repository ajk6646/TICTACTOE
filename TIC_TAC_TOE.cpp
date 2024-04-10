// TIC_TAC_TOE //

#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

using namespace std;

enum class Player { EMPTY, X, O };

class TicTacToe {
private:
    vector<vector<Player>> board;
    Player currentPlayer;
    bool singlePlayer;

public:
    TicTacToe(bool singlePlayerMode) : board(3, vector<Player>(3, Player::EMPTY)), currentPlayer(Player::X), singlePlayer(singlePlayerMode) {}

    void printBoard() {
        cout << "  1 2 3\n";
        for (int i = 0; i < 3; ++i) {
            cout << i + 1 << " ";
            for (int j = 0; j < 3; ++j) {
                switch (board[i][j]) {
                case Player::EMPTY:
                    cout << "_ ";
                    break;
                case Player::X:
                    cout << "X ";
                    break;
                case Player::O:
                    cout << "O ";
                    break;
                }
            }
            cout << endl;
        }
    }

    bool makeMove(int row, int col) {
        if (row < 0 || row >= 3 || col < 0 || col >= 3 || board[row][col] != Player::EMPTY) {
            cout << "Invalid move! Try again.\n";
            return false;
        }
        board[row][col] = currentPlayer;
        return true;
    }

    bool checkWin() {
        // Check rows and columns
        for (int i = 0; i < 3; ++i) {
            if (board[i][0] != Player::EMPTY && board[i][0] == board[i][1] && board[i][1] == board[i][2])
                return true; // row win
            if (board[0][i] != Player::EMPTY && board[0][i] == board[1][i] && board[1][i] == board[2][i])
                return true; // column win
        }
        // Check diagonals
        if (board[0][0] != Player::EMPTY && board[0][0] == board[1][1] && board[1][1] == board[2][2])
            return true; // diagonal win
        if (board[0][2] != Player::EMPTY && board[0][2] == board[1][1] && board[1][1] == board[2][0])
            return true; // diagonal win
        return false;
    }

    bool boardFull() {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (board[i][j] == Player::EMPTY)
                    return false;
            }
        }
        return true;
    }

    void switchPlayer() {
        currentPlayer = (currentPlayer == Player::X) ? Player::O : Player::X;
    }

    void play() {
        while (!checkWin() && !boardFull()) {
            printBoard();
            int row, col;
            cout << "Player " << (currentPlayer == Player::X ? 'X' : 'O') << ", enter your move (row col): ";
            cin >> row >> col;
            row--; col--; // Adjust for zero-based indexing
            while (!makeMove(row, col)) {
                cout << "Player " << (currentPlayer == Player::X ? 'X' : 'O') << ", enter your move (row col): ";
                cin >> row >> col;
                row--; col--; // for zero-based indexing
            }
            if (checkWin()) {
                printBoard();
                cout << "Player " << (currentPlayer == Player::X ? 'X' : 'O') << " wins!\n";
                break;
            }
            if (boardFull()) {
                printBoard();
                cout << "It's a draw!\n";
                break;
            }
            switchPlayer();
            if (singlePlayer && currentPlayer == Player::O) {
                makeComputerMove();
                if (checkWin()) {
                    printBoard();
                    cout << "Computer wins!\n";
                    break;
                }
                switchPlayer();
            }
        }
    }

    void makeComputerMove() {
        cout << "Computer is making a move...\n";
        srand(time(0));
        int row, col;
        do {
            row = rand() % 3;
            col = rand() % 3;
        } while (!makeMove(row, col));
    }
};

int main() {
    cout << "Welcome to Tic-Tac-Toe!\n";
    cout << "Enter 1 for single player (against computer), 2 for two players: ";
    int choice;
    cin >> choice;
    bool singlePlayer = (choice == 1);
    TicTacToe game(singlePlayer);
    game.play();
    return 0;
}

