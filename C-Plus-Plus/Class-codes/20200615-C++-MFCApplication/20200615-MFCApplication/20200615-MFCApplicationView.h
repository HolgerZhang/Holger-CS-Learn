
// 20200615-MFCApplicationView.h : CMy20200615MFCApplicationView ��Ľӿ�
//

#pragma once


class CMy20200615MFCApplicationView : public CView
{
protected: // �������л�����
	CMy20200615MFCApplicationView();
	DECLARE_DYNCREATE(CMy20200615MFCApplicationView)

// ����
public:
	CMy20200615MFCApplicationDoc* GetDocument() const;

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
	virtual ~CMy20200615MFCApplicationView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
private:
	int m_x;
    int m_step;
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // 20200615-MFCApplicationView.cpp �еĵ��԰汾
inline CMy20200615MFCApplicationDoc* CMy20200615MFCApplicationView::GetDocument() const
   { return reinterpret_cast<CMy20200615MFCApplicationDoc*>(m_pDocument); }
#endif

