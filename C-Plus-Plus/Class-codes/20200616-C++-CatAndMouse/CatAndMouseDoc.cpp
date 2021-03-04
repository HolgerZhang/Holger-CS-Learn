// CatAndMouseDoc.cpp : implementation of the CCatAndMouseDoc class
//

#include "stdafx.h"
#include "CatAndMouse.h"

#include "CatAndMouseDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCatAndMouseDoc

IMPLEMENT_DYNCREATE(CCatAndMouseDoc, CDocument)

BEGIN_MESSAGE_MAP(CCatAndMouseDoc, CDocument)
	//{{AFX_MSG_MAP(CCatAndMouseDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCatAndMouseDoc construction/destruction

CCatAndMouseDoc::CCatAndMouseDoc()
{
	// TODO: add one-time construction code here

}

CCatAndMouseDoc::~CCatAndMouseDoc()
{
}

BOOL CCatAndMouseDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CCatAndMouseDoc serialization

void CCatAndMouseDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CCatAndMouseDoc diagnostics

#ifdef _DEBUG
void CCatAndMouseDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CCatAndMouseDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCatAndMouseDoc commands
