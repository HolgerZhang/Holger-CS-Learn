
// 20200616-MFCApplicationDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"


// CMy20200616MFCApplicationDlg �Ի���
class CMy20200616MFCApplicationDlg : public CDialogEx
{
// ����
public:
	CMy20200616MFCApplicationDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MY20200616MFCAPPLICATION_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	// �������
	CEdit m_editIn1;
	// �Ҳ�����
	CEdit m_editIn2;
	// ���
	CEdit m_editOut;

	int m_opera;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedRadio3();
	afx_msg void OnBnClickedRadio4();
};
