#include "stdafx.h"
#include "usbcdd.h"

CUsbCDD::CUsbCDD(void)
:m_bAttached(false)

{
	m_hCCDdll=NULL;

	m_fCCD_Init=NULL;
	m_fCCD_HitTest=NULL;
	m_fCCD_CameraReset=NULL;
	m_fCCD_SetExtendParameters=NULL;
	m_fCCD_GetExtendParameters=NULL;
	m_fCCD_SetParameter=NULL;
	m_fCCD_GetParameter=NULL;
	m_fCCD_InitMeasuring=NULL;
	m_fCCD_InitMeasuringData=NULL;
	m_fCCD_StartWaitMeasuring=NULL;
	m_fCCD_StartMeasuring=NULL;
	m_fCCD_GetMeasureStatus=NULL;
	m_fCCD_GetData=NULL;
	m_fCCD_GetSerialNum=NULL;
	m_fCCD_GetID=NULL;
	m_nID=0;
	m_pData=NULL;
	m_nNcol=m_nNrow=m_nNF=0;
	//	Exp_Time_int = 50; 
}

CUsbCDD::~CUsbCDD(void)
{
	//CCDDCOM_DisconectDCOM(ID);
	if(m_pData!=NULL) delete[] m_pData;
	FreeLibrary(m_hCCDdll);
}

//Начальная инициализация
BOOL CUsbCDD::InitInstance()
{
	//	AfxTrace("LoadLibrary\n");
	m_hCCDdll=::LoadLibrary("CCDUSBDCOM01.dll");
	//	if((m_hCCDdll=::LoadLibrary("CCDUSBDCOM01.dll"))==NULL)
	if(m_hCCDdll == NULL)
	{ /* не удалось загрузить DLL */ 
		DWORD err = GetLastError();
		Beep(3000,500);
		return FALSE;
	}
 	else 
	{ /* приложение имеет право пользоваться функциями DLL через m_hCCDdll */ 
		m_fCCD_Init=(PCCD_Init)::GetProcAddress(m_hCCDdll,"CCD_Init");
		m_fCCD_HitTest=(PCCD_HitTest)::GetProcAddress(m_hCCDdll,"CCD_HitTest");
		m_fCCD_CameraReset=(PCCD_CameraReset)::GetProcAddress(m_hCCDdll,"CCD_CameraReset");
		m_fCCD_SetExtendParameters=(PCCD_SetExtendParameters)::GetProcAddress(m_hCCDdll,"CCD_SetExtendParameters");
		m_fCCD_GetExtendParameters=(PCCD_GetExtendParameters)::GetProcAddress(m_hCCDdll,"CCD_GetExtendParameters");
		m_fCCD_SetParameter=(PCCD_SetParameter)::GetProcAddress(m_hCCDdll,"CCD_SetParameter");
		m_fCCD_GetParameter=(PCCD_GetParameter)::GetProcAddress(m_hCCDdll,"CCD_GetParameter");
		m_fCCD_InitMeasuring=(PCCD_InitMeasuring)::GetProcAddress(m_hCCDdll,"CCD_InitMeasuring");
		m_fCCD_InitMeasuringData=(PCCD_InitMeasuringData)::GetProcAddress(m_hCCDdll,"CCD_InitMeasuringData");
		m_fCCD_StartWaitMeasuring=(PCCD_StartWaitMeasuring)::GetProcAddress(m_hCCDdll,"CCD_StartWaitMeasuring");
		m_fCCD_StartMeasuring=(PCCD_StartMeasuring)::GetProcAddress(m_hCCDdll,"CCD_StartMeasuring");
		m_fCCD_GetMeasureStatus=(PCCD_GetMeasureStatus)::GetProcAddress(m_hCCDdll,"CCD_GetMeasureStatus");
		m_fCCD_GetData=(PCCD_GetData)::GetProcAddress(m_hCCDdll,"CCD_GetData");
		m_fCCD_GetSerialNum=(PCCD_GetSerialNum)::GetProcAddress(m_hCCDdll,"CCD_GetSerialNum");
		m_fCCD_GetID=(PCCD_GetID)::GetProcAddress(m_hCCDdll,"CCD_GetID");
		integer ID;
		//Инициализация устройства
		return m_fCCD_Init(0, 0, &ID);
	}
}

