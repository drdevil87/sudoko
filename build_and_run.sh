#!/bin/bash
# Clean option to remove executables
if [[ "$1" == "clean" ]]; then
    echo "Cleaning executables..."
    rm -f sudoku_solver *.exe
    exit 0
fi
# Build the Sudoku solver
if g++ sudoku_solver.cpp -o sudoku_solver; then
    echo "Build successful."
    echo "Launching Sudoku solver..."
    ./sudoku_solver "$@"
else
    echo "Build failed."
    exit 1
fi
