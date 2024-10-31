#include "pch.h"
#include "RatApp.h"

BEGIN_MESSAGE_MAP(CRatMazeWnd, CFrameWnd)
    ON_WM_PAINT()
    ON_WM_KEYDOWN()
END_MESSAGE_MAP()

CRatMazeApp theApp;

BOOL CRatMazeApp::InitInstance() {
    m_pMainWnd = new CRatMazeWnd();
    m_pMainWnd->ShowWindow(m_nCmdShow);
    m_pMainWnd->UpdateWindow();
    return TRUE;
}

CRatMazeWnd::CRatMazeWnd() {
    Create(NULL, _T("Rat Maze Game"));
    m_board.SetupBoard();
    m_ratX = 1;
    m_ratY = 1;
}

void CRatMazeWnd::OnPaint() {
    CPaintDC dc(this);
    for (int i = 0; i < m_board.GetRows(); ++i) {
        for (int j = 0; j < m_board.GetColumns(); ++j) {
            CBrush brush(m_board.GetColor(i, j));
            dc.FillRect(CRect(j * 20, i * 20, (j + 1) * 20, (i + 1) * 20), &brush);
        }
    }
}

void CRatMazeWnd::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
    int newX = m_ratX;
    int newY = m_ratY;
    switch (nChar) {
    case VK_LEFT: newX--; break;
    case VK_RIGHT: newX++; break;
    case VK_UP: newY--; break;
    case VK_DOWN: newY++; break;
    }
    if (newX >= 0 && newX < m_board.GetColumns() && newY >= 0 && newY < m_board.GetRows() &&
        m_board.GetCell(newY, newX) != 3) { // Проверка, что новая клетка не стена
        m_board.SetCell(m_ratY, m_ratX, 0); // Сброс предыдущей позиции крысы
        m_ratX = newX;
        m_ratY = newY;
        if (m_board.GetCell(m_ratY, m_ratX) == 2) { // Проверка, достигла ли крыса сыра
            RestartGame();
        }
        else {
            m_board.SetCell(m_ratY, m_ratX, 1); // Установка новой позиции крысы
            Invalidate();
        }
    }
}

void CRatMazeWnd::RestartGame() {
    m_board.SetupBoard();
    m_ratX = 1;
    m_ratY = 1;
    Invalidate(); // Перерисовка окна
}
