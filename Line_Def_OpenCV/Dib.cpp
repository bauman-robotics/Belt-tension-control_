#include "stdafx.h"
#include "Dib.h"
#include "windowsx.h"



	CDib::CDib(CString filename)
{
	

	LoadFile(filename);
}

CDib::~CDib()
{
	GlobalFree(lpInfo);

	delete [] x_Bmp;
}

void CDib::LoadFile(CString filename)
{
	CString af;
	af = "Not Bmp File";
	//CFile file(filename,CFile::modeRead);

Error_Open_File = false;

	CFile file;

	if ( !file.Open(filename,CFile::modeRead) )  
		
	{
	Error_Open_File = true;

		return;
	}

	BITMAPFILEHEADER bmf;
	file.Read((void *)&bmf,sizeof(bmf));
	if (bmf.bfType  != 0x4d42)
	{
		AfxMessageBox(af);
	}
	else
	{



		DWORD sizebmp=file.GetLength()-sizeof(bmf); 
		//BYTE* ptrBmp = (BYTE*)GlobalAlloc(GMEM_MOVEABLE,sizebmp);
		BYTE* ptrBmp = (BYTE*)GlobalAllocPtr(GMEM_MOVEABLE,sizebmp);
		file.Read((void*)ptrBmp,sizebmp); 
		file.Close(); 
		lpInfo=(LPBITMAPINFO)ptrBmp;

//int *a = new int[n];
//delete [] a;
//x_Bmp_dm = new DWORD[sizebmp];

		x_Bmp  = new DWORD[sizebmp];

//  NEW !!!
		lpHeader=(LPBITMAPINFOHEADER)ptrBmp;
		lpRGB = (RGBQUAD*)(ptrBmp+lpHeader->biSize); 
		int num=GetNumColor();
		DWORD sizetable=num*sizeof(RGBQUAD);
		lpBMP=ptrBmp+lpHeader->biSize+sizetable; 

		Bmp_bmf = sizeof(bmf);
	Bmp_num = num;
		Bmp_sizetable = sizetable; //sizeof(RGBQUAD); // sizetable;

		Bmp_BMP_1 = *lpBMP;	

Bmp_sizebmp = sizebmp; 

//for (int i=0; i<1000; i++)
for (int i=0; i<sizebmp; i++)

{
x_Bmp[i] = *(ptrBmp+i);
}


		 //	x_Bmp[0] = *ptrBmp;
		 //  x_Bmp[1] = *(ptrBmp+1);




//  NEW !!! //  NEW !!! //  NEW !!!
		 Bmp_bfType = bmf.bfType;   // 	    WORD   
			Bmp_bfSize = bmf.bfSize;   // 		DWORD  
				 Bmp_bfOffBits = bmf.bfOffBits;  // 	DWORD 

//HBITMAP hImage; //{ хэндл картинки, его можно получить так:   // Работает
//HANDLE hIm;
//hIm = LoadImage(0,filename,IMAGE_BITMAP,0,0,LR_LOADFROMFILE); //}





		HBITMAP hBitmap = (HBITMAP)::LoadImage(AfxGetInstanceHandle(),
				filename, IMAGE_BITMAP, 0, 0,
				LR_LOADFROMFILE | LR_CREATEDIBSECTION);


	hIm = hBitmap; //* 28.01.2011

		m_bmpBitmap.Detach();
		m_bmpBitmap.Attach(hBitmap); 

		//m_bmpBitmap. // SetBitmapBits

	


	}
}

UINT CDib::GetNumColor()
{
//	if ((lpHeader->biClrUsed == 0 ) && (lpHeader->biClrUsed <9))
//		return lpHeader->biClrUsed; 

	if (lpHeader->biClrUsed == 0 )
	{
		if  (lpHeader->biBitCount == 1)  return 2; //  
	
		if (lpHeader->biBitCount == 4)   return 16;

		if  (lpHeader->biBitCount == 8)  return 256;

		if  (lpHeader->biBitCount == 24)  return 0;
	} 
	else return lpHeader->biClrUsed;
}