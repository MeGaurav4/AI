#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

#define N 8

// Function to print the chessboard
void printBoard(vector<int>& board) {
    cout << "\nSolution:\n";
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (board[i] == j)
                cout << "Q ";
            else
                cout << ". ";
        }
        cout << endl;
    }
    cout << endl;
}

// Check if placing queen at (row, col) is safe
bool isSafe(vector<int>& board, int row, int col) {
    // Check all previous rows
    for (int i = 0; i < row; i++) {
        // Same column check
        if (board[i] == col)
            return false;
        
        // Diagonal check
        if (abs(board[i] - col) == abs(i - row))
            return false;
    }
    return true;
}

// ============================================
// STRATEGY 1: BACKTRACKING (Most Efficient)
// ============================================
bool solveBacktracking(vector<int>& board, int row) {
    // Base case: All queens placed successfully
    if (row == N) {
        return true;
    }
    
    // Try placing queen in each column of current row
    for (int col = 0; col < N; col++) {
        if (isSafe(board, row, col)) {
            board[row] = col;  // Place queen
            
            // Recursively place remaining queens
            if (solveBacktracking(board, row + 1))
                return true;
            
            // Backtrack if placement doesn't lead to solution
            board[row] = -1;
        }
    }
    
    return false;  // No solution found
}

void nQueensBacktracking() {
    vector<int> board(N, -1);  // -1 means no queen placed
    
    cout << "\n========== BACKTRACKING APPROACH ==========\n";
    
    if (solveBacktracking(board, 0)) {
        printBoard(board);
        cout << "Solution found using Backtracking!\n";
    } else {
        cout << "No solution exists!\n";
    }
}

// ============================================
// STRATEGY 2: BRUTE FORCE
// ============================================
bool isValidConfiguration(vector<int>& board) {
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            // Check same column
            if (board[i] == board[j])
                return false;
            
            // Check diagonal
            if (abs(board[i] - board[j]) == abs(i - j))
                return false;
        }
    }
    return true;
}

void generatePermutation(vector<int>& board, int index, bool& found) {
    if (found) return;
    
    if (index == N) {
        if (isValidConfiguration(board)) {
            found = true;
        }
        return;
    }
    
    for (int i = 0; i < N; i++) {
        board[index] = i;
        generatePermutation(board, index + 1, found);
        if (found) return;
    }
}

void nQueensBruteForce() {
    vector<int> board(N, -1);
    bool found = false;
    
    cout << "\n========== BRUTE FORCE APPROACH ==========\n";
    cout << "(Note: This is slower - trying all combinations)\n";
    
    generatePermutation(board, 0, found);
    
    if (found) {
        printBoard(board);
        cout << "Solution found using Brute Force!\n";
    } else {
        cout << "No solution exists!\n";
    }
}

// ============================================
// STRATEGY 3: BRANCH AND BOUND
// ============================================
int solutionCount = 0;

void solveBranchAndBound(vector<int>& board, int row) {
    if (row == N) {
        solutionCount++;
        if (solutionCount == 1) {  // Print first solution
            printBoard(board);
        }
        return;
    }
    
    for (int col = 0; col < N; col++) {
        // Bound: Check if this branch can lead to solution
        if (isSafe(board, row, col)) {
            board[row] = col;
            solveBranchAndBound(board, row + 1);
            board[row] = -1;  // Backtrack
        }
        // Else: Prune this branch (bound condition)
    }
}

void nQueensBranchAndBound() {
    vector<int> board(N, -1);
    solutionCount = 0;
    
    cout << "\n========== BRANCH AND BOUND APPROACH ==========\n";
    
    solveBranchAndBound(board, 0);
    
    cout << "Total solutions found: " << solutionCount << endl;
}

// ============================================
// MAIN FUNCTION
// ============================================
int main() {
    int choice;
    
    cout << "======================================\n";
    cout << "   8-QUEENS PROBLEM SOLVER\n";
    cout << "======================================\n";
    cout << "\nSelect Search Strategy:\n";
    cout << "1. Backtracking (Recommended)\n";
    cout << "2. Brute Force\n";
    cout << "3. Branch and Bound (Find all solutions)\n";
    cout << "4. Run All Strategies\n";
    cout << "\nEnter your choice: ";
    cin >> choice;
    
    switch(choice) {
        case 1:
            nQueensBacktracking();
            break;
        case 2:
            nQueensBruteForce();
            break;
        case 3:
            nQueensBranchAndBound();
            break;
        case 4:
            nQueensBacktracking();
            nQueensBruteForce();
            nQueensBranchAndBound();
            break;
        default:
            cout << "Invalid choice!\n";
    }
    
    return 0;
}