
// 20200615-MFCApplicationView.h : CMy20200615MFCApplicationView 类的接口
//

#pragma once


class CMy20200615MFCApplicationView : public CView
{
protected: // 仅从序列化创建
	CMy20200615MFCApplicationView();
	DECLARE_DYNCREATE(CMy20200615MFCApplicationView)

// 特性
public:
	CMy20200615MFCApplicationDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CMy20200615MFCApplicationView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
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

#ifndef _DEBUG  // 20200615-MFCApplicationView.cpp 中的调试版本
inline CMy20200615MFCApplicationDoc* CMy20200615MFCApplicationView::GetDocument() const
   { return reinterpret_cast<CMy20200615MFCApplicationDoc*>(m_pDocument); }
#endif

