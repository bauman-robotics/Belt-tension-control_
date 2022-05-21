// CPP DemoDlg.cpp : implementation file
#include "stdafx.h"
#include "CPP Demo.h"
#include "CPP DemoDlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#if defined DEBUG_MD_PART 
	Mat result;
	IplImage* frame=0; //
	CvCapture * camera;
	using namespace std;
	using namespace cv;
	FILE * pFile;
	bool CreateDir1(TCHAR * sPathTo);
	inline bool saveImg(Mat image, const string DIRECTORY, const string EXTENSION, const char * DIR_FORMAT, const char * FILE_FORMAT);
#endif

bool Glob_GetParameters(void);
static UINT proc2(LPVOID Param);


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCPPDemoDlg dialog

CCPPDemoDlg::CCPPDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCPPDemoDlg::IDD, pParent)
	, m_strSN(_T(""))
	, Num_srtr_val(_T(""))
	
	, m_colomn(_T(""))
	, m_level_val(_T(""))
	
	, m_Exp_Time(_T(""))
	, m_Diam(_T(""))
	, m_approx(FALSE)
	, Temp_text(_T(""))
{
	//{{AFX_DATA_INIT(CCPPDemoDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	i1 = 1234567890;
	cbmfile=NULL;
	On_Read_BMP = false;
	Num_srtr_val = "300";
	m_colomn = "1";
	N_Str_int = 300;
	N_Colomn_int = 1;
	is_Data_Light = 0;
	Is_Stop_Series = false;
	fixed_level = 127; //
	m_level_val = "127";
	level_val_int = 127;
	Old_level_val = 127;
	#if !defined DEBUG_MD_PART 
		m_usbCCD.Exp_Time_int = 50;
		m_Exp_Time.Format("%d", m_usbCCD.Exp_Time_int );
	#else
	m_Exp_Time.Format("%d", 50);
	#endif

	//	m_Exp_Time = "50";
	//  x_0 = 234;			// Координаты левого верхнего угла
	//  y_0 = 41;			// Координаты левого верхнего угла
	x_0 = 200;				// Координаты левого верхнего угла
	y_0 = 41;				// Координаты левого верхнего угла
    gr1_x_0 = x_0;
	gr1_y_0 = 887;			// Координаты 0 первого графика
	gr2_x_0 = 1244;
    gr2_y_0 = y_0  + 581;	// Координаты 0 второго графика  //  -1
	x_cg = 10;
	y_cg = 10;
    palitra256 = false;
	is_StartWaitMeasure = false;
	// Имитация данных
	DataArr = (LPDWORD)GlobalAlloc(GMEM_FIXED, 782*582);
	ByteArr = (LPBYTE)GlobalAlloc(GMEM_FIXED, 782*582*3+ 2*782);
	//D6_Arr = (PFLOAT)GlobalAlloc(GMEM_FIXED, 1000);
	D6_Arr= (PFLOAT)malloc(2);
	//PFLOAT D6_Arr;
	Pen10.CreatePen(PS_SOLID,1,RGB(255,0,0));
	Pen11.CreatePen(PS_SOLID,1,RGB(255,255,0));
	Pen12.CreatePen(PS_SOLID,1,RGB(0,255,127));// зеленый
	Pen13.CreatePen(PS_SOLID,1,RGB(223,115,255));// розовый
	Pen16.CreatePen(PS_SOLID,1,RGB(140,127,245));// синий

	//Bmp_File_Name = "F:\\Documents and Settings\\Ar-han\\Мои документы\\Visual Studio 2008\\Projects\\CPP Demo4\\My_BMP_USB.bmp";
	//Bmp_File_Name = "С:\\Program Files\\CPP Demo4\\My_BMP_USB.bmp";
	
	Bmp_File_Name = "C:\\BMP_FILES\\My_BMP_USB.bmp";
	Bmp_File_Name_var = Bmp_File_Name;
	Store_up_pic = false;
	Num_Store_up_pic = 0;
	Num_Read_saved_pic = 0;
	m_che1 = false;
	m_che2 = false;
	m_che3 = false;
	m_che4 = false;
	m_che6 = true;
	m_dia  = true;
	m_approx_b = false;
	m_fast_mode_b = true;	
	N_count_EN = false;	
	N_Read_EN = false;	
	f_level_change = false;	
	sr_shelf = 0;	
	Error_File = false;	
	First_On_Ser_Def_Edge = true;	
	First_Read_Bmp = true;	
	nW = 20; // temp Wheight 
	fc =1;
	for (int i=0; i<782 ; i++)	{
		OLD_STR_1[i] =  0;
		OLD_STR_2[i] =  0;
	}
	color=GetSysColor(COLOR_3DFACE);  // цвет фона окна
	Pen15.CreatePen(PS_SOLID,1,color); // цвет фона окна
	m_find_cg = false;
	m_ucg_b = true;
	susp_proc2 = false;
	D6_old = 0;
	New_point = false;
	Only_Del = false;
	/*
	image = 0;
	dst = 0;
	erode = 0;
	
	open = 0;
	close = 0;
	gradient = 0;
	tophat = 0;
	blackhat = 0;
	
	src = 0;
	dst = 0;
	dst2 = 0;
	*/
	//_____	
	//pMetaFileDC = new CMetaFileDC();
	// pMetaFileDC ->Create();	
}


void CCPPDemoDlg::DoDataExchange(CDataExchange* pDX)
{ 
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCPPDemoDlg)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
	DDX_Text(pDX, IDC_SERIAL, m_strSN);
	DDX_Control(pDX, IDC_LIST1, m_List);
	DDX_Control(pDX, IDC_LIST2, m_Col_List);
	DDX_Control(pDX, IDC_LIST3, m_List_BMP);
	DDX_Control(pDX, IDC_LIST4, m_List_Pix);
	DDX_Control(pDX, IDC_EDIT2, m_num_str);
	DDX_Text(pDX, IDC_EDIT2, Num_srtr_val);

	DDX_Text(pDX, IDC_EDIT3, m_colomn);
	DDX_Control(pDX, IDC_LIST6, List_Colomn);
	DDX_Control(pDX, IDC_LIST5, m_List5);
	DDX_Control(pDX, IDC_CHECK1, m_check1);
	DDX_Control(pDX, IDC_CHECK2, m_check2);
	DDX_Control(pDX, IDC_CHECK3, m_check3);
	DDX_Control(pDX, IDC_CHECK4, m_check4);
	DDX_Control(pDX, IDC_CHECK5, m_diagram);

	DDX_Text(pDX, IDC_EDIT1, m_level_val);


	DDX_Control(pDX, IDC_BUTTON9, Ok_level_control);
	DDX_Control(pDX, IDC_CHECK6, m_check6);

	DDX_Text(pDX, IDC_EDIT4, m_Exp_Time);
	DDX_Control(pDX, IDC_CHECK7, m_ucg);
	DDX_Text(pDX, IDC_Dia, m_Diam);
	DDX_Control(pDX, IDC_Dia, m_Diam_contr);
	//	DDX_Check(pDX, IDC_CHECK8, m_approx);
	//	DDX_Control(pDX, IDC_CHECK8, m_approx_c);
	DDX_Control(pDX, IDC_CHECK9, app_c);
	DDX_Control(pDX, IDC_CHECK10, m_fast_mode);
	DDX_Text(pDX, IDC_s_temp, Temp_text);
}

BEGIN_MESSAGE_MAP(CCPPDemoDlg, CDialog)
	//{{AFX_MSG_MAP(CCPPDemoDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_StartWaitMeasureBUTTON, OnStartWaitMeasureBUTTON)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_CameraResetBUTTON, OnBnClickedCameraresetbutton)
	ON_BN_CLICKED(IDC_GetSerialNumberBUTTON, OnBnClickedGetserialnumberbutton)
	ON_STN_CLICKED(IDC_SERIAL, &CCPPDemoDlg::OnStnClickedSerial)
	ON_BN_CLICKED(IDC_BUTTON1, &CCPPDemoDlg::OnBnClickedButton1)
//	ON_BN_CLICKED(IDC_BUTTON2, &CCPPDemoDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_READ_BMP, &CCPPDemoDlg::OnBnClickedReadBmp)
	ON_BN_CLICKED(IDOK, &CCPPDemoDlg::OnBnClickedOk)
	ON_LBN_SELCHANGE(IDC_LIST3, &CCPPDemoDlg::OnLbnSelchangeList3)
	ON_EN_CHANGE(IDC_EDIT2, &CCPPDemoDlg::OnEnChangeEdit2)
	ON_BN_CLICKED(IDC_BUT_N_Str, &CCPPDemoDlg::OnBnClickedButNStr)
	ON_LBN_SELCHANGE(IDC_LIST4, &CCPPDemoDlg::OnLbnSelchangeList4)
//	ON_LBN_SELCHANGE(IDC_LIST5, &CCPPDemoDlg::OnLbnSelchangeList5)
	ON_EN_CHANGE(IDC_EDIT3, &CCPPDemoDlg::OnEnChangeEdit3)
	ON_LBN_SELCHANGE(IDC_LIST6, &CCPPDemoDlg::OnLbnSelchangeList6)
	ON_BN_CLICKED(IDC_BUTTON4, &CCPPDemoDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_Store, &CCPPDemoDlg::OnBnClickedStore)
//	ON_BN_CLICKED(IDC_BUTTON5, &CCPPDemoDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CCPPDemoDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &CCPPDemoDlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON8, &CCPPDemoDlg::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON11, &CCPPDemoDlg::OnBnClickedButton11)	
	ON_BN_CLICKED(IDC_CHECK1, &CCPPDemoDlg::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_CHECK2, &CCPPDemoDlg::OnBnClickedCheck2)
	ON_BN_CLICKED(IDC_CHECK3, &CCPPDemoDlg::OnBnClickedCheck3)
	ON_BN_CLICKED(IDC_CHECK4, &CCPPDemoDlg::OnBnClickedCheck4)
	ON_BN_CLICKED(IDC_CHECK5, &CCPPDemoDlg::OnBnClickedCheck5)
	ON_MESSAGE(WM_THREAD_Redraw_W, &CCPPDemoDlg::Red_W )
	ON_BN_CLICKED(IDC_BUTTON9, &CCPPDemoDlg::OnBnClickedButton9)
	ON_EN_CHANGE(IDC_EDIT1, &CCPPDemoDlg::OnEnChangeEdit1)	
	ON_BN_CLICKED(IDC_CHECK6, &CCPPDemoDlg::OnBnClickedCheck6)
	ON_BN_CLICKED(IDC_BUTTON10, &CCPPDemoDlg::OnBnClickedButton10)
	ON_BN_CLICKED(IDC_BUTTON5, &CCPPDemoDlg::OnBnClickedButton5)
	ON_EN_CHANGE(IDC_EDIT4, &CCPPDemoDlg::OnEnChangeEdit4)
	ON_BN_CLICKED(IDC_CHECK7, &CCPPDemoDlg::OnBnClickedCheck7)
	ON_STN_CLICKED(IDC_Dia, &CCPPDemoDlg::OnStnClickedDia)
	ON_LBN_SELCHANGE(IDC_LIST2, &CCPPDemoDlg::OnLbnSelchangeList2)
	//ON_BN_CLICKED(IDC_CHECK8, &CCPPDemoDlg::OnBnClickedCheck8)
	ON_BN_CLICKED(IDC_CHECK9, &CCPPDemoDlg::OnBnClickedCheck9)
	ON_BN_CLICKED(IDC_CHECK10, &CCPPDemoDlg::OnBnClickedCheck10)
	ON_STN_CLICKED(IDC_s_temp, &CCPPDemoDlg::OnStnClickedstemp)
	ON_BN_CLICKED(IDC_BUTTON_Get_One_Pic, &CCPPDemoDlg::OnBnClickedButtonGetOnePic)
	ON_BN_CLICKED(IDC_BUTTON_Get_One_Pic_and_store, &CCPPDemoDlg::OnBnClickedButtonGetOnePicandstore)
END_MESSAGE_MAP()
	/////////////////////////////////////////////////////////////////////////////
	// CCPPDemoDlg message handlers

