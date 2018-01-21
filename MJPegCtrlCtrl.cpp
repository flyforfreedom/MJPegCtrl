// MJPegCtrlCtrl.cpp : CMJPegCtrlCtrl ActiveX 控件类的实现。

#include "stdafx.h"
#include "MJPegCtrl.h"
#include "MJPegCtrlCtrl.h"
#include "MJPegCtrlPropPage.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#pragma warning(disable: 4244)
#pragma warning(disable: 4996)
#pragma warning(disable: 4018)

#define FILE_PREFIX _T("MJPegCtrl")
#define JPEG_SIZE 1024*1024
static HGLOBAL g_HMemJPeg[2] = {NULL};
static int g_nUsed = 0;
static HINTERNET g_hSession = NULL;
static CRITICAL_SECTION g_cs;

IMPLEMENT_DYNCREATE(CMJPegCtrlCtrl, COleControl)


// 消息映射

BEGIN_MESSAGE_MAP(CMJPegCtrlCtrl, COleControl)
	ON_MESSAGE(WM_REFRESH, OnRefresh)
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_TIMER()
END_MESSAGE_MAP()



// 调度映射

BEGIN_DISPATCH_MAP(CMJPegCtrlCtrl, COleControl)
	DISP_FUNCTION_ID(CMJPegCtrlCtrl, "AboutBox", DISPID_ABOUTBOX, AboutBox, VT_EMPTY, VTS_NONE)
	DISP_STOCKPROP_BACKCOLOR()
	DISP_STOCKPROP_FORECOLOR()
	DISP_FUNCTION_ID(CMJPegCtrlCtrl, "GetAddress", dispidGetAddress, GetAddress, VT_BSTR, VTS_NONE)
	DISP_FUNCTION_ID(CMJPegCtrlCtrl, "SetAddress", dispidSetAddress, SetAddress, VT_EMPTY, VTS_BSTR)
	DISP_FUNCTION_ID(CMJPegCtrlCtrl, "SetPort", dispidSetPort, SetPort, VT_EMPTY, VTS_UI4)
	DISP_FUNCTION_ID(CMJPegCtrlCtrl, "GetPort", dispidGetPort, GetPort, VT_UI4, VTS_NONE)
	DISP_FUNCTION_ID(CMJPegCtrlCtrl, "SetURL", dispidSetURL, SetURL, VT_EMPTY, VTS_BSTR)
END_DISPATCH_MAP()



// 事件映射

BEGIN_EVENT_MAP(CMJPegCtrlCtrl, COleControl)
END_EVENT_MAP()



// 属性页

// TODO: 按需要添加更多属性页。请记住增加计数!
BEGIN_PROPPAGEIDS(CMJPegCtrlCtrl, 2)
	PROPPAGEID(CMJPegCtrlPropPage::guid)
	PROPPAGEID(CLSID_CColorPropPage)
END_PROPPAGEIDS(CMJPegCtrlCtrl)



// 初始化类工厂和 guid

IMPLEMENT_OLECREATE_EX(CMJPegCtrlCtrl, "MJPEGCTRL.MJPegCtrlCtrl.1",
	0x26ae4ded, 0xd11, 0x45a5, 0xb3, 0xd4, 0x3a, 0xca, 0x21, 0x30, 0x58, 0x50)



// 键入库 ID 和版本

IMPLEMENT_OLETYPELIB(CMJPegCtrlCtrl, _tlid, _wVerMajor, _wVerMinor)



// 接口 ID

const IID BASED_CODE IID_DMJPegCtrl =
		{ 0xEC0AB74A, 0xD271, 0x4947, { 0xA7, 0x37, 0xB3, 0x11, 0xF7, 0x60, 0xA3, 0x45 } };
const IID BASED_CODE IID_DMJPegCtrlEvents =
		{ 0xCC1A542C, 0xD1BD, 0x45F1, { 0xB5, 0x96, 0x91, 0x2A, 0xF4, 0x4, 0x8A, 0xD4 } };



// 控件类型信息

static const DWORD BASED_CODE _dwMJPegCtrlOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CMJPegCtrlCtrl, IDS_MJPEGCTRL, _dwMJPegCtrlOleMisc)



// CMJPegCtrlCtrl::CMJPegCtrlCtrlFactory::UpdateRegistry -
// 添加或移除 CMJPegCtrlCtrl 的系统注册表项

