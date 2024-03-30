
// GameDlg.h : header file
//

#pragma once

#define  W   675  // 遊戲框的寬度
#define  H   770  // 遊戲框的高度
#define  WN  8    // 每層磚塊數
#define  HN  6    // 磚塊層數
#define  BN  3    // 球數量

// CGameDlg dialog
class CGameDlg : public CDialogEx
{
// Construction
public:
	CGameDlg(CWnd* pParent = nullptr);	// standard constructor

	// 成員變數 & 函式
	HDC  hdc; // 繪圖用
	int bx[BN], by[BN], br[BN], bc[BN], bdx[BN], bdy[BN]; // 球參數
	int mx, my, mw, mh, mc, LBD_F;       // 接球平台參數
	int Data[HN][WN][6]; // 紀錄磚塊參數, 0~1: 磚塊左上座標, 2~3:磚塊右下座標, 4:顏色, 5:狀態

	void Circle(int cx, int cy, int r, int C, int F);	
	void Rect(int x1, int y1, int x2, int y2, int C, int F);
	void Check_Block(); // 判斷是否打到磚塊
	void Check_Loss();  // 判斷是否接到球

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GAME_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};
