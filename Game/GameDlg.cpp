
// GameDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "Game.h"
#include "GameDlg.h"
#include "afxdialogex.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CGameDlg dialog



CGameDlg::CGameDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GAME_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CGameDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CGameDlg::OnBnClickedButton1)
	ON_WM_TIMER()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


// CGameDlg message handlers

BOOL CGameDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CGameDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CGameDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CGameDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CGameDlg::Circle(int cx,int cy,int r,int C,int F)
{
	// 1.設定色筆
	CPen P1(PS_SOLID, 1, RGB((C >> 16) & 0xFF, (C >> 8) & 0xFF, (C >> 0) & 0xFF));
	SelectObject(hdc, P1);

	// 3.畫圓
	int   x, y;
	int   i;    // 角度
	float i1; // 徑度
	for (i = 0; i <= 360; i++)
	{
		i1 = (float)i * 3.14159 / 180;
		x = cx + r * cos(i1);
		y = cy + r * sin(i1);
		if (F == 0) // 空心
		{
			if (i == 0) MoveToEx(hdc, x, y, 0);
			LineTo(hdc, x, y);
		}
		else // 實心
		{
			MoveToEx(hdc, cx, cy, 0);
			LineTo(hdc, x, y);
		}
	}
}
void CGameDlg::Rect(int x1,int y1,int x2,int y2,int C,int F)
{
	// 設定色筆
	CPen P1(PS_SOLID, 1, RGB((C >> 16) & 0xFF, (C >> 8) & 0xFF, (C >> 0) & 0xFF));
	SelectObject(hdc, P1);
	if (F == 0) // 空心
	{
		// 畫矩形
		MoveToEx(hdc, x1, y1, 0);
		LineTo(hdc, x1, y2);
		LineTo(hdc, x2, y2);
		LineTo(hdc, x2, y1);
		LineTo(hdc, x1, y1);
	}
	else // 實心
	{
		for (int y = y1; y <= y2; y++)
		{
			MoveToEx(hdc, x1, y, 0); LineTo(hdc, x2, y);
		}
	}
}

// 練習一: 打磚塊遊戲設計
void CGameDlg::OnBnClickedButton1() // 開始遊戲
{
	// 0.初始化
	hdc = ::GetDC(m_hWnd); // 取得畫圖用之視窗代碼
	SetWindowText("Game: Designed by HSF");

	// 1.繪出打磚塊遊戲框
	Rect(0, 0, W, H, 0x0, 0);
		
	// 2.移動球初始化
	SetTimer(5566, 1, 0); // 每100ms處理球移動(代號:5566)
	for (int i = 0; i < BN; i++)
	{
		bx[i] = W / 2; // 球心x軸
		by[i] = H / 2; // 球心y軸
		br[i] = 15;     // 求半徑
		bc[i] = rand()+(rand()<<12); // 球顏色
		bdx[i] = (rand()%16)-8;    // 球移動x向量  
		bdy[i] = (rand()%20)-10;   // 球移動y向量
	}
	// 3.接球平台，處理滑鼠控制
	mw = 150;      // 接球平台寬
	mh = 20;       // 接球平台高
	mx = W / 2;    // 接球平台左上角x座標
	my = H - mh-3; // 接球平台左上角y座標
	mc = 0x502211; // 接球平台顏色
	LBD_F = 0;     // 滑鼠未按下
	Rect(mx, my, mx + mw, my + mh, mc, 1);

	// 4.繪出磚塊
	int k = (W-10) / WN; // 磚塊最大寬度
	for (int y = 0; y < HN; y++)
	for (int x = 0; x < WN; x++)
	{
		// 左上座標
		Data[y][x][0] = 5 + x * k;
		Data[y][x][1] = 10 + y * 25;
		// 右下座標,磚塊(寬,高)=(k-3,20)
		Data[y][x][2] = Data[y][x][0]+k-3;
		Data[y][x][3] = Data[y][x][1]+20;
		// 顏色 R:G:B
		Data[y][x][4] = rand() +(rand() << 12);
		// 狀態: 0:消失, 1:出現, 2:往下掉
		Data[y][x][5] = 1; 
		// 繪出磚塊
		Rect(Data[y][x][0], Data[y][x][1], Data[y][x][2], Data[y][x][3], Data[y][x][4], 1);
	}
	SetTimer(3388, 500, 0); // 0.5秒處理磚塊掉下

	// 5.處理磚塊被打程序
}
#include "mmsystem.h"
#pragma comment(lib,"winmm.lib")
void CGameDlg::Check_Block() // 檢查是否打到磚塊
{
	int k;
	for (int y = HN-1; y >= 0; y--) // 從下層檢查到上層
	for (int x = 0;    x < WN; x++) // 從左到右
	{
		if (Data[y][x][5] >= 1) // 磚塊存在(1,2)才打
		{
			for (int i = 0; i < BN; i++)
			{
				// Case-1: 往下打
				// bdy>0, 往下走, 檢查磚塊上緣
				// 檢查球下緣之y座標by+br是否已經進入磚塊上緣y座標Data[y][x][1]
				//.....

				// Case-2: 往左打

				// Case-3: 往右打

				// Case-4: 往上打
				// bdy<0, 往上走, 檢查磚塊下緣
				// 檢查球上緣之y座標by-br是否已經進入磚塊下緣y座標Data[y][x][3]
				if ((by[i] - br[i]) <= Data[y][x][3])
				{
					// 檢查球之x座標是否已經落在方塊範圍[0]~[2]
					if ((bx[i] > Data[y][x][0]) && (bx[i] < Data[y][x][2]))
					{
						if (Data[y][x][5] == 1) // 1-> 2或0
						{
							if ((rand() % 5) == 0) Data[y][x][5] = 2; // 五顆隨機選一顆磚塊往下掉
							else
							{
								Data[y][x][5] = 0; // 磚塊消失=0 塗銷磚塊，
								Rect(Data[y][x][0], Data[y][x][1], Data[y][x][2], Data[y][x][3], 0xF0F0F0, 1);
							}
						}
						bdy[i] *= -1; // 球反彈
						PlaySound("KbdKeyTap.wav", 0, SND_ASYNC);
					}
				}
			}
		}
	}
}

