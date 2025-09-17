@echo off
REM Build the Docker image
set IMAGE_NAME=sudoku_ubuntu24
set CONTAINER_NAME=sudoku_solver

if "%1"=="clean" (
    echo Cleaning executables...
    del /Q sudoku_solver
    exit /b
)

docker build -t %IMAGE_NAME% .devcontainer

docker run --rm -it --name %CONTAINER_NAME% -v "%cd%:/sudoku" %IMAGE_NAME%