BOOL CMJPegCtrlCtrl::CMJPegCtrlCtrlFactory::UpdateRegistry(BOOL bRegister)
{
	// TODO: 验证您的控件是否符合单元模型线程处理规则。
	// 有关更多信息，请参考 MFC 技术说明 64。
	// 如果您的控件不符合单元模型规则，则
	// 必须修改如下代码，将第六个参数从
	// afxRegApartmentThreading 改为 0。

	if (bRegister)
		return AfxOleRegisterControlClass(
			AfxGetInstanceHandle(),
			m_clsid,
			m_lpszProgID,
			IDS_MJPEGCTRL,
			IDB_MJPEGCTRL,
			afxRegApartmentThreading,
			_dwMJPegCtrlOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}



// 授权字符串

static const TCHAR BASED_CODE _szLicFileName[] = _T("MJPegCtrl.lic");

static const WCHAR BASED_CODE _szLicString[] =
	L"Copyright (c) 2011 ";



// CMJPegCtrlCtrl::CMJPegCtrlCtrlFactory::VerifyUserLicense -
// 检查是否存在用户许可证

BOOL CMJPegCtrlCtrl::CMJPegCtrlCtrlFactory::VerifyUserLicense()
{
	return AfxVerifyLicFile(AfxGetInstanceHandle(), _szLicFileName,
		_szLicString);
}



// CMJPegCtrlCtrl::CMJPegCtrlCtrlFactory::GetLicenseKey -
// 返回运行时授权密钥

BOOL CMJPegCtrlCtrl::CMJPegCtrlCtrlFactory::GetLicenseKey(DWORD dwReserved,
	BSTR FAR* pbstrKey)
{
	if (pbstrKey == NULL)
		return FALSE;

	*pbstrKey = SysAllocString(_szLicString);
	return (*pbstrKey != NULL);
}

// CMJPegCtrlCtrl::CMJPegCtrlCtrl - 构造函数

CMJPegCtrlCtrl::CMJPegCtrlCtrl()
{
	InitializeIIDs(&IID_DMJPegCtrl, &IID_DMJPegCtrlEvents);

	m_Port = 8080;

	m_Server = _T("");

	m_URL = _T("");
}


CMJPegCtrlCtrl::~CMJPegCtrlCtrl()
{

}

void CMJPegCtrlCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	//PX_String(pPX, _T("Server"), m_Server, m_Server.GetBuffer());
	//PX_ULong(pPX, _T("Port"), m_Port, m_Port);
	// TODO: 为每个持久的自定义属性调用 PX_ 函数。
}

// CMJPegCtrlCtrl::OnResetState - 将控件重置为默认状态

void CMJPegCtrlCtrl::OnResetState()
{
	COleControl::OnResetState();  // 重置 DoPropExchange 中找到的默认值

	// TODO: 在此重置任意其他控件状态。
}

// CMJPegCtrlCtrl::AboutBox - 向用户显示“关于”框

void CMJPegCtrlCtrl::AboutBox()
{
	CDialog dlgAbout(IDD_ABOUTBOX_MJPEGCTRL);
	dlgAbout.DoModal();
}


LRESULT CMJPegCtrlCtrl::OnRefresh(WPARAM wParam,LPARAM lParam)
{
	InvalidateControl();

	return TRUE;
}

int CMJPegCtrlCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (COleControl::OnCreate(lpCreateStruct) == -1)
		return -1;

	g_HMemJPeg[0] = GlobalAlloc(GMEM_MOVEABLE, JPEG_SIZE);
	g_HMemJPeg[1] = GlobalAlloc(GMEM_MOVEABLE, JPEG_SIZE);

	m_hGetVideo = CreateThread(NULL,
								 0,
								 GetVideoThread,
								 this,
								 0,
								 0);

	return 0;
}

void CMJPegCtrlCtrl::OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
	if(pdc)
	{
		pdc->FillRect(&rcBounds, 
			          CBrush::FromHandle((HBRUSH)GetStockObject(BLACK_BRUSH)));
	}

	IPicture *pPic;
	IStream *pStm;	

	if (g_HMemJPeg[g_nUsed] != NULL)
	{
		CreateStreamOnHGlobal(g_HMemJPeg[g_nUsed], FALSE, &pStm);

		if(SUCCEEDED(OleLoadPicture(pStm, JPEG_SIZE, TRUE,IID_IPicture,(LPVOID*)&pPic)))
		{
			OLE_XSIZE_HIMETRIC hmWidth;
			OLE_YSIZE_HIMETRIC hmHeight;

			pPic->get_Width(&hmWidth);
			pPic->get_Height(&hmHeight);

			HDC hdc = ::GetDC(m_hWnd);

			RECT  rc;
			GetClientRect( &rc); 

			FAILED(pPic->Render(hdc,
								0,0,
								(DWORD)rc.right-rc.left,
								(DWORD)rc.bottom-rc.top,
								0,
								hmHeight,
								hmWidth,
								-hmHeight,
								&rc));

			pPic->Release(); 
		} 

		pStm->Release();
	}
}

