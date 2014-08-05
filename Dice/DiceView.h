// DiceView.h : interface of the CDiceView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DICEVIEW_H__23D7D104_2038_4C82_B9B5_9FA7653FFE08__INCLUDED_)
#define AFX_DICEVIEW_H__23D7D104_2038_4C82_B9B5_9FA7653FFE08__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Node.h"
#include "Player.h"

struct fightInfo
{
	int country;
	int fightPts;
	CRect fightRect;		
};

class CDiceView : public CView
{
protected: // create from serialization only
	CDiceView();
	DECLARE_DYNCREATE(CDiceView)

// Attributes
public:
	CDiceDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDiceView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDiceView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDiceView)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CNode nodes[5*6];
	set<int> path[5*6];
	CPlayer players[8];

	int cellx;
	int celly;
	int radius;

	struct fightInfo ftInfo[2];

	CRect buttonRect;
	bool btnClicked;

	int chosenNode;
	
	void initNodes();
	void initPath();

	bool isFightable(int src, int des);
	void fight(int src, int des);
	int countMaxConnection(int country);
	int countBranchConnection(int node, int country, set<int>* pSet);
	void addDice(int country);


	void AIaction();
	void actInTurn(int country);

};

#ifndef _DEBUG  // debug version in DiceView.cpp
inline CDiceDoc* CDiceView::GetDocument()
   { return (CDiceDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DICEVIEW_H__23D7D104_2038_4C82_B9B5_9FA7653FFE08__INCLUDED_)
