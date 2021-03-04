
// 20200611-MFCApplication1View.cpp : CMy20200611MFCApplication1View ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
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
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

// CMy20200611MFCApplication1View ����/����

CMy20200611MFCApplication1View::CMy20200611MFCApplication1View()
	: m_click_flag(false), m_rect_count(0)
{
	// TODO: �ڴ˴���ӹ������
    for (int i = 0; i < 10; i++) {
		m_rect_list[i] = CRect(0, 0, 0, 0);
    }
}

CMy20200611MFCApplication1View::~CMy20200611MFCApplication1View()
{
}

BOOL CMy20200611MFCApplication1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CMy20200611MFCApplication1View ����

void CMy20200611MFCApplication1View::OnDraw(CDC* pDC)
{
	CMy20200611MFCApplication1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���

	CRect none(0, 0, 0, 0);

    if (m_click_flag)
        for (int i = 0; i < 10; i++) {
            if (m_rect_list[i] != none) {
				pDC->Ellipse(m_rect_list[i]);
            }
        }

}


// CMy20200611MFCApplication1View ��ӡ

BOOL CMy20200611MFCApplication1View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CMy20200611MFCApplication1View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CMy20200611MFCApplication1View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}


// CMy20200611MFCApplication1View ���

#ifdef _DEBUG
void CMy20200611MFCApplication1View::AssertValid() const
{
	CView::AssertValid();
}

void CMy20200611MFCApplication1View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy20200611MFCApplication1Doc* CMy20200611MFCApplication1View::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy20200611MFCApplication1Doc)));
	return (CMy20200611MFCApplication1Doc*)m_pDocument;
}
#endif //_DEBUG


// CMy20200611MFCApplication1View ��Ϣ�������


void CMy20200611MFCApplication1View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
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