BOOL CCPPDemoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	// Add "About..." menu item to system menu.
	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);
	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	SetWindowPos(&wndTopMost, 0, 0, ::GetSystemMetrics(SM_CXSCREEN), ::GetSystemMetrics(SM_CYSCREEN) ,SWP_SHOWWINDOW);
	m_diagram.SetCheck(1);	
	m_check6.SetCheck(1);	
	m_ucg.SetCheck(1);	
	m_fast_mode.SetCheck(1);
	#if !defined DEBUG_MD_PART 
		m_usbCCD.InitInstance();
	#else
	//#if defined DEBUG_MD_PART 
		camera = cvCaptureFromCAM(CV_CAP_ANY);
		//cvSetCaptureProperty(camera, CV_CAP_PROP_FRAME_WIDTH, 1280); // width of viewport of camera
		//cvSetCaptureProperty(camera, CV_CAP_PROP_FRAME_HEIGHT, 720); // height of ...
		cvSetCaptureProperty(camera, CV_CAP_PROP_FRAME_WIDTH, 800); // width of viewport of camera
		cvSetCaptureProperty(camera, CV_CAP_PROP_FRAME_HEIGHT, 600); // height of ...
	#endif
	//m_approx_c.SetCheck(1);	
	LOGFONT lf =  { 32, 0, 0, 0, FW_BOLD, 0, 0, 0, 
			RUSSIAN_CHARSET, OUT_TT_ONLY_PRECIS, CLIP_DEFAULT_PRECIS,
			PROOF_QUALITY, VARIABLE_PITCH | FF_ROMAN, NULL } ;
			font.CreateFontIndirect( &lf ) ;
			m_Diam_contr.SetFont(&font);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CCPPDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CCPPDemoDlg::OnPaint() 
{
	if (IsIconic())	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else	{
		CDialog::OnPaint();  
		// -----------------------------my -----------------------------------
		dc2=GetWindowDC();
		if (cbmfile!=NULL) {
			//StretchDIBits(dc2->m_hDC,232,41,782,582,0,0,782,582,cbmfile->lpBMP ,cbmfile->lpInfo,DIB_RGB_COLORS,SRCCOPY);  
			//StretchDIBits(dc2->m_hDC,232,41,782,582,0,0,782,582,cbmfile->lpBMP ,cbmfile->lpInfo,DIB_PAL_COLORS,SRCCOPY);  
			//    работает
			CDC dcTemp; 
			dcTemp.CreateCompatibleDC(dc2); 
			dcTemp.SelectObject(cbmfile-> m_bmpBitmap); 
			BITMAP bm;
			if (cbmfile-> m_bmpBitmap.GetSafeHandle()!=NULL) 
				cbmfile->m_bmpBitmap.GetBitmap(&bm);
			dc2->BitBlt(x_0,y_0,bm.bmWidth,bm.bmHeight,&dcTemp,0,0,SRCCOPY);  // 234, 41
			//dc2->MoveTo(gr2_x_0 , gr2_y_0);        //  горизонтальная линия
			//dc2->LineTo(gr2_x_0 - 500 ,gr2_y_0 );  //  горизонтальная линия
			if (is_Data_Light)	{
				if (m_che1)	{
					dc2->SelectObject(&Pen10);  // ок работает
					// Rise_Line
					dc2->MoveTo(xRise_t1, yRise_t1);  //  вертикальная линия
					dc2->LineTo(xRise_t2, yRise_t2);  //  вертикальная линия
					//_______
					// Fall_Line
					dc2->MoveTo(xFall_t1, yFall_t1);  //  вертикальная линия
					dc2->LineTo(xFall_t2, yFall_t2);  //  вертикальная линия
					//_______
					dc2->SelectObject(&Pen10);  // ок работает
				}
				if (m_che2) {
					// Rise_2_Line
					dc2->SelectObject(&Pen11);  // ок работает  // желтый цвет
					dc2->MoveTo(xRise2_t1, yRise2_t1);  //  вертикальная линия
					dc2->LineTo(xRise2_t2, yRise2_t2);  //  вертикальная линия
					// Fall_2_Line
					dc2->MoveTo(xFall2_t1, yFall2_t1);  //  вертикальная линия
					dc2->LineTo(xFall2_t2, yFall2_t2);  //  вертикальная линия
					//_______
					dc2->SelectObject(&Pen10);  // ок работает
					//_________
				}
				if (m_che3) {
					// Rise_3_Line
					dc2->SelectObject(&Pen12);  // ок работает  // малиновый цвет
					dc2->MoveTo(xRise3_t1, yRise3_t1);  //  вертикальная линия
					dc2->LineTo(xRise3_t2, yRise3_t2);  //  вертикальная линия
					// Fall_3_Line
					dc2->MoveTo(xFall3_t1, yFall3_t1);  //  вертикальная линия
					dc2->LineTo(xFall3_t2, yFall3_t2);  //  вертикальная линия
					//_______
					dc2->SelectObject(&Pen10);  // ок работает
				}
				if (m_che4) {
					// Rise_4_Line
					//dc2->SelectObject(&Pen13);  // ок работает  // розовый
					dc2->SelectObject(&Pen16);  // ок работает  // синий
					dc2->MoveTo(xRise4_t1, yRise4_t1);  //  вертикальная линия
					dc2->LineTo(xRise4_t2, yRise4_t2);  //  вертикальная линия
					// Fall_4_Line
					dc2->MoveTo(xFall4_t1, yFall4_t1);  //  вертикальная линия
					dc2->LineTo(xFall4_t2, yFall4_t2);  //  вертикальная линия
					//_______
					dc2->SelectObject(&Pen10);  // ок работает
				}
				if ((m_che6) && (m_ucg_b) && (m_find_cg))  {     //  sign5  центр тяжести, пересечение контуров
					//dc2->SelectObject(&Pen16);  // ок работает  // синий
					dc2->SelectObject(&Pen13);  // ок работает  // розовый
					// // Rise_5_Line
					xRise5_t1 = x_0 + x_c1;
					xRise5_t2 = xRise5_t1;
					yRise5_t1 = y_0;
					yRise5_t2 = y_0 + cbmfile->lpHeader->biHeight;
					dc2->MoveTo(xRise5_t1, yRise5_t1);  //  вертикальная линия
					dc2->LineTo(xRise5_t2, yRise5_t2);  //  вертикальная линия
					// Fall_5_Line
					xFall5_t1 = x_0 + x_c2;
					xFall5_t2 = xFall5_t1;
					yFall5_t1 = y_0;
					yFall5_t2 = y_0 + cbmfile->lpHeader->biHeight;
					//_
					dc2->MoveTo(xFall5_t1, yFall5_t1);  //  вертикальная линия
					dc2->LineTo(xFall5_t2, yFall5_t2);  //  вертикальная линия
					dc2->SelectObject(&Pen10);  // ок работает
				}
				//_________							
				if (m_dia) {
					/*
					dc2->SelectObject(&Pen10);  // ок работает
					dc2->MoveTo(xStr_t1, yStr_t1);  //  горизонтальная линия
					dc2->LineTo(xStr_t2, yStr_t2);  //  горизонтальная линия
					dc2->MoveTo(xCol_t1, yCol_t1);  //  вертикальная линия
					dc2->LineTo(xCol_t2, yCol_t2);  //  вертикальная линия
					*/
					//  цетр тяжести    x_cg, y_cg
					//x_0, y_0
	
					//if (m_find_cg)
					if ((m_ucg_b) && (m_find_cg)) {
						dc2->SelectObject(&Pen13);  //   розовый
						dc2->MoveTo(x_0, y_0 + y_cg);
						dc2->LineTo(x_0 + 782, y_0 + y_cg);  //  горизонтальная линия
						/*
						dc2->MoveTo(x_0 + x_cg, y_0);  //  вертикальная линия
						dc2->LineTo(x_0 + x_cg, y_0 + 582);  //  вертикальная линия
						*/
					} 
					else {   // Маркеры 
						dc2->SelectObject(&Pen10);  // ок работает
						dc2->MoveTo(xStr_t1, yStr_t1);  //  горизонтальная линия	 
						dc2->LineTo(xStr_t2, yStr_t2);  //  горизонтальная линия
						dc2->MoveTo(xCol_t1, yCol_t1);  //  вертикальная линия	 
						dc2->LineTo(xCol_t2, yCol_t2);  //  вертикальная линия
					}
					// end of  цетр тяжести
					// график диаметра 
					int ic = 0;
					int ic1 = 0;
					//CString TTT;
					int L_g_d = 255;
					if (New_point)	{
						New_point = false;
						// Стирание старого
						dc2->SelectObject(&Pen15);  // цвет фона окна
						int D_val = 0;
						int D_val_1 = 0;
						for (int i = Old_i_count_glob - L_g_d; i< Old_i_count_glob; i++) {
							ic1 ++;
							if (i <= 1) i = 1;	
							D_val = (int)(D6_Arr[i]/4);
							D_val_1 = (int)(D6_Arr[i+1]/4);
							dc2->MoveTo(gr1_x_0 + 790 + ic1, gr1_y_0 - D_val); 
							dc2->LineTo(gr1_x_0 + 790 + ic1+1, gr1_y_0  - D_val_1 ); 
					}
					if (!Only_Del) {    // рисование нового		
						dc2->SelectObject(&Pen10);  //  красный
						for (int i = i_count_glob - L_g_d; i< i_count_glob; i++) {
							ic ++;
							if (i <= 1) i = 1;
							D_val = (int)(D6_Arr[i]/4);
							D_val_1 = (int)(D6_Arr[i+1]/4);
							dc2->MoveTo(gr1_x_0 + 790 + ic, gr1_y_0 - D_val);
							dc2->LineTo(gr1_x_0 + 790 + ic+1, gr1_y_0  - D_val_1 ); 
						}
						Old_i_count_glob = i_count_glob;
					}
					else 
						Only_Del = false;   
				}	// end of is_Data_Light
				// End of // график диаметра 
				// ****** стирание старого графика 1  *******
				dc2->SelectObject(&Pen15);      // цвет фона окна
				dc2->MoveTo(gr1_x_0, gr1_y_0);  // 
				for (int i = 0;  i< cbmfile->lpHeader->biWidth ; i++)  {   //  рис граф 1
					dc2->LineTo(gr1_x_0 + i, gr1_y_0 - OLD_STR_1[i] ); 
				}
				// ****** end of стир. стар. граф.  ******
				// ****** стирание старого уровня ******
				//if (f_level_change)   // уровень
				//{
				//f_level_change = false;
				dc2->MoveTo(gr1_x_0, gr1_y_0 - Old_level_val);
				dc2->LineTo(gr1_x_0 + 782,  gr1_y_0 - Old_level_val);
				//}
				// end of  ****** стирание старого уровня  ******
				// рисование нового уровня
				if (m_che4) {
					dc2->SelectObject(&Pen10);  //  красный
					dc2->MoveTo(gr1_x_0, gr1_y_0 - level_val_int);
					dc2->LineTo(gr1_x_0 + 782,  gr1_y_0 - level_val_int);
					Old_level_val = level_val_int;
				}
				// end of рисование нового уровня
				//  ******    График 1  ******
				if ((m_ucg_b) && (m_find_cg)) {		
					N_Str_OnPaint = 582 - y_cg;
					dc2->SelectObject(&Pen13);  // розовый
				}	
				else  {
					N_Str_OnPaint = N_Str_int;
					dc2->SelectObject(&Pen10);  //  красный
				}
				dc2->MoveTo(gr1_x_0, gr1_y_0);  //  
				for (int i = 0;  i< cbmfile->lpHeader->biWidth ; i++)	{		//  рис граф 1
					int temp_y;
					temp_y = Get_Pixel( i + 1, N_Str_OnPaint ) ;
					dc2->LineTo(gr1_x_0 + i, gr1_y_0 - temp_y );   // i + 1  ?
					OLD_STR_1[i] = temp_y;
				}   // end рис граф 1
				// __	end of График 1
				// ****** стирание старого графика 2  *******
				dc2->SelectObject(&Pen15);  // цвет фона окна
				dc2->MoveTo(gr2_x_0, gr2_y_0);  //  
				for (int i = 0;  i< cbmfile->lpHeader->biHeight; i++)	{		//  рис граф 1
					dc2->LineTo(gr2_x_0  - OLD_STR_2[i] , gr2_y_0 -  i ); 
				}
				// ****** END OF стирание старого графика 2  *******
				// График 2 
				if ((m_ucg_b) && (m_find_cg))	{
					dc2->SelectObject(&Pen13);  // розовый
					N_Colomn_int_OnPaint = x_cg;
				}
				else	{
					N_Colomn_int_OnPaint = N_Colomn_int;
					dc2->SelectObject(&Pen10);  //  красный
				}
				dc2->MoveTo(gr2_x_0, gr2_y_0);  //  
				for (int i = 0;  i< cbmfile->lpHeader->biHeight ; i++)	{		//  рис граф 2
					int temp_x;
					temp_x = Get_Pixel( N_Colomn_int_OnPaint , i + 1 );
					dc2->LineTo(gr2_x_0  - temp_x , gr2_y_0 -  i ); 
					OLD_STR_2[i] = temp_x;
				}
				// __	end of График 2
				}	// end of m_dia
			}	// end of is_Data_Light
		}	 
	}
}


// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CCPPDemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CCPPDemoDlg::OnStartWaitMeasureBUTTON() 
{
	is_StartWaitMeasure = true;
	int u1, co1;
	//CString s_data;						// 1111111 NEW  Ошибка
	// TODO: Add your control notification handler code here
	#if !defined DEBUG_MD_PART
		if ( m_usbCCD.Attach())	{
			if (m_usbCCD.SetExpTime(m_usbCCD.Exp_Time_int))	{} //  m_strSN.Format("%d",50);
				m_usbCCD.GetData();
			// Spectra processing
			//	  double mean = 0.0;
			//	  for (int i=0; i<m_usbCCD.m_nNumPixelsH; i++)
			//	    mean += m_usbCCD.m_pData[i];
			//	  mean /= m_usbCCD.m_nNumPixelsH;
				
			//	m_usbCCD.GetSerialNum(m_strSN); // 1111111  NEW
			//s_data = "66";
			//m_strSN = s_data; //atoi(55);        // 1111111 NEW
			//m_strSN.Format("%d",m_usbCCD.m_nNumPixelsH);   // 1111111 NEW
			//m_strSN.Format("%d",m_usbCCD.m_dwDeviceMode);   // 1111111 NEW
			//m_strSN.Format("%d",m_usbCCD.m_pData[1]);   // 1111111 NEW
			//	itoa(i1,szString,10);
			//m_strSN.Format("%d",szString);   // 1111111 NEW
			//u1 = m_usbCCD.m_pData[1] >> 4; // делить на 16  //u1 = 0xfff >> 4;   
			// co1 = u1 + (u1 << 8)+ (u1 << 16);
			//m_strSN.Format("%d",co1);   // 1111111 NEW
			//	UpdateData(FALSE);                
		}
	#endif
}

void CCPPDemoDlg::OnBnClickedCameraresetbutton()
{
	#if !defined DEBUG_MD_PART
		if ( m_usbCCD.Attach())		{
		m_usbCCD.Reset();
		}
	#endif
}

void CCPPDemoDlg::OnBnClickedGetserialnumberbutton()
{
	#if !defined DEBUG_MD_PART
		if ( m_usbCCD.Attach())
			m_usbCCD.GetSerialNum(m_strSN);
		UpdateData(FALSE);	
	#endif
}

void CCPPDemoDlg::OnStnClickedSerial()
{
	// TODO: Add your control notification handler code here
}

