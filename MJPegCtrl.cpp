// MJPegCtrl.cpp : CMJPegCtrlApp 和 DLL 注册的实现。

#include "stdafx.h"
#include "MJPegCtrl.h"
#include  <comcat.h>
#include  <objsafe.h> 

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#pragma warning(disable: 4996)

CMJPegCtrlApp theApp;

const GUID CDECL BASED_CODE _tlid =
		{ 0x70EF8D5A, 0x1F3B, 0x4AD8, { 0xAA, 0x83, 0x87, 0x42, 0xB4, 0x61, 0x40, 0xC1 } };

const WORD _wVerMajor = 1;
const WORD _wVerMinor = 0;

// CMJPegCtrlApp::InitInstance - DLL 初始化

BOOL CMJPegCtrlApp::InitInstance()
{
	BOOL bInit = COleControlModule::InitInstance();

	if (bInit)
	{
		// TODO: 在此添加您自己的模块初始化代码。
	}

	return bInit;
}



// CMJPegCtrlApp::ExitInstance - DLL 终止

int CMJPegCtrlApp::ExitInstance()
{
	// TODO: 在此添加您自己的模块终止代码。

	return COleControlModule::ExitInstance();
}

const GUID CDECL CLSID_SafeItem = { 0x26AE4DED, 0x0D11, 0x45A5, { 0xB3, 0xD4, 0x3A, 0xCA, 0x21, 0x30, 0x58, 0x50} }; 

HRESULT CreateComponentCategory(CATID catid, WCHAR* catDescription)
{
	ICatRegister* pcr = NULL ;
	HRESULT hr = S_OK ;

	hr = CoCreateInstance(CLSID_StdComponentCategoriesMgr,  
		                  NULL, CLSCTX_INPROC_SERVER, 
						  IID_ICatRegister, 
						  (void**)&pcr);
	if (FAILED(hr))
		return hr;

	// Make sure the HKCR\Component Categories\{..catid}
	// key is registered.
	CATEGORYINFO catinfo;
	catinfo.catid = catid;
	catinfo.lcid = 0x0409 ; // English

	// Make sure the provided description is not too long.
	// Only copy the first 127 characters if it is.
	int len = wcslen(catDescription);
	if (len>127)
		len = 127;
	wcsncpy(catinfo.szDescription, catDescription, len);

	// Make sure the description is null terminated.
	catinfo.szDescription[len] = _T('\0');

	hr = pcr->RegisterCategories(1, &catinfo);
	pcr->Release();

	return hr;
}

// 注册组件种类
HRESULT RegisterCLSIDInCategory(REFCLSID clsid, CATID catid)
{
	// Register your component categories information.
	ICatRegister* pcr = NULL ;
	HRESULT hr = S_OK ;
	hr = CoCreateInstance(CLSID_StdComponentCategoriesMgr,
		                  NULL, 
						  CLSCTX_INPROC_SERVER,
						  IID_ICatRegister, 
						  (void**)&pcr);
	if (SUCCEEDED(hr))
	{
		// Register this category as being implemented by the class.
		CATID rgcatid[1] ;
		rgcatid[0] = catid;
		hr = pcr->RegisterClassImplCategories(clsid, 1, rgcatid);
	}
	if (pcr != NULL)
		pcr->Release();
	return hr;
}

// 卸载组件种类
HRESULT UnRegisterCLSIDInCategory(REFCLSID clsid, CATID catid)
{
	ICatRegister* pcr = NULL ;
	HRESULT hr = S_OK ;

	hr = CoCreateInstance(CLSID_StdComponentCategoriesMgr, 
		                  NULL, 
						  CLSCTX_INPROC_SERVER, 
						  IID_ICatRegister, 
						  (void**)&pcr);
	if (SUCCEEDED(hr))
	{

		// Unregister this category as being implemented by the class.
		CATID rgcatid[1] ;
		rgcatid[0] = catid;
		hr = pcr->UnRegisterClassImplCategories(clsid, 1, rgcatid);
	}

	if (pcr != NULL)
		pcr->Release();

	return hr;
}

// DllRegisterServer - 将项添加到系统注册表

STDAPI DllRegisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleRegisterTypeLib(AfxGetInstanceHandle(), _tlid))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(TRUE))
		return ResultFromScode(SELFREG_E_CLASS);

	// 标记控件初始化安全.
	// 创建初始化安全组件种类
	HRESULT hr = CreateComponentCategory(CATID_SafeForInitializing, L"Controls safely initializable from persistent data!");
	if (FAILED(hr))
		return hr;

	// 注册初始化安全
	hr = RegisterCLSIDInCategory(CLSID_SafeItem, CATID_SafeForInitializing);
	if (FAILED(hr))
		return hr;

	// 标记控件脚本安全
	// 创建脚本安全组件种类 
	hr = CreateComponentCategory(CATID_SafeForScripting, L"Controls safely scriptable!");
	if (FAILED(hr))
		return hr;

	// 注册脚本安全组件种类
	hr = RegisterCLSIDInCategory(CLSID_SafeItem, CATID_SafeForScripting);
	if (FAILED(hr))
		return hr;

	return NOERROR;
}

// DllUnregisterServer - 将项从系统注册表中移除

STDAPI DllUnregisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	// 删除控件初始化安全入口.
	HRESULT hr=UnRegisterCLSIDInCategory(CLSID_SafeItem, CATID_SafeForInitializing);
	if (FAILED(hr))
		return hr;

	// 删除控件脚本安全入口
	hr=UnRegisterCLSIDInCategory(CLSID_SafeItem, CATID_SafeForScripting);
	if (FAILED(hr))
		return hr;

	if (!AfxOleUnregisterTypeLib(_tlid, _wVerMajor, _wVerMinor))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(FALSE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}
