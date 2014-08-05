// DiceView.cpp : implementation of the CDiceView class
//

#include "stdafx.h"
#include "Dice.h"

#include "DiceDoc.h"
#include "DiceView.h"

#include "stdlib.h"
#include "time.h"
#include "windows.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDiceView

IMPLEMENT_DYNCREATE(CDiceView, CView)

BEGIN_MESSAGE_MAP(CDiceView, CView)
	//{{AFX_MSG_MAP(CDiceView)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDiceView construction/destruction

CDiceView::CDiceView()
{
	// TODO: add construction code here
	initNodes();
	initPath();

	for(int i = 0; i<8; i++)
	{
		players[i].maxConnection = countMaxConnection(i);
		players[i].excessNum = 0;
		players[i].isMyTurn = false;
	}

	players[0].isMyTurn = true;

	chosenNode = -1;	

	btnClicked = false;

	ftInfo[0].country = -1;
	ftInfo[1].country = -1;

}

CDiceView::~CDiceView()
{
}

BOOL CDiceView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	
	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CDiceView drawing

void CDiceView::OnDraw(CDC* pDC)
{
	CDiceDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here

	//initialize
	CRect viewRect;
	CWnd::GetClientRect(&viewRect);
	
	cellx = viewRect.right/(6+1);
	celly = viewRect.bottom/(5+1);
	radius = celly/3;


	//draw vs
	CRect vsRect;
	vsRect.left = viewRect.right/2 - radius*2;
	vsRect.top = 0;
	vsRect.right = viewRect.right/2 + radius*2;
	vsRect.bottom = celly;
	pDC->DrawText("VS", vsRect, DT_VCENTER|DT_CENTER|DT_SINGLELINE);

	//draw fight info
	for(int j = 0; j<2; j++)
	{
		if(ftInfo[j].country < 0)
			break;
		ftInfo[j].fightRect.left = (j+3)*cellx;
		ftInfo[j].fightRect.top = celly/4;
		ftInfo[j].fightRect.right = (j+3)*cellx + radius;
		ftInfo[j].fightRect.bottom = celly/4 + radius;

		CBrush brush;

		switch(ftInfo[j].country)
		{
			case 0:
				brush.CreateSolidBrush(RGB(128,128,128));
				pDC->SetBkColor(RGB(128,128,128));
				break;
            case 1:
				brush.CreateSolidBrush(RGB(255,0,0));
				pDC->SetBkColor(RGB(255,0,0));
				break;
			case 2:
				brush.CreateSolidBrush(RGB(0,255,0));
				pDC->SetBkColor(RGB(0,255,0));
				break;
			case 3:
				brush.CreateSolidBrush(RGB(0,0,255));
				pDC->SetBkColor(RGB(0,0,255));
				break;
			case 4:
				brush.CreateSolidBrush(RGB(255,255,0));
				pDC->SetBkColor(RGB(255,255,0));
				break;
			case 5:
				brush.CreateSolidBrush(RGB(255,0,255));
				pDC->SetBkColor(RGB(255,0,255));
				break;
			case 6:
				brush.CreateSolidBrush(RGB(0,255,255));
				pDC->SetBkColor(RGB(0,255,255));
				break;
			case 7:
				brush.CreateSolidBrush(RGB(0,128,128));
				pDC->SetBkColor(RGB(0,128,128));
				break;
			default:break;

		}

		pDC->FillRect(ftInfo[j].fightRect,&brush);

		char text[1] = {0};
		pDC->SetTextColor(RGB(255,255,255));
		itoa(ftInfo[j].fightPts,text,10);

		pDC->DrawText(text,ftInfo[j].fightRect,DT_VCENTER|DT_CENTER|DT_SINGLELINE);
	}

	//draw button
	buttonRect.left = viewRect.right-100;
	buttonRect.top = viewRect.bottom-50;
	buttonRect.right = viewRect.right-5;
	buttonRect.bottom = viewRect.bottom-5;
	
	CBrush brush;	
	brush.CreateSolidBrush(RGB(160,160,160));
	pDC->FillRect(buttonRect,&brush);
	pDC->SetBkColor(RGB(160,160,160));

	if(btnClicked)
		pDC->DrawEdge(buttonRect,EDGE_SUNKEN,BF_BOTTOMRIGHT | BF_TOPLEFT); 
	else
		pDC->DrawEdge(buttonRect,EDGE_RAISED,BF_BOTTOMRIGHT | BF_TOPLEFT);

	pDC->DrawText("End Turn",buttonRect,DT_VCENTER|DT_CENTER|DT_SINGLELINE);
	
	//draw maxConnection
	for(int i = 0; i<8; i++)
	{
		CBrush brush;
		CRect maxConnectionRect;
		maxConnectionRect.left = (i+1)*cellx/1.5 + cellx/2.25 - radius/1.5;
		maxConnectionRect.top =  (5+0.75)*celly - radius/1.5; 
		maxConnectionRect.right = (i+1)*cellx/1.5 +cellx/2.25 + radius/1.5;
		maxConnectionRect.bottom = (5+0.75)*celly + radius/1.5;

		players[i].maxConnectionRect = CRect(maxConnectionRect.left - 5, maxConnectionRect.top - 5, 
			maxConnectionRect.right +5, maxConnectionRect.bottom+5);
	
		switch(i)
		{
			case 0:
				brush.CreateSolidBrush(RGB(128,128,128));
				pDC->SetBkColor(RGB(128,128,128));
				break;
            case 1:
				brush.CreateSolidBrush(RGB(255,0,0));
				pDC->SetBkColor(RGB(255,0,0));
				break;
			case 2:
				brush.CreateSolidBrush(RGB(0,255,0));
				pDC->SetBkColor(RGB(0,255,0));
				break;
			case 3:
				brush.CreateSolidBrush(RGB(0,0,255));
				pDC->SetBkColor(RGB(0,0,255));
				break;
			case 4:
				brush.CreateSolidBrush(RGB(255,255,0));
				pDC->SetBkColor(RGB(255,255,0));
				break;
			case 5:
				brush.CreateSolidBrush(RGB(255,0,255));
				pDC->SetBkColor(RGB(255,0,255));
				break;
			case 6:
				brush.CreateSolidBrush(RGB(0,255,255));
				pDC->SetBkColor(RGB(0,255,255));
				break;
			case 7:
				brush.CreateSolidBrush(RGB(0,128,128));
				pDC->SetBkColor(RGB(0,128,128));
				break;
			default:break;

		}

		pDC->FillRect(maxConnectionRect,&brush);

		char text[1] = {0};
		pDC->SetTextColor(RGB(255,255,255));
		itoa(players[i].maxConnection,text,10);
		pDC->DrawText(text,maxConnectionRect,DT_VCENTER|DT_CENTER|DT_SINGLELINE);
		pDC->DrawEdge(maxConnectionRect,EDGE_RAISED,BF_BOTTOMRIGHT | BF_TOPLEFT);

		if(players[i].isMyTurn)
		{
			CPen pen,*oldPen;
			oldPen = pDC->GetCurrentPen();
			pen.CreatePen(PS_SOLID,4,RGB(0,0,0));
			pDC->SelectObject(pen);

			
			pDC->MoveTo(maxConnectionRect.left, maxConnectionRect.top);
			pDC->LineTo(maxConnectionRect.right, maxConnectionRect.top);
			pDC->MoveTo(maxConnectionRect.right, maxConnectionRect.top);
			pDC->LineTo(maxConnectionRect.right, maxConnectionRect.bottom);
			pDC->MoveTo(maxConnectionRect.right, maxConnectionRect.bottom);
			pDC->LineTo(maxConnectionRect.left, maxConnectionRect.bottom);
			pDC->MoveTo(maxConnectionRect.left, maxConnectionRect.bottom);
			pDC->LineTo(maxConnectionRect.left, maxConnectionRect.top);

			pDC->SelectObject(oldPen);
			
		}

	}

	//draw Nodes & draw path
	int visited = 0;
	CPoint from,to;

	for(int num = 0; num<5*6; num++)
	{
		from.x = (num%6 + 1)*cellx;
		from.y = (num/(5+1) + 1)*celly;

		for(set<int>::iterator iter = path[num].begin(); iter!=path[num].end(); iter++)
		{
			if(*iter<visited)
				continue;
			
			to.x = (*iter%6 + 1)*cellx;
			to.y = (*iter/(5+1) + 1)*celly;
			pDC->MoveTo(from);
			pDC->LineTo(to);
		}
		visited++;

		CBrush brush;
		CRect rect(from.x-radius,from.y-radius,from.x+radius,from.y+radius);
		nodes[num].nodeRect = CRect(from.x-radius-5,from.y-radius-5,from.x+radius+5,from.y+radius+5);

		//chooseColor
		switch(nodes[num].country)
		{
			case 0:
				brush.CreateSolidBrush(RGB(128,128,128));
				pDC->SetBkColor(RGB(128,128,128));
				break;
            case 1:
				brush.CreateSolidBrush(RGB(255,0,0));
				pDC->SetBkColor(RGB(255,0,0));
				break;
			case 2:
				brush.CreateSolidBrush(RGB(0,255,0));
				pDC->SetBkColor(RGB(0,255,0));
				break;
			case 3:
				brush.CreateSolidBrush(RGB(0,0,255));
				pDC->SetBkColor(RGB(0,0,255));
				break;
			case 4:
				brush.CreateSolidBrush(RGB(255,255,0));
				pDC->SetBkColor(RGB(255,255,0));
				break;
			case 5:
				brush.CreateSolidBrush(RGB(255,0,255));
				pDC->SetBkColor(RGB(255,0,255));
				break;
			case 6:
				brush.CreateSolidBrush(RGB(0,255,255));
				pDC->SetBkColor(RGB(0,255,255));
				break;
			case 7:
				brush.CreateSolidBrush(RGB(0,128,128));
				pDC->SetBkColor(RGB(0,128,128));
				break;
			default:break;

		}

		if(nodes[num].isChosen)
		{
			CPen pen,*oldPen;
			oldPen = pDC->GetCurrentPen();
			pen.CreatePen(PS_SOLID,7,RGB(0,0,0));
			pDC->SelectObject(pen);
			pDC->Ellipse(rect);
			pDC->SelectObject(oldPen);
		}
	

		pDC->SelectObject(brush);
		pDC->Ellipse(rect);

		CFont font;
		font.CreateFont(
			radius*1.2,                        // nHeight
			0,                         // nWidth
			0,                         // nEscapement
			0,                         // nOrientation
			FW_NORMAL,                 // nWeight
			FALSE,                     // bItalic
			FALSE,                     // bUnderline
			0,                         // cStrikeOut
			ANSI_CHARSET,              // nCharSet
			OUT_DEFAULT_PRECIS,        // nOutPrecision
			CLIP_DEFAULT_PRECIS,       // nClipPrecision
			DEFAULT_QUALITY,           // nQuality
			DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
			"Arial");     
		pDC->SelectObject(&font);

		char text[1] = {0};
		pDC->SetTextColor(RGB(255,255,255));
		itoa(nodes[num].diceNum,text,10);
		pDC->DrawText(text,rect,DT_VCENTER|DT_CENTER|DT_SINGLELINE);
	}
}

