
// 20200615-MFCApplicationView.cpp : CMy20200615MFCApplicationView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "20200615-MFCApplication.h"
#endif

#include "20200615-MFCApplicationDoc.h"
#include "20200615-MFCApplicationView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy20200615MFCApplicationView

IMPLEMENT_DYNCREATE(CMy20200615MFCApplicationView, CView)

BEGIN_MESSAGE_MAP(CMy20200615MFCApplicationView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_TIMER()
	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()

// CMy20200615MFCApplicationView 构造/析构

CMy20200615MFCApplicationView::CMy20200615MFCApplicationView()
	: m_x(500), m_step(15)
{
	// TODO: 在此处添加构造代码

}

CMy20200615MFCApplicationView::~CMy20200615MFCApplicationView()
{
}

BOOL CMy20200615MFCApplicationView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CMy20200615MFCApplicationView 绘制

void CMy20200615MFCApplicationView::OnDraw(CDC* pDC)
{
	CMy20200615MFCApplicationDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码

	// pDC->TextOut(m_x, 300, TEXT("Welcome"));

	// CPen newPen(PS_DOT, 1, RGB(0, 0, 255));
	// CPen *pOldPen = pDC->SelectObject(&newPen);
	// pDC->MoveTo(300, 200);
	// pDC->LineTo(200, 300);
	// pDC->SelectObject(pOldPen);

	// CBrush brush1;
	// brush1.CreateHatchBrush(HS_CROSS, RGB(0, 255, 0));
	// CBrush *pOldBrush = pDC->SelectObject(&brush1);
	// CRect rc(100, 100, 300, 300);
	// pDC->Rectangle(&rc);
	// pDC->SelectObject(pOldBrush);

	// CBitmap bmp;
	// bmp.LoadBitmap(IDB_BITMAP1);
	// BITMAP bitmap;
	// bmp.GetBitmap(&bitmap);
	// int bmpwidth = bitmap.bmWidth;
	// int bmpheight = bitmap.bmHeight;
	// CDC memDC;
	// memDC.CreateCompatibleDC(pDC);
	// memDC.SelectObject(bmp);
 //
	// CRect rect;
	// GetClientRect(rect);
 //    for (int x=0;x<rect.right; x+=bmpwidth)
 //        for (int y=0;y<rect.bottom;y+=bmpheight)
	//         pDC->BitBlt(x, y, bmpwidth, bmpheight, &memDC, 0, 0, SRCCOPY);

	LOGFONT lf;
	pDC->GetCurrentFont()->GetLogFont(&lf);
	CFont *pOldFont;
	lf.lfCharSet = 40;
	lf.lfHeight = -30;
	lf.lfWidth = 0;
	wcscpy(lf.lfFaceName, TEXT("等线"));
	CFont font;
	font.CreateFontIndirect(&lf);
	pOldFont = pDC->SelectObject(&font);
	pDC->TextOut(10, 10, TEXT("张昊"));
	pDC->SelectObject(pOldFont);

}


// CMy20200615MFCApplicationView 打印

BOOL CMy20200615MFCApplicationView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CMy20200615MFCApplicationView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CMy20200615MFCApplicationView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CMy20200615MFCApplicationView 诊断

#ifdef _DEBUG
void CMy20200615MFCApplicationView::AssertValid() const
{
	CView::AssertValid();
}

void CMy20200615MFCApplicationView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy20200615MFCApplicationDoc* CMy20200615MFCApplicationView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy20200615MFCApplicationDoc)));
	return (CMy20200615MFCApplicationDoc*)m_pDocument;
}
#endif //_DEBUG


// CMy20200615MFCApplicationView 消息处理程序


void CMy20200615MFCApplicationView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	// CRect rc;
	// rc.left = point.x - 20;
	// rc.top = point.y - 20;
	// rc.right = point.x + 20;
	// rc.bottom = point.y + 20;
	// CClientDC dc(this);
	// dc.SelectStockObject(GRAY_BRUSH);
	// dc.Ellipse(&rc);


	CView::OnMouseMove(nFlags, point);
}


void CMy20200615MFCApplicationView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//
	// SetTimer(5000, 50, nullptr);

	CView::OnLButtonDown(nFlags, point);
}


void CMy20200615MFCApplicationView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	// RECT rect;
	// GetClientRect(&rect);
	// if (m_x <= 0 || m_x >= rect.right - 10) {
	// 	m_step *= -1;
	// }
 //    m_x += m_step;
	// InvalidateRect(nullptr);

	CView::OnTimer(nIDEvent);
}


void CMy20200615MFCApplicationView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	// KillTimer(5000);

	CView::OnRButtonDown(nFlags, point);
}
