// 20200616-MFCApplicationDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "20200616-MFCApplication.h"
#include "20200616-MFCApplicationDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx {
public:
    CAboutDlg();

    // 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
    virtual void DoDataExchange(CDataExchange* pDX); // DDX/DDV 支持

    // 实现
protected:
DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX) {}

void CAboutDlg::DoDataExchange(CDataExchange* pDX) { CDialogEx::DoDataExchange(pDX); }

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMy20200616MFCApplicationDlg 对话框


CMy20200616MFCApplicationDlg::CMy20200616MFCApplicationDlg(CWnd* pParent /*=NULL*/)
    : CDialogEx(IDD_MY20200616MFCAPPLICATION_DIALOG, pParent), m_opera(0) {
    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMy20200616MFCApplicationDlg::DoDataExchange(CDataExchange* pDX) {
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EDIT1, m_editIn1);
    DDX_Control(pDX, IDC_EDIT2, m_editIn2);
    DDX_Control(pDX, IDC_EDIT3, m_editOut);
}

BEGIN_MESSAGE_MAP(CMy20200616MFCApplicationDlg, CDialogEx)
    ON_WM_SYSCOMMAND()
    ON_WM_PAINT()
    ON_WM_QUERYDRAGICON()
    ON_BN_CLICKED(IDC_BUTTON1, &CMy20200616MFCApplicationDlg::OnBnClickedButton1)
    ON_BN_CLICKED(IDC_RADIO1, &CMy20200616MFCApplicationDlg::OnBnClickedRadio1)
    ON_BN_CLICKED(IDC_RADIO2, &CMy20200616MFCApplicationDlg::OnBnClickedRadio2)
    ON_BN_CLICKED(IDC_RADIO3, &CMy20200616MFCApplicationDlg::OnBnClickedRadio3)
    ON_BN_CLICKED(IDC_RADIO4, &CMy20200616MFCApplicationDlg::OnBnClickedRadio4)
END_MESSAGE_MAP()


// CMy20200616MFCApplicationDlg 消息处理程序

BOOL CMy20200616MFCApplicationDlg::OnInitDialog() {
    CDialogEx::OnInitDialog();

    // 将“关于...”菜单项添加到系统菜单中。

    // IDM_ABOUTBOX 必须在系统命令范围内。
    ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
    ASSERT(IDM_ABOUTBOX < 0xF000);

    CMenu* pSysMenu = GetSystemMenu(FALSE);
    if (pSysMenu != NULL) {
        BOOL bNameValid;
        CString strAboutMenu;
        bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
        ASSERT(bNameValid);
        if (!strAboutMenu.IsEmpty()) {
            pSysMenu->AppendMenu(MF_SEPARATOR);
            pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
        }
    }

    // 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
    //  执行此操作
    SetIcon(m_hIcon, TRUE); // 设置大图标
    SetIcon(m_hIcon, FALSE); // 设置小图标

    // TODO: 在此添加额外的初始化代码

    return TRUE; // 除非将焦点设置到控件，否则返回 TRUE
}

void CMy20200616MFCApplicationDlg::OnSysCommand(UINT nID, LPARAM lParam) {
    if ((nID & 0xFFF0) == IDM_ABOUTBOX) {
        CAboutDlg dlgAbout;
        dlgAbout.DoModal();
    }
    else { CDialogEx::OnSysCommand(nID, lParam); }
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMy20200616MFCApplicationDlg::OnPaint() {
    if (IsIconic()) {
        CPaintDC dc(this); // 用于绘制的设备上下文

        SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

        // 使图标在工作区矩形中居中
        int cxIcon = GetSystemMetrics(SM_CXICON);
        int cyIcon = GetSystemMetrics(SM_CYICON);
        CRect rect;
        GetClientRect(&rect);
        int x = (rect.Width() - cxIcon + 1) / 2;
        int y = (rect.Height() - cyIcon + 1) / 2;

        // 绘制图标
        dc.DrawIcon(x, y, m_hIcon);
    }
    else { CDialogEx::OnPaint(); }
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMy20200616MFCApplicationDlg::OnQueryDragIcon() { return static_cast<HCURSOR>(m_hIcon); }


void CMy20200616MFCApplicationDlg::OnBnClickedButton1() {
    CString in1, in2, out;
    double inNumber1, inNumber2, result = 0.0;
    m_editIn1.GetWindowText(in1);
    m_editIn2.GetWindowText(in2);
    inNumber1 = _tstof(in1);
    inNumber2 = _tstof(in2);
    switch (m_opera) {
    case 1:
        result = inNumber1 + inNumber2;
        break;
    case 2:
        result = inNumber1 - inNumber2;
        break;
    case 3:
        result = inNumber1 * inNumber2;
        break;
    case 4:
        if (inNumber2 == 0) {
            MessageBoxW(TEXT("除数不能为0"));
			m_editOut.SetWindowText(CString("错误"));
            return;
        }
        result = inNumber1 / inNumber2;
        break;
    default:
        MessageBoxW(TEXT("请选择运算符"));
		m_editOut.SetWindowText(CString("错误"));
        return;
    }
    out.Format(_T("%g"), result);
	m_editOut.SetWindowText(out);

}


void CMy20200616MFCApplicationDlg::OnBnClickedRadio1() {
    m_opera = 1;
}


void CMy20200616MFCApplicationDlg::OnBnClickedRadio2() {
    m_opera = 2;
}


void CMy20200616MFCApplicationDlg::OnBnClickedRadio3() {
    m_opera = 3;
}


void CMy20200616MFCApplicationDlg::OnBnClickedRadio4() {
    m_opera = 4;
}
