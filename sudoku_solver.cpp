#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <csdtint>
using namespace std;

#define N 9

bool isSafe(const vector<vector<uint8_t>>& grid, const uint8_t &row, const uint8_t& col, const uint8_t& num) {
    // Check row and column in a single loop
    for (uint8_t x = 0; x < N; x++) {
        if (grid[row][x] == num || grid[x][col] == num) {
            return false;
        }
    }

    // Check 3x3 subgrid
    const uint8_t startRow = (row / 3) * 3;
    const uint8_t startCol = (col / 3) * 3;
    for (uint8_t i = 0; i < 3; i++) {
        for (uint8_t j = 0; j < 3; j++) {
            if (grid[startRow + i][startCol + j] == num) {
                return false;
            }
        }
    }

    return true;
}

bool solveSudoku(vector<vector<uint8_t>>& grid, const uint8_t& pos) {
    // Base case: if we've filled all 81 cells (0-80), puzzle is solved
    if (pos == N * N) {
        return true;
    }

    const uint8_t row = pos / N;
    const uint8_t col = pos % N;

    // If current cell is already filled, move to next cell
    if (grid[row][col] != 0) {
        return solveSudoku(grid, pos + 1);
    }

    // Try numbers 1-9 for empty cell
    for (uint8_t num = 1; num <= N; num++) {
        if (isSafe(grid, row, col, num)) {
            grid[row][col] = num;
            if (solveSudoku(grid, pos + 1)) {
                return true;
            }
            grid[row][col] = 0; // Backtrack only when recursive call fails
        }
    }

    return false;
}

// Wrapper function for easier calling
bool solveSudoku(vector<vector<uint8_t>>& grid) {
    return solveSudoku(grid, 0);
}

bool hasEmptyCell(const vector<vector<uint8_t>>& grid) {
    for (uint8_t row = 0; row < N; row++) {
        for (uint8_t col = 0; col < N; col++) {
            if (grid[row][col] == 0) {
                return true;
            }
        }
    }
    return false;
}

void printGrid(const vector<vector<uint8_t>>& grid) {
    for (uint8_t r = 0; r < N; r++) {
        for (uint8_t d = 0; d < N; d++) {
            cout << (int)grid[r][d] << " ";
        }
        cout << endl;
    }
}

vector<vector<uint8_t>> readGridFromFile(const string& filename) {
    vector<vector<uint8_t>> grid(N, vector<uint8_t>(N, 0));
    ifstream infile(filename);
    if (!infile.is_open()) {
        cerr << "Error: Could not open file " << filename << endl;
        return grid;
    }

    string line;
    uint8_t row = 0;
    while (getline(infile, line) && row < N) {
        stringstream ss(line);
        for (uint8_t col = 0; col < N; col++) {
            int val;
            if (ss >> val) {
                grid[row][col] = (uint8_t)val;
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

    vector<vector<uint8_t>> grid;
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
    // If no empty cell is found, puzzle is solved
    if (!hasEmptyCell(grid)) {
        cout << "The puzzle is already solved." << endl;
        printGrid(grid);
        return 0;
    }

    if (solveSudoku(grid)) {
        cout << "Solved Sudoku:" << endl;
        printGrid(grid);
    } else {
        cout << "No solution exists" << endl;
    }
    return 0;
}
