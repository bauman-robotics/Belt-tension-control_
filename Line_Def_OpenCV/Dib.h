#include <atlimage.h>

#pragma once

class CDib
{
public:
	CDib(CString filename);
	virtual ~CDib();
	void LoadFile(CString filename);
	LPBITMAPINFO lpInfo;
	LPBITMAPINFOHEADER lpHeader;
	RGBQUAD* lpRGB;
	BYTE* lpBMP;
	bool Error_Open_File;
	//int *a = new int[n];
	//delete [] a;
	///	DWORD x_Bmp[1000];
	DWORD *x_Bmp;
	//delete [] x_Bmp;
	WORD    Bmp_bfType;
    DWORD   Bmp_bfSize;
    DWORD   Bmp_bfOffBits;
	DWORD  Bmp_sizetable;
	DWORD   Bmp_num;
	DWORD Bmp_bmf;
	DWORD   Bmp_BMP_1;
	DWORD Bmp_sizebmp;
	HANDLE hIm;
	//HBITMAP hBitmap;
	CBitmap m_bmpBitmap;	
	//CImage img;
	//CBitmap bitmap; //Инициализируем, затем кидаем туда данные
	UINT GetNumColor();
};