int CMJPegCtrlCtrl::OpenRequest(HINTERNET & HSession, 
								HINTERNET & HConnet, 
								HINTERNET & HRequest)
{
	TCHAR strAccept[] = _T("*/*");
	LPTSTR* lpAccpt = new TCHAR*[2];
	*lpAccpt = strAccept;
	*(lpAccpt + 1) = NULL;
	LPCTSTR* cLpAccept = (LPCTSTR*)lpAccpt;

	DWORD dwRet = 0;

	/*TCHAR szRequest[MAX_PATH] = {_T("/videostream.cgi?user=admin&pwd=123456&resolution=32")};*/ 

	HSession = InternetOpen(_T("http"),
								INTERNET_OPEN_TYPE_PRECONFIG,
								NULL,
								NULL,
								NULL);
	if (NULL == HSession) 
	{
		dwRet = 1;
		goto END;
	}

	HConnet = InternetConnect(g_hSession,
								m_Server.GetBuffer(),
								m_Port,
								NULL,
								NULL,
								INTERNET_SERVICE_HTTP,
								0,
								0);
	if (NULL == HConnet) 
	{
		dwRet = 2;
		goto END;
	}

	HRequest = HttpOpenRequest(HConnet,
								_T("GET"),
								m_URL,
								_T("HTTP/1.1"),
								NULL,
								cLpAccept,
								INTERNET_FLAG_RELOAD,
								0);
	if (NULL == HRequest) 
	{
		dwRet = 3;
		goto END;
	}

	if (!HttpSendRequest(HRequest, NULL, 0, NULL, 0)) 
	{
		dwRet = 4;
		goto END;
	}

END:

	if(dwRet && HSession)
		InternetCloseHandle(HSession);
		
	return dwRet;
}

