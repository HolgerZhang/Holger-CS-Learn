
// 20200616-MFCApplication.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMy20200616MFCApplicationApp: 
// �йش����ʵ�֣������ 20200616-MFCApplication.cpp
//

class CMy20200616MFCApplicationApp : public CWinApp
{
public:
	CMy20200616MFCApplicationApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMy20200616MFCApplicationApp theApp;