void CCPPDemoDlg::OnBnClickedButton1()
{
	#if !defined DEBUG_MD_PART
		if (is_StartWaitMeasure == false) CCPPDemoDlg::OnStartWaitMeasureBUTTON();
		int u, co;
		CMetaFileDC* pMetaFileDC;
		CDC* dc3;
		dc3=GetDC();
		//	pMetaFileDC = new CMetaFileDC();  // работает
		//	pMetaFileDC ->Create();   // работает
		//	pMetaFileDC-> SetPixel(240 ,20,200);              // работает
		//	HMETAFILE MetaFileHandle = pMetaFileDC-> Close();  // работает
		//	dc3-> PlayMetaFile(MetaFileHandle);                 // работает
		//  /*
		for (int r=0; r < 582; r++)	{		// m_usbCCD.m_nNumPixelsH
			for (int c=0; c < 782; c++)	{	// m_usbCCD.m_nNumPixelsH
				u = m_usbCCD.m_pData[c + 782* r] >> 4;
				co = u  + (u << 8)+ (u << 16);
				dc3-> SetPixel(231 + c ,12 + r,co); // работает
				//	pMetaFileDC-> SetPixel(230 + c ,10 + r,co); // работает
				//	pMetaFileDC-> SetPixel(c ,r,co); // работает
			}
		} 
		//HMETAFILE MetaFileHandle = pMetaFileDC-> Close();  // работает
		//CopyMetaFile(MetaFileHandle, "painter.wmf");  // работает
		///dc3-> PlayMetaFile(MetaFileHandle);
		/*
		CMetaFileDC* ReplacementMetaFile = new CMetaFileDC();
		ReplacementMetaFile ->Create();
		ReplacementMetaFile ->PlayMetaFile(MetaFileHandle);
		// /*
		DeleteMetaFile(MetaFileHandle);
		delete  pMetaFileDC;
		pMetaFileDC = ReplacementMetaFile;
		dc3-> PlayMetaFile(MetaFileHandle);
		*/
		//  */
		//-----
	#endif
}
void CCPPDemoDlg::OnBnClickedReadBmp()
{
	// TODO: Add your control notification handler code here
	if (cbmfile!=NULL) delete cbmfile;
	cbmfile = new CDib(Bmp_File_Name);
	//cbmfile = new CDib("F:\\windows\\my1.bmp");  // forest 24
	//cbmfile = new CDib("F:\\windows\\My_BMP_USB.bmp");  // ____________
	//cbmfile = new CDib("F:\\windows\\24B_Frorest_100_100.bmp");
	//cbmfile = new CDib("F:\\windows\\red_black.bmp");
	//cbmfile = new CDib("F:\\windows\\47_48.bmp");
	//cbmfile = new CDib("F:\\windows\\46_46.bmp");
	//cbmfile = new CDib("F:\\windows\\45_45.bmp");
	//cbmfile = new CDib("F:\\windows\\my1pal.bmp");
	//cbmfile = new CDib("F:\\windows\\picture.bmp");
	//cbmfile = new CDib("F:\\windows\\My_BMP.bmp");
	//cbmfile = new CDib("F:\\windows\\48_48_256c.bmp");
	//cbmfile = new CDib("F:\\windows\\48_48_256c_3.bmp");
	//cbmfile = new CDib("F:\\windows\\48_48_24b_1.bmp");	
	//cbmfile = new CDib("F:\\windows\\46_46_24b_1.bmp");	
	//cbmfile = new CDib("F:\\windows\\red_black.bmp");
	//cbmfile = new CDib("F:\\windows\\46_46_256c.bmp");
	//cbmfile = new CDib("F:\\windows\\4_4_256c.bmp");
	//cbmfile = new CDib("F:\\windows\\8_8_256c.bmp");
	//cbmfile = new CDib("F:\\windows\\1.bmp");
	//cbmfile = new CDib("F:\\windows\\47_47_256c.bmp");
	//cbmfile = new CDib("F:\\windows\\45_45_256c.bmp");
	//cbmfile = new CDib("F:\\windows\\my10_10.bmp");
	//cbmfile = new CDib("F:\\windows\\bitmap2.bmp");
	//cbmfile = new CDib("F:\\windows\\6_6_gray.bmp");  //16 цв
	//cbmfile = new CDib("F:\\windows\\6_6_string.bmp");
	//cbmfile = new CDib("F:\\windows\\6_6_gray_24.bmp");
	//cbmfile = new CDib("F:\\windows\\6_6_col_24.bmp");
	On_Read_BMP = true;
	/*
    gr1_x_0 = 234;
	gr1_y_0 = 971; // Координаты 0 первого графика
	gr2_x_0 = 1288;
	gr2_y_0 = y_0  + cbmfile->lpHeader->biHeight - 1; // Координаты 0 второго графика  //  -1
	*/
	RedrawWindow();
	//m_List.AddString("aaa");
	//UpdateData(false);
	//m_strSN.Format("%d",co1);   // 1111111 NEW
	CString arg, arg_i;
	CString Col_arg_0, Col_arg_1, Col_arg_2, Col_arg_3;
	int col_index;
	arg.Format("%d",cbmfile->lpHeader->biBitCount);
	m_List.AddString("lpHeader->biBitCount= " +arg);
	arg.Format("%d",cbmfile->lpHeader->biClrImportant);
	m_List.AddString("lpHeader->biClrImportant= " +arg);
	arg.Format("%d",cbmfile->lpHeader->biClrUsed);
	m_List.AddString("lpHeader->biClrUsed= " +arg);
	arg.Format("%d",cbmfile->lpHeader->biCompression);
    m_List.AddString("lpHeader->biCompression= " +arg);
	arg.Format("%d",cbmfile->lpHeader->biHeight);
	m_List.AddString("lpHeader->biHeight= " +arg);
	arg.Format("%d",cbmfile->lpHeader->biPlanes);
	m_List.AddString("lpHeader->biPlanes= " +arg);
	arg.Format("%d",cbmfile->lpHeader->biSize);
	m_List.AddString("lpHeader->biSize= " +arg);
	arg.Format("%d",cbmfile->lpHeader->biSizeImage);
	m_List.AddString("lpHeader->biSizeImage= " +arg);
	arg.Format("%d",cbmfile->lpHeader->biWidth);
	m_List.AddString("lpHeader->biWidth= " +arg);
	arg.Format("%d",cbmfile->lpHeader->biXPelsPerMeter);
	m_List.AddString("lpHeader->biXPelsPerMeter= " +arg);
	arg.Format("%d",cbmfile->lpHeader->biYPelsPerMeter);
	m_List.AddString("lpHeader->biYPelsPerMeter= " +arg);
	arg.Format("%d",cbmfile->lpBMP);
	//arg.Format("%c",cbmfile->lpBMP);
	m_List.AddString("lpBMP= " +arg);
	arg.Format("%d",cbmfile->lpInfo->bmiHeader);
	m_List.AddString("lpInfo->bmiHeader= " +arg);
	arg.Format("%d",cbmfile->lpInfo->bmiColors->rgbBlue);
	m_List.AddString("lpInfo->bmiColors->rgbBlue= " +arg);
	arg.Format("%d",cbmfile->lpInfo->bmiColors->rgbGreen);
	m_List.AddString("lpInfo->bmiColors->rgbGreen= " +arg);
	arg.Format("%d",cbmfile->lpInfo->bmiColors->rgbRed);
	m_List.AddString("lpInfo->bmiColors->rgbRed= " +arg);
	arg.Format("%d",cbmfile->lpInfo->bmiColors->rgbReserved);
	m_List.AddString("lpInfo->bmiColors->rgbReserved= " +arg);
	arg.Format("%d",cbmfile->Bmp_bfType);
	m_List.AddString("Bmp_bfType= " +arg);
	arg.Format("%d",cbmfile->Bmp_bfSize);
	m_List.AddString("Bmp_bfSize= " +arg);
	arg.Format("%d",cbmfile->Bmp_bfOffBits);
	m_List.AddString("Bmp_bfOffBits= " +arg);
	//Bmp_sizetable
	arg.Format("%d", cbmfile->Bmp_sizetable);
	m_List.AddString("Bmp_sizetable= " +arg);
	//Bmp_num
	arg.Format("%d", cbmfile->Bmp_num);
	m_List.AddString("Bmp_num= " +arg);
	//Bmp_bmf
	arg.Format("%d", cbmfile->Bmp_bmf);
	m_List.AddString("Bmp_bmf= " +arg);
	//Bmp_BMP_1
	arg.Format("%d", cbmfile->Bmp_BMP_1);
	m_List.AddString("Bmp_BMP_1= " +arg);
	//lpRGB+0
	arg.Format("%d", *(cbmfile->lpRGB));
	m_List.AddString("lpRGB+0= " +arg);
	//Bmp_sizebmp
	arg.Format("%d", cbmfile->Bmp_sizebmp);
	m_List.AddString("Bmp_sizebmp= " +arg);
	int c_n;
	if (cbmfile->Bmp_sizebmp > 2000) {
		c_n = 2000;
	}
	else  
		c_n = cbmfile->Bmp_sizebmp;
	//*************____________   Палитра
	if (cbmfile->lpHeader->biBitCount != 24)   { 	
		//*************____________   Палитра
		arg.Format("%d",  cbmfile->Bmp_num );  // число цветов в таблице
		m_Col_List.AddString("Кол-во цветов= " +arg);  // Bmp_num
		//m_Col_List
		int i4;
		for (int i=0; i< cbmfile->Bmp_num; i++) {   // 16 раз //256 раз
			i4 = i * 4;
			Col_arg_0.Format("%d",  cbmfile->x_Bmp[40 + i4] );  // синий
			Col_arg_1.Format("%d",  cbmfile->x_Bmp[40 + i4 + 1] );  // зеленый
			Col_arg_2.Format("%d",  cbmfile->x_Bmp[40 + i4 + 2] );    //  красный
			Col_arg_3.Format("%d",  cbmfile->x_Bmp[40 + i4 + 3] );  
			arg_i.Format("%d", i);
			m_Col_List.AddString("Color_MAP_" +  arg_i + " =" +Col_arg_2 + " " +  Col_arg_1 + " " + Col_arg_0);// + "    " + Col_arg_3);
		}
		// Массив пикселей
		// Палитра 16 цветов  ( biBitCount == 4 )	
		int  f_start_4;
		CString f_i, f_i1;	
		int c_pos_pix_in_str;
		int c_str;
		int c_pix_out;
		int c_byte_read;
		int c_n_4;
		int c_biw;		
		f_start_4 =  cbmfile->Bmp_bfOffBits -  cbmfile->Bmp_bmf; // смещение к битам без заголовка // 104  для 16 цветов
		arg.Format("%d", f_start_4);  
		m_List_BMP.AddString("Address_pix=" +arg);
		if  (cbmfile->lpHeader->biBitCount == 4) {
			palitra256 = false;
			if (cbmfile->lpHeader->biHeight > 100)  { //  ---------- не больше ста строк __  дисплей --------
				c_n_4 = 100;                        //  ---------- не больше ста строк __  дисплей --------
			}
		else  c_n_4 = cbmfile->lpHeader->biHeight;
		c_pix_out = 1;
		c_byte_read = 0;
		for(c_str=0; c_str < c_n_4; c_str++ )	{		// строки     ---------- не больше ста строк __  дисплей --------
			//  _____________строки
			c_pos_pix_in_str = 1;  // позиция пикселя в строке
			c_biw = cbmfile->lpHeader->biWidth/2;
			//   Строка 1   Определение кол-ва байт в строке 
			if ( cbmfile->lpHeader->biWidth % 2  != 0)  { 	//(cbmfile->lpHeader->biWidth)
				c_biw = cbmfile->lpHeader->biWidth/2 + 1 ;
			}
			//   Строка 1  
			for (int i=0; i<c_biw; i++)   {	 // biWidth/2 раз
				// f_start_4 = 104;
				f_i.Format("%d", c_pix_out );
				// ______________ старшие пол байта
				arg.Format("%d",  (cbmfile->x_Bmp[f_start_4 + c_byte_read]) >> 4 );  // старшие пол байта
				m_List_BMP.AddString("Pix[" + f_i + "]= " +arg);
				c_pos_pix_in_str = c_pos_pix_in_str + 1;   // позиция пикселя в строке
				c_pix_out = c_pix_out + 1;
				f_i.Format("%d", c_pix_out );
				if (c_pos_pix_in_str   <=   cbmfile->lpHeader->biWidth)	{
					// ______________ младшие пол байта
					arg.Format("%d",  (cbmfile->x_Bmp[f_start_4 + c_byte_read]) & 15   ); // младшие пол байта
					m_List_BMP.AddString("Pix[" + f_i + "]= " +arg);
					c_pos_pix_in_str = c_pos_pix_in_str + 1;   // позиция пикселя в строке
					c_pix_out = c_pix_out + 1;
					f_i.Format("%d", c_pix_out );
				}  //  _______ of         c_pos_pix_in_str <= cbmfile->lpHeader->biWidth
			c_byte_read = c_byte_read + 1;  // число прочитанных байт
			} // end of строка 1
	
			//*** определение смещения 
			if ( cbmfile->lpHeader->biWidth % 4  != 0)	{  //(cbmfile->lpHeader->biWidth)
				if ( cbmfile->lpHeader->biWidth % 4  == 2 )
					c_byte_read = c_byte_read  +	1;  //  (4 - cbmfile->lpHeader->biWidth % 4) ;
				if ( cbmfile->lpHeader->biWidth % 4  == 1 )
					c_byte_read = c_byte_read  +	1;  //  (4 - cbmfile->lpHeader->biWidth % 4) ;
			}
			//  **** end of   определение смещения 
			} //end of строки
		}//  *******END OF  *************** палитра 16 цветов*************************
	
		//  ********************** палитра 256 цветов*************************
		CString C_arg_0;
		CString C_arg_1;
		CString C_arg_2;
		CString C_arg_3;
		
		if  (cbmfile->lpHeader->biBitCount == 8)	{	
			palitra256 = true;
			if (cbmfile->lpHeader->biHeight > 10)	{//  ---------- не больше  десяти/ Ста строк __  дисплей --------
				c_n_4 = 10;                        //  ---------- не больше десяти/ Ста  строк __  дисплей --------
			}
			else	
				c_n_4 = cbmfile->lpHeader->biHeight;
			c_pix_out = 1;
			c_byte_read = 0;	
			for(c_str=0; c_str < c_n_4; c_str++ )	{		// строки     ---------- не больше ста строк __  дисплей --------
				//  _____________строки
				c_pos_pix_in_str = 1;  // позиция пикселя в строке
				//  Строка 1  
				for (int i=0; i<cbmfile->lpHeader->biWidth; i++)	{    // biWidth
					// f_start_4 = 104;
					f_i.Format("%d", c_pix_out );
					// ______________ считывание байта
					arg.Format("%d",  cbmfile->x_Bmp[f_start_4 + c_byte_read ] );  // считывание байта
					m_List_BMP.AddString("Pix[" + f_i + "]= " +arg);
					col_index = cbmfile->x_Bmp[f_start_4 + c_byte_read ];
					C_arg_0.Format("%d",  cbmfile->x_Bmp[39 + col_index] );  // синий   
					C_arg_1.Format("%d",  cbmfile->x_Bmp[39  + 1 + col_index] );  // зеленый
					C_arg_2.Format("%d",  cbmfile->x_Bmp[39  + 2 + col_index] ); //  красный
					C_arg_3.Format("%d",  cbmfile->x_Bmp[39  + 3 + col_index] );   
					m_List_Pix.AddString("Data_" +  f_i + " =" + C_arg_2 + " " + C_arg_1 + " " + C_arg_0);
					c_pos_pix_in_str = c_pos_pix_in_str + 1;   // позиция пикселя в строке
					c_pix_out = c_pix_out + 1;
					f_i.Format("%d", c_pix_out );
					c_byte_read = c_byte_read + 1;  // число прочитанных байт		
				} // end of строка 1
				//*** определение смещения 	
				if ( cbmfile->lpHeader->biWidth % 4  != 0)	{	//(cbmfile->lpHeader->biWidth)	
					if ( cbmfile->lpHeader->biWidth % 4  == 1 )	
						c_byte_read = c_byte_read  +	3;  //  (4 - cbmfile->lpHeader->biWidth % 4);	
					if ( cbmfile->lpHeader->biWidth % 4  == 2 )	
						c_byte_read = c_byte_read  +	2;  //  (4 - cbmfile->lpHeader->biWidth % 4) ;
					if ( cbmfile->lpHeader->biWidth % 4  == 3 )
						c_byte_read = c_byte_read  +	1;  //  (4 - cbmfile->lpHeader->biWidth % 4) ;
				}
			//  **** end of   определение смещения 	
			} //end of строки
		} //  *******END OF  *************** палитра 256 цветов*************************
	}  // *** END OF !=24b **********
	if  (cbmfile->lpHeader->biBitCount == 24)	{	// Полноцветное изображение
		palitra256 = false;
		m_Col_List.AddString("Палитра цветов отсутствует");  // Bmp_num
		m_List_BMP.AddString("24 bits");
		arg.Format("%d", cbmfile->lpHeader->biWidth);
		m_List_BMP.AddString("lpHeader->biWidth= " +arg);
		int f_start = 40;
		CString f_col_1, f_col_2, f_col_3, f_i, f_hi;
		int h_max_string = 10;  // Отображение на экране не более 10 строк
		if (cbmfile->lpHeader->biHeight < 10) h_max_string = cbmfile->lpHeader->biHeight;
		for (int hi= 0; hi < h_max_string; hi++)	{
			//  Первая строка
			for (int i=0; i< cbmfile->lpHeader->biWidth; i++)	{	// ширина строки
				f_col_1.Format("%d", cbmfile->x_Bmp[f_start]);
				f_col_2.Format("%d", cbmfile->x_Bmp[f_start + 1]);
				f_col_3.Format("%d", cbmfile->x_Bmp[f_start + 2]);
				f_i.Format("%d", i + 1);
				f_hi.Format("%d", hi + 1);
				m_List_BMP.AddString("Str_" + f_hi + "_Num[" + f_i + "]= "+ f_col_1 + " " + f_col_2 + " " + f_col_3);
				f_start = f_start + 3;
			}
			//*** определение смещения 
			if ( cbmfile->lpHeader->biWidth % 4  != 0)	{	//(cbmfile->lpHeader->biWidth)
				f_start = f_start +	(4 - cbmfile->lpHeader->biWidth % 4) ;
			}
			//  **** end of   определение смещения 
		}  ///******* for (int hi
	}
	UpdateData(false);
}

void CCPPDemoDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	/*
	    // освобождаем ресурсы
        cvReleaseImage(&image);
        cvReleaseImage(&dst);
        cvReleaseImage(&erode);    
        // удаляем окно
        cvDestroyWindow("original");
        cvDestroyWindow("erode");
	*/
	#if defined DEBUG_MD_PART
		cvReleaseCapture( &camera ); 
	#endif
	DestroyWindow();
}

void CCPPDemoDlg::OnLbnSelchangeList3()
{
	// TODO: Add your control notification handler code here
}

void CCPPDemoDlg::OnEnChangeEdit2()
{
	UpdateData(true);

	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	// TODO:  Add your control notification handler code here
}

