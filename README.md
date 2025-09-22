# sudoko

# Sudoku Solver Dev Container

This workspace launches a Docker container running Ubuntu 24.04 with GCC and C++ tools installed for compiling and running Sudoku solvers.

## How to Use

1. **Open in VS Code**
   - Use the "Remote - Containers" extension or "Dev Containers" to open this folder in a container.

2. **Build the Container**
   - VS Code will automatically build the container using `.devcontainer/Dockerfile`.

3. **Compile and Run the Solver**
   - Open a terminal in VS Code (inside the container).
   - Run:
     ```sh
     bash build_and_run.sh [testfile]
     ```
   - You can specify a test file (e.g., `sudoku_test1.txt`). If no file is given, the default puzzle is used.

4. **Run from Windows CMD or PowerShell**
   - You can also launch the Docker container directly by running the batch script:
     ```bat
     .\launch_container.bat
     ```
   - This works from either Command Prompt (CMD) or PowerShell.

## How the Sudoku Solver Algorithm Works

The provided C++ solver uses a **backtracking algorithm** to solve Sudoku puzzles:

1. **Find Empty Cell:**
   - The algorithm searches for the next empty cell (represented by 0).
2. **Try Numbers 1-9:**
   - For each empty cell, it tries numbers from 1 to 9.
3. **Check Validity:**
   - For each number, it checks if placing it in the cell is valid (no conflicts in the row, column, or 3x3 subgrid).
4. **Recursive Search:**
   - If a valid number is found, it is placed in the cell and the algorithm recursively attempts to solve the rest of the grid.
5. **Backtrack if Needed:**
   - If no valid number can be placed, the algorithm backtracks (removes the last number placed) and tries the next possibility.
6. **Solution Found:**
   - The process continues until the grid is completely filled or no solution exists.

This approach is efficient for standard Sudoku puzzles and guarantees a solution if one exists.

## Files
- `.devcontainer/Dockerfile`: Ubuntu 24.04 with GCC, g++
- `.devcontainer/devcontainer.json`: Dev Container configuration
- `sudoku_solver.cpp`: Example C++ Sudoku solver

## Requirements
- [VS Code](https://code.visualstudio.com/)
- [Dev Containers extension](https://marketplace.visualstudio.com/items?itemName=ms-vscode-remote.remote-containers)

