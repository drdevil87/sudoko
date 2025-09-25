#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

#define N 9

bool isSafe(const vector<vector<int>>& grid, int row, int col, int num) {
    // Check row and column in a single loop
    for (int x = 0; x < N; x++) {
        if (grid[row][x] == num || grid[x][col] == num) {
            return false;
        }
    }

    // Check 3x3 subgrid
    int startRow = (row / 3) * 3;
    int startCol = (col / 3) * 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (grid[startRow + i][startCol + j] == num) {
                return false;
            }
        }
    }

    return true;
}

bool findEmptyCell(const vector<vector<int>>& grid, int& row, int& col) {
    for (row = 0; row < N; row++) {
        for (col = 0; col < N; col++) {
            if (grid[row][col] == 0) {
                return true;
            }
        }
    }
    return false;
}

bool solveSudoku(vector<vector<int>>& grid) {
    int row, col;

    // If no empty cell is found, puzzle is solved
    if (!findEmptyCell(grid, row, col)) {
        return true;
    }

    for (int num = 1; num <= N; num++) {
        if (isSafe(grid, row, col, num)) {
            grid[row][col] = num;
            if (solveSudoku(grid)) {
                return true;
            }
            grid[row][col] = 0; // Backtrack only when recursive call fails
        }
    }

    return false;
}

void printGrid(const vector<vector<int>>& grid) {
    for (int r = 0; r < N; r++) {
        for (int d = 0; d < N; d++) {
            cout << grid[r][d] << " ";
        }
        cout << endl;
    }
}

vector<vector<int>> readGridFromFile(const string& filename) {
    vector<vector<int>> grid(N, vector<int>(N, 0));
    ifstream infile(filename);
    if (!infile.is_open()) {
        cerr << "Error: Could not open file " << filename << endl;
        return grid;
    }

    string line;
    int row = 0;
    while (getline(infile, line) && row < N) {
        stringstream ss(line);
        for (int col = 0; col < N; col++) {
            int val;
            if (ss >> val) {
                grid[row][col] = val;
            }
        }
        row++;
    }

    return grid;
}

void printHelp() {
    cout << "Sudoku Solver Help" << endl;
    cout << "Usage: sudoku_solver [testfile]" << endl;
    cout << "If no testfile is provided, a default puzzle is used." << endl;
    cout << "Example: ./sudoku_solver sudoku_test1.txt" << endl;
}

int main(int argc, char* argv[]) {
    if (argc > 1 && (string(argv[1]) == "--help" || string(argv[1]) == "-h")) {
        printHelp();
        return 0;
    }

    vector<vector<int>> grid;
    if (argc > 1) {
        cout << "Reading puzzle from file: " << argv[1] << endl;
        grid = readGridFromFile(argv[1]);
    } else {
        cout << "No input file provided. Using default puzzle." << endl;
        grid = {
            {3, 0, 6, 5, 0, 8, 4, 0, 0},
            {5, 2, 0, 0, 0, 0, 0, 0, 0},
            {0, 8, 7, 0, 0, 0, 0, 3, 1},
            {0, 0, 3, 0, 1, 0, 0, 8, 0},
            {9, 0, 0, 8, 6, 3, 0, 0, 5},
            {0, 5, 0, 0, 9, 0, 6, 0, 0},
            {1, 3, 0, 0, 0, 0, 2, 5, 0},
            {0, 0, 0, 0, 0, 0, 0, 7, 4},
            {0, 0, 5, 2, 0, 6, 3, 0, 0}
        };
    }
    if (solveSudoku(grid)) {
        cout << "Solved Sudoku:" << endl;
        printGrid(grid);
    } else {
        cout << "No solution exists" << endl;
    }
    return 0;
}