void CCPPDemoDlg::OnBnClickedButNStr()  // Ok
{
	/*
	if (On_Read_BMP != true)	{ ``
		CCPPDemoDlg::OnBnClickedReadBmp();
	}
	*/
	CCPPDemoDlg::OnReadMyBmp_Mark();
	int f_pix_N_str;
	CString Pix_Str, a_p_i;
	CString Col_pix_0;  // синий
	CString Col_pix_1;  // зеленый
	CString Col_pix_2;  //  красный
	int i3, i_4, ff_start_4;
	ff_start_4 =  cbmfile->Bmp_bfOffBits -  cbmfile->Bmp_bmf; // смещение к битам без заголовка
	// Строка
	N_Str_int = atoi(Num_srtr_val);  
	if (( N_Str_int> 0 ) && (N_Str_int<= cbmfile->lpHeader->biHeight)) {
		// Корректная строка
		N_Str.Format("%d", N_Str_int); 
	} 	
	else	{ 
		N_Str_int = 1;
		N_Str.Format("%d", 1); // Первая строка
		Num_srtr_val = "1";
		UpdateData(false);
	}
	// ______
	// Столбец
	N_Colomn_int =atoi(m_colomn);
	if (( N_Colomn_int> 0 ) && (N_Colomn_int<= cbmfile->lpHeader->biWidth)) {
		// Корректный столбец
		N_Col.Format("%d", N_Colomn_int);
	} 
	else 	{
		N_Colomn_int = 1;
		N_Col.Format("%d", N_Colomn_int); // Первая строка
		m_colomn = "1";
		UpdateData(false);
	}
	//1 // Data_Light(N_Str_int, N_Colomn_int);
	// __________ Палитра 256 цветов__   
	if (cbmfile->lpHeader->biBitCount == 8) 	{
		f_pix_N_str = FindFirstPixel_256(N_Str_int - 1); //  Определение первого пикселя заданной строки
		m_List_Pix.ResetContent();
		List_Colomn.ResetContent();
		//	m_List_Pix.AddString("строка= " + N_Str);
		First_Pix_Str.Format("%d", f_pix_N_str); 
		m_List_Pix.AddString("Cтрока= " + N_Str); //  + " --> Ном. пер. пик= " + First_Pix_Str);
		//	First_Pix_Col.Format("%d", N_Colomn_int); 
		List_Colomn.AddString("Колонка= " + N_Col);  // + " --> Ном. пер. пик= " + N_Col);
		//  ____ 256 цветов
		//  Вывод заданной строки  
		for (int i=0; i< cbmfile->lpHeader->biWidth; i++)		{
			int n_in_tab;
			//i_4 = i * 4;
			n_in_tab =   4 * ( cbmfile->x_Bmp[ff_start_4 + i+ f_pix_N_str] );
			Col_pix_0.Format("%d",  cbmfile->x_Bmp[ 40 + n_in_tab + 2] );  // синий
			Col_pix_1.Format("%d",   cbmfile->x_Bmp[ 40 + n_in_tab + 1]  );  // зеленый
			Col_pix_2.Format("%d",   cbmfile->x_Bmp[ 40 + n_in_tab + 0]  );    //  красный
			a_p_i.Format("%d", i);	
			m_List_Pix.AddString("Col_pix" +  a_p_i + " =" +Col_pix_0 + " " +  Col_pix_1 + " " + Col_pix_2);
		}
		//______________
		//  Вывод заданного столбца
		for (int i=0; i< cbmfile->lpHeader->biHeight; i++)	{ 
			CString a_p_f;
			int byte_address;
			int Value_of_byte_address;
			int n_in_tab; // номер байта в таблице цветов
			f_pix_N_str = FindFirstPixel_256(i); // первый пиксел заданной строки i
			byte_address = f_pix_N_str +  N_Colomn_int - 1; // адрес байта  заданной строки i, заданного столбца N_Str_int
			Value_of_byte_address = cbmfile->x_Bmp[ff_start_4 + byte_address]; // смещение в таблице цветов
			//	a_p_f.Format("%d", byte_address);
			//	List_Colomn.AddString(a_p_f);
			//	a_p_f.Format("%d", Value_of_byte_address);
			//	List_Colomn.AddString(a_p_f);
			n_in_tab =   4 * Value_of_byte_address;
			Col_pix_0.Format("%d",  cbmfile->x_Bmp[ 40 + n_in_tab + 2] );  // синий
			Col_pix_1.Format("%d",   cbmfile->x_Bmp[ 40 + n_in_tab + 1]  );  // зеленый
			Col_pix_2.Format("%d",   cbmfile->x_Bmp[ 40 + n_in_tab + 0]  );    //  красный
			a_p_i.Format("%d", i);
			List_Colomn.AddString("Col_pix" +  a_p_i + " =" +Col_pix_0 + " " +  Col_pix_1 + " " + Col_pix_2);
		}    // End__of___ Вывод заданного столбца
	}   // __End of________ Палитра 256 цветов 
	// __ Полноцветное изображение   
	// _____________24__________24_____________24
	if  (cbmfile->lpHeader->biBitCount == 24)	{
		f_pix_N_str = FindFirstPixel_24b(N_Str_int-1); //Определение первого пикселя заданной строки  24
		m_List_Pix.ResetContent();
		List_Colomn.ResetContent();
		//	m_List_Pix.AddString("строка= " + N_Str);
		First_Pix_Str.Format("%d", f_pix_N_str); 
		m_List_Pix.AddString("Cтрока= " + N_Str);// + " --> Ном. пер. пик= " + First_Pix_Str);
		//	First_Pix_Col.Format("%d", 33); 
		List_Colomn.AddString("Колонка= " + N_Col);// + " --> Ном. пер. пик= " + N_Col); //First_Pix_Col);
		//  ____ 24 bits
		//  Вывод заданной строки   
		for (int i=0; i< cbmfile->lpHeader->biWidth; i++)	{
			//x_Bmp[First_Pix_Str + i];
			i3 = i * 3;
			Col_pix_0.Format("%d",  cbmfile->x_Bmp[40 + f_pix_N_str + i3] );  // синий
			Col_pix_1.Format("%d",  cbmfile->x_Bmp[40 + f_pix_N_str + i3 + 1] );  // зеленый
			Col_pix_2.Format("%d",  cbmfile->x_Bmp[40 + f_pix_N_str + i3 + 2] );    //  красный
			a_p_i.Format("%d", i);
			m_List_Pix.AddString("Col_pix" +  a_p_i + " =" +Col_pix_0 + " " +  Col_pix_1 + " " + Col_pix_2);
		}
		//  Вывод заданного столбца
		for (int i=0; i< cbmfile->lpHeader->biHeight; i++)	{
			int FP;
			int N_pix;
			CString a_p_f;
			FP = FindFirstPixel_24b(i);
			N_pix = FP + (N_Colomn_int - 1)*3;
			//	a_p_f.Format("%d", N_pix);
			//	List_Colomn.AddString(a_p_f);
			Col_pix_0.Format("%d",  cbmfile->x_Bmp[40 + N_pix + 0] );  // синий
			Col_pix_1.Format("%d",  cbmfile->x_Bmp[40 + N_pix + 1] );  // зеленый
			Col_pix_2.Format("%d",  cbmfile->x_Bmp[40 + N_pix + 2] );    //  красный
			a_p_i.Format("%d", i);
			List_Colomn.AddString("Col_pix" +  a_p_i + " =" +Col_pix_0 + " " +  Col_pix_1 + " " + Col_pix_2);
		}
	} // // __End of____ полноцветное изображение 
	//	a_p_i.Format("%d", Get_Pixel( N_Colomn_int, N_Str_int) ); // x, y
	//	m_List5.AddString("Get_Pixel(" + N_Col + "," + N_Str + ") = " +  a_p_i);
	CCPPDemoDlg::OnReadMyBmp_Mark();
	RedrawWindow();
	//OnPaint();
}

void CCPPDemoDlg::OnLbnSelchangeList4()
{
	// TODO: Add your control notification handler code here
}

void CCPPDemoDlg::OnLbnSelchangeList5()
{
	// TODO: Add your control notification handler code here
}

void CCPPDemoDlg::OnEnChangeEdit3()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	UpdateData(true);
}

void CCPPDemoDlg::OnLbnSelchangeList6()
{
	// TODO: Add your control notification handler code here
}

int CCPPDemoDlg::FindFirstPixel_24b(int n_str)
{
	int ff_pix_N_str;
	if (cbmfile->lpHeader->biWidth % 4 == 0)	{
		ff_pix_N_str = (cbmfile->lpHeader->biWidth) * n_str * 3 ; 
	}
	if (cbmfile->lpHeader->biWidth % 4 == 1)	{	
		ff_pix_N_str = (cbmfile->lpHeader->biWidth) * n_str * 3 + n_str * 3; 
	}	 
	if (cbmfile->lpHeader->biWidth % 4 == 2)	{
		ff_pix_N_str = (cbmfile->lpHeader->biWidth) * n_str * 3 + n_str * 2; 
	}	 
	if (cbmfile->lpHeader->biWidth % 4 == 3)	{
		ff_pix_N_str = (cbmfile->lpHeader->biWidth) * n_str * 3+ n_str * 1; 
	}
	return ff_pix_N_str;
}

int CCPPDemoDlg::FindFirstPixel_256(int n_str)
{
	int ff_pix_N_str;
	if (cbmfile->lpHeader->biWidth % 4 == 0)	{
		ff_pix_N_str = (cbmfile->lpHeader->biWidth) * n_str ; 
	}
	if (cbmfile->lpHeader->biWidth % 4 == 1)	{	
		ff_pix_N_str = (cbmfile->lpHeader->biWidth) * n_str + n_str * 3; 
	}	 
	if (cbmfile->lpHeader->biWidth % 4 == 2)	{
		ff_pix_N_str = (cbmfile->lpHeader->biWidth) * n_str + n_str * 2; 
	}	 
	if (cbmfile->lpHeader->biWidth % 4 == 3)	{
		ff_pix_N_str = (cbmfile->lpHeader->biWidth) * n_str + n_str * 1; 
	}
return ff_pix_N_str;
}

BOOL CCPPDemoDlg::StoreBitmapFile(LPCTSTR lpszFileName, HBITMAP HBM)
{
	BITMAP BM;
	BITMAPFILEHEADER BFH;
	LPBITMAPINFO BIP;	
	CDC* DC;
	LPBYTE Buf;
	DWORD ColorSize,DataSize;
	WORD BitCount;
	HANDLE FP;
	DWORD dwTemp;	
	GetObject(HBM, sizeof(BITMAP), (LPSTR)&BM);	
	BitCount = (WORD)BM.bmPlanes * BM.bmBitsPixel;
	switch (BitCount)	{
		case 1:
		case 4:
		case 8: 
		case 32:
			//ColorSize = sizeof(RGBQUAD) * (1 &lt;&lt; BitCount);
			ColorSize = sizeof(RGBQUAD) * (1 << BitCount);		
		break;  //   !!		
		case 16:
		case 24:
		ColorSize = 0;
	}
	/*	
		First_Pix_Str.Format("%d", BM.bmWidth); 
		m_List_Pix.AddString("BM.bmWidth= " + First_Pix_Str); 
		First_Pix_Str.Format("%d", ColorSize); 
		m_List_Pix.AddString("ColorSize= " + First_Pix_Str); 
		First_Pix_Str.Format("%d", BitCount); 
		m_List_Pix.AddString("BitCount= " + First_Pix_Str); 
		First_Pix_Str.Format("%d", sizeof(RGBQUAD)); 
		m_List_Pix.AddString("sizeof(RGBQUAD)= " + First_Pix_Str); 
		First_Pix_Str.Format("%d", 1 << BitCount); 
		m_List_Pix.AddString("1 << BitCount= " + First_Pix_Str); 
	*/
	DataSize = ((BM.bmWidth*BitCount+31) & ~31)/8*BM.bmHeight;
	/*
		First_Pix_Str.Format("%d", DataSize); 
		m_List_Pix.AddString("DataSize= " + First_Pix_Str); 	
	*/
	BIP=(LPBITMAPINFO)HeapAlloc(GetProcessHeap(),HEAP_ZERO_MEMORY,sizeof(BITMAPINFOHEADER)+ColorSize);
	/*
		First_Pix_Str.Format("%d", sizeof(BITMAPINFOHEADER)+ColorSize); 
		m_List_Pix.AddString("BITMAPINFOHEADER+CS= " + First_Pix_Str);
	*/
	BIP->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	BIP->bmiHeader.biWidth = BM.bmWidth;
	BIP->bmiHeader.biHeight = BM.bmHeight;
	BIP->bmiHeader.biPlanes = 1;
	BIP->bmiHeader.biBitCount = BitCount;
	BIP->bmiHeader.biCompression = 0;
	BIP->bmiHeader.biSizeImage = DataSize;
	BIP->bmiHeader.biXPelsPerMeter = 0;
	BIP->bmiHeader.biYPelsPerMeter = 0;	
	if (BitCount < 16) BIP->bmiHeader.biClrUsed = (1<<BitCount);	
	BIP->bmiHeader.biClrImportant = 0;	
	BFH.bfType = 0x4d42;	
	BFH.bfOffBits=sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)+ BIP->bmiHeader.biClrUsed * sizeof(RGBQUAD);
	/*
		First_Pix_Str.Format("%d", BFH.bfOffBits); 
		m_List_Pix.AddString("BFH.bfOffBits= " + First_Pix_Str); 
	*/	
	BFH.bfReserved1 = 0;
	BFH.bfReserved2 = 0;
	BFH.bfSize = BFH.bfOffBits + DataSize;
	/*
		First_Pix_Str.Format("%d", BFH.bfSize); 
		m_List_Pix.AddString("BFH.bfSizes= " + First_Pix_Str); 
	*/
	Buf = (LPBYTE)GlobalAlloc(GMEM_FIXED, DataSize);
	/*
		First_Pix_Str.Format("%d", BIP->bmiHeader.biClrUsed); 
		m_List_Pix.AddString("BIP->bmiHeader.biClrUsed= " + First_Pix_Str); 
	*/
	int RRet; 	
	DC = GetDC(); 
	RRet = GetDIBits(*DC, HBM, 0,(WORD)BM.bmHeight, Buf, BIP, DIB_RGB_COLORS);
	//GetDIBits(*DC, HBM, 0,(WORD)BM.bmHeight, Buf, BIP, DIB_PAL_COLORS);
	ReleaseDC(DC);	
	if (BitCount < 16) BIP->bmiHeader.biClrUsed = (1<<BitCount);  // второй раз !!
	/*
		First_Pix_Str.Format("%d", RRet); 
		m_List_Pix.AddString("RRet= " + First_Pix_Str); 
		First_Pix_Str.Format("%d", (WORD)BM.bmHeight); 
		m_List_Pix.AddString("(WORD)BM.bmHeight= " + First_Pix_Str); 
		First_Pix_Str.Format("%d", Buf[0]); 
		m_List_Pix.AddString(" Buf[0]= " + First_Pix_Str); 
		First_Pix_Str.Format("%d", Buf[1]); 
		m_List_Pix.AddString(" Buf[1]= " + First_Pix_Str); 
		First_Pix_Str.Format("%d",  Buf[2]); 
		m_List_Pix.AddString(" Buf[2]= " + First_Pix_Str); 
		First_Pix_Str.Format("%d",  Buf[3]); 
		m_List_Pix.AddString(" Buf[3]= " + First_Pix_Str); 
		First_Pix_Str.Format("%d",  Buf[4]); 
		m_List_Pix.AddString(" Buf[4]= " + First_Pix_Str); 
		First_Pix_Str.Format("%d", Buf[5]); 
		m_List_Pix.AddString(" Buf[5]= " + First_Pix_Str); 
		First_Pix_Str.Format("%d",  Buf[6]); 
		m_List_Pix.AddString(" Buf[6]= " + First_Pix_Str); 
		First_Pix_Str.Format("%d",  Buf[7]); 
		m_List_Pix.AddString(" Buf[7]= " + First_Pix_Str); 
		First_Pix_Str.Format("%d",  Buf[8]); 
		m_List_Pix.AddString(" Buf[8]= " + First_Pix_Str); 
		First_Pix_Str.Format("%d", (WORD)BM.bmHeight); 
		m_List_Pix.AddString("(WORD)BM.bmHeight= " + First_Pix_Str); 
	*/
	//HDC DC;
	//DC = GetDC(0); 
	//GetDIBits(DC, HBM, 0,(WORD)BM.bmHeight, Buf, BIP, DIB_RGB_COLORS); 
	//ReleaseDC(0, DC);
	FP=CreateFile(lpszFileName,GENERIC_READ | GENERIC_WRITE, 0, NULL,
	CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL); 
	WriteFile(FP,&BFH,sizeof(BITMAPFILEHEADER),&dwTemp,NULL); 
	WriteFile(FP,BIP,sizeof(BITMAPINFOHEADER) + BIP->bmiHeader.biClrUsed * sizeof(RGBQUAD),&dwTemp,NULL); 
	WriteFile(FP,Buf,DataSize,&dwTemp,NULL);
	/*
		First_Pix_Str.Format("%d", sizeof(BITMAPFILEHEADER)); 
		m_List_Pix.AddString("sizeof(BITMAPFILEHEADER)= " + First_Pix_Str); 
		First_Pix_Str.Format("%d", sizeof(BITMAPINFOHEADER) + BIP->bmiHeader.biClrUsed * sizeof(RGBQUAD)); 
		m_List_Pix.AddString("si + BIP)= " + First_Pix_Str); 
		First_Pix_Str.Format("%d", DataSize); 
		m_List_Pix.AddString("DataSize= " + First_Pix_Str); 
		First_Pix_Str.Format("%d", sizeof(BITMAPINFOHEADER)); 
		m_List_Pix.AddString("sizeof(BITMAPINFOHEADER)= " + First_Pix_Str); 
		First_Pix_Str.Format("%d", BIP->bmiHeader.biClrUsed * sizeof(RGBQUAD)); 
		m_List_Pix.AddString("BIP->Used * sof(RG= " + First_Pix_Str); 
		First_Pix_Str.Format("%d", sizeof(RGBQUAD)); 
		m_List_Pix.AddString("sizeof(RGBQUAD)= " + First_Pix_Str); 
		First_Pix_Str.Format("%d", BIP->bmiHeader.biClrUsed); 
		m_List_Pix.AddString("BIP->Used= " + First_Pix_Str); 
		First_Pix_Str.Format("%d", BIP->bmiHeader.biClrUsed); 
		m_List_Pix.AddString("BIP->bmiHeader.biClrUsed= " + First_Pix_Str); 
	*/
	CloseHandle(FP);
	GlobalFree((HGLOBAL)Buf);
	HeapFree(GetProcessHeap(),0,(LPVOID)BIP);	
	return(true);
}

//StoreBitmapFile("11111.bmp",(HBITMAP)bitmap-&gt;m_hObject);

