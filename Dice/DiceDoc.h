// DiceDoc.h : interface of the CDiceDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DICEDOC_H__57C76CC5_BFDC_42DD_A60E_F31C99350DDC__INCLUDED_)
#define AFX_DICEDOC_H__57C76CC5_BFDC_42DD_A60E_F31C99350DDC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CDiceDoc : public CDocument
{
protected: // create from serialization only
	CDiceDoc();
	DECLARE_DYNCREATE(CDiceDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDiceDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDiceDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDiceDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DICEDOC_H__57C76CC5_BFDC_42DD_A60E_F31C99350DDC__INCLUDED_)