/////////////////////////////////////////////////////////////////////////////
// CDiceView printing

BOOL CDiceView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CDiceView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CDiceView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CDiceView diagnostics

#ifdef _DEBUG
void CDiceView::AssertValid() const
{
	CView::AssertValid();
}

void CDiceView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDiceDoc* CDiceView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDiceDoc)));
	return (CDiceDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDiceView message handlers
void CDiceView::initNodes()
{
	int count = 0;
	srand((unsigned) time(NULL));

	for(int i = 0; i<5*6; i++)
	{
		nodes[i].country = rand()%8;
		nodes[i].diceNum = rand()%8 + 1;
		nodes[i].isChosen = false;
		players[ nodes[i].country ].nodes.insert(count);
		count++;				
	}
}

void CDiceView::initPath()
{
	int neighbor[8] = {-6-1, -6, -6+1, -1, +1, +6-1, +6, +6+1};
	int visited = 0;
	srand((unsigned) time(NULL));

	for(int i = 0; i<5*6; i++)
	{
		do
		{
			for(int j = 0; j<8; j++)
			{
				int to = i+neighbor[j];
				if( to < 0 || to > 5*6-1 
					|| ((i%6 == 5) && (to == i+1 || to == i+6+1 || to == i-6+1))
					|| ((i%6 == 0) && (to == i-1 || to == i-6-1 || to == i+6-1))
					|| path[i].find(to) != path[i].end()) 
					continue;
				if(rand()%4 == 0)
				{
					path[i].insert(to);
					path[to].insert(i);

				}
			}
		}
		while(path[i].empty());
	}
}

void CDiceView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	int roughX, roughY, excessX, excessY, nodeX, nodeY;
	int selectedNode;

	if(buttonRect.PtInRect(point))
	{
		btnClicked = true;
		CWnd::InvalidateRect(buttonRect);
		return;
	}

	roughX = point.x/cellx;
	roughY = point.y/celly;
	excessX = point.x%cellx;
	excessY = point.y%celly;

	if(   (excessX>radius && excessX<cellx-radius)
		||(excessY>radius && excessY<celly-radius) )
		return;
	if(excessX<radius)
		nodeX = roughX;
	else
		nodeX = roughX+1;
	if(excessY<radius)
		nodeY = roughY;
	else
		nodeY= roughY+1;

	selectedNode = (nodeY-1)*6 + nodeX-1;
//	CRect rect(nodeX*cellx-radius-5,nodeY*celly-radius-5,nodeX*cellx+radius+5,nodeY*celly+radius+5);

	if(chosenNode<0)
	{
		if(nodes[selectedNode].country != 0)
			return;
		chosenNode = selectedNode;
		nodes[chosenNode].isChosen = true;
		CWnd::InvalidateRect(nodes[chosenNode].nodeRect);
	}
	else if(chosenNode == selectedNode)
	{
		nodes[chosenNode].isChosen = false;		
		CWnd::InvalidateRect(nodes[chosenNode].nodeRect);
		chosenNode = -1;
	}
	else
	{
		if(isFightable(chosenNode, selectedNode))
		{
			nodes[selectedNode].isChosen = true;
			CWnd::InvalidateRect(nodes[selectedNode].nodeRect);
			fight(chosenNode, selectedNode);
		}
			
	}
	
	CView::OnLButtonDown(nFlags, point);
}

