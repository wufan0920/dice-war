// Node.h: interface for the CNode class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NODE_H__FE7F75E9_768D_414E_8068_2F8F6D94C829__INCLUDED_)
#define AFX_NODE_H__FE7F75E9_768D_414E_8068_2F8F6D94C829__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CNode  
{
public:
	CNode();
	virtual ~CNode();
	int country;
	int diceNum;
	bool isChosen;
	CRect nodeRect;
};

#endif // !defined(AFX_NODE_H__FE7F75E9_768D_414E_8068_2F8F6D94C829__INCLUDED_)
