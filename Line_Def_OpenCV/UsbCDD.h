//#include "CPP DemoDlg.h" 

#ifndef usbccd
#define usbccd

#pragma once

#define BYTEx8_ALIGN __declspec(align(8))


//The parameter identification number

//The digit capacity of CCD-camera
#define  PRM_DIGIT       1 
//The pixel rate
#define  PRM_PIXELRATE   2 
//The number of pixels
#define  PRM_NUMPIXELS   3 
//The number of readouts
#define PRM_READOUTS     4
//The exposure time
#define PRM_EXPTIME      5
//The synchronization mode
#define PRM_SYNCHR       6
//The number of pixels on a horizontal (columns number of CCD-array)
#define PRM_NUMPIXELSH   7
//The number of pixels on a vertical (rows number of CCD-array)
#define PRM_NUMPIXELSV   8
 //The summing mode
#define PRM_SUMMING      9 
//The device mode
#define PRM_DEVICEMODE   10 
                       // DEVICEMODEA1 - Matrix mode #1
                       // DEVICEMODEA2 - Matrix mode #2
                       // DEVICEMODES  - The spectroscope mode without a strips.
                       //                The matrix is submitted as one line
//The number of strips for a spectral mode
#define PRM_STRIPCOUNT   11
//The sensitivity
#define PRM_SENSIT          14
//The device property.
#define PRM_DEVICEPROPERTY  15
// The Time preliminary burning in seconds.
#define PRM_PREBURNING      16
                         // Really only at synchronization SYNCHR_CONTR_NEG but not for all cameras!!!
                         // Use GetDeviceProperty function to receive properties of the device.
                         // Is used  at a spectrum measurements.
#define PRM_SHUTERTIME      17;//

// The synchronization mode
// Without synchronization.
#define SYNCHR_NONE      0x01
// In the beginning of the first accumulation the positive
// pulse of synchronization is formed.
#define SYNCHR_CONTR     0x20
// Clock pulse is formed in the beginning of each accumulation.
#define SYNCHR_CONTR_FRS 0x04   
// One pulse of synchronization is formed on all time of registration.
// A pulse of negative polarity.
#define SYNCHR_CONTR_NEG 0x08   
                          
// The beginning of the first accumulation is adhered to growing
// front of external clock pulse.
//All other accumulation occur so quickly as it is possible.
// In a limit -- without the misses.
#define SYNCHR_EXT       0x10

// The beginning of each accumulation is adhered to growing front of clock pulse.
// How much accumulation, so much clock pulses are expected.
#define SYNCHR_EXT_FRS   0x02   
                          
                          
//The status of measurement
//the measurement in processing
#define STATUS_WAIT_DATA   1
//the waiting of synchronization pulse
#define STATUS_WAIT_TRIG   2
//the measurement has been finished
#define STATUS_DATA_READY  3 

#define MAXSTRIPS  8

// DEVICE MODE
// Some cameras on the basis of CCD-matrixes have an additional modes. See dwProperty.
// DP_MODEA2 It is an additional mode of the matrix registrar. If the device has DP_MODEA2 property it is possible to establish dwDeviceMode in value DEVICEMODEA2.
// In mode DEVICEMODES the device works in a spectroscopic mode.
// The photosensitive field of a matrix is broken into some strips. Strips are set by parameters nStripCount and rcStrips.
// While translating the device in mode DEVICEMODES change nNumPixelsH and nNumPixelsV.
#define DEVICEMODEA1  0x0002
#define DEVICEMODEA2  0x0000
#define DEVICEMODES   0x0003

// DEVICEPROPERTY

// SYNCHR_CONTR is enaible
#define DP_SYNCHR_CONTR         0x00000001 
// SYNCHR_CONTR_FRS is enaible
#define DP_SYNCHR_CONTR_FRS     0x00000002 
// SYNCHR_CONTR_NEG is enaible
#define DP_SYNCHR_CONTR_NEG     0x00000004 
// SYNCHR_EXT is enaible
#define DP_SYNCHR_EXT           0x00000008 
// SYNCHR_EXT_FRS is enaible
#define DP_SYNCHR_EXT_FRS       0x00000010 
// The sensor has a mode of the raised sensitivity.
#define DP_SENSIT               0x00000020; 
// Additional matrix mode of the camera.
#define DP_MODEA2               0x00000040 
// Spectroscopic mode of a CCD-matrix.
#define DP_MODES1               0x00000080 
// Spectroscopic mode of a CCD-matrix.
#define DP_MODES2               0x00000100 
// Opportunity to establish preliminary burning.
#define DP_PREBURNING           0x00000200 
// Property of an electronic shutter.
#define DP_SHUTER               0x00000400 
// Control ADC clock frequency (nPixelRate).
#define DP_CLOCKCONTROL         0x00000800 

