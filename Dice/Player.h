// Player.h: interface for the CPlayer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PLAYER_H__05D7DB28_EE61_45FC_AD61_B4E2DDBE8317__INCLUDED_)
#define AFX_PLAYER_H__05D7DB28_EE61_45FC_AD61_B4E2DDBE8317__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <set>
#include "afxwin.h"
using namespace std;

class CPlayer  
{
public:
	CPlayer();
	virtual ~CPlayer();

	set<int> nodes;
	int maxConnection;
	int excessNum;
	CRect maxConnectionRect;
	bool isMyTurn;

};

#endif // !defined(AFX_PLAYER_H__05D7DB28_EE61_45FC_AD61_B4E2DDBE8317__INCLUDED_)
