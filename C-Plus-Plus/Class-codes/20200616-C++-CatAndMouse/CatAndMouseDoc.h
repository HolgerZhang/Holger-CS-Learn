// CatAndMouseDoc.h : interface of the CCatAndMouseDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CATANDMOUSEDOC_H__A32BC94B_06FC_11D7_A056_00065BD708D9__INCLUDED_)
#define AFX_CATANDMOUSEDOC_H__A32BC94B_06FC_11D7_A056_00065BD708D9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CCatAndMouseDoc : public CDocument
{
protected: // create from serialization only
	CCatAndMouseDoc();
	DECLARE_DYNCREATE(CCatAndMouseDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCatAndMouseDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCatAndMouseDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CCatAndMouseDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CATANDMOUSEDOC_H__A32BC94B_06FC_11D7_A056_00065BD708D9__INCLUDED_)
