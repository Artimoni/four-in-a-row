#include <iostream>
#include <locale>
using namespace std;

const int ROWS = 6; 
const int COLS = 7; 
const char EMPTY = '.'; 
const char PLAYER1 = '1'; 
const char PLAYER2 = '2'; 

void initialize(char board[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            board[i][j] = EMPTY; //Создание поля и его заполнение пустыми клетками
        }
    }
}

void printBoard(char board[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            cout << board[i][j] << " "; //Вывод поля с строками
        }
        cout << endl;
    }
    for (int j = 0; j < COLS; j++) {
        cout << j + 1 << " "; //Нумерация столбцов
    }
    cout << endl; 
}

bool dropPiece(char board[ROWS][COLS], int col, char player) { //Фишки  в столбце
    if (col < 0 || col >= COLS) {
        return false; //Проверка на правильное расположение фишки
    }

    for (int row = ROWS - 1; row >= 0; row--) {
        if (board[row][col] == EMPTY) {
            board[row][col] = player; 
            return true; //Поиск свободной клетки и размещение
        }
    }
    return false;
}

bool checkWin(char board[ROWS][COLS], char player) { //Проверка победы
    for (int row = 0; row < ROWS; row++) {
        for (int col = 0; col < COLS - 3; col++) {
            if (board[row][col] == player &&
                board[row][col + 1] == player &&
                board[row][col + 2] == player &&
                board[row][col + 3] == player) {
                return true; //Горизонталь
            }
        }
    }
    for (int col = 0; col < COLS; col++) {
        for (int row = 0; row < ROWS - 3; row++) {
            if (board[row][col] == player &&
                board[row + 1][col] == player &&
                board[row + 2][col] == player &&
                board[row + 3][col] == player) {
                return true; //Вертикаль
            }
        }
    }
    //25.02
    for (int row = 0; row < ROWS - 3; row++) {
        for (int col = 0; col < COLS - 3; col++) {
            if (board[row][col] == player &&
                board[row + 1][col + 1] == player &&
                board[row + 2][col + 2] == player &&
                board[row + 3][col + 3] == player) {
                return true;
            }
        }
        for (int col = 3; col < COLS; col++) {
            if (board[row][col] == player &&
                board[row + 1][col - 1] == player &&
                board[row + 2][col - 2] == player &&
                board[row + 3][col - 3] == player) {
                return true; //Проверка по диагонали
            }
        }
    }
    return false; 
}
bool checkDraw(char board[ROWS][COLS]) {
    for (int col = 0; col < COLS; col++) {
        if (board[0][col] == EMPTY) {
            return false; //Проверка на пустоту верхней строки
        }
    }
    return true; //Если строка заполнена - ничья
}

//27.02
int main() {
    setlocale(LC_ALL, "Russian");
    char board[ROWS][COLS]; 
    initialize(board); 
    char currentPlayer = PLAYER1; 
    bool gameOver = false; 
    cout << "4 в ряд\n";

    while (!gameOver) {
        printBoard(board); 
        cout << "Игрок " << currentPlayer << ", ваш ход (1-" << COLS << "): ";
        int col;
        cin >> col;
        col--; //Преобразование в индекс массива

        if (col < 0 || col >= COLS || !dropPiece(board, col, currentPlayer)) {
            cout << "Ход невозможен\n";
            continue; //Введенное значение не может быть отрицательным, а так же больше чем кол-во столбцов
        }
        if (checkWin(board, currentPlayer)) { //Проверка на победу
            printBoard(board);
            cout << "Игрок " << currentPlayer << " выиграл\n";
            gameOver = true;
        }
        else if (checkDraw(board)) {
            printBoard(board); 
            cout << "Ничья\n"; 
            gameOver = true;
        }

        if (currentPlayer == PLAYER1) {
            currentPlayer = PLAYER2;
        }
        else {
            currentPlayer = PLAYER1; //Смена сторон
        }
    }

    return 0;
}