bool CDiceView::isFightable(int src, int des)
{
	if(nodes[src].country == nodes[des].country)
		return false;
	else if(path[src].find(des) == path[src].end() || nodes[src].diceNum == 1)
		return false;
	else
		return true;
}

void CDiceView::fight(int src, int des)
{
	int temp, srcPt, desPt, srcCountry, desCountry;
	srcPt = 0;
	desPt = 0;
	srcCountry = nodes[src].country;
	desCountry = nodes[des].country;

	for(int i = 0; i<nodes[src].diceNum; i++)
	{
		temp = rand()%6 + 1;
		srcPt += temp;
	}

	for(int j = 0; j<nodes[des].diceNum; j++)
	{
		temp = rand()%6 + 1;
		desPt += temp;
	}

	//display the Pt
	MSG msg;

	ftInfo[0].country = srcCountry;
	ftInfo[1].country = desCountry;
	ftInfo[0].fightPts = srcPt;
	ftInfo[1].fightPts = desPt;

	CWnd::InvalidateRect(CRect(cellx*3, celly/4, cellx*4 + radius, celly/4 + radius));

	GetMessage(&msg,NULL,0,0);	
	TranslateMessage(&msg);
	DispatchMessage(&msg);
	::Sleep(1000);

	
	if(srcPt > desPt)
	{
		nodes[des].diceNum = nodes[src].diceNum - 1;
		nodes[src].diceNum = 1;

		players[ desCountry ].nodes.erase(des);
		players[ srcCountry ].nodes.insert(des);

		nodes[des].country = nodes[src].country;

		players[ desCountry ].maxConnection = countMaxConnection(desCountry);
		players[ srcCountry ].maxConnection = countMaxConnection(srcCountry);


		CWnd::InvalidateRect(players[ desCountry ].maxConnectionRect);
		CWnd::InvalidateRect(players[ srcCountry ].maxConnectionRect);


	}
	else
	{
		nodes[src].diceNum = 1;
	}

	nodes[des].isChosen = false;
	nodes[src].isChosen = false;

	chosenNode = -1;

	CWnd::InvalidateRect(nodes[des].nodeRect);
	CWnd::InvalidateRect(nodes[src].nodeRect);
	
	GetMessage(&msg,NULL,0,0);	
	TranslateMessage(&msg);
	DispatchMessage(&msg);
	::Sleep(50);

}

