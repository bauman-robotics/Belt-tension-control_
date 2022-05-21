// CPP DemoDlg.h : header file
//

#if !defined(AFX_CPPDEMODLG_H__8B31C5E3_F733_4740_98A0_3CBF05C30C53__INCLUDED_)
#define AFX_CPPDEMODLG_H__8B31C5E3_F733_4740_98A0_3CBF05C30C53__INCLUDED_

#include "UsbCDD.h"	// Added by ClassView
#include "dib.h"
#include "afxwin.h"
// OpenCV projects
#include <cv.h>
#include <highgui.h>
#include <stdlib.h>
#include <stdio.h>
//
#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#define DEBUG_MD_PART
#define SHOW_ADD_WINDOWS
//#define SAVE_PIC_IN_POTOK
#define SHOW_DEBUG_INFO

#if defined DEBUG_MD_PART 
	#include <opencv2/opencv.hpp>
	#include <ctime>
	using namespace cv;
	using namespace std;
#endif
/////////////////////////////////////////////////////////////////////////////
// CCPPDemoDlg dialog

class CCPPDemoDlg : public CDialog
{
// Construction
public:
	#if defined DEBUG_MD_PART
		CUsbCDD m_usbCCD;
	#endif
	CCPPDemoDlg(CWnd* pParent = NULL);	// standard constructor
	BOOL StoreBitmapFile(LPCTSTR lpszFileName, HBITMAP HBM);
	void StoreMyBmp(void);

// Dialog Data
	//{{AFX_DATA(CCPPDemoDlg)
	enum { IDD = IDD_CPPDEMO_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCPPDemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL
// Implementation
protected:
	HICON m_hIcon;
	// Generated message map functions
	//{{AFX_MSG(CCPPDemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnStartWaitMeasureBUTTON();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCameraresetbutton();
	afx_msg void OnBnClickedGetserialnumberbutton();
	CString m_strSN;
	CString N_Str;
	CString N_Col;
	bool On_Read_BMP;
    int FindFirstPixel_24b(int n_str);
	int FindFirstPixel_256(int n_str);
    int Get_Pixel(int n_str, int n_col);
	void Data_Light(int str, int col);
	void Data_To_DIB(void);
	void USB_Data_To_DIB(void);
	void OnReadMyBmp(void);
	void OnReadMyBmp_Mark(void);
	void Data_In_Potok(void);
    void Def_Edges_1(void);
	CString First_Pix_Str;
	CString First_Pix_Col;
	int N_Str_int;
	int N_Colomn_int;
	bool is_Data_Light;
	bool palitra256;
	int Start_Address_String_Light; 
	//int DataArr[455000];
	LPDWORD DataArr;
	LPBYTE ByteArr;
	PFLOAT D6_Arr;	
	//PDWORDArr DataArr;	
	int x_0, y_0;  // Верхний левый угол
	int xStr_t1, yStr_t1;  // Линия начало
	int xStr_t2, yStr_t2;  // Линия конец	
	int xCol_t1, yCol_t1;  // Линия вертикальная начало
	int xCol_t2, yCol_t2;  // Линия вертикальная конец	
	
	int xRise_t1, yRise_t1;  // Линия вертикальная начало
	int xRise_t2, yRise_t2;  // Линия вертикальная конец	
	int xFall_t1, yFall_t1;  // Линия вертикальная начало
	int xFall_t2, yFall_t2;  // Линия вертикальная конец
	
	
	int xRise2_t1, yRise2_t1;  // Линия вертикальная начало
	int xRise2_t2, yRise2_t2;  // Линия вертикальная конец	
	int xFall2_t1, yFall2_t1;  // Линия вертикальная начало
	int xFall2_t2, yFall2_t2;  // Линия вертикальная конец	
	
	int xRise3_t1, yRise3_t1;  // Линия вертикальная начало
	int xRise3_t2, yRise3_t2;  // Линия вертикальная конец	
	int xFall3_t1, yFall3_t1;  // Линия вертикальная начало
	int xFall3_t2, yFall3_t2;  // Линия вертикальная конец
	
	int xRise4_t1, yRise4_t1;  // Линия вертикальная начало
	int xRise4_t2, yRise4_t2;  // Линия вертикальная конец	
	int xFall4_t1, yFall4_t1;  // Линия вертикальная начало
	int xFall4_t2, yFall4_t2;  // Линия вертикальная конец
		
	int xRise5_t1, yRise5_t1;  // Линия вертикальная начало
	int xRise5_t2, yRise5_t2;  // Линия вертикальная конец	
	int xFall5_t1, yFall5_t1;  // Линия вертикальная начало
	int xFall5_t2, yFall5_t2;  // Линия вертикальная конец
	
	int gr1_x_0; // Координаты 0 первого графика
	int gr1_y_0; // Координаты 0 первого графика	
	int gr2_x_0; // Координаты 0 второго графика
	int gr2_y_0; // Координаты 0 второго графика
	
