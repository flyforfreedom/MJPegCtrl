#pragma once
#include "afxcmn.h"

// MJPegCtrlPropPage.h : CMJPegCtrlPropPage ����ҳ���������


// CMJPegCtrlPropPage : �й�ʵ�ֵ���Ϣ������� MJPegCtrlPropPage.cpp��

class CMJPegCtrlPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CMJPegCtrlPropPage)
	DECLARE_OLECREATE_EX(CMJPegCtrlPropPage)

// ���캯��
public:
	CMJPegCtrlPropPage();

// �Ի�������
	enum { IDD = IDD_PROPPAGE_MJPEGCTRL };

// ʵ��
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ��Ϣӳ��
protected:
	DECLARE_MESSAGE_MAP()
public:
	DWORD m_Port;
	CString m_szIP;
};

