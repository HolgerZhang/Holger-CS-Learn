
// 20200611-MFCApplication1View.h : CMy20200611MFCApplication1View ��Ľӿ�
//

#pragma once
#include "atltypes.h"


class CMy20200611MFCApplication1View : public CView
{
protected: // �������л�����
	CMy20200611MFCApplication1View();
	DECLARE_DYNCREATE(CMy20200611MFCApplication1View)

// ����
public:
	CMy20200611MFCApplication1Doc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CMy20200611MFCApplication1View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
private:
	// ���������ڴ洢10��Բ�����������
	CRect m_rect_list[10];
	// �Ƿ�������Ļ
	bool m_click_flag;
	// ��ǰԲ�θ���
    int m_rect_count;

};

#ifndef _DEBUG  // 20200611-MFCApplication1View.cpp �еĵ��԰汾
inline CMy20200611MFCApplication1Doc* CMy20200611MFCApplication1View::GetDocument() const
   { return reinterpret_cast<CMy20200611MFCApplication1Doc*>(m_pDocument); }
#endif