void CGameDlg::Check_Loss()
{
	for (int i = 0; i < BN; i++)
	{
		if ((by[i] + br[i]) >= my) // 球心y座標必須碰觸到平台my
		{
			// D1.球心x座標需落在 mx~mx + mw之間,
			if ((bx[i] >= mx) && (bx[i] <= (mx + mw)))
			{
				bdy[i] *= -1; // 繼續且球y座標反轉
				by[i] = my - br[i] - 1; // 修正球位置，避免打凹平台
				PlaySound("KbdKeyTap.wav", 0, SND_ASYNC);
			}
			else
			{
				//KillTimer(5566); // 停止球移動
				SetWindowText("You Loss");
				PlaySound("KbdKeyTap.wav", 0, SND_ASYNC);
			}
		}
	}
}

void CGameDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	if (nIDEvent == 3388) // 每 0.5秒處理磚塊掉下
	{
		for (int y = HN - 1; y >= 0; y--) // 從下層檢查到上層
		for (int x = 0; x < WN; x++) // 從左到右
		{
			if (Data[y][x][5] == 2) // 磚塊(2)才移動
			{
				// 塗銷舊磚塊
				Rect(Data[y][x][0], Data[y][x][1], Data[y][x][2], Data[y][x][3], 0xF0F0F0, 1);
				// 往下移, y+=4;
				Data[y][x][1] += 4;
				Data[y][x][3] += 4;
				// 畫新磚塊
				Rect(Data[y][x][0], Data[y][x][1], Data[y][x][2], Data[y][x][3], Data[y][x][4], 1);
			}
		}
	}
	else if (nIDEvent == 5566) // 每100ms處理球移動
	{
		for (int i = 0; i < BN; i++)
		{
			// A.塗銷舊球
			Circle(bx[i], by[i], br[i], 0xF0F0F0, 1);
			// B.移動球座標
			bx[i] += bdx[i];
			by[i] += bdy[i];
			// C.修正球心座標
			if ((by[i] - br[i]) <= 1) { by[i] = br[i] + 1;     bdy[i] *= -1; }
			if ((by[i] + br[i]) >= H) { by[i] = H - br[i] - 1; bdy[i] *= -1; }
			if ((bx[i] - br[i]) <= 1) { bx[i] = br[i] + 1;     bdx[i] *= -1; }
			if ((bx[i] + br[i]) >= W) { bx[i] = W - br[i] - 1; bdx[i] *= -1; }
			// B1.判斷球是否打到磚塊
			Check_Block();
			// D.判斷是否有接到球	
			Check_Loss();
			// E.繪出新球
			Circle(bx[i], by[i], br[i], bc[i], 1);
			// G.呼叫滑鼠移動函式(自動玩)
			CPoint point;
			UINT   nFlag = 0;
			point.x = bx[i];
			LBD_F = 1;
			if ((bdy[i]>0)&&((by[i]+br[i]+20)>=my))	OnMouseMove(nFlag, point);
		}
	}
	CDialogEx::OnTimer(nIDEvent);
}


void CGameDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	LBD_F = 1;
	CDialogEx::OnLButtonDown(nFlags, point);
}


void CGameDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	LBD_F = 0;
	CDialogEx::OnLButtonUp(nFlags, point);
}


void CGameDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (LBD_F == 1)
	{
		// 塗銷舊平台
		Rect(mx, my, mx + mw, my + mh, 0xF0F0F0, 1);
		// 移動平台座標
		mx = point.x - mw / 2;
		// 修正移動平台座標
		if      (mx <= 2) mx = 2; 
		else if ((mx + mw) >= (W - 2)) mx = W - 2 - mw;
		// 繪出新平台
		Rect(mx, my, mx + mw, my + mh, mc, 1);
	}
	CDialogEx::OnMouseMove(nFlags, point);
}