void CCPPDemoDlg::OnBnClickedButton4()  //stor bmp
{
	#if !defined DEBUG_MD_PART  
		if (On_Read_BMP != true)	{
			CCPPDemoDlg::OnBnClickedReadBmp();
		}
		//CCPPDemoDlg::Data_To_DIB();
		CCPPDemoDlg::USB_Data_To_DIB();
	#endif	
	CCPPDemoDlg::StoreMyBmp();  
	// TODO: Add your control notification handler code here
	//CCPPDemoDlg::StoreBitmapFile("11111.bmp",(HBITMAP)bitmap->m_hObject);
	//CCPPDemoDlg::StoreBitmapFile("11111.bmp",(HBITMAP)cbmfile-> m_bmpBitmap);  // ч. к. 
		//CCPPDemoDlg::StoreBitmapFile("11111.bmp",(HBITMAP)cbmfile->lpBMP ); //580 mb
	CCPPDemoDlg::StoreBitmapFile("1.bmp",(HBITMAP)cbmfile->hIm);
	
	
}

void CCPPDemoDlg::Data_Light(int str, int col)
{
	//int x_0, y_0;  // Верхний левый угол
	//int x_t1, y_t1;  // Линия начало
	//int x_t2, y_t2;  // Линия конец
	// int xCol_t1, yCol_t1;  // Линия вертикальная начало
	// int xCol_t2, yCol_t2;  // Линия вертикальная конец
		
	// горизонтальная линия
	xStr_t1 = x_0;	
	yStr_t1 = y_0 + cbmfile->lpHeader->biHeight - str ;	
	yStr_t2 = yStr_t1;	
	xStr_t2 = xStr_t1 + cbmfile->lpHeader->biWidth;	
	// ---
	
	// Вертикальная линия	
	xCol_t1 = x_0 + col - 1; 
	xCol_t2 = xCol_t1;	
	yCol_t1 = y_0;
	yCol_t2 = y_0 + cbmfile->lpHeader->biHeight;
	// ---
	is_Data_Light  = 1;
}

int CCPPDemoDlg::Get_Pixel(int n_col, int n_str)  // x,y  (1,1 - первый)
{
	int n_in_tab;
	int f_pix_N_str;
	int ff_start_4;
	int ret;	
	if  (cbmfile->lpHeader->biBitCount == 8)  { // Палитра 256 цветов
		//if  (palitra256 == true)   // Палитра 256 цветов	
		ff_start_4 =  cbmfile->Bmp_bfOffBits -  cbmfile->Bmp_bmf; // смещение к битам без заголовка
		f_pix_N_str = FindFirstPixel_256(n_str-1);
		//n_in_tab =   4 * ( cbmfile->x_Bmp[ff_start_4 + f_pix_N_str + n_col] );
		n_in_tab =   4 * ( cbmfile->x_Bmp[ff_start_4 + f_pix_N_str + n_col-1] );
		ret = cbmfile->x_Bmp[ 40 + n_in_tab];  // красный;
	}
	if  (cbmfile->lpHeader->biBitCount == 24)	{  // 24b Полноцветное изображение
		f_pix_N_str = FindFirstPixel_24b(n_str-1);
		ret = cbmfile->x_Bmp[40 + f_pix_N_str + (n_col - 1) * 3];  // Red only
	}
return ret; 
}

void CCPPDemoDlg::StoreMyBmp()
{

	CString f_Name;
	CString aff;
	LPCTSTR lpszFileName;
	//Bmp_File_Name = "C:\\BMP_FILES\\My_BMP_USB.bmp";
	//LPCTSTR lpszFileName = "My_BMP_USB.bmp"; 
	//LPCTSTR lpszFileName = "F:\\Documents and Settings\\Ar-han\\Мои документы\\Visual Studio 2008\\Projects\\CPP Demo4\\My_BMP_USB.bmp"; 
	if (!Store_up_pic) 
		lpszFileName = Bmp_File_Name;
	else	{
		f_Name = Bmp_File_Name; 
		Num_Store_up_pic++;
		Num_pic.Format("%d", Num_Store_up_pic);
		f_Name.Insert(23, Num_pic);
		Bmp_File_Name_var = f_Name;
		lpszFileName = f_Name; // + Num_pic;
	}	
	#if !defined DEBUG_MD_PART 
		//f_Name = Bmp_File_Name; 
		//Num_pic = "0001";
		//f_Name.Insert(23,Num_pic);
		//m_List5.AddString("Name = " + f_Name);		
		BITMAP BM;
		BITMAPFILEHEADER BFH;
		LPBITMAPINFO BIP;	
		CDC* DC;
		LPBYTE Buf;
		DWORD ColorSize,DataSize;
		WORD BitCount;
		HANDLE FP;
		DWORD dwTemp;	
		BM.bmWidth = 782;	
		BM.bmHeight = 582;	
		//BM.bmHeight = 50;	
		//GetObject(HBM, sizeof(BITMAP), (LPSTR)&BM);	
		BitCount = 24;
		ColorSize = 0; 		
		DataSize = ((BM.bmWidth*BitCount+31) & ~31)/8*BM.bmHeight;	
		/*
			First_Pix_Str.Format("%d", DataSize); 
			m_List_Pix.AddString("DataSize= " + First_Pix_Str);	
		*/
		BIP=(LPBITMAPINFO)HeapAlloc(GetProcessHeap(),HEAP_ZERO_MEMORY,sizeof(BITMAPINFOHEADER)+ColorSize);
		/*
			First_Pix_Str.Format("%d", sizeof(BITMAPINFOHEADER)+ColorSize); 
			m_List_Pix.AddString("BITMAPINFOHEADER+CS= " + First_Pix_Str);
		*/
		BIP->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
		BIP->bmiHeader.biWidth = BM.bmWidth;
		BIP->bmiHeader.biHeight = BM.bmHeight;
		BIP->bmiHeader.biPlanes = 1;
		BIP->bmiHeader.biBitCount = BitCount;
		BIP->bmiHeader.biCompression = 0;
		BIP->bmiHeader.biSizeImage = DataSize;
		BIP->bmiHeader.biXPelsPerMeter = 0;
		BIP->bmiHeader.biYPelsPerMeter = 0;	
		if (BitCount < 16) 
			BIP->bmiHeader.biClrUsed = (1<<BitCount);	
		BIP->bmiHeader.biClrImportant = 0;	
		BFH.bfType = 0x4d42;	
		BFH.bfOffBits=sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)+ BIP->bmiHeader.biClrUsed * sizeof(RGBQUAD);
		/*
			First_Pix_Str.Format("%d", BFH.bfOffBits); 
			m_List_Pix.AddString("BFH.bfOffBits= " + First_Pix_Str); 
		*/
		
		BFH.bfReserved1 = 0;
		BFH.bfReserved2 = 0;
		BFH.bfSize = BFH.bfOffBits + DataSize;
		/*
			First_Pix_Str.Format("%d", BFH.bfSize); 
			m_List_Pix.AddString("BFH.bfSizes= " + First_Pix_Str); 
		*/
		Buf = (LPBYTE)GlobalAlloc(GMEM_FIXED, DataSize);
		/*
			First_Pix_Str.Format("%d", BIP->bmiHeader.biClrUsed); 
			m_List_Pix.AddString("BIP->bmiHeader.biClrUsed= " + First_Pix_Str); 
		*/
		int RRet; 	
		FP=CreateFile(lpszFileName,GENERIC_READ | GENERIC_WRITE, 0, NULL,
		CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL); 
		WriteFile(FP,&BFH,sizeof(BITMAPFILEHEADER),&dwTemp,NULL); 
		WriteFile(FP,BIP,sizeof(BITMAPINFOHEADER) + BIP->bmiHeader.biClrUsed * sizeof(RGBQUAD),&dwTemp,NULL); 
		WriteFile(FP,ByteArr,DataSize,&dwTemp,NULL);	
		//WriteFile(FP,Buf,DataSize,&dwTemp,NULL);
		//WriteFile(FP, m_usbCCD.m_pData ,DataSize,&dwTemp,NULL);	
		CloseHandle(FP);
		GlobalFree((HGLOBAL)Buf);
		HeapFree(GetProcessHeap(),0,(LPVOID)BIP);	
	#else
		#if !defined SAVE_PIC_IN_POTOK
			//lpszFileName
			//lpszFileName = Bmp_File_Name; //temp
			CStringA sB(lpszFileName);
			const char* filename = sB; 
			cvSaveImage(filename, frame);
		#endif
	#endif
}

void CCPPDemoDlg::Data_To_DIB()
{
	// DataArr
	// ByteArr
	int  Dob_In_Str ;
	CString TempStr;
	int N_Elem;	
	byte zx;	
	int N_Elem_int;
	int i,k;	
	N_Elem_int = 0;
	N_Elem = 0;	
	Dob_In_Str = 4  - (782 * 3) % 4;	
	for ( k = 0; k<50; k++)	{	// 582		
		for ( i = 0; i<782; i++)	{	
			zx = DataArr[N_Elem_int]/16;
			N_Elem_int ++;
			ByteArr[N_Elem] = zx;
			ByteArr[N_Elem + 1] = zx;
			ByteArr[N_Elem + 2] = zx;	
			//TempStr.Format("%d", ByteArr[N_Elem ]  ); 
			//m_List5.AddString("ByteArr[N_Elem ] = " +  TempStr);
			//TempStr.Format("%d", N_Elem  ); 
			//m_List5.AddString("N_Elem = " +  TempStr);
			N_Elem = 3 + N_Elem ;
			//TempStr.Format("%d", DataArr[N_Elem_int]  ); 
			//m_List5.AddString("DataArr[i] = " +  TempStr);
			//TempStr.Format("%d", zx  ); 
			//m_List5.AddString("zx = " +  TempStr);
		}
	N_Elem = N_Elem + Dob_In_Str;
	}
}

void CCPPDemoDlg::USB_Data_To_DIB(void)
{
#if !defined DEBUG_MD_PART 
	// DataArr
	// ByteArr
	int  Dob_In_Str ;
	CString TempStr;
	int N_Elem;	
	byte zx;	
	int i,k;
	int Out_N_Pixel;
	int Out_N_Byte;	
	int N_Elem_int;
	int out_n_str;  // Строка выходного массива  0-581
	int in_n_str;   // Строка входного массива   0-581
	int Out_N_colomn; 
	int Out_N_First_Byte_In_Str; // Номер первого байта в строке
	int Out_N_Pixel_In_Str;
	int Out_N_Byte_In_Str;	
	N_Elem_int = 0;
	N_Elem = 0;	
	int N_Byte_In_Str;  // Число байт в строке выходного массива
	Dob_In_Str = 4  - (782 * 3) % 4;  // Добавок к строке до 4 х байт
	N_Byte_In_Str = 782 * 3 + Dob_In_Str; // Число байт в строке выходного массива
	for ( k = 0; k<582; k++)	{	// 582
		in_n_str = k;
		out_n_str = 581 - in_n_str; 
		Out_N_First_Byte_In_Str =  N_Byte_In_Str * out_n_str;
		//TempStr.Format("%d", Out_N_First_Byte_In_Str  ); 
		//m_List5.AddString("Out_N_First_Byte_In_Str = " +  TempStr);
		for ( i = 0; i<782; i++)	{	// Out_N_Elem
			//zx = m_usbCCD.m_pData[N_Elem_int]/16;
			zx = m_usbCCD.m_pData[N_Elem_int] >> 4;
			N_Elem_int ++;
			Out_N_Pixel_In_Str = i;	
			Out_N_Byte_In_Str = Out_N_Pixel_In_Str * 3;
			Out_N_Byte = Out_N_First_Byte_In_Str + Out_N_Byte_In_Str;
			ByteArr[Out_N_Byte] = zx;
			ByteArr[Out_N_Byte + 1] = zx;
			ByteArr[Out_N_Byte + 2] = zx;	
		}	
	Out_N_Byte = Out_N_Byte + Dob_In_Str;  //	
	}
#else

#endif
}

void CCPPDemoDlg::OnBnClickedStore()
{
	CCPPDemoDlg::OnStartWaitMeasureBUTTON(); 
	CCPPDemoDlg::USB_Data_To_DIB();
	CCPPDemoDlg::StoreMyBmp();  
	CCPPDemoDlg::OnReadMyBmp();
	//CCPPDemoDlg::OnBnClickedButNStr();  // Ok
	//CCPPDemoDlg::Def_Edges_1();  
}

//____________________________