DWORD WINAPI CMJPegCtrlCtrl::GetVideoThread(LPVOID lpParameter)
{
	CMJPegCtrlCtrl* pThis = (CMJPegCtrlCtrl*)lpParameter;
	
	while(pThis->m_Server == _T("")
		 ||pThis->m_Port == 0)
	{
		Sleep(2000);
	}

	HINTERNET hConnect = NULL;
	HINTERNET hRequest = NULL;

	DWORD dwRet = 0;

	if((dwRet = pThis->OpenRequest(g_hSession, hConnect, hRequest)) == 0)
	{	
		DWORD dwByteAvail = 0;
		DWORD dwByteRead = 0;

		if(InternetQueryDataAvailable(hRequest,
										&dwByteAvail,
										NULL,
										NULL))
		{
			LPBYTE lpBuffer = new BYTE[dwByteAvail+1];
			::ZeroMemory(lpBuffer, dwByteAvail+1);

			if(!lpBuffer)
			{
				dwRet = 1;
				goto EDN;   
			}
			
			LPVOID lpData = GlobalLock(g_HMemJPeg[!g_nUsed]);

			if(!lpData)
			{
				delete [] lpBuffer;
				dwRet = 2;
				goto EDN;   
			}

			::ZeroMemory(lpData, JPEG_SIZE);

			int nCurrentPos = 0;
            bool bReachEnd = true;

			while(InternetReadFile(hRequest,
									lpBuffer,  
									dwByteAvail,
									&dwByteRead) && dwByteRead != 0)
			{
				int i = 0;					

	MultiJPeg:
				LPBYTE pImageHead = NULL;
				LPBYTE pImageTail = NULL;

				while(i < (int)dwByteRead-3)
				{
					if( ((int)lpBuffer[i] == 0xFF )
						&& ((int)lpBuffer[i+1] == 0xD8)
						&& ((int)lpBuffer[i+3] != 0xDB))
					{
						pImageHead = &lpBuffer[i];
					}
					else if( ((int)lpBuffer[i] == 0xFF)
							 && ((int)lpBuffer[i+1] == 0xD9) 
							 && ((int)lpBuffer[i+2] == 0x0D))
					{
						pImageTail = &lpBuffer[i];
						i +=2;
						break;
					}
					i++;
				}		

				if(pImageHead == NULL 
				   && pImageTail == NULL)
				{ 
					if(!bReachEnd && (nCurrentPos+dwByteRead) < JPEG_SIZE)
					{
						::CopyMemory(((LPBYTE)lpData)+nCurrentPos, lpBuffer, dwByteRead);

						nCurrentPos += dwByteRead;
					}
				}
				else if(pImageTail == NULL)
				{
					int nLen = dwByteRead-(pImageHead-lpBuffer);

					if(nLen < JPEG_SIZE)
					{	
						::ZeroMemory(lpData, JPEG_SIZE);

						::CopyMemory((LPBYTE)lpData, 
										pImageHead, 
										nLen);

						nCurrentPos = nLen;	
						
						bReachEnd = false;							
					}			
				}
				else if(pImageHead == NULL)
				{
					if((int)((LPBYTE)lpData)[0] == 0xFF
						&& (int)((LPBYTE)lpData)[1] == 0xD8)
					{
						if((nCurrentPos+pImageTail-lpBuffer+2) < JPEG_SIZE)
						{
							::CopyMemory(((LPBYTE)lpData)+nCurrentPos, 
											lpBuffer, 
											pImageTail-lpBuffer+2);

							nCurrentPos = 0;	

							GlobalUnlock(g_HMemJPeg[!g_nUsed]);

							lpData = GlobalLock(g_HMemJPeg[g_nUsed]);

							if(!lpData)
							{
								break;
							}

							g_nUsed = !g_nUsed;

							pThis->OnDraw(NULL, NULL, NULL);

							bReachEnd = true;	

							if(i < dwByteRead-1)
							{
								goto MultiJPeg;
							}	    
						}				
					}
				}
				else
				{
					if((nCurrentPos+pImageTail-pImageHead+2) < JPEG_SIZE)
					{
						::ZeroMemory(lpData, JPEG_SIZE);

						::CopyMemory((LPBYTE)lpData, 
										pImageHead, 
										pImageTail-pImageHead+2);

						nCurrentPos = 0;

						GlobalUnlock(g_HMemJPeg[!g_nUsed]);

						lpData = GlobalLock(g_HMemJPeg[g_nUsed]);

						if(!lpData)
						{
							break;
						}

						g_nUsed = !g_nUsed;

						pThis->OnDraw(NULL, NULL, NULL);

						bReachEnd = true;

						if(i < dwByteRead-1)
						{
							goto MultiJPeg;
						}	
					}
				
				}

				dwByteAvail = 0;

				InternetQueryDataAvailable(hRequest,
											&dwByteAvail,
											NULL,
											NULL);

				if(dwByteAvail == 0)
					break;
				
				dwByteRead = 0;

				delete [] lpBuffer;

				lpBuffer = new BYTE[dwByteAvail+1];

				if(!lpBuffer)
					break;

				::ZeroMemory(lpBuffer, dwByteAvail+1);	
			}

			delete [] lpBuffer;	
		}
	}

EDN:

	InternetCloseHandle(g_hSession);

	g_hSession = NULL;

	return dwRet;
}

void CMJPegCtrlCtrl::OnDestroy()
{
	COleControl::OnDestroy();

	GlobalFree(g_HMemJPeg[0]);
	GlobalFree(g_HMemJPeg[1]);

	if(WAIT_OBJECT_0 != WaitForSingleObject(m_hGetVideo, 200))
	{
	    TerminateThread(m_hGetVideo, 1);
	}

	if(g_hSession)
	{
	    InternetCloseHandle(g_hSession);
	}
}

void CMJPegCtrlCtrl::OnTimer(UINT_PTR nIDEvent)
{
	COleControl::OnTimer(nIDEvent);
}

BSTR CMJPegCtrlCtrl::GetAddress(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CString strResult;

	strResult = m_Server;

	return strResult.AllocSysString();
}

void CMJPegCtrlCtrl::SetAddress(LPCTSTR HostAddr)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	m_Server = HostAddr;
}

void CMJPegCtrlCtrl::SetPort(ULONG uPort)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	m_Port = uPort;
}

ULONG CMJPegCtrlCtrl::GetPort(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	return m_Port;
}

void CMJPegCtrlCtrl::SetURL(LPCTSTR URL)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	m_URL = URL;
}
