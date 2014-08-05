// DiceDoc.cpp : implementation of the CDiceDoc class
//

#include "stdafx.h"
#include "Dice.h"

#include "DiceDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDiceDoc

IMPLEMENT_DYNCREATE(CDiceDoc, CDocument)

BEGIN_MESSAGE_MAP(CDiceDoc, CDocument)
	//{{AFX_MSG_MAP(CDiceDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDiceDoc construction/destruction

CDiceDoc::CDiceDoc()
{
	// TODO: add one-time construction code here

}

CDiceDoc::~CDiceDoc()
{
}

BOOL CDiceDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CDiceDoc serialization

void CDiceDoc::Serialize(CArchive& ar)
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
// CDiceDoc diagnostics

#ifdef _DEBUG
void CDiceDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDiceDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDiceDoc commands