void CCPPDemoDlg::OnReadMyBmp()
{
	if (cbmfile!=NULL) 
		delete cbmfile;
	cbmfile = new CDib("F:\\Documents and Settings\\Ar-han\\Мои документы\\Visual Studio 2008\\Projects\\CPP Demo4\\My_BMP_USB.bmp");  // ____________
	On_Read_BMP = true;
	// gr1_x_0 = 234;
	//gr1_y_0 = 971; // Координаты 0 первого графика
	// gr2_x_0 = 1288;
	// gr2_y_0 = y_0  + cbmfile->lpHeader->biHeight - 1; // Координаты 0 второго графика  //  -1
	RedrawWindow();
	//m_List.AddString("aaa");
	//UpdateData(false);
	//m_strSN.Format("%d",co1);   // 1111111 NEW
	CString arg, arg_i;
	CString Col_arg_0, Col_arg_1, Col_arg_2, Col_arg_3;
	int col_index;
	arg.Format("%d",cbmfile->lpHeader->biBitCount);
	m_List.AddString("lpHeader->biBitCount= " +arg);
	arg.Format("%d",cbmfile->lpHeader->biClrImportant);
   	m_List.AddString("lpHeader->biClrImportant= " +arg);
	arg.Format("%d",cbmfile->lpHeader->biClrUsed);
	m_List.AddString("lpHeader->biClrUsed= " +arg);
	arg.Format("%d",cbmfile->lpHeader->biCompression);
    m_List.AddString("lpHeader->biCompression= " +arg);
	arg.Format("%d",cbmfile->lpHeader->biHeight);
	m_List.AddString("lpHeader->biHeight= " +arg);
	arg.Format("%d",cbmfile->lpHeader->biPlanes);
	m_List.AddString("lpHeader->biPlanes= " +arg);
	arg.Format("%d",cbmfile->lpHeader->biSize);
    m_List.AddString("lpHeader->biSize= " +arg);
	arg.Format("%d",cbmfile->lpHeader->biSizeImage);
	m_List.AddString("lpHeader->biSizeImage= " +arg);
	arg.Format("%d",cbmfile->lpHeader->biWidth);
    m_List.AddString("lpHeader->biWidth= " +arg);
	arg.Format("%d",cbmfile->lpHeader->biXPelsPerMeter);
	m_List.AddString("lpHeader->biXPelsPerMeter= " +arg);
	arg.Format("%d",cbmfile->lpHeader->biYPelsPerMeter);
	m_List.AddString("lpHeader->biYPelsPerMeter= " +arg);
	arg.Format("%d",cbmfile->lpBMP);
	//	arg.Format("%c",cbmfile->lpBMP);
	m_List.AddString("lpBMP= " +arg);
	arg.Format("%d",cbmfile->lpInfo->bmiHeader);
	m_List.AddString("lpInfo->bmiHeader= " +arg);
	arg.Format("%d",cbmfile->lpInfo->bmiColors->rgbBlue);
    m_List.AddString("lpInfo->bmiColors->rgbBlue= " +arg);
	arg.Format("%d",cbmfile->lpInfo->bmiColors->rgbGreen);
	m_List.AddString("lpInfo->bmiColors->rgbGreen= " +arg);
	arg.Format("%d",cbmfile->lpInfo->bmiColors->rgbRed);
    m_List.AddString("lpInfo->bmiColors->rgbRed= " +arg);
	arg.Format("%d",cbmfile->lpInfo->bmiColors->rgbReserved);
	m_List.AddString("lpInfo->bmiColors->rgbReserved= " +arg);
	arg.Format("%d",cbmfile->Bmp_bfType);
	m_List.AddString("Bmp_bfType= " +arg);
	arg.Format("%d",cbmfile->Bmp_bfSize);
	m_List.AddString("Bmp_bfSize= " +arg);
	arg.Format("%d",cbmfile->Bmp_bfOffBits);
	m_List.AddString("Bmp_bfOffBits= " +arg);
	//Bmp_sizetable
	arg.Format("%d", cbmfile->Bmp_sizetable);
	m_List.AddString("Bmp_sizetable= " +arg);
	//Bmp_num
	arg.Format("%d", cbmfile->Bmp_num);
	m_List.AddString("Bmp_num= " +arg);
	//Bmp_bmf
	arg.Format("%d", cbmfile->Bmp_bmf);
	m_List.AddString("Bmp_bmf= " +arg);
	//Bmp_BMP_1
	arg.Format("%d", cbmfile->Bmp_BMP_1);
	m_List.AddString("Bmp_BMP_1= " +arg);
	//lpRGB+0
	arg.Format("%d", *(cbmfile->lpRGB));
	m_List.AddString("lpRGB+0= " +arg);
	//Bmp_sizebmp
	arg.Format("%d", cbmfile->Bmp_sizebmp);
	m_List.AddString("Bmp_sizebmp= " +arg);
	int c_n;
	if (cbmfile->Bmp_sizebmp > 2000)	{
		c_n = 2000;
	}
	else  
		c_n = cbmfile->Bmp_sizebmp;
	
	//*************____________   Палитра
	if (cbmfile->lpHeader->biBitCount != 24)	{	//*************____________   Палитра
		arg.Format("%d",  cbmfile->Bmp_num );  // число цветов в таблице
		m_Col_List.AddString("Кол-во цветов= " +arg);  // Bmp_num
		//m_Col_List
		int i4;
		for (int i=0; i< cbmfile->Bmp_num; i++)	{	// 16 раз //256 раз
			i4 = i * 4;
			Col_arg_0.Format("%d",  cbmfile->x_Bmp[40 + i4] );  // синий
			Col_arg_1.Format("%d",  cbmfile->x_Bmp[40 + i4 + 1] );  // зеленый
			Col_arg_2.Format("%d",  cbmfile->x_Bmp[40 + i4 + 2] );    //  красный
			Col_arg_3.Format("%d",  cbmfile->x_Bmp[40 + i4 + 3] );  
			arg_i.Format("%d", i);
			m_Col_List.AddString("Color_MAP_" +  arg_i + " =" +Col_arg_2 + " " +  Col_arg_1 + " " + Col_arg_0);// + "    " + Col_arg_3);
		}
		// Массив пикселей
		// Палитра 16 цветов  ( biBitCount == 4 )
		int  f_start_4;
		CString f_i, f_i1;
		int c_pos_pix_in_str;
		int c_str;
		int c_pix_out;
		int c_byte_read;
		int c_n_4;
		int c_biw;
		f_start_4 =  cbmfile->Bmp_bfOffBits -  cbmfile->Bmp_bmf; // смещение к битам без заголовка // 104  для 16 цветов
		arg.Format("%d", f_start_4);  
		m_List_BMP.AddString("Address_pix=" +arg);
		if  (cbmfile->lpHeader->biBitCount == 4)	{
			palitra256 = false;
			if (cbmfile->lpHeader->biHeight > 100)	{	//  ---------- не больше ста строк __  дисплей --------
				c_n_4 = 100;                        //  ---------- не больше ста строк __  дисплей --------
			}
			else  
				c_n_4 = cbmfile->lpHeader->biHeight;
			c_pix_out = 1;
			c_byte_read = 0;
			for	(c_str=0; c_str < c_n_4; c_str++ )	{	// строки     ---------- не больше ста строк __  дисплей --------
				//  _____________строки
				c_pos_pix_in_str = 1;  // позиция пикселя в строке
				c_biw = cbmfile->lpHeader->biWidth/2;
				//   Строка 1   Определение кол-ва байт в строке 
				if ( cbmfile->lpHeader->biWidth % 2  != 0)	{	//(cbmfile->lpHeader->biWidth)
					c_biw = cbmfile->lpHeader->biWidth/2 + 1 ;
				}
				//   Строка 1  
				for (int i=0; i<c_biw; i++)	{	// biWidth/2 раз
					// f_start_4 = 104;
					f_i.Format("%d", c_pix_out );
					// ______________ старшие пол байта
					arg.Format("%d",  (cbmfile->x_Bmp[f_start_4 + c_byte_read]) >> 4 );  // старшие пол байта
					m_List_BMP.AddString("Pix[" + f_i + "]= " +arg);
					c_pos_pix_in_str = c_pos_pix_in_str + 1;   // позиция пикселя в строке
					c_pix_out = c_pix_out + 1;
					f_i.Format("%d", c_pix_out );
					if (c_pos_pix_in_str   <=   cbmfile->lpHeader->biWidth)	{
						// ______________ младшие пол байта
						arg.Format("%d",  (cbmfile->x_Bmp[f_start_4 + c_byte_read]) & 15   ); // младшие пол байта
						m_List_BMP.AddString("Pix[" + f_i + "]= " +arg);
						c_pos_pix_in_str = c_pos_pix_in_str + 1;   // позиция пикселя в строке
						c_pix_out = c_pix_out + 1;
						f_i.Format("%d", c_pix_out );
					}  //  _______ of         c_pos_pix_in_str <= cbmfile->lpHeader->biWidth
				c_byte_read = c_byte_read + 1;  // число прочитанных байт
				} // end of строка 1
				//*** определение смещения 
				if ( cbmfile->lpHeader->biWidth % 4 != 0)	{	//(cbmfile->lpHeader->biWidth)
					if ( cbmfile->lpHeader->biWidth % 4 == 2 )
						c_byte_read = c_byte_read + 1;  //  (4 - cbmfile->lpHeader->biWidth % 4) ;
					if ( cbmfile->lpHeader->biWidth % 4 == 1)
						c_byte_read = c_byte_read  +	1;  //  (4 - cbmfile->lpHeader->biWidth % 4) ;
				}
				//  **** end of   определение смещения 
			} //end of строки
		}//  *******END OF  *************** палитра 16 цветов*************************
	
		//  ********************** палитра 256 цветов*************************
		CString C_arg_0;
		CString C_arg_1;
		CString C_arg_2;
		CString C_arg_3;
		if  (cbmfile->lpHeader->biBitCount == 8)	{ 
			palitra256 = true;
			if (cbmfile->lpHeader->biHeight > 10)	{	//  ---------- не больше  десяти/ Ста строк __  дисплей --------
				c_n_4 = 10;                        //  ---------- не больше десяти/ Ста  строк __  дисплей --------
			}
			else  
				c_n_4 = cbmfile->lpHeader->biHeight;
			c_pix_out = 1;
			c_byte_read = 0;
			for (c_str=0; c_str < c_n_4; c_str++ )	{	// строки     ---------- не больше ста строк __  дисплей --------
				//  _____________строки
				c_pos_pix_in_str = 1;  // позиция пикселя в строке
				//   Строка 1  
				for (int i=0; i<cbmfile->lpHeader->biWidth; i++)	{   // biWidth
					// f_start_4 = 104;
					f_i.Format("%d", c_pix_out );
					// ______________ считывание байта
					arg.Format("%d",  cbmfile->x_Bmp[f_start_4 + c_byte_read ] );  // считывание байта
					m_List_BMP.AddString("Pix[" + f_i + "]= " +arg);
					col_index = cbmfile->x_Bmp[f_start_4 + c_byte_read ];
					C_arg_0.Format("%d",  cbmfile->x_Bmp[39 + col_index] );  // синий   
					C_arg_1.Format("%d",  cbmfile->x_Bmp[39  + 1 + col_index] );  // зеленый
					C_arg_2.Format("%d",  cbmfile->x_Bmp[39  + 2 + col_index] ); //  красный
					C_arg_3.Format("%d",  cbmfile->x_Bmp[39  + 3 + col_index] );   
					m_List_Pix.AddString("Data_" +  f_i + " =" + C_arg_2 + " " + C_arg_1 + " " + C_arg_0);
					c_pos_pix_in_str = c_pos_pix_in_str + 1;   // позиция пикселя в строке
					c_pix_out = c_pix_out + 1;
					f_i.Format("%d", c_pix_out );
					c_byte_read = c_byte_read + 1;  // число прочитанных байт
				} // end of строка 1
				//*** определение смещения 
				if ( cbmfile->lpHeader->biWidth % 4  != 0)	{	//(cbmfile->lpHeader->biWidth)
					if ( cbmfile->lpHeader->biWidth % 4  == 1 )
						c_byte_read = c_byte_read  +	3;  //  (4 - cbmfile->lpHeader->biWidth % 4) ;
					if ( cbmfile->lpHeader->biWidth % 4  == 2 )
						c_byte_read = c_byte_read  +	2;  //  (4 - cbmfile->lpHeader->biWidth % 4) ;
					if ( cbmfile->lpHeader->biWidth % 4  == 3 )
						c_byte_read = c_byte_read  +	1;  //  (4 - cbmfile->lpHeader->biWidth % 4) ;
				}
				//  **** end of   определение смещения 
			} //end of строки
		} //  *******END OF  *************** палитра 256 цветов*************************
	}  // *** END OF !=24b **********
	
	if  (cbmfile->lpHeader->biBitCount == 24)	{	// Полноцветное изображение
		palitra256 = false;
		m_Col_List.AddString("Палитра цветов отсутствует");  // Bmp_num
		m_List_BMP.AddString("24 bits");
		arg.Format("%d", cbmfile->lpHeader->biWidth);
		m_List_BMP.AddString("lpHeader->biWidth= " +arg);
		int f_start = 40;
		CString f_col_1, f_col_2, f_col_3, f_i, f_hi;
		int h_max_string = 10;  // Отображение на экране не более 10 строк
		if (cbmfile->lpHeader->biHeight < 10)
			h_max_string = cbmfile->lpHeader->biHeight;
		for (int hi= 0; hi < h_max_string; hi++)	{
			//  Первая строка
			for (int i=0; i< cbmfile->lpHeader->biWidth; i++)	{	// ширина строки	
				f_col_1.Format("%d", cbmfile->x_Bmp[f_start]);
				f_col_2.Format("%d", cbmfile->x_Bmp[f_start + 1]);
				f_col_3.Format("%d", cbmfile->x_Bmp[f_start + 2]);
				f_i.Format("%d", i + 1);
				f_hi.Format("%d", hi + 1);
				m_List_BMP.AddString("Str_" + f_hi + "_Num[" + f_i + "]= "+ f_col_1 + " " + f_col_2 + " " + f_col_3);
				f_start = f_start + 3;
			}
			//*** определение смещения 
			if ( cbmfile->lpHeader->biWidth % 4  != 0)	{	//(cbmfile->lpHeader->biWidth)
				f_start = f_start +	(4 - cbmfile->lpHeader->biWidth % 4) ;
			}	//  **** end of   определение смещения		 
		}  ///******* for (int hi
	}
	UpdateData(false);
}

void CCPPDemoDlg::OnBnClickedButton6()  //        Стоп       series
{
	m_fast_mode.EnableWindow(true); // 
	Is_Stop_Series = true;
	First_On_Ser_Def_Edge = true;
}

static UINT proc2(LPVOID Param)
{
	CCPPDemoDlg* myInstance = (CCPPDemoDlg*)Param;
	myInstance->Data_In_Potok();
	return 0;
}
	
