
// 20200616-MFCApplicationDlg.h : 头文件
//

#pragma once
#include "afxwin.h"


// CMy20200616MFCApplicationDlg 对话框
class CMy20200616MFCApplicationDlg : public CDialogEx
{
// 构造
public:
	CMy20200616MFCApplicationDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MY20200616MFCAPPLICATION_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	// 左操作数
	CEdit m_editIn1;
	// 右操作数
	CEdit m_editIn2;
	// 结果
	CEdit m_editOut;

	int m_opera;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedRadio3();
	afx_msg void OnBnClickedRadio4();
};
