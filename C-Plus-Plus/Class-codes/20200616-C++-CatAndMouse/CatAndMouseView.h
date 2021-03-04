// CatAndMouseView.h : interface of the CCatAndMouseView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CATANDMOUSEVIEW_H__A32BC94D_06FC_11D7_A056_00065BD708D9__INCLUDED_)
#define AFX_CATANDMOUSEVIEW_H__A32BC94D_06FC_11D7_A056_00065BD708D9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CCatAndMouseView : public CView
{
protected: // create from serialization only
	CCatAndMouseView();
	DECLARE_DYNCREATE(CCatAndMouseView)

// Attributes
public:
	CCatAndMouseDoc* GetDocument();

private:
	BOOL m_IsPlaying;
	CPoint	m_Cat;
	CPoint	m_Mice;
	int		m_MiceStep;
	int		m_CatStep;
	CRect	m_ClientRc;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCatAndMouseView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCatAndMouseView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CCatAndMouseView)
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in CatAndMouseView.cpp
inline CCatAndMouseDoc* CCatAndMouseView::GetDocument()
   { return (CCatAndMouseDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CATANDMOUSEVIEW_H__A32BC94D_06FC_11D7_A056_00065BD708D9__INCLUDED_)