// Привязка к устройству по порядковому номеру
bool CUsbCDD::Attach()
{
	bool result=m_fCCD_HitTest(0);
	if (result) m_nID=0;
	m_bAttached=result;
	return result;
}
bool CUsbCDD::Attach(int ID)
{
	bool result=m_fCCD_HitTest(ID);
	if (result) m_nID=ID;
	m_bAttached=result;
	return result;
}


// Получить данные от устройства

bool CUsbCDD::GetData_G(void)
{
	m_Pab = 10;
	int Np; 
	if(!m_bAttached)return FALSE;
	GetParameters();

	m_fCCD_SetParameter(0, PRM_DEVICEMODE, 16); // FastMode

	Np = m_nNumPixelsH * m_nNumPixelsV;
	if(m_pData==NULL)m_pData = new DWORD[((int)Np)*((int)m_nNumReadOuts)];
	//m_fCCD_GetParameter(m_nID, PRM_DEVICEMODE, &m_Pab_f);
	//m_Pab = m_dwDeviceMode;
	if (m_fCCD_InitMeasuring(m_nID))
	{	//m_Pab = 11;
		if (m_fCCD_StartMeasuring(m_nID))
		{	//m_Pab = 12;
			m_fCCD_GetData(m_nID, m_pData); // было
			//if ( m_fCCD_GetData(m_nID, m_pData) )
			return TRUE;

			//for i:=0 to (Round(Np*m_nNumReadOuts)-1) do
			//Series1.AddXY(i,pData[i],'',clTeeColor);
		};
	};

	return FALSE;
}

bool CUsbCDD::GetData(void)
{
	int Np; 
	if(!m_bAttached)return FALSE;
	GetParameters();

	Np = m_nNumPixelsH * m_nNumPixelsV;
	if(m_pData==NULL)m_pData = new DWORD[((int)Np)*((int)m_nNumReadOuts)];
	if (m_fCCD_InitMeasuringData(m_nID,m_pData))
	{
		if (m_fCCD_StartWaitMeasuring(m_nID))
		{
			//for i:=0 to (Round(Np*m_nNumReadOuts)-1) do
			//Series1.AddXY(i,pData[i],'',clTeeColor);
			return TRUE;
		};
	};

	return FALSE;
}

// Сброс устройства
bool CUsbCDD::Reset(void)
{
	if(!m_bAttached)return FALSE;
	return m_fCCD_CameraReset(m_nID);
}

// Получить серийный номер
bool CUsbCDD::GetSerialNum(CString& strSerialNumber)
{
	PCHAR pstr;
	if(!m_bAttached)return FALSE;
	m_fCCD_GetSerialNum( m_nID,&pstr);
    strSerialNumber = pstr;
	return TRUE;
}

// Получаем параметры устройства
bool CUsbCDD::GetParameters(void)
{
	if(!m_bAttached)return FALSE;
	TCCDUSBExtendParams Prms;
	if (m_fCCD_GetExtendParameters( m_nID , &Prms )) 
	{
		m_dwDigitCapacity=Prms.dwDigitCapacity;
		m_nPixelRate=Prms.nPixelRate;
		m_nNumPixelsH=Prms.nNumPixelsH;
		m_nNumPixelsV=Prms.nNumPixelsV;
		m_nNumReadOuts=Prms.nNumReadOuts;
		m_sPreBurning=Prms.sPreBurning;
		m_sExposureTime=Prms.sExposureTime;
		m_dwSynchr=Prms.dwSynchr;
		m_bSummingMode=Prms.bSummingMode;
		m_dwDeviceMode=Prms.dwDeviceMode;
		m_nStripCount=Prms.nStripCount;
		//RECT rcStrips[MAXSTRIPS]; // The strips for a spectral mode.
		m_dwSensitivity=Prms.dwSensitivity;
		m_dwProperty=Prms.dwProperty ;
		m_sShuterTime=Prms.sShuterTime;
        return TRUE;
	};
	return FALSE;
}

