
// 20200615-MFCApplication.h : 20200615-MFCApplication 应用程序的主头文件
//
#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"       // 主符号


// CMy20200615MFCApplicationApp:
// 有关此类的实现，请参阅 20200615-MFCApplication.cpp
//

class CMy20200615MFCApplicationApp : public CWinApp
{
public:
	CMy20200615MFCApplicationApp();


// 重写
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// 实现
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMy20200615MFCApplicationApp theApp;