int CDiceView::countMaxConnection(int country)
{
	if(players[country].nodes.size() == 0)
		return 0;

	set<int> visited, maxConnection;
	for(set<int>::iterator iter = players[country].nodes.begin(); iter != players[country].nodes.end(); iter++)
	{
		if(visited.find(*iter)!=visited.end())
			continue;
		
		int branchConnection = countBranchConnection(*iter, country, &visited);
		maxConnection.insert(branchConnection);
	}

	return *maxConnection.rbegin();
}

int CDiceView::countBranchConnection(int node, int country, set<int>* pSet)
{
	int sum = 1;
	pSet->insert(node);
	for(set<int>::iterator iter = path[node].begin(); iter != path[node].end(); iter++)
	{
		if(nodes[*iter].country != country || pSet->find(*iter) != pSet->end())
			continue;
		else
		{
			//pSet->insert(*iter);
			sum += countBranchConnection(*iter, country, pSet);
		}
	}
	return sum;
}

void CDiceView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if(buttonRect.PtInRect(point))
	{
		btnClicked =false;
		CWnd::InvalidateRect(buttonRect);

	//	players[0].maxConnection = countMaxConnection(0);
		addDice(0);

		players[0].isMyTurn = false;
		CWnd::InvalidateRect(players[0].maxConnectionRect);

		AIaction();
	}

	CView::OnLButtonUp(nFlags, point);
}
 
