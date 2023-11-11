#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ROWS 20
#define COLS 20

// Функция для печати доски
void printBoard(char board[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) { // проходим по каждой строке
        for (int j = 0; j < COLS; j++) { // проходим по каждому столбцу
            printf("|%c", board[i][j] ? '^' : ' ');
        }
        printf("|\n");
    }

}

int countNeighbors(char board[ROWS][COLS], int x, int y) {
    int count = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0) {
                continue;
            }
            int newX = x + i;
            int newY = y + j;
            if (newX >= 0 && newX < ROWS && newY >= 0 && newY < COLS && board[newX][newY]) {
                count++;
            }
        }
    }
    return count;
}

void updateBoard(char board[ROWS][COLS]) {
    char newBoard[ROWS][COLS];
    int allEmpty = 1; // Флаг, который показывает, что все клетки пустые
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            int neighbors = countNeighbors(board, i, j);
            if (board[i][j]) {
                newBoard[i][j] = (neighbors == 2 || neighbors == 3);
                allEmpty = 0; // Если есть хотя бы одна непустая клетка, сбросить флаг
            }
            else {
                newBoard[i][j] = (neighbors == 3);
            }
        }
    }
    if (allEmpty) {
        printf("All cells are empty. Stopping the simulation.\n");
        exit(0); // Остановка выполнения программы
    }
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            board[i][j] = newBoard[i][j];
        }
    }
}

void fillRandomFirstRow(char board[ROWS][COLS]) {
    for (int j = 0; j < COLS; j++) {
        board[0][j] = rand() % 2;
    }
}

int main() {
    char board[ROWS][COLS];
    srand(time(0)); // Инициализация генератора случайных чисел
    fillRandomFirstRow(board);
    for (int i = 1; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            board[i][j] = 0;
        }
    }

    for (int generation = 0; generation < 10; generation++) {
        printf("Generation %d:\n", generation);
        printBoard(board);
        updateBoard(board);
    }

    return 0;
}