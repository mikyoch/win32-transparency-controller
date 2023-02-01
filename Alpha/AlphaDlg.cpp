
// AlphaDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "Alpha.h"
#include "AlphaDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define ALPHA_UP 1001
#define ALPHA_DOWN 1002
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


// CAlphaDlg dialog



CAlphaDlg::CAlphaDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ALPHA_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAlphaDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAlphaDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_HOTKEY()
END_MESSAGE_MAP()


// CAlphaDlg message handlers

BOOL CAlphaDlg::OnInitDialog()
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
	RegisterHotKey(GetSafeHwnd(), ALPHA_UP, MOD_ALT | MOD_WIN, VK_UP);
	RegisterHotKey(GetSafeHwnd(), ALPHA_DOWN, MOD_ALT | MOD_WIN, VK_DOWN);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CAlphaDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CAlphaDlg::OnPaint()
{
	ShowWindow(SW_HIDE);
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
HCURSOR CAlphaDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CAlphaDlg::OnHotKey(UINT nHotKeyId, UINT nKey1, UINT nKey2)
{
	CWnd* cWnd = GetForegroundWindow();
	SetWindowLong(cWnd->GetSafeHwnd(), GWL_EXSTYLE,
		GetWindowLong(cWnd->GetSafeHwnd(), GWL_EXSTYLE) | WS_EX_LAYERED);
	COLORREF pcrKey;
	BYTE pbAlpha;
	DWORD flags;
	int k = 1;
	BOOL ret = cWnd->GetLayeredWindowAttributes(&pcrKey, &pbAlpha, &flags);
	if (nHotKeyId == ALPHA_UP) {
		pbAlpha = pbAlpha + k > 255 ? 255 : pbAlpha + k;
	}
	else if (nHotKeyId == ALPHA_DOWN) {
		pbAlpha = pbAlpha - k < 0 ? 0 : pbAlpha - k;
	}
	cWnd->SetLayeredWindowAttributes(0, pbAlpha, LWA_ALPHA);
	CDialogEx::OnHotKey(nHotKeyId, nKey1, nKey2);
}
