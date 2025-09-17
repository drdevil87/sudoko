@echo off
REM Build the Docker image
set IMAGE_NAME=sudoku_ubuntu24
set CONTAINER_NAME=sudoku_solver

if "%1"=="clean" (
    echo Cleaning executables...
    del /Q sudoku_solver
    exit /b
)

REM Check if image exists
set IMAGE_ID=
for /f "delims=" %%i in ('docker images -q %IMAGE_NAME%') do set IMAGE_ID=%%i

if defined IMAGE_ID (
    REM Image exists, skip build and message
) else (
    echo Building Docker image %IMAGE_NAME% ...
    docker build -t %IMAGE_NAME% .devcontainer
)

docker run --rm -it --name %CONTAINER_NAME% -v "%cd%:/sudoku" %IMAGE_NAME%
