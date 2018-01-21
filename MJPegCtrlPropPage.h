#pragma once
#include "afxcmn.h"

// MJPegCtrlPropPage.h : CMJPegCtrlPropPage 属性页类的声明。


// CMJPegCtrlPropPage : 有关实现的信息，请参阅 MJPegCtrlPropPage.cpp。

class CMJPegCtrlPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CMJPegCtrlPropPage)
	DECLARE_OLECREATE_EX(CMJPegCtrlPropPage)

// 构造函数
public:
	CMJPegCtrlPropPage();

// 对话框数据
	enum { IDD = IDD_PROPPAGE_MJPEGCTRL };

// 实现
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 消息映射
protected:
	DECLARE_MESSAGE_MAP()
public:
	DWORD m_Port;
	CString m_szIP;
};