void CCPPDemoDlg::Def_Edges_1(void)//  Def_Edges_1 Max_Fall
{
	m_List5.ResetContent();
	CString aff, aff1, aff2;
	int diff_fall;
	int a1, a2;
	int i1;
	int m_fall;
	int n_m_max_fall;	
	int m_rise;
	int n_m_max_rise;
	int diff_rise;
	int Num_String;	
	int b_area_rise;
	int e_area_rise;
	int lenght_area_rise;
	int max_lenght_area_rise;
	int b_max_lenght_area_rise;
	bool last_diff_rise; 	
	int b_area_fall;
	int e_area_fall;
	int lenght_area_fall;
	int max_lenght_area_fall;
	bool last_diff_fall;
	int b_max_lenght_area_fall;	
	int j;	
	last_diff_rise = false;
	max_lenght_area_rise = 0;
	lenght_area_rise = 0;
	b_max_lenght_area_rise= 1;
	b_area_rise = 0;
	last_diff_fall = false;
	max_lenght_area_fall = 0;
	lenght_area_fall = 0;
	b_max_lenght_area_fall= 1;
	b_area_fall = 1;
	//    ******     OpenCV   *********   
	IplImage *src=0, *dst=0, *dst2=0 ; 
	CvSeq* contours = 0;   
	CvMemStorage* storage = cvCreateMemStorage(0);
	int Nc = 0; 
	CString TempStr;
	CvPoint* p1;
	CvPoint* p2;
	int i11;
	int num_f_pix = 0;
	int h_line;
	src = cvLoadImage(Bmp_File_Name_var, 0);
    dst = cvCreateImage( cvSize(src->width, src->height), IPL_DEPTH_8U, 1);
	dst2 = cvCreateImage( cvSize(src->width, src->height), IPL_DEPTH_8U, 3);
	cvThreshold(src, dst, 100, 255, CV_THRESH_BINARY);
	//	cvAdaptiveThreshold(src, dst2, 250, CV_ADAPTIVE_THRESH_GAUSSIAN_C, CV_THRESH_BINARY , 7, 1);
	//	CV_ADAPTIVE_THRESH_MEAN_C   CV_ADAPTIVE_THRESH_GAUSSIAN_C   CV_THRESH_BINARY_INV   CV_THRESH_BINARY
	//	показываем результаты
	//	cvAdaptiveThreshold(src, dst, 255, CV_ADAPTIVE_THRESH_GAUSSIAN_C , CV_THRESH_BINARY, 21, 7);
	//  int Nc = cvFindContours( dst, storage, &contours, sizeof(CvContour), CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, cvPoint(0,0) ) ;
	//	CV_RETR_LIST
	//int Nc = cvFindContours( dst, storage, &contours, sizeof(CvContour), CV_RETR_LIST); //, CV_CHAIN_APPROX_SIMPLE, cvPoint(0,0) ) ;
	/*
	CvSeq* C_Max_area = 0;
	CvMoments moments;
	double m_x, m_y;
	double C_area;
	double C_area_max = 0;
	*/
	C_Max_area = 0;
	C_area_max = 0;
	//	CV_RETR_EXTERNAL  только внешние
	//	int Nc = cvFindContours( dst, storage, &contours, sizeof(CvContour), CV_RETR_EXTERNAL); //, CV_CHAIN_APPROX_SIMPLE, cvPoint(0,0) ) ;
	Nc = cvFindContours( dst, storage, &contours, sizeof(CvContour), CV_RETR_EXTERNAL); //, CV_CHAIN_APPROX_SIMPLE, cvPoint(0,0) ) ;
	if (Nc)	{
		if (m_approx_b)
			contours = cvApproxPoly( contours, sizeof(CvContour), storage, CV_POLY_APPROX_DP, 3, 1 );
		// 	точнее работает без аппроксимации
		//	m_Col_List.ResetContent();
		//	TempStr.Format("%d", Nc); 
		//	m_Col_List.AddString("Nc = " +  TempStr);
		for( CvSeq* c=contours; c!=NULL; c=c->h_next )	{
			C_area = cvContourArea(c);
			if (C_area < C_area_max)  {		// отрицательная площадь ??
				C_area_max = C_area;
				C_Max_area = c;
			}
		}
		if (C_Max_area)	{
			//if (C_area != 0)
			m_find_cg = true;
			cvContourMoments(C_Max_area, &moments);
			m_x = moments.m10/C_area_max;
			m_y = moments.m01/C_area_max;
			x_cg = -(int)m_x;
			//	y_cg = 582 + (int)m_y;
			y_cg = -(int)m_y;
			/*
			TempStr.Format("%f", moments.m00); 
			m_Col_List.AddString("C_area_max = " +  TempStr);		
			TempStr.Format("%d", 582 - y_cg); 
			m_Col_List.AddString("N_str_cg = " +  TempStr);		
			TempStr.Format("%d", x_cg); 
			m_Col_List.AddString("N_col_cg = " +  TempStr);
			*/
			//  def edge		
			/*
			CvPoint* p1;
			CvPoint* p2;
			int i1;
			int num_f_pix = 0;
			int h_line;
			*/
			//Some defines we left out of the book
			#define CVX_RED		CV_RGB(0xff,0x00,0x00)
			#define CVX_GREEN	CV_RGB(0x00,0xff,0x00)
			#define CVX_BLUE	CV_RGB(0x00,0x00,0xff)
			//  ****  h_line = 200;  ***
			if (m_ucg_b)	{
				h_line = y_cg;
			}
			else	{ 
				h_line = 582 - N_Str_int;
			}		
			for( int i=0; i<C_Max_area->total; ++i )	{
				i11 = i+1;
				p1 = CV_GET_SEQ_ELEM( CvPoint, C_Max_area, i );
				p2 = CV_GET_SEQ_ELEM( CvPoint, C_Max_area, i11 );
				//printf("(%d,%d,"    ",%d,%d)\n", p1->x, p1->y , p2->x, p2->y );
				if	(((p1->y >= h_line) && (p2->y < h_line)) || 
					((p1->y <= h_line) && (p2->y > h_line)) ||  
					((p1->y > h_line) && (p2->y == h_line)) ||
					((p1->y < h_line) && (p2->y == h_line)))	{ 	
					cvLine(dst, *p1, *p2, CV_RGB(255,255,255));	
					if (!num_f_pix)
						x_c1 = (double)(p2->x - p1->x) * (h_line - p1->y) / (p2->y - p1->y)  + p1->x;
					else 
						x_c2 = (double)(p2->x - p1->x) * (h_line - p1->y) / (p2->y - p1->y)  + p1->x;
					D6 = x_c2 - x_c1;
					num_f_pix++;
				}	
			}
			//cvLine(dst2, cvPoint(10,10), cvPoint(i_count_glob, D6_Arr[i_count_glob] ) , CVX_RED);
			//D6_old = D6;	
			/*
			if (x_c2 < x_c1) 
			{
				x_cb = x_c1;
				x_c1 = x_c2;
				x_c2 = x_cb;
			
				D6 = x_c2 - x_c1;
			}
			*/	
			//CString D_Str;
			//CString i_Count_Str;			
			if (D6 < 0) D6 = -D6;		
			//D_Str.Format("%.1f", D6);
			//i_Count_Str.Format("%d", i_count_glob);
			//D6_Arr = (PFLOAT)malloc(i_count_glob*sizeof(float));	
			/*
			D6_Arr = (PFLOAT)realloc(D6_Arr, (i_count_glob+1)*sizeof(float));	
			D6_Arr[i_count_glob] = D6;	
			D_file =fopen("C:\\BMP_FILES\\D_file.txt", "a");	
			fprintf(D_file, i_Count_Str);
			fprintf(D_file," ");
			fprintf(D_file, D_Str);
			fprintf(D_file,"\n");	
			fclose(D_file);	
			New_point = true;
			*/	
			/*
			TempStr.Format("%f", x_c1); 
			m_Col_List.AddString("x_c1 = " +  TempStr);	
			TempStr.Format("%f", x_c2); 
			m_Col_List.AddString("x_c2 = " +  TempStr);	
			TempStr.Format("%f", x_c2 - x_c1); 
			m_Col_List.AddString("D = " +  TempStr);
			*/	
			//m_Col_List.AddString("D = " +  TempStr);
			//m_List5.AddString("D = " +  TempStr);	
			//CFont* pfont;
			//m_Diam_contr.SetFont(pfont);	
			//CFont font;
			/*
			LOGFONT lf =  { 32, 0, 0, 0, FW_BOLD, 0, 0, 0, 
					RUSSIAN_CHARSET, OUT_TT_ONLY_PRECIS, CLIP_DEFAULT_PRECIS,
					PROOF_QUALITY, VARIABLE_PITCH | FF_ROMAN, NULL } ;
				font.CreateFontIndirect( &lf ) ;
			m_Diam_contr.SetFont(&font);
			*/	
		}  // end of c_max_area	
		else {
			m_find_cg = false;
		}		
		/*
		TempStr.Format("%f", C_area_max); 
		m_Col_List.AddString("C_area_max = " +  TempStr);	
		TempStr.Format("%d", contours->block_max); 
		m_Col_List.AddString("block_max = " +  TempStr);	
		TempStr.Format("%d", contours->delta_elems); 
		m_Col_List.AddString("delta_elems = " +  TempStr);	
		TempStr.Format("%d", contours->elem_size); 
		m_Col_List.AddString("elem_size= " +  TempStr);	
		TempStr.Format("%d", contours->first); 
		m_Col_List.AddString("first = " +  TempStr);	
		TempStr.Format("%d", contours->flags); 
		m_Col_List.AddString("flags = " +  TempStr);	
		TempStr.Format("%d", contours->free_blocks); 
		m_Col_List.AddString("free_blocks = " +  TempStr);	
		TempStr.Format("%d", contours->h_next); 
		m_Col_List.AddString("h_next = " +  TempStr);	
		TempStr.Format("%d", contours->h_prev); 
		m_Col_List.AddString("h_prev= " +  TempStr);	
		TempStr.Format("%d", contours->header_size); 
		m_Col_List.AddString("header_size = " +  TempStr);	
		TempStr.Format("%d", contours->ptr); 
		m_Col_List.AddString("ptr = " +  TempStr);		
		TempStr.Format("%d", contours->storage); 
		m_Col_List.AddString("storage = " +  TempStr);	
		TempStr.Format("%d", contours->total); 
		m_Col_List.AddString("total = " +  TempStr);	
		TempStr.Format("%d", contours->v_next); 
		m_Col_List.AddString("v_next= " +  TempStr);	
		TempStr.Format("%d", contours->v_prev); 
		m_Col_List.AddString("v_prev = " +  TempStr);
		*/
		if (m_find_cg)	{	
			D_Str.Format("%.1f", D6);
			m_Diam = "D = ";
			m_Diam.Append(D_Str);
			UpdateData(false);	
		}
		else {
			m_Diam = "";
			UpdateData(false);
			D6 = 0;
		}	
	}  // end of    if (Nc)
	else	{
		//m_Col_List.ResetContent();
		m_find_cg = false;
		m_Diam = "";
		UpdateData(false);
		D6 = 0;
	}	
	D_Str.Format("%.1f", D6);
	i_Count_Str.Format("%d", i_count_glob);
	D6_Arr = (PFLOAT)realloc(D6_Arr, (i_count_glob+1)*sizeof(float));
	D_file =fopen("C:\\BMP_FILES\\D_file.txt", "a");
	D6_Arr[i_count_glob] = D6;
	fprintf(D_file, i_Count_Str);
	fprintf(D_file," ");
	fprintf(D_file, D_Str);
	fprintf(D_file,"\n");	
	fclose(D_file);
	New_point = true;	
	int ic = 0;
	for (int i = i_count_glob - 200; i< i_count_glob; i++)	{
		ic ++;
		if (i <= 0) i = 1;
		cvLine(dst2, cvPoint(ic, 582 - D6_Arr[i]), cvPoint(ic+1,582 - D6_Arr[i+1] ) , CVX_RED);
	}
	#if defined SHOW_ADD_WINDOWS
		cvDrawContours( dst2, contours, CV_RGB(0,0,255), CV_RGB(0,255,0),2, 1, CV_AA, cvPoint(0,0) );	// синий	
		cvDrawContours( dst2, C_Max_area, CV_RGB(255,0,0), CV_RGB(0,255,0),0, 1, CV_AA, cvPoint(0,0) );	// красный	
		cvNamedWindow( "cvThreshold", 1 );
		cvNamedWindow( "cvFindContours", 1 );
		cvShowImage( "cvThreshold", dst);
		cvShowImage( "cvFindContours", dst2);
	#endif

	/*
	cvDrawContours( src, contours, CV_RGB(0,0,255), CV_RGB(0,255,0),2, 1, CV_AA, cvPoint(0,0) );	// синий	
	cvDrawContours( src, C_Max_area, CV_RGB(255,0,0), CV_RGB(0,255,0),0, 1, CV_AA, cvPoint(0,0) );	// красный	
	cvNamedWindow( "cvThreshold", 1 );
	cvShowImage( "cvThreshold", src);
	*/
	// end of OpenCv part
	/*
	cvReleaseImage(&src);
	cvReleaseImage(&dst);
	cvReleaseImage(&dst2);
	return;
	*/	
	//Num_String =  N_Str_int; 
	if ((m_ucg_b) && (m_find_cg))	{ 	
		Num_String =  582- y_cg; //N_Str_int; 
	}
	else   
		Num_String =  N_Str_int; 
	//	aff.Format("%d",  N_Str_int);
	//	m_List5.AddString("N_Str_int = " + aff);
	//	aff.Format("%d", Get_Pixel( 0, N_Str_int));
	//	m_List5.AddString("0 = " + aff);
	/*	aff.Format("%d", Get_Pixel( 1, N_Str_int));
		m_List5.AddString("1 = " + aff);
		aff.Format("%d", Get_Pixel( 2, N_Str_int));
		m_List5.AddString("2 = " + aff);
		aff.Format("%d", Get_Pixel( 3, N_Str_int));
		m_List5.AddString("3 = " + aff);
	*/
	m_fall = 0;
	m_rise = 0;
	n_m_max_rise = 0;
	n_m_max_fall = 0;
	for (int i = 0; i < cbmfile->lpHeader->biWidth; i++)	{	
		i1 = i + 1;  // Get_Pixel(1,1) первый пиксел
	 	//	aff.Format("%d",  i1 );
		//	aff1.Format("%d",  Get_Pixel( i, N_Str_int));
		//	m_List5.AddString("m[" + aff +"]= " + aff1);
		if (i  != (cbmfile->lpHeader->biWidth) - 1)	{
			a2 = Get_Pixel( i1 + 1, Num_String);
			a1 = Get_Pixel( i1, Num_String );
			diff_fall = a1 - a2;
			diff_rise = a2 - a1;
			if (diff_rise > m_rise)	{				
				m_rise = diff_rise;
				n_m_max_rise = i1;
			}
			if (diff_fall > m_fall) {				
				m_fall = diff_fall;
				n_m_max_fall = i1 + 1;
			}
			// Rise
			xRise_t1 = x_0 + n_m_max_rise;
			xRise_t2 = xRise_t1;
			
			yRise_t1 = y_0;
			yRise_t2 = y_0 + cbmfile->lpHeader->biHeight;
			//_
			
			// Fall
			xFall_t1 = x_0 + n_m_max_fall;
			xFall_t2 = xFall_t1;
			
			yFall_t1 = y_0;
			yFall_t2 = y_0 + cbmfile->lpHeader->biHeight;
			//_			
			//int xRise_t1, yRise_t1;  // Линия вертикальная начало
			//int xRise_t2, yRise_t2;  // Линия вертикальная конец			
			//xCol_t1 = x_0 + col - 1; 
			//xCol_t2 = xCol_t1;			
			//yCol_t1 = y_0;
			//yCol_t2 = y_0 + cbmfile->lpHeader->biHeight;
			// area
			//int b_area_rise;
			//int e_area_rise;
			//int b_area_fall;
			//int e_area_fall;
			//int lenght_area_rise;
			//int lenght_area_fall;
			//int j;
			//bool last_diff_rise; 
			//int max_lenght_area_rise;
			//int max_lenght_area_fall;
			//int b_max_lenght_area_rise			
			/// *********        область возрастания    *******
			if (diff_rise > 0)	{ 	// область возрастания		
				if (!last_diff_rise) 
					b_area_rise = i1;
				last_diff_rise = true;
				if (i1 > b_area_rise)	{			
					e_area_rise = i1;
					lenght_area_rise = e_area_rise - b_area_rise;
				}	
			}
			else	{ 
				last_diff_rise = false;
			}
			// end of   ****  область возрастания *****
			// *****   область убывания   ******
			if (diff_fall > 0)	{	 // область убывания	
				if (!last_diff_fall) b_area_fall = i1;
				last_diff_fall = true;
				if (i1 > b_area_fall)	{			
					e_area_fall = i1;
					lenght_area_fall = e_area_fall - b_area_fall;
				}
			}
			else	{ 
				last_diff_fall = false;
			}
			/// *********    END of     область убывания   *******
			//aff.Format("%d",  b_area_rise);
			//aff1.Format("%d",  e_area_rise);
			//aff2.Format("%d",  lenght_area_rise);
			if (lenght_area_rise > max_lenght_area_rise)	{ 		
				max_lenght_area_rise = lenght_area_rise;
				b_max_lenght_area_rise = b_area_rise;
			}
			if (lenght_area_fall > max_lenght_area_fall) 	{
				max_lenght_area_fall = lenght_area_fall;
				b_max_lenght_area_fall = b_area_fall;
			}
		} // end  if (i !=
	}  // end for i
	if (N_count_EN)	{
		aff.Format("%d",  i_count_glob);
		m_List5.AddString("N = " + aff);
	}
	if (N_Read_EN)	{	
 		aff.Format("%d",  Num_Read_saved_pic);
		m_List5.AddString("N = " + aff);
	}
	if (m_che1)	{	
		aff.Format("%d",  m_rise);
		aff1.Format("%d",  n_m_max_rise);
		m_List5.AddString("max_rise[" + aff1 +"]= " + aff);
 		aff.Format("%d",  m_fall);
		aff1.Format("%d",  n_m_max_fall);
		m_List5.AddString("max_fall[" + aff1 +"]= " + aff);
		//		aff.Format("%d",  m_rise);
		aff1.Format("%d",  n_m_max_fall - n_m_max_rise);
		m_List5.AddString("D= " + aff1);
	}
	// *****  Второй проход ***** 
	//int m_rise2;
	//int n_m_max_rise2;
	//int diff_rise2;
	//int a2_2;
	//int a1_2;	
	m_fall = 0;
	m_rise = 0;
	n_m_max_rise = 0;
	n_m_max_fall = 0;	
	cur_level = level_val_int ;	
	// Область возрастания 2
	for (int i2 = b_max_lenght_area_rise; i2 < (b_max_lenght_area_rise + max_lenght_area_rise); i2++)	{
		if (i2  != (cbmfile->lpHeader->biWidth) - 1)	{
			a2 = Get_Pixel( i2 + 1, Num_String);
			a1 = Get_Pixel( i2, Num_String );
			diff_rise = a2 - a1;
			if (diff_rise > m_rise)	{				
					m_rise = diff_rise;
					n_m_max_rise = i2;
				} 
		// критерий 4 ***    fixed_level  ***   rise
		//if  (  (Get_Pixel( b_max_lenght_area_rise, Num_String )  < cur_level ) && (Get_Pixel( b_max_lenght_area_rise + max_lenght_area_rise, Num_String ) > cur_level ) )
		//	{
		if  (a1 < cur_level) last_less_fixed_level_rise = i2;
		//	}   // темп. чтоб не терялся маркер
		//else  last_less_fixed_level_rise = 1;
		//  end of   критерий 4 ***    fixed_level  *** 
		}
	}
	// end of область возрастания 2
	// область убывания
	for (int i2 = b_max_lenght_area_fall; i2 < (b_max_lenght_area_fall + max_lenght_area_fall); i2++)	{
		if (i2  != (cbmfile->lpHeader->biWidth) - 1)	{		
			a2 = Get_Pixel( i2 + 1, Num_String);
			a1 = Get_Pixel( i2, Num_String );
			diff_fall = a1 - a2;
			if (diff_fall > m_fall)	{				
				m_fall = diff_fall;
				n_m_max_fall = i2;
			}
			// критерий 4 ***    fixed_level  ***  fall 
			if  (a1 > cur_level) 
				last_less_fixed_level_fall = i2;
			//  end of   критерий 4 ***    fixed_level  *** 
		}
	}
	// end of область убывания 2
	//  ****** определение средней полки  *******  к четвертому критерию
	for (int i2 = b_max_lenght_area_rise + max_lenght_area_rise;  i2 < b_max_lenght_area_fall; i2++)	{
		a1 = Get_Pixel( i2, Num_String );
		sr_shelf = sr_shelf + a1;
	}
	lenght_shelf = b_max_lenght_area_fall - b_max_lenght_area_rise + max_lenght_area_rise;
	if (lenght_shelf)
		sr_shelf = (int)(sr_shelf/lenght_shelf);
	else  sr_shelf = 0;
	//  end of   ****** определение средней полки  *******
	// Rise_ 4
	xRise4_t1 = x_0 + last_less_fixed_level_rise;
	xRise4_t2 = xRise4_t1;
	yRise4_t1 = y_0;
	yRise4_t2 = y_0 + cbmfile->lpHeader->biHeight;
	//_
	// Fall _ 4
	xFall4_t1 = x_0 + last_less_fixed_level_fall;
	xFall4_t2 = xFall4_t1;
	yFall4_t1 = y_0;
	yFall4_t2 = y_0 + cbmfile->lpHeader->biHeight;
	//_
	// Rise_ 2
	xRise2_t1 = x_0 + n_m_max_rise;
	xRise2_t2 = xRise2_t1;
	yRise2_t1 = y_0;
	yRise2_t2 = y_0 + cbmfile->lpHeader->biHeight;
	//_
	// Fall _ 2
	xFall2_t1 = x_0 + n_m_max_fall;
	xFall2_t2 = xFall2_t1;
	yFall2_t1 = y_0;
	yFall2_t2 = y_0 + cbmfile->lpHeader->biHeight;
	//_
	// Критерий 3
	b_max_lenght_area_fall + ((int)max_lenght_area_fall/2);
	b_max_lenght_area_rise + ((int)max_lenght_area_rise/2);
	// Rise_ 3
	xRise3_t1 = x_0 + b_max_lenght_area_rise + ((int)max_lenght_area_rise/2);
	xRise3_t2 = xRise3_t1;
	yRise3_t1 = y_0;
	yRise3_t2 = y_0 + cbmfile->lpHeader->biHeight;
	//_
	// Fall _ 3
	xFall3_t1 = x_0 + b_max_lenght_area_fall + ((int)max_lenght_area_fall/2);
	xFall3_t2 = xFall3_t1;
	yFall3_t1 = y_0;
	yFall3_t2 = y_0 + cbmfile->lpHeader->biHeight;
	//_
	// end of критерий 3
	if (m_che2)	{
		aff.Format("%d",  max_lenght_area_rise);
		aff1.Format("%d",  b_max_lenght_area_rise);
		m_List5.AddString("b_m_l_rise =" + aff1 +" m_l= " + aff);
	    aff.Format("%d",  max_lenght_area_fall);
		aff1.Format("%d",  b_max_lenght_area_fall);
		m_List5.AddString("b_m_l_fall =" + aff1 +" m_l= " + aff);
		aff.Format("%d",  m_rise);
		aff1.Format("%d",  n_m_max_rise);
		m_List5.AddString("max_rise_2_[" + aff1 +"]= " + aff);
		aff.Format("%d",  m_fall);
		aff1.Format("%d",  n_m_max_fall);
		m_List5.AddString("max_fall_2_[" + aff1 +"]= " + aff);
		aff.Format("%d",  n_m_max_fall - n_m_max_rise );
		m_List5.AddString("D2=" + aff);
	}
	if (m_che3) {
		aff.Format("%d", b_max_lenght_area_rise + ((int)max_lenght_area_rise/2));
		m_List5.AddString("N_rise_3_= " + aff);
		aff.Format("%d",  b_max_lenght_area_fall + ((int)max_lenght_area_fall/2));
		m_List5.AddString("N_fall_3_= " + aff);
		aff.Format("%d", (b_max_lenght_area_fall + ((int)max_lenght_area_fall/2)) -(b_max_lenght_area_rise + ((int)max_lenght_area_rise/2) ) );
		m_List5.AddString("D3=" + aff);
	}
	if (m_che4)   {		// критерий 4 *** fixed_level
		aff.Format("%d", level_val_int );
		m_List5.AddString("level= " + aff);
		aff.Format("%d", sr_shelf );
		m_List5.AddString("sr_shelf= " + aff);
		aff.Format("%d",  last_less_fixed_level_rise);
		m_List5.AddString("last_less_fixed_level_rise= " + aff);
		aff.Format("%d",  last_less_fixed_level_fall);
		m_List5.AddString("last_less_fixed_level_fall= " + aff);
		aff.Format("%d", last_less_fixed_level_fall - last_less_fixed_level_rise  );
		m_List5.AddString("D4=" + aff);
	}
	cvReleaseImage(&src);
    cvReleaseImage(&dst);
	cvReleaseImage(&dst2);
	return;
}

