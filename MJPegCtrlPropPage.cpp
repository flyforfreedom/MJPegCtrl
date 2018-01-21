// MJPegCtrlPropPage.cpp : CMJPegCtrlPropPage ����ҳ���ʵ�֡�

#include "stdafx.h"
#include "MJPegCtrl.h"
#include "MJPegCtrlPropPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


IMPLEMENT_DYNCREATE(CMJPegCtrlPropPage, COlePropertyPage)


// ��Ϣӳ��

BEGIN_MESSAGE_MAP(CMJPegCtrlPropPage, COlePropertyPage)
END_MESSAGE_MAP()



// ��ʼ���๤���� guid

IMPLEMENT_OLECREATE_EX(CMJPegCtrlPropPage, "MJPEGCTRL.MJPegCtrlPropPage.1",
	0xb27f8e17, 0x7440, 0x4849, 0x9b, 0x85, 0x23, 0x6e, 0x6b, 0xa, 0xd1, 0xbb)



// CMJPegCtrlPropPage::CMJPegCtrlPropPageFactory::UpdateRegistry -
// ��ӻ��Ƴ� CMJPegCtrlPropPage ��ϵͳע�����

BOOL CMJPegCtrlPropPage::CMJPegCtrlPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_MJPEGCTRL_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}



// CMJPegCtrlPropPage::CMJPegCtrlPropPage - ���캯��

CMJPegCtrlPropPage::CMJPegCtrlPropPage() :
	COlePropertyPage(IDD, IDS_MJPEGCTRL_PPG_CAPTION)
		, m_Port(0)
		, m_szIP(_T(""))
	{
}


// CMJPegCtrlPropPage::DoDataExchange - ��ҳ�����Լ��ƶ�����

void CMJPegCtrlPropPage::DoDataExchange(CDataExchange* pDX)
{
	DDP_Text(pDX, IDC_EDIT_IP, m_szIP, _T("Server"));
	DDX_Text(pDX, IDC_EDIT_IP, m_szIP);
	DDP_Text(pDX, IDC_EDIT2, m_Port, _T("Port"));
	DDX_Text(pDX, IDC_EDIT2, m_Port);
	DDP_PostProcessing(pDX);	
	
}

