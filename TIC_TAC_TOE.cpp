// TIC Tac Toe //


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
    int boardSize;

public:
    TicTacToe(bool singlePlayerMode) : currentPlayer(Player::X), singlePlayer(singlePlayerMode), boardSize(3) {
        // Initialize the board with the initial size (3x3)
        board = vector<vector<Player>>(boardSize, vector<Player>(boardSize, Player::EMPTY));
    }

    void printBoard() {
        cout << " ";
        for (int i = 0; i < boardSize; ++i) {
            cout << " " << i + 1;
        }
        cout << endl;

        for (int i = 0; i < boardSize; ++i) {
            cout << i + 1 << " ";
            for (int j = 0; j < boardSize; ++j) {
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
        if (row < 0 || row >= boardSize || col < 0 || col >= boardSize || board[row][col] != Player::EMPTY) {
            cout << "Invalid move! Try again.\n";
            return false;
        }
        board[row][col] = currentPlayer;
        return true;
    }

    // Function to count consecutive symbols in a specified row
    int countSymbolsInRow(int row, Player symbol) const {
        int count = 0;
        for (int col = 0; col < boardSize; ++col) {
            if (board[row][col] == symbol) {
                count++;
            }
        }
        return count;
    }

    // Function to count consecutive symbols in a specified column
    int countSymbolsInCol(int col, Player symbol) const {
        int count = 0;
        for (int row = 0; row < boardSize; ++row) {
            if (board[row][col] == symbol) {
                count++;
            }
        }
        return count;
    }

    // Function to count consecutive symbols in the main diagonal
    int countSymbolsInMainDiagonal(Player symbol) const {
        int count = 0;
        for (int i = 0; i < boardSize; ++i) {
            if (board[i][i] == symbol) {
                count++;
            }
        }
        return count;
    }

    // Function to count consecutive symbols in the anti-diagonal
    int countSymbolsInAntiDiagonal(Player symbol) const {
        int count = 0;
        for (int i = 0; i < boardSize; ++i) {
            if (board[i][boardSize - 1 - i] == symbol) {
                count++;
            }
        }
        return count;
    }

    // Function to check if a player has won (i.e., has enough consecutive symbols in a line)
    bool checkWin(Player player) const {
        Player symbol = (player == Player::X) ? Player::X : Player::O;

        // Check rows and columns
        for (int i = 0; i < boardSize; ++i) {
            if (countSymbolsInRow(i, symbol) == boardSize || countSymbolsInCol(i, symbol) == boardSize) {
                return true;
            }
        }

        // Check diagonals
        if (countSymbolsInMainDiagonal(symbol) == boardSize || countSymbolsInAntiDiagonal(symbol) == boardSize) {
            return true;
        }

        return false;
    }

    bool boardFull() {
        for (int i = 0; i < boardSize; ++i) {
            for (int j = 0; j < boardSize; ++j) {
                if (board[i][j] == Player::EMPTY)
                    return false;
            }
        }
        return true;
    }

    void switchPlayer() {
        currentPlayer = (currentPlayer == Player::X) ? Player::O : Player::X;
    }

    void resetBoard() {
        boardSize = boardSize + 1; // Increase board size for the next game
        board = vector<vector<Player>>(boardSize, vector<Player>(boardSize, Player::EMPTY));
    }

    void play() {
        bool playAgain = true;
        while (playAgain) {
            while (!checkWin(currentPlayer) && !boardFull()) {
                printBoard();
                int row, col;
                cout << "Player " << (currentPlayer == Player::X ? 'X' : 'O') << ", enter your move (row col): ";
                cin >> row >> col;
                row--; col--; // Adjust for zero-based indexing
                while (!makeMove(row, col)) {
                    cout << "Invalid move! Player " << (currentPlayer == Player::X ? 'X' : 'O') << ", enter your move (row col): ";
                    cin >> row >> col;
                    row--; col--; // Adjust for zero-based indexing
                }
                if (checkWin(currentPlayer)) {
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
                    if (checkWin(currentPlayer)) {
                        printBoard();
                        cout << "Computer wins!\n";
                        break;
                    }
                    switchPlayer();
                }
            }
            cout << "Do you want to play again? (1: Yes, 0: No): ";
            cin >> playAgain;
            if (playAgain) {
                resetBoard();
            }
        }
    }

    void makeComputerMove() {
        cout << "Computer is making a move...\n";
        srand(time(0));
        int row, col;
        do {
            row = rand() % boardSize;
            col = rand() % boardSize;
        } while (!makeMove(row, col));
    }
};

int main() {
    cout << "Welcome to Tic-Tac-Toe!\n";
    cout << "Select Gamemode: \n";
    cout << "Single Player (1) \n";
    cout << "Two Players (2) \n";
    cout << "Enter your choice: ";
    int choice;
    cin >> choice;
    bool singlePlayer = (choice == 1);

    TicTacToe game(singlePlayer);
    game.play();

    return 0;
}