#define NCAMMAX  3

//typedef DWORD*      TDWORDArr;   
typedef DWORD*  PDWORDArr;
typedef WORD*   PWORDArr;
typedef RECT TRect;
/*
PWORDArr = ^TWORDArr;
 TWORDArr = array[0..0] of WORD;
*/
#define integer int

typedef struct 
 {
   DWORD dwDigitCapacity;  //The digit capacity of CCD-camera
   integer nPixelRate;//The pixel rate kHz
   integer nNumPixels;//The number of pixels

   integer nNumReadOuts;//The number of readouts
   integer nExposureTime;//The exposure time
   DWORD dwSynchr;  //The synchronization mode
 } TCCDUSBParams;



 #define single float
 #define boolean bool

 typedef struct BYTEx8_ALIGN
 {
   DWORD dwDigitCapacity;  //The digit capacity of CCD-camera
   integer nPixelRate;//The pixel rate kHz
   integer nNumPixelsH;// The number of pixels on a horizontal (columns number of CCD-array)
   integer nNumPixelsV;// The number of pixels on a vertical (rows number of CCD-array)
   DWORD Reserve1; // not used
   DWORD Reserve2; // not used

   integer nNumReadOuts; // The number of readouts
   single sPreBurning; // The Time preliminary burning in seconds.
                             // Really only at synchronization SYNCHR_CONTR_NEG but not for all cameras!!!
                             // Use GetDeviceProperty function to receive properties of the device.
                             // Is used at a spectrum measurements.
   single sExposureTime; // The exposure time
   single sTime2; // not used
   DWORD dwSynchr;  // The synchronization mode.
   boolean bSummingMode; // Turn on(off) summing mode. Not used.

   DWORD dwDeviceMode; // Turn on(off) spectral mode of CCD-array.
                            // Some cameras on the basis of CCD-matrixes have an additional modes. See dwProperty.
                            // DP_MODEA2 It is an additional mode of the matrix registrar. If the device has DP_MODEA2 property it is possible to establish dwDeviceMode in value DEVICEMODEA2.
                            // In mode DEVICEMODES the device works in a spectroscopic mode.
                            // The photosensitive field of a matrix is broken into some strips. Strips are set by parameters nStripCount and rcStrips.
                            // While translating the device in mode DEVICEMODES change nNumPixelsH and nNumPixelsV.
   integer nStripCount; // The number of strips for a spectral mode
   RECT rcStrips[MAXSTRIPS]; // The strips for a spectral mode.
   integer Reserve11;

   DWORD dwSensitivity; // Turn on (off) a mode of the raised sensitivity of a CCD-sensor control. Actually if dwProperty & DP_SENSIT <> 0.
   DWORD dwProperty ; // The device property.
   single sShuterTime; // Shuter time (ms). Active in minimal exposure time.
                             // Exposure time = MinExp - sShaterTime.
   DWORD Reserve6; // not used
   DWORD Reserve7; // not used
   DWORD Reserve8; // not used
   DWORD Reserve9; // not used
   DWORD Reserve10; // not used
 } TCCDUSBExtendParams;

#define PChar PCHAR

//if the operation was executed successfully then all function results True

//The function CCD_Init should start before all another function.
//This function performs the search of all CCD-cameras and sets the initial parameters
//ahAppWnd may be 0. Prm and ID not used;
typedef boolean (__stdcall *PCCD_Init)(HWND ahAppWnd, PChar Prm, integer* ID);
//function CCD_Init (ahAppWnd : HWND; Prm : PChar; Var ID : Integer) : boolean; stdcall; external 'CCDUSBDCOM01.DLL'

//The function CCD_HitTest is used for hit test of CCD-cameras
//If some devices are used ID is the identifier USB-device. Can be 0, 1, 2.
//If one device is used then ID = 0.
typedef boolean (__stdcall *PCCD_HitTest)(integer ID);
//function CCD_HitTest (ID : Integer) : boolean; stdcall; external 'CCDUSBDCOM01.DLL'

// Cause function CCD_CameraReset when there was a mistake or it is necessary to interrupt registration.
//If some devices are used ID is the identifier USB-device. Can be 0, 1, 2.
//If one device is used then ID = 0.
typedef boolean (__stdcall *PCCD_CameraReset)(integer ID);
//CCD_CameraReset (ID : Integer) : boolean; stdcall; external 'CCDUSBDCOM01.DLL'

