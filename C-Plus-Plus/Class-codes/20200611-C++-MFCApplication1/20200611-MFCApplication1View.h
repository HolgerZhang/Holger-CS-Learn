
// 20200611-MFCApplication1View.h : CMy20200611MFCApplication1View 类的接口
//

#pragma once
#include "atltypes.h"


class CMy20200611MFCApplication1View : public CView
{
protected: // 仅从序列化创建
	CMy20200611MFCApplication1View();
	DECLARE_DYNCREATE(CMy20200611MFCApplication1View)

// 特性
public:
	CMy20200611MFCApplication1Doc* GetDocument() const;

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
	virtual ~CMy20200611MFCApplication1View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
private:
	// 本变量用于存储10个圆的外接正方形
	CRect m_rect_list[10];
	// 是否点击过屏幕
	bool m_click_flag;
	// 当前圆形个数
    int m_rect_count;

};

#ifndef _DEBUG  // 20200611-MFCApplication1View.cpp 中的调试版本
inline CMy20200611MFCApplication1Doc* CMy20200611MFCApplication1View::GetDocument() const
   { return reinterpret_cast<CMy20200611MFCApplication1Doc*>(m_pDocument); }
#endif

