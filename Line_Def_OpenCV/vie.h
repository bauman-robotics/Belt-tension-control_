#pragma once


// vie dialog

class vie : public CDialog
{
	DECLARE_DYNAMIC(vie)

public:
	vie(CWnd* pParent = NULL);   // standard constructor
	virtual ~vie();

// Dialog Data
	enum { IDD = IDD_CPPDEMO_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
