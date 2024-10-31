#pragma once

#include <afxwin.h>

class Board {
public:
    Board();
    ~Board();
    void SetupBoard();
    COLORREF GetColor(int row, int col) const;
    int GetWidth() const { return m_nWidth; }
    int GetHeight() const { return m_nHeight; }
    int GetColumns() const { return m_nColumns; }
    int GetRows() const { return m_nRows; }
    int GetCell(int row, int col) const;
    void SetCell(int row, int col, int value);
    void DeleteBoard();

private:
    void CreateBoard();
    void GenerateMaze(int startX, int startY);

    int** m_arrBoard;
    COLORREF m_arrColors[4];
    int m_nColumns;
    int m_nRows;
    int m_nHeight;
    int m_nWidth;
};
