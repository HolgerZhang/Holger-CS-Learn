
// 20200611-MFCApplication1.h : 20200611-MFCApplication1 Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CMy20200611MFCApplication1App:
// �йش����ʵ�֣������ 20200611-MFCApplication1.cpp
//

class CMy20200611MFCApplication1App : public CWinApp
{
public:
	CMy20200611MFCApplication1App();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMy20200611MFCApplication1App theApp;