//The function CCD_SetParameters is used for CCD-camera parameters' setting.
//The parameter Prms is structure of type TCCDUSBParams. The declaration of structure
//TCCDUSBParams defines above.
//It is allowed to set only following parameters:
//  - exposure time
//  - number of readouts
//  - synchronization mode
//The remaining parameters is set automatically
//If some devices are used ID is the identifier USB-device. Can be 0, 1, 2.
//If one device is used then ID = 0.
typedef boolean (__stdcall *PCCD_SetParameters)(integer ID,TCCDUSBParams* Prms);
//CCD_SetParameters(ID : Integer; var Prms : TCCDUSBParams) : boolean; stdcall; external 'CCDUSBDCOM01.DLL'

//The function CCD_SetExtendParameters is used for CCD-camera parameters' setting.
//The parameter Prms is structure of type TCCDUSBExtendParams. The declaration of structure
//TCCDUSBExtendParams defines above.
//It is allowed to set only following parameters:
//  - exposure time
//  - number of readouts
//  - synchronization mode
//  - device mode
//  - strips
//  - the time preliminary burning
//  - the raised sensitivity
//  - shuter time
//The remaining parameters is set automatically.
//If some devices are used ID is the identifier USB-device. Can be 0, 1, 2.
//If one device is used then ID = 0.
typedef boolean (__stdcall *PCCD_SetExtendParameters)(integer ID, TCCDUSBExtendParams* Prms);
//CCD_SetExtendParameters(ID : Integer; var Prms : TCCDUSBExtendParams) : boolean; stdcall; external 'CCDUSBDCOM01.DLL'

//The function CCD_GetParameters is used to get the current parameters
//of CCD-camera.
//If some devices are used ID is the identifier USB-device. Can be 0, 1, 2.
//If one device is used then ID = 0.
typedef boolean (__stdcall *PCCD_GetParameters)      (integer ID, TCCDUSBExtendParams* Prms);
typedef boolean (__stdcall *PCCD_GetExtendParameters)(integer ID, TCCDUSBExtendParams* Prms);
//CCD_GetParameters(ID : Integer; var Prms : TCCDUSBParams) : boolean; stdcall; external 'CCDUSBDCOM01.DLL'
//CCD_GetExtendParameters(ID : Integer; var Prms : TCCDUSBExtendParams) : boolean; stdcall; external 'CCDUSBDCOM01.DLL'

//The function CCD_SetParameter is used to set the parameters of CCD-camera separately
// If some devices are used ID is the identifier USB-device. Can be 0, 1, 2.
// If one device is used then ID = 0.
// dwPrmID - parameter identification number. Its can take following values of constants:
// PRM_READOUTS - the number of readouts
// PRM_EXPTIME  - the exposure time
// PRM_SYNCHR   - the synchronization mode. In the external synchronization mode the number of
//                readouts always equals one.
//Prm - the value of parameter

typedef boolean (__stdcall *PCCD_SetParameter)(integer ID,DWORD dwPrmID, single Prm);
//CCD_SetParameter(ID : Integer; dwPrmID : DWORD; Prm : single) : boolean; stdcall; external 'CCDUSBDCOM01.DLL'

//The function CCD_GetParameter is used to get the parameters of CCD-camera separately
// If some devices are used ID is the identifier USB-device. Can be 0, 1, 2.
// If one device is used then ID = 0.
// dwPrmID - parameter identification number. Its can take following values of constants:
// PRM_DIGIT       - The digit capacity of CCD-camera
// PRM_PIXELRATE   - The pixel timing
// PRM_NUMPIXELS   - The number of pixels
// PRM_READOUTS    - The  number of readouts
// PRM_EXPTIME     - The exposure time
// PRM_SYNCHR      - The synchronization mode
//Prm - the returned value of parameter

typedef boolean (__stdcall *PCCD_GetParameter)(integer ID,DWORD dwPrmID, single* Prm);
//CCD_GetParameter(ID : Integer; dwPrmID : DWORD; var Prm : single) : boolean; stdcall; external 'CCDUSBDCOM01.DLL'

//The function CCD_InitMeasuring must be start before beginning of measuring
//If some devices are used ID is the identifier USB-device. Can be 0, 1, 2.
//If one device is used then ID = 0.
typedef boolean (__stdcall *PCCD_InitMeasuring)(integer ID);
//CCD_InitMeasuring(ID : Integer) : boolean; stdcall; external 'CCDUSBDCOM01.DLL'