void CCPPDemoDlg::OnBnClickedButton7() // Def Edges
{
	//CCPPDemoDlg::OnBnClickedStore(); // STORE 
	CCPPDemoDlg::OnStartWaitMeasureBUTTON(); 
	CCPPDemoDlg::USB_Data_To_DIB();
	CCPPDemoDlg::StoreMyBmp();  
	//CCPPDemoDlg::OnReadMyBmp();
	CCPPDemoDlg::OnReadMyBmp_Mark();
	//CCPPDemoDlg::OnBnClickedButNStr();  // OK
	N_Str_int = 300;
	N_Colomn_int = 1;
	Data_Light(N_Str_int, N_Colomn_int);
	CCPPDemoDlg::Def_Edges_1();
}

void CCPPDemoDlg::OnReadMyBmp_Mark(void)
{
	//x_Bmp
	if (cbmfile!=NULL) 	delete cbmfile;
	cbmfile = new CDib(Bmp_File_Name_var);
	On_Read_BMP = true;
	//N_Str_int = 300;
	//N_Colomn_int = 1;
	Data_Light(N_Str_int, N_Colomn_int);
	CCPPDemoDlg::Def_Edges_1();
}

void CCPPDemoDlg::OnBnClickedButton8()  // ser def edge
{
	First_Read_Bmp = true; // график диаметра при Read BMP New
	if (First_On_Ser_Def_Edge)	{
		D_file =fopen("C:\\BMP_FILES\\D_file.txt", "w");
		m_fast_mode.EnableWindow(false); // 
		First_On_Ser_Def_Edge= false;
		N_count_EN = true;
		N_Read_EN = false;
		Bmp_File_Name_var	= Bmp_File_Name;
		//  к графику диаметра
		New_point = true;
		Only_Del = true;
		OnPaint();
		AfxBeginThread(proc2, this);	 // Первый поток
		//--------------------------------
	}
	Num_Read_saved_pic = 0; 
}

void CCPPDemoDlg::Data_In_Potok()
{
	i_count_glob = 0;
	Is_Stop_Series = false;
	DWORD StTime, CurTime;
	float TempPar;
	StTime = GetTickCount();
	#if defined DEBUG_MD_PART 
		#if defined SAVE_PIC_IN_POTOK
			CString f_Name;
			CString aff;
			LPCTSTR lpszFileName;
			if (!Store_up_pic) 
				lpszFileName = Bmp_File_Name;
			else	{
				f_Name = Bmp_File_Name; 
				Num_Store_up_pic++;
				Num_pic.Format("%d", Num_Store_up_pic);
				f_Name.Insert(23, Num_pic);
				Bmp_File_Name_var = f_Name;
				lpszFileName = f_Name; // + Num_pic;
			}
			lpszFileName = Bmp_File_Name; //temp
			CStringA sB(lpszFileName);
			const char* filename = sB; 
		#endif
		if (camera)
			while (1) {					
						frame = cvQueryFrame(camera);
						#if defined SAVE_PIC_IN_POTOK
							cvSaveImage(filename, frame);
						#endif 
						i_count_glob++;
						SendMessage(WM_THREAD_Redraw_W, 0, 0 ); 
						if (Is_Stop_Series)	{					
							CurTime = GetTickCount();
							TempPar = (float)(CurTime - StTime)/1000 ;
							aff100.Format("%d", i_count_glob);
							m_List5.AddString("kol-vo = " + aff100);
							aff100.Format("%f", i_count_glob/TempPar);
							m_List5.AddString("pic in sec = " + aff100);
						return;
						}	
				}
	#else 	
		if (m_usbCCD.Set_PRM())  // ExpTime
			while (1)	{
				if (m_fast_mode_b)	{			
					if (m_usbCCD.GetData_G())	{	// FastMode
						i_count_glob++;
						SendMessage(WM_THREAD_Redraw_W, 0, 0 );
					}
				}			
				else	{
					if (m_usbCCD.GetData())	{			
						i_count_glob++;
						SendMessage(WM_THREAD_Redraw_W, 0, 0 ); 					
					}
				}				
				if (Is_Stop_Series)	{					
					CurTime = GetTickCount();
					TempPar = (float)(CurTime - StTime)/1000 ;
					aff100.Format("%d", i_count_glob);
					m_List5.AddString("kol-vo = " + aff100);
					aff100.Format("%f", i_count_glob/TempPar);
					m_List5.AddString("pic in sec = " + aff100);
					return;
				}	
			}
	#endif
}

void CCPPDemoDlg::OnBnClickedButton11() // Store up pic
{
	CCPPDemoDlg::OnBnClickedButton6();  // стоп сериес
	Store_up_pic  = true;
	CCPPDemoDlg::OnBnClickedButton8();  // ser def edge
}

void CCPPDemoDlg::OnBnClickedCheck1()
{	
	if (m_check1.GetCheck() == 1) 	
		m_che1 = true;
	else  
		m_che1 = false;
}

void CCPPDemoDlg::OnBnClickedCheck2()
{	
	if (m_check2.GetCheck() == 1) 	
		m_che2 = true;
	else  
		m_che2 = false;
 }

 void CCPPDemoDlg::OnBnClickedCheck3()
 {
	if (m_check3.GetCheck() == 1) 	
		m_che3 = true;
	else  
		m_che3 = false;
 }

void CCPPDemoDlg::OnBnClickedCheck5()
{
 	if (m_diagram.GetCheck() == 1) 	
		m_dia = true;
	else  
		m_dia = false;
}

long CCPPDemoDlg::Red_W(WPARAM wParam, LPARAM lParam)
{
	#if !defined DEBUG_MD_PART
		CCPPDemoDlg::USB_Data_To_DIB();
	#endif
		CCPPDemoDlg::StoreMyBmp(); 
		CCPPDemoDlg::OnReadMyBmp_Mark();
		if (m_dia)	{
			OnPaint();
			//RedrawWindow();
			//Invalidate();
			//UpdateWindow();	
			/*	
			ddd_rect.bottom = gr1_y_0;
			ddd_rect.left = gr1_x_0 - 5;
			ddd_rect.right = gr2_x_0;
			ddd_rect.top = y_0  + cbmfile->lpHeader->biHeight;
			RedrawWindow(&ddd_rect,NULL,RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE | RDW_NOINTERNALPAINT  ); // ????????????????????????????
			// былонужно
			ddd_rect.bottom = y_0  + cbmfile->lpHeader->biHeight;
			ddd_rect.left =  gr1_x_0 +  cbmfile->lpHeader->biWidth ;
			ddd_rect.right = gr2_x_0;
			ddd_rect.top = 1;
			RedrawWindow(&ddd_rect,NULL,RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE | RDW_NOINTERNALPAINT  ); // ????????????????????????????
			// былонужно
			*/
		}	
	return 0;
}

void CCPPDemoDlg::OnBnClickedCheck4()
{
	//Ok_level_control.SetProperty(WS_DISABLED,TRUE); 
	if (m_check4.GetCheck() == 1)	{ 	
		m_che4 = true;
		//	f_level_change = true;
	}
	else	{
		m_che4 = false;
	}
}

void CCPPDemoDlg::OnBnClickedButton9() // ок level
{
	CString aff;
	level_val_int = atoi(m_level_val);
	if (( level_val_int > 0 ) && (level_val_int< 256)) {	// Корректная строка
		//level_val_int = atoi(m_level_val);
	} //   End off ____// Корректная строка
	else	{
		m_level_val = "127";
		level_val_int = 127;
		UpdateData(false);
	}
	m_List5.ResetContent();
	aff.Format("%d", level_val_int );
	m_List5.AddString("level_val_int=" + aff);
	OnPaint();
}

void CCPPDemoDlg::OnEnChangeEdit1()  // level input
{
	UpdateData(true);
}

void CCPPDemoDlg::OnBnClickedCheck6()
{
	if (m_check6.GetCheck() == 1)	{	
		m_che6 = true;
		//	f_level_change = true;
	}
	else	{
		m_che6 = false;
	}
}

void CCPPDemoDlg::OnBnClickedButton10()  //  Read Bmp NEW
{
	//Num_Read_saved_pic
	//Num_pic_read
	if (First_Read_Bmp)	{
		First_Read_Bmp = false;
		D_file =fopen("C:\\BMP_FILES\\D_file.txt", "w");
		i_count_glob = 0;
	} 
	CCPPDemoDlg::OnBnClickedButton6();  //        Стоп       series
	CString f_Name;
	N_Read_EN = true;
	N_count_EN = false;
	f_Name = Bmp_File_Name; 
	Num_Read_saved_pic++;
	Num_pic_read.Format("%d", Num_Read_saved_pic);
	f_Name.Insert(23,Num_pic_read);
	Bmp_File_Name_var = f_Name;
	//	lpszFileName = f_Name; // + Num_pic;
	//	aff.Format("%d",  n_m_max_fall - n_m_max_rise );
	//	m_List5.AddString("D2=" + aff);
	if (!Error_File) {
		if (cbmfile!=NULL) 
			delete cbmfile; 	
		}
	cbmfile = new CDib(Bmp_File_Name_var);
	if (cbmfile->Error_Open_File)	{
		m_List5.ResetContent();
		m_List5.AddString("End of series files");
		Error_File = true;
		Num_Read_saved_pic = 0;
	} 	
	else 	{
		m_List5.ResetContent();
		On_Read_BMP = true;
		i_count_glob ++;
		CCPPDemoDlg::Def_Edges_1();
		if ((m_ucg_b) && (m_find_cg))	{
			Data_Light(582 - y_cg, 1);
			// Data_Light(582 - y_cg, N_Colomn_int);
			// Data_Light(582 - y_cg, x_cg);
		}
		else	{
			Data_Light(N_Str_int, N_Colomn_int);
		}
		RedrawWindow();
	}
}

void CCPPDemoDlg::OnBnClickedButton5() // Ок ExpTime
{
	#if !defined DEBUG_MD_PART
		m_usbCCD.Exp_Time_int = atoi(m_Exp_Time);  
		if (m_usbCCD.SetExpTime(m_usbCCD.Exp_Time_int))	{	
			m_List5.ResetContent();
			m_List5.AddString("ExpTime=" + m_Exp_Time);
		}
	#endif
}

void CCPPDemoDlg::OnEnChangeEdit4()
{
	UpdateData(true);
}

void CCPPDemoDlg::OnBnClickedCheck7()
{
	if (m_ucg.GetCheck() == 1)	{
		m_ucg_b = true;
	}
	else 	{
		m_ucg_b = false;
	}
}

void CCPPDemoDlg::OnStnClickedDia()
{
}

void CCPPDemoDlg::OnLbnSelchangeList2()
{
}
/*
void CCPPDemoDlg::OnBnClickedCheck8()
{
	if (m_approx_c.GetCheck() == 1) {
		m_approx_b = true;
	}
	else 	{
		m_approx_b = false;
	}
}
*/

void CCPPDemoDlg::OnBnClickedCheck9()
{
	
	if (app_c.GetCheck() == 1)	{
		m_approx_b = true;
	}
	else 	{
		m_approx_b = false;
	}
}

void CCPPDemoDlg::OnBnClickedCheck10()
{
	#if !defined DEBUG_MD_PART
		m_usbCCD.Reset();
		//CCPPDemoDlg::OnBnClickedButton6();  //        Стоп       series
		if (m_fast_mode.GetCheck() == 1)	{
			m_fast_mode_b = true;
		}
		else 	{
			m_fast_mode_b = false;
	#endif
}

void CCPPDemoDlg::OnStnClickedstemp()
{	
}


#if defined DEBUG_MD_PART 

	bool CreateDir1(TCHAR * sPathTo)
	{
	 //пока директория не создана, будем пытаться её создать//
		  if (CreateDirectory(sPathTo, NULL) == 0)
		  {
		   return 0;
		  }
	 return 1;
	}


	inline bool saveImg(Mat image, const string DIRECTORY, const string EXTENSION, const char * DIR_FORMAT, const char * FILE_FORMAT)
	{
		static int incr = 0;
		stringstream ss;
		time_t seconds;
		struct tm * timeinfo;
		char TIME[80];
		time (&seconds);
		// Get the current time
		timeinfo = localtime (&seconds); 

		// Create name for the date directory
		strftime (TIME,80,DIR_FORMAT,timeinfo);

		ss.str("");
		ss << DIRECTORY << TIME;
  
		CreateDir1((TCHAR *)ss.str().c_str()); 
		ss << "/cropped";
		CreateDir1((TCHAR *)ss.str().c_str()); 

		// Create name for the image
		strftime (TIME,80,FILE_FORMAT,timeinfo);
	  
		 ss.str("");

		if(incr < 100) incr++; // quick fix for when delay < 1s && > 10ms, (when delay <= 10ms, images are overwritten)
		else incr = 0;
		ss << DIRECTORY << TIME <<"_" << static_cast<int>(incr) << EXTENSION;
		return imwrite(ss.str().c_str(), image);
	}

#endif 


void CCPPDemoDlg::OnBnClickedButtonGetOnePic()
{
	#if defined DEBUG_MD_PART
		Is_Stop_Series = true;
		frame = cvQueryFrame(camera);
		CCPPDemoDlg::StoreMyBmp(); 
		CCPPDemoDlg::OnReadMyBmp_Mark();
		if (m_dia)	{
			OnPaint();
		}	
	#endif
}

void CCPPDemoDlg::OnBnClickedButtonGetOnePicandstore()
{
	#if defined DEBUG_MD_PART
		Store_up_pic  = true;
		Is_Stop_Series = true;
		frame = cvQueryFrame(camera);
		CCPPDemoDlg::StoreMyBmp(); 
		CCPPDemoDlg::OnReadMyBmp_Mark();
		if (m_dia)	{
			OnPaint();
		}	
	#endif
}
