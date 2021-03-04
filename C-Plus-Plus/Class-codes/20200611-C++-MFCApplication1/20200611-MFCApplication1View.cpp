
// 20200611-MFCApplication1View.cpp : CMy20200611MFCApplication1View 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "20200611-MFCApplication1.h"
#endif

#include "20200611-MFCApplication1Doc.h"
#include "20200611-MFCApplication1View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy20200611MFCApplication1View

IMPLEMENT_DYNCREATE(CMy20200611MFCApplication1View, CView)

BEGIN_MESSAGE_MAP(CMy20200611MFCApplication1View, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

// CMy20200611MFCApplication1View 构造/析构

CMy20200611MFCApplication1View::CMy20200611MFCApplication1View()
	: m_click_flag(false), m_rect_count(0)
{
	// TODO: 在此处添加构造代码
    for (int i = 0; i < 10; i++) {
		m_rect_list[i] = CRect(0, 0, 0, 0);
    }
}

CMy20200611MFCApplication1View::~CMy20200611MFCApplication1View()
{
}

BOOL CMy20200611MFCApplication1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CMy20200611MFCApplication1View 绘制

void CMy20200611MFCApplication1View::OnDraw(CDC* pDC)
{
	CMy20200611MFCApplication1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码

	CRect none(0, 0, 0, 0);

    if (m_click_flag)
        for (int i = 0; i < 10; i++) {
            if (m_rect_list[i] != none) {
				pDC->Ellipse(m_rect_list[i]);
            }
        }

}


// CMy20200611MFCApplication1View 打印

BOOL CMy20200611MFCApplication1View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CMy20200611MFCApplication1View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CMy20200611MFCApplication1View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CMy20200611MFCApplication1View 诊断

#ifdef _DEBUG
void CMy20200611MFCApplication1View::AssertValid() const
{
	CView::AssertValid();
}

void CMy20200611MFCApplication1View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy20200611MFCApplication1Doc* CMy20200611MFCApplication1View::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy20200611MFCApplication1Doc)));
	return (CMy20200611MFCApplication1Doc*)m_pDocument;
}
#endif //_DEBUG


// CMy20200611MFCApplication1View 消息处理程序


void CMy20200611MFCApplication1View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	// MessageBox(TEXT("OK"), TEXT("OK"), MB_OK);
	m_rect_count++;
    
	m_rect_list[m_rect_count % 10].left = point.x - 20;
	m_rect_list[m_rect_count % 10].right = point.x + 20;
	m_rect_list[m_rect_count % 10].top = point.y - 20;
	m_rect_list[m_rect_count % 10].bottom = point.y + 20;
	m_click_flag = true;
	InvalidateRect(nullptr);

	CView::OnLButtonDown(nFlags, point);
}
