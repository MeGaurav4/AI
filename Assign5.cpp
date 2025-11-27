#include <iostream>
#include <vector>
#include <climits>
using namespace std;

// Constants for players
const char HUMAN = 'O';
const char AI = 'X';

// Function to display the board
void displayBoard(vector<vector<char>>& board) {
    cout << "\n";
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << " " << board[i][j];
            if (j < 2) cout << " |";
        }
        cout << "\n";
        if (i < 2) cout << "---|---|---\n";
    }
    cout << "\n";
}

// Check if there are any moves left
bool isMovesLeft(vector<vector<char>>& board) {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] == '_')
                return true;
    return false;
}

// Evaluate the board and return score
int evaluate(vector<vector<char>>& board) {
    // Check rows for victory
    for (int row = 0; row < 3; row++) {
        if (board[row][0] == board[row][1] && 
            board[row][1] == board[row][2]) {
            if (board[row][0] == AI)
                return +10;
            else if (board[row][0] == HUMAN)
                return -10;
        }
    }

    // Check columns for victory
    for (int col = 0; col < 3; col++) {
        if (board[0][col] == board[1][col] && 
            board[1][col] == board[2][col]) {
            if (board[0][col] == AI)
                return +10;
            else if (board[0][col] == HUMAN)
                return -10;
        }
    }

    // Check diagonals for victory
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
        if (board[0][0] == AI)
            return +10;
        else if (board[0][0] == HUMAN)
            return -10;
    }

    if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
        if (board[0][2] == AI)
            return +10;
        else if (board[0][2] == HUMAN)
            return -10;
    }

    // No winner yet
    return 0;
}

// MinMax Algorithm Implementation
int minimax(vector<vector<char>>& board, int depth, bool isMax) {
    int score = evaluate(board);

    // If AI has won, return positive score
    if (score == 10)
        return score - depth;

    // If Human has won, return negative score
    if (score == -10)
        return score + depth;

    // If no moves left, it's a tie
    if (!isMovesLeft(board))
        return 0;

    // Maximizer's move (AI)
    if (isMax) {
        int best = INT_MIN;

        // Traverse all cells
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                // Check if cell is empty
                if (board[i][j] == '_') {
                    // Make the move
                    board[i][j] = AI;

                    // Recursively call minimax for minimizer
                    best = max(best, minimax(board, depth + 1, !isMax));

                    // Undo the move
                    board[i][j] = '_';
                }
            }
        }
        return best;
    }
    // Minimizer's move (Human)
    else {
        int best = INT_MAX;

        // Traverse all cells
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                // Check if cell is empty
                if (board[i][j] == '_') {
                    // Make the move
                    board[i][j] = HUMAN;

                    // Recursively call minimax for maximizer
                    best = min(best, minimax(board, depth + 1, !isMax));

                    // Undo the move
                    board[i][j] = '_';
                }
            }
        }
        return best;
    }
}

// Find the best move for AI
pair<int, int> findBestMove(vector<vector<char>>& board) {
    int bestVal = INT_MIN;
    pair<int, int> bestMove = {-1, -1};

    // Traverse all cells
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            // Check if cell is empty
            if (board[i][j] == '_') {
                // Make the move
                board[i][j] = AI;

                // Compute evaluation function for this move
                int moveVal = minimax(board, 0, false);

                // Undo the move
                board[i][j] = '_';

                // Update best move if current move is better
                if (moveVal > bestVal) {
                    bestMove = {i, j};
                    bestVal = moveVal;
                }
            }
        }
    }

    cout << "AI chose position: (" << bestMove.first << ", " 
         << bestMove.second << ") with value: " << bestVal << "\n";
    return bestMove;
}

// Check if game is over
bool isGameOver(vector<vector<char>>& board) {
    return (evaluate(board) != 0 || !isMovesLeft(board));
}

// Main function
int main() {
    vector<vector<char>> board = {
        {'_', '_', '_'},
        {'_', '_', '_'},
        {'_', '_', '_'}
    };

    cout << "=== Tic-Tac-Toe with MinMax Algorithm ===\n";
    cout << "You are O, AI is X\n";
    cout << "Enter row and column (0-2) to make a move\n";

    displayBoard(board);

    while (!isGameOver(board)) {
        // Human's turn
        int row, col;
        cout << "Your move (row col): ";
        cin >> row >> col;

        if (row < 0 || row > 2 || col < 0 || col > 2 || 
            board[row][col] != '_') {
            cout << "Invalid move! Try again.\n";
            continue;
        }

        board[row][col] = HUMAN;
        displayBoard(board);

        if (isGameOver(board))
            break;

        // AI's turn
        cout << "AI is thinking...\n";
        pair<int, int> aiMove = findBestMove(board);
        board[aiMove.first][aiMove.second] = AI;
        displayBoard(board);
    }

    // Game result
    int result = evaluate(board);
    if (result == 10)
        cout << "AI Wins!\n";
    else if (result == -10)
        cout << "You Win!\n";
    else
        cout << "It's a Draw!\n";

    return 0;
}