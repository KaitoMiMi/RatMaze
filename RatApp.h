#pragma once

#include "Board.h"

class CRatMazeApp : public CWinApp {
public:
    virtual BOOL InitInstance();
};

class CRatMazeWnd : public CFrameWnd {
public:
    CRatMazeWnd();
    afx_msg void OnPaint();
    afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
    DECLARE_MESSAGE_MAP()
private:
    void RestartGame();
    Board m_board;
    int m_ratX;
    int m_ratY;
};
