// 20200616-MFCApplicationDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "20200616-MFCApplication.h"
#include "20200616-MFCApplicationDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx {
public:
    CAboutDlg();

    // �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
    virtual void DoDataExchange(CDataExchange* pDX); // DDX/DDV ֧��

    // ʵ��
protected:
DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX) {}

void CAboutDlg::DoDataExchange(CDataExchange* pDX) { CDialogEx::DoDataExchange(pDX); }

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMy20200616MFCApplicationDlg �Ի���


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


// CMy20200616MFCApplicationDlg ��Ϣ�������

BOOL CMy20200616MFCApplicationDlg::OnInitDialog() {
    CDialogEx::OnInitDialog();

    // ��������...���˵�����ӵ�ϵͳ�˵��С�

    // IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

    // ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
    //  ִ�д˲���
    SetIcon(m_hIcon, TRUE); // ���ô�ͼ��
    SetIcon(m_hIcon, FALSE); // ����Сͼ��

    // TODO: �ڴ���Ӷ���ĳ�ʼ������

    return TRUE; // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CMy20200616MFCApplicationDlg::OnSysCommand(UINT nID, LPARAM lParam) {
    if ((nID & 0xFFF0) == IDM_ABOUTBOX) {
        CAboutDlg dlgAbout;
        dlgAbout.DoModal();
    }
    else { CDialogEx::OnSysCommand(nID, lParam); }
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMy20200616MFCApplicationDlg::OnPaint() {
    if (IsIconic()) {
        CPaintDC dc(this); // ���ڻ��Ƶ��豸������

        SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

        // ʹͼ���ڹ����������о���
        int cxIcon = GetSystemMetrics(SM_CXICON);
        int cyIcon = GetSystemMetrics(SM_CYICON);
        CRect rect;
        GetClientRect(&rect);
        int x = (rect.Width() - cxIcon + 1) / 2;
        int y = (rect.Height() - cyIcon + 1) / 2;

        // ����ͼ��
        dc.DrawIcon(x, y, m_hIcon);
    }
    else { CDialogEx::OnPaint(); }
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
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
            MessageBoxW(TEXT("��������Ϊ0"));
			m_editOut.SetWindowText(CString("����"));
            return;
        }
        result = inNumber1 / inNumber2;
        break;
    default:
        MessageBoxW(TEXT("��ѡ�������"));
		m_editOut.SetWindowText(CString("����"));
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
