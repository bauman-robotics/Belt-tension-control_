// vie.cpp : implementation file
//

#include "stdafx.h"
#include "CPP Demo.h"
#include "vie.h"


// vie dialog

IMPLEMENT_DYNAMIC(vie, CDialog)

vie::vie(CWnd* pParent /*=NULL*/)
	: CDialog(vie::IDD, pParent)
{

}

vie::~vie()
{
}

void vie::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(vie, CDialog)
END_MESSAGE_MAP()


// vie message handlers