bool CUsbCDD::SetParameters(void)
{
	if(!m_bAttached)return FALSE;

	TCCDUSBExtendParams Prms;

	Prms.dwDigitCapacity=m_dwDigitCapacity;
	Prms.nPixelRate=m_nPixelRate;
	Prms.nNumPixelsH=m_nNumPixelsH;
	Prms.nNumPixelsV=m_nNumPixelsV;
	Prms.nNumReadOuts=m_nNumReadOuts;
	Prms.sPreBurning=m_sPreBurning;
	Prms.sExposureTime=m_sExposureTime;
	Prms.dwSynchr=m_dwSynchr;
	Prms.bSummingMode=m_bSummingMode;
	Prms.dwDeviceMode=m_dwDeviceMode;
	Prms.nStripCount=m_nStripCount;
	//RECT rcStrips[MAXSTRIPS]; // The strips for a spectral mode.
	Prms.dwSensitivity=m_dwSensitivity;
	Prms.dwProperty=m_dwProperty ;
	Prms.sShuterTime=m_sShuterTime;
    if (m_fCCD_SetExtendParameters(m_nID,&Prms)) 
	{
		if (m_fCCD_GetExtendParameters( m_nID , &Prms )) 
		{
			m_dwDigitCapacity=Prms.dwDigitCapacity;
			m_nPixelRate=Prms.nPixelRate;
			m_nNumPixelsH=Prms.nNumPixelsH;
			m_nNumPixelsV=Prms.nNumPixelsV;
			m_nNumReadOuts=Prms.nNumReadOuts;
			m_sPreBurning=Prms.sPreBurning;
			m_sExposureTime=Prms.sExposureTime;
			m_dwSynchr=Prms.dwSynchr;
			m_bSummingMode=Prms.bSummingMode;
			m_dwDeviceMode=Prms.dwDeviceMode;
			m_nStripCount=Prms.nStripCount;
			//RECT rcStrips[MAXSTRIPS]; // The strips for a spectral mode.
			m_dwSensitivity=Prms.dwSensitivity;
			m_dwProperty=Prms.dwProperty ;
			m_sShuterTime=Prms.sShuterTime;

			if (NULL==m_pData) delete []m_pData;
        	int Np; 
        	Np = m_nNumPixelsH * m_nNumPixelsV;
	        if(m_pData==NULL)m_pData = new DWORD[((int)Np)*((int)m_nNumReadOuts)];
		}
	}
	return FALSE;
}

bool CUsbCDD::SetReadOuts(int nNumReadOuts)
{
	if(!m_bAttached)return FALSE;
	if(m_fCCD_SetParameter(m_nID,PRM_READOUTS,nNumReadOuts))
	{
		if (m_fCCD_GetParameter(m_nID,PRM_READOUTS,(single*)&nNumReadOuts))
		{
			m_nNumReadOuts=nNumReadOuts;
			return TRUE;
		}
	}
	return FALSE;
}
bool CUsbCDD::SetExpTime(single sExposureTime)
{
	if(!m_bAttached)return FALSE;
	if(m_fCCD_SetParameter(m_nID,PRM_EXPTIME,sExposureTime))
	{
		if (m_fCCD_GetParameter(m_nID,PRM_EXPTIME,&sExposureTime))
		{
			m_sExposureTime=sExposureTime;
			return TRUE;
		}
	}
	return FALSE;
}
bool CUsbCDD::SetSynhr(DWORD dwSynchr)
{
	if(!m_bAttached)return FALSE;
	if(m_fCCD_SetParameter(m_nID,PRM_SYNCHR,dwSynchr))
	{
		if (m_fCCD_GetParameter(m_nID,PRM_SYNCHR,(single*)&dwSynchr))
		{
			m_dwSynchr=dwSynchr;
			return TRUE;
		}
	}
	return FALSE;
}


bool CUsbCDD::Set_PRM(void)
{
	if (Attach())
	{
	

		if (SetExpTime(Exp_Time_int))	{} //  m_strSN.Format("%d",100);

		return true;
	}
	return false;
}