	int x_cg, y_cg; // координаты центра тяжести
	bool is_StartWaitMeasure; 
	int i_count_glob;
	int g_count_glob;	
	HBITMAP bmLogo2;
	int level_val_int;
	int sr_shelf;
	int lenght_shelf;	
	BITMAPFILEHEADER R_bmf;	
	bool Is_Stop_Series;
	//CPen Pen1; 
	CPen Pen10; 
	CPen Pen11; 
	CPen Pen12; 
	CPen Pen13;
	CPen Pen15;
	CPen Pen16; 
	CDC* dc2;
	DWORD color;	
	//CDC dcTemp;	
	CString Bmp_File_Name; 
	CString Bmp_File_Name_var;	
	CString D_Str;
	CString i_Count_Str;	
	bool Store_up_pic;
	int Num_Store_up_pic;
	int Num_Read_saved_pic;	
	CString Num_pic;	
	CString Num_pic_read;	
	bool m_che1;
	bool m_che2;
	bool m_che3;
	bool m_che4;
	bool m_che6;
	bool m_ucg_b;
	bool m_approx_b;
	bool m_fast_mode_b;	
	bool m_dia;
	CString  aff100;	
	DWORD StTime, CurTime;
	float TempPar;
	RECT ddd_rect;	
	int OLD_STR_1[782];
	int OLD_STR_2[782];
	//782*582	
	#define WM_THREAD_Redraw_W  WM_USER+1 	
	int fixed_level;
	int cur_level;
	int last_less_fixed_level_rise;
	int last_less_fixed_level_fall;	
	bool N_count_EN;
	bool N_Read_EN;
	bool f_level_change;	
	int Old_level_val;
	bool Error_File;
	//HANDLE event;
	bool First_On_Ser_Def_Edge;
	bool First_Read_Bmp;
	CvSeq* C_Max_area;
	CvMoments moments;
	double m_x, m_y;
	double C_area;
	double C_area_max;	
	bool m_find_cg;	
	int N_Str_OnPaint;
	int N_Colomn_int_OnPaint;	
	double x_c1, x_c2, x_cb;
	CFont font;	
	bool susp_proc2;
	double D6;
	double D6_old;	
	int nW, fc;
	FILE *D_file;
	int Old_i_count_glob;
	bool New_point;
	bool Only_Del;
	/*
	IplImage* image;
	//IplImage* dst;
	IplImage* erode;
	IplImage* open;
	IplImage* close;
	IplImage* gradient;
	IplImage* tophat;
	IplImage* blackhat;
	IplImage *src;
	IplImage *dst;
	IplImage *dst2;
	*/
	//	int i[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};		
	//	CMetaFileDC* pMetaFileDC;
	afx_msg void OnStnClickedSerial();
	char szString;
    int i1;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedReadBmp();
	CDib *cbmfile;
	CListBox m_List;
	CListBox m_Col_List;
	afx_msg void OnBnClickedOk();
	CListBox m_List_BMP;
	afx_msg void OnLbnSelchangeList3();
	CListBox m_List_Pix;
	CEdit m_num_str;
	afx_msg void OnEnChangeEdit2();
	CString Num_Str;
	afx_msg void OnBnClickedButNStr();
	CString Num_srtr_val;
	afx_msg void OnLbnSelchangeList4();
	afx_msg void OnLbnSelchangeList5();
	afx_msg void OnEnChangeEdit3();
	CString m_colomn;
	afx_msg void OnLbnSelchangeList6();
	CListBox List_Colomn;
	afx_msg void OnBnClickedButton4();
	CListBox m_List5;
	afx_msg void OnBnClickedStore();
	//  afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedButton11();
	//  afx_msg void OnBnClickedCheck2();
	afx_msg void OnBnClickedCheck1();
	CButton m_check1;
	afx_msg void OnBnClickedCheck3();
	CButton m_check3;
	CButton m_check4;
	afx_msg void OnBnClickedCheck4();
	CButton m_diagram;
	afx_msg void OnBnClickedCheck5();
	afx_msg long Red_W(WPARAM wParam, LPARAM lParam);	
	//  CListBox m_level;
	//  afx_msg void OnLbnSelchangeList7();
	//  CString m_level_val;
	afx_msg void OnBnClickedButton9();
	CString m_level_val;
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnBnClickedCheck2();	
	CButton m_check2;
	CButton Ok_level_control;
	afx_msg void OnBnClickedCheck6();
	CButton m_check6;
	afx_msg void OnBnClickedButton10();	
	afx_msg void OnBnClickedButton5();
	afx_msg void OnEnChangeEdit4();
	CString m_Exp_Time;
	CButton m_ucg;
	afx_msg void OnBnClickedCheck7();
	CString m_Diam;
	afx_msg void OnStnClickedDia();
	CStatic m_Diam_contr;
	afx_msg void OnLbnSelchangeList2();
	BOOL m_approx;
	//	CButton m_approx_c;
	//	afx_msg void OnBnClickedCheck8();
	CButton app_c;
	afx_msg void OnBnClickedCheck9();
	CButton m_fast_mode;
	afx_msg void OnBnClickedCheck10();
	CString Temp_text;
	afx_msg void OnStnClickedstemp();
	afx_msg void OnBnClickedButtonGetOnePic();
	afx_msg void OnBnClickedButtonGetOnePicandstore();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CPPDEMODLG_H__8B31C5E3_F733_4740_98A0_3CBF05C30C53__INCLUDED_)