void CDiceView::addDice(int country)
{
	int addSum = players[country].maxConnection + players[country].excessNum;
	int addNum = 655535;

	addSum = (addSum > (5*6) ? (5*6): addSum);
	
	set<int> nodesNum8;

	while(addSum>0)
	{
		for(set<int>::iterator iter = players[country].nodes.begin(); iter != players[country].nodes.end(); iter++)
		{
			if(nodes[*iter].diceNum == 8)
			{
				nodesNum8.insert(*iter);
				continue;
			}

			do
			{
				addNum = rand()%(8-nodes[*iter].diceNum+1);
			}
			while(addSum - addNum < 0);
				
			nodes[*iter].diceNum += addNum;
			CWnd::InvalidateRect(nodes[*iter].nodeRect);
			addSum -= addNum;

		}

		if(nodesNum8.size() == players[country].nodes.size())
			break;
	}
	players[country].excessNum = addSum;
	//CWnd::Invalidate();
}

void CDiceView::AIaction()
{
	MSG msg;
	for(int country = 1; country<8; country++)
	{
		if(players[country].nodes.size() != 0)
		{
			players[country].isMyTurn = true;
			CWnd::InvalidateRect(players[country].maxConnectionRect);
			GetMessage(&msg,NULL,0,0);	
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			actInTurn(country);

			players[country].isMyTurn = false;
			CWnd::InvalidateRect(players[country].maxConnectionRect);	
			GetMessage(&msg,NULL,0,0);	
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
			
	}
	players[0].isMyTurn = true;
	ftInfo[0].country = -1;
	ftInfo[1].country = -1;
	
	CWnd::InvalidateRect(players[0].maxConnectionRect);
	CWnd::InvalidateRect(CRect(cellx*3, celly/4, cellx*4 + radius, celly/4 + radius));
	return;
}

void CDiceView::actInTurn(int country)
{
	set<int> finishedNodes;
	MSG msg;
	while(1)
	{
		for(set<int>::iterator iter = players[country].nodes.begin(); iter != players[country].nodes.end(); iter++)
		{
			int AIchosenNode = *iter;
			if(finishedNodes.find(AIchosenNode) != finishedNodes.end())
				continue;

			for(set<int>::iterator pNeighbor = path[*iter].begin(); pNeighbor != path[*iter].end(); pNeighbor++)
			{
				int selectedNode = *pNeighbor;
				if(isFightable(AIchosenNode, selectedNode) && nodes[AIchosenNode].diceNum >= nodes[selectedNode].diceNum)
				{
					nodes[AIchosenNode].isChosen = true;
					nodes[selectedNode].isChosen = true;
					CWnd::InvalidateRect(nodes[AIchosenNode].nodeRect);
					CWnd::InvalidateRect(nodes[selectedNode].nodeRect);
				//	CWnd::Invalidate();
				//	GetMessage(&msg,NULL,0,0);	
				//	TranslateMessage(&msg);
				//	DispatchMessage(&msg);
				//	::Sleep(10);
					fight(AIchosenNode, selectedNode);
					
				}
			}
			finishedNodes.insert(AIchosenNode);
		}
		if(finishedNodes.size() == players[country].nodes.size())
			break;
	}
	players[country].maxConnection = countMaxConnection(country);
	addDice(country);
}

