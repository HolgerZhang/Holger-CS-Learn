// CatAndMouseView.cpp : implementation of the CCatAndMouseView class
//

#include "stdafx.h"
#include "CatAndMouse.h"

#include "CatAndMouseDoc.h"
#include "CatAndMouseView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCatAndMouseView

IMPLEMENT_DYNCREATE(CCatAndMouseView, CView)

BEGIN_MESSAGE_MAP(CCatAndMouseView, CView)
	//{{AFX_MSG_MAP(CCatAndMouseView)
	ON_WM_KEYUP()
	ON_WM_TIMER()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCatAndMouseView construction/destruction

CCatAndMouseView::CCatAndMouseView()
{
	m_IsPlaying=FALSE;
	m_MiceStep=50;
	m_CatStep=20;

}

CCatAndMouseView::~CCatAndMouseView()
{
}

BOOL CCatAndMouseView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CCatAndMouseView drawing

void CCatAndMouseView::OnDraw(CDC* pDC)
{
	CCatAndMouseDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if(m_IsPlaying==FALSE)
	{
//		CRect	rc;
//		GetClientRect(&rc);
		pDC->TextOut (m_ClientRc.right /2-50,m_ClientRc.bottom /2,"按F2键开始游戏");

		m_Cat.x =m_ClientRc.right /2;
		m_Cat.y =m_ClientRc.bottom*3/4;

		m_Mice.x =m_ClientRc.right /2;
		m_Mice.y =m_ClientRc.bottom /4;

		pDC->TextOut (m_Mice.x ,m_Mice.y ,"鼠");
		pDC->TextOut (m_Cat.x ,m_Cat.y ,"猫");
	}
	else
	{
		pDC->TextOut (m_Mice.x ,m_Mice.y ,"鼠");
		pDC->TextOut (m_Cat.x ,m_Cat.y ,"猫");
	}
}

/////////////////////////////////////////////////////////////////////////////
// CCatAndMouseView printing

BOOL CCatAndMouseView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CCatAndMouseView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CCatAndMouseView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CCatAndMouseView diagnostics

#ifdef _DEBUG
void CCatAndMouseView::AssertValid() const
{
	CView::AssertValid();
}

void CCatAndMouseView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCatAndMouseDoc* CCatAndMouseView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCatAndMouseDoc)));
	return (CCatAndMouseDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCatAndMouseView message handlers

void CCatAndMouseView::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if(nChar==VK_F2&&m_IsPlaying==FALSE)
	{
		m_IsPlaying=TRUE;
		InvalidateRect(NULL);

		SetTimer(IDC_TIMER,500,NULL);

	}
	if(m_IsPlaying==TRUE)
	{
		switch(nChar)
		{
			case VK_LEFT:
				
				if(m_Cat.x >=m_CatStep) m_Cat.x -=m_CatStep;
				break;
			case VK_RIGHT:
				if(m_Cat.x<=m_ClientRc.right-m_CatStep) 
					m_Cat.x +=m_CatStep;
				break;
			case VK_UP:
				if(m_Cat.y >=m_CatStep) m_Cat.y -=m_CatStep;
				break;
			case VK_DOWN:
				if(m_Cat.y <=m_ClientRc.bottom -m_CatStep) 
					m_Cat.y +=m_CatStep;
				break;
		}
		InvalidateRect(NULL);
		
		if(abs(m_Cat.x -m_Mice.x)<20 && abs(m_Cat.y -m_Mice.y)<20)
		{
			KillTimer(IDC_TIMER);
			m_IsPlaying=FALSE;
			AfxMessageBox("Catch!");
			InvalidateRect(NULL);
		}
	}
	CView::OnKeyUp(nChar, nRepCnt, nFlags);
}

void CCatAndMouseView::OnTimer(UINT nIDEvent) 
{
	int i=rand()%4;
	CRect	rc;
	GetClientRect(&rc);
	switch(i)
	{
	case 0:
			if(m_Mice.x+m_MiceStep<rc.right)
				m_Mice.x +=m_MiceStep;
			break;
	case 1:
			if(m_Mice.x -m_MiceStep>0)
				m_Mice.x -=m_MiceStep;
			break;
	case 2:
			if(m_Mice.y+m_MiceStep<rc.bottom)
				m_Mice.y +=m_MiceStep;
			break;
	case 3:
			if(m_Mice.y -m_MiceStep>0)
				m_Mice.y -=m_MiceStep;
			break;
	}
	InvalidateRect(NULL);
	if(abs(m_Cat.x -m_Mice.x)<20 && abs(m_Cat.y -m_Mice.y)<20)
	{
		KillTimer(IDC_TIMER);
		m_IsPlaying=FALSE;
		AfxMessageBox("Catch!");
		InvalidateRect(NULL);
	}
	CView::OnTimer(nIDEvent);
}

void CCatAndMouseView::OnSize(UINT nType, int cx, int cy) 
{
	GetClientRect(&m_ClientRc);
	CView::OnSize(nType, cx, cy);
}