//The function CCD_InitMeasuringData must be start before beginning of measuring
//If some devices are used ID is the identifier USB-device. Can be 0, 1, 2.
//If one device is used then ID = 0.
//apData is the pointegr to array of DWORD.
//The size of array must be equal tothe pixels' number of CCD-camera
//(nNumPixelsH*nNumPixelsV*nNumReadOuts*SizeOf(DWORD))
typedef boolean (__stdcall *PCCD_InitMeasuringData)(integer ID,PDWORDArr apData);
//CCD_InitMeasuringData(ID : Integer; apData : PDWORDArr) : boolean; stdcall; external 'CCDUSBDCOM01.DLL'

//The function CCD_StartWaitMeasuring is used to start and wait the measurement.
//The function starts the measurement and waits the finishing of the measurement.
//If some devices are used ID is the identifier USB-device. Can be 0, 1, 2.
//If one device is used then ID = 0.
typedef boolean (__stdcall *PCCD_StartWaitMeasuring) (integer ID);
//CCD_StartWaitMeasuring (ID : Integer) : boolean; stdcall; external 'CCDUSBDCOM01.DLL'

//The function CCD_StartMeasuring is used to start the measurement only
//If some devices are used ID is the identifier USB-device. Can be 0, 1, 2.
//If one device is used then ID = 0.
typedef boolean (__stdcall *PCCD_StartMeasuring) (integer aID);
//CCD_StartMeasuring (aID : Integer) : boolean; stdcall; external 'CCDUSBDCOM01.DLL'

// The function CCD_GetMeasureStatus is used to check status of a measurement.
// This function is used with the function CCDUSB_StartMeasuring.
// If some devices are used ID is the identifier USB-device. Can be 0, 1, 2.
// If one device is used then ID = 0.
// dwStatus - the result value can take one of following constants:
// STATUS_WAIT_DATA  - the measurement in processing
// STATUS_WAIT_TRIG  - the waiting of synchronization pulse
// STATUS_DATA_READY - the measurement has been finished
typedef boolean (__stdcall *PCCD_GetMeasureStatus)(integer ID, DWORD* adwStatus);
//CCD_GetMeasureStatus(ID : Integer; var adwStatus : DWORD) : boolean; stdcall; external 'CCDUSBDCOM01.DLL'

//The function CCD_GetData is used to get the result of measurement.
//If some devices are used ID is the identifier USB-device. Can be 0, 1, 2.
//If one device is used then ID = 0.
//bData - the pointegr to array of DWORD. The length of array must be equal to
//the pixels' number of CCD-camera
//It is applied to cameras with a linear CCD-sensor and function CCDUSB_InitMeasuring.
//To matrix registrars should apply function CCDUSB_InitMeasuringData.
typedef boolean (__stdcall *PCCD_GetData)(integer ID, PDWORDArr pData);
//CCD_GetData(ID : Integer; pData : PDWORDArr) : boolean; stdcall; external 'CCDUSBDCOM01.DLL'

//The function CCD_GetSerialNum returns unique serial number of CCD-camera.
//If some devices are used ID is the identifier USB-device. Can be 0, 1, 2.
//If one device is used then ID = 0.
typedef boolean (__stdcall *PCCD_GetSerialNum)(integer ID, PCHAR* sernum);
//CCD_GetSerialNum (ID : Integer; Var sernum : PChar) : boolean; stdcall; external 'CCDUSBDCOM01.DLL'

//The function CCD_GetID allows to receive ID for the chamber with known serial number.
typedef boolean (__stdcall *PCCD_GetID) (PCHAR sernum, integer * ID );
//CCD_GetID ( sernum : PChar; Var ID : Integer ) : boolean; stdcall; external 'CCDUSBDCOM01.DLL'

//Parameters of a spectroscopic mode of a matrix are established either through function CCDUSB_SetExtendParameters
//or through functions CCD_ClearStrips, CCD_AddStrip and CCD_DeleteStrip.

//This function is used for management in parameters of a spectroscopic mode of a CCD-matrix.
//Function CCD_ClearStrips clears the list of strips.
//If some devices are used ID is the identifier USB-device. Can be 0, 1, 2.
//If one device is used then ID = 0.
typedef boolean (__stdcall *PCCD_ClearStrips) (integer ID);
//CCD_ClearStrips (ID : Integer) : boolean; stdcall;  external 'CCDUSBDCOM01.DLL'

