
// 20200615-MFCApplication.h : 20200615-MFCApplication Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CMy20200615MFCApplicationApp:
// �йش����ʵ�֣������ 20200615-MFCApplication.cpp
//

class CMy20200615MFCApplicationApp : public CWinApp
{
public:
	CMy20200615MFCApplicationApp();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMy20200615MFCApplicationApp theApp;
