#include "pch.h"
#include "Board.h"
#include <cstdlib>
#include <ctime>
#include <stack>
#include <algorithm>
#include <vector>

Board::Board() {
    m_nColumns = 20;
    m_nRows = 20;
    m_nHeight = 400;
    m_nWidth = 400;
    m_arrColors[0] = RGB(0, 0, 0); // Фон
    m_arrColors[1] = RGB(255, 0, 0); // Крыса
    m_arrColors[2] = RGB(255, 255, 0); // Сыр (финиш)
    m_arrColors[3] = RGB(0, 0, 255); // Стены
    m_arrBoard = nullptr; // указатель ноль
    CreateBoard();
}

Board::~Board() {
    DeleteBoard();
}

void Board::CreateBoard() {
    // Убедимся, что старый массив удален
    DeleteBoard();

    // Инициализация массива
    m_arrBoard = new int* [m_nRows];
    for (int i = 0; i < m_nRows; ++i) {
        m_arrBoard[i] = new int[m_nColumns];
        for (int j = 0; j < m_nColumns; ++j) {
            m_arrBoard[i][j] = 3; // Изначально все клетки - стены
        }
    }

    // Генерация лабиринта
    GenerateMaze(1, 1);

    // Разместим крысу и сыр
    m_arrBoard[1][1] = 1; // Крыса
    m_arrBoard[m_nRows - 3][m_nColumns - 3] = 2; // Сыр на одну клетку вверх и влево от нижнего правого угла
}

void Board::GenerateMaze(int startX, int startY) {
    std::stack<std::pair<int, int>> stack;
    stack.push({ startX, startY });
    m_arrBoard[startY][startX] = 0; // Начальная точка - пустое место

    while (!stack.empty()) {
        int x = stack.top().first;
        int y = stack.top().second;
        stack.pop();

        // Создаем массив направлений и перемешиваем его
        std::vector<std::pair<int, int>> directions = { {0, -2}, {2, 0}, {0, 2}, {-2, 0} };
        std::random_shuffle(directions.begin(), directions.end());

        for (auto& dir : directions) {
            int nx = x + dir.first;
            int ny = y + dir.second;

            if (nx > 0 && nx < m_nColumns - 1 && ny > 0 && ny < m_nRows - 1 && m_arrBoard[ny][nx] == 3) {
                if (m_arrBoard[ny - dir.second / 2][nx - dir.first / 2] == 3) {
                    m_arrBoard[ny][nx] = 0;
                    m_arrBoard[ny - dir.second / 2][nx - dir.first / 2] = 0;
                    stack.push({ nx, ny });
                }
            }
        }
    }
}

void Board::DeleteBoard() {
    if (m_arrBoard != nullptr) {
        for (int i = 0; i < m_nRows; ++i) {
            delete[] m_arrBoard[i];
        }
        delete[] m_arrBoard;
        m_arrBoard = nullptr; // Устанавливаем указатель в nullptr после удаления
    }
}

COLORREF Board::GetColor(int row, int col) const {
    if (row >= 0 && row < m_nRows && col >= 0 && col < m_nColumns) {
        return m_arrColors[m_arrBoard[row][col]];
    }
    return RGB(0, 0, 0); // Возвращаем черный цвет, если индексы не валидны
}

void Board::SetupBoard() {
    srand((unsigned)time(NULL));
    DeleteBoard();
    CreateBoard();
}

int Board::GetCell(int row, int col) const {
    if (row >= 0 && row < m_nRows && col >= 0 && col < m_nColumns) {
        return m_arrBoard[row][col];
    }
    return -1; // Возвращаем -1, если индексы не валидны
}

void Board::SetCell(int row, int col, int value) {
    if (row >= 0 && row < m_nRows && col >= 0 && col < m_nColumns) {
        m_arrBoard[row][col] = value;
    }
}