//Function CCD_AddStrip adds a strip in the list.
//Parameters of a strip are specified in arcStrip.
//The number of strips increases on 1.
//Strips cannot be blocked.
//Function returns TRUE if parameters of a strip are correct also a strip is successfully added.
//If some devices are used ID is the identifier USB-device. Can be 0, 1, 2.
//If one device is used then ID = 0.
typedef boolean (__stdcall *PCCD_AddStrip)  (integer ID, TRect arcStrip);
//CCD_AddStrip (ID : Integer; arcStrip : TRect) : boolean; stdcall;  external 'CCDUSBDCOM01.DLL'

//Function CCD_DeleteStrip deletes a strip with number Index from the list of strips.
//The number of strips in the list decreases on 1.
//If some devices are used ID is the identifier USB-device. Can be 0, 1, 2.
//If one device is used then ID = 0.
typedef boolean (__stdcall *PCCD_DeleteStrip) ( integer ID , integer Index);
//CCD_DeleteStrip (ID : Integer; Index : Integer) : boolean; stdcall;  external 'CCDUSBDCOM01.DLL'

typedef boolean (__stdcall *PCCDDCOM_DisconectDCOM) (integer ID);
//CCDDCOM_DisconectDCOM (ID : Integer) : boolean; stdcall; external 'CCDUSBDCOM01.dll'

typedef boolean (__stdcall *PCCDDCOM_SetDCOMRemoteName) (integer ID, PCHAR RemoteName);
//CCDDCOM_SetDCOMRemoteName (ID : Integer; RemoteName : PChar) : boolean;  stdcall; external 'CCDUSBDCOM01.dll'


class CUsbCDD
{
public:
	CUsbCDD(void);
	//Начальная инициализация
	virtual BOOL InitInstance();
	~CUsbCDD(void);
private:
	//CCD_Init
	PCCD_Init m_fCCD_Init;
	//Hit test of CCD-cameras
	PCCD_HitTest m_fCCD_HitTest;
	//Reset Camera
	PCCD_CameraReset m_fCCD_CameraReset;
	//EXParameters setting
	PCCD_SetExtendParameters m_fCCD_SetExtendParameters;
	//EXGet the current parameters
	PCCD_GetExtendParameters m_fCCD_GetExtendParameters;
	//Set the parameters of CCD-camera separately
	PCCD_SetParameter m_fCCD_SetParameter;
	//Get the parameters of CCD-camera separately
	PCCD_GetParameter m_fCCD_GetParameter;
	PCCD_InitMeasuring m_fCCD_InitMeasuring;
	PCCD_InitMeasuringData m_fCCD_InitMeasuringData;
	PCCD_StartWaitMeasuring m_fCCD_StartWaitMeasuring;
	PCCD_StartMeasuring m_fCCD_StartMeasuring;
	PCCD_GetMeasureStatus m_fCCD_GetMeasureStatus;
	PCCD_GetData m_fCCD_GetData;
	PCCD_GetSerialNum m_fCCD_GetSerialNum;
	PCCD_GetID m_fCCD_GetID;

public:
	// Привязка к устройству по порядковому номеру
	bool Attach(int ID);
	bool Attach();

	DWORD m_dwDigitCapacity;
	int	m_nPixelRate;
	int	m_nNumPixelsH;
	int	m_nNumPixelsV;
	int	m_nNumReadOuts;
	single m_sPreBurning;
	single m_sExposureTime;
	DWORD m_dwSynchr;
	boolean m_bSummingMode;
	DWORD m_dwDeviceMode;
	int	m_nStripCount;
		//RECT rcStrips[MAXSTRIPS]; // The strips for a spectral mode.
	DWORD m_dwSensitivity;
	DWORD m_dwProperty ;
	single m_sShuterTime;

	int m_Pab;
		float m_Pab_f;

	//	CCPPDemoDlg *Dlg_port;

		int Exp_Time_int;

private:
	// Если устройство подключено,то =TRUE
	bool m_bAttached;
	//DLL HANDLE
	HMODULE m_hCCDdll;
	int m_nID;
	int m_nNcol;
	int m_nNrow;
	int m_nNF;

public:
	// Получить данные от устройства
	bool GetData(void);

	bool GetData_G(void);
	// Сброс устройства
	bool Reset(void);
	// Получить серийный номер
	bool GetSerialNum(CString& strSerialNumber);
	// Масив данных
	PDWORDArr m_pData;
	// Получаем параметры устройства
	bool GetParameters(void);
	bool SetParameters(void);
	bool SetReadOuts(int nNumReadOuts);
	bool SetExpTime(single sExposureTime);
	bool SetSynhr(DWORD dwSynchr);
	bool Set_PRM(void);

};

#endif //usbccd