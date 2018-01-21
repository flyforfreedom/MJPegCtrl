#pragma once

#include <wininet.h>

#define WM_REFRESH (WM_USER+1)

// CMJPegCtrlCtrl : 有关实现的信息，请参阅 MJPegCtrlCtrl.cpp。

class CMJPegCtrlCtrl : public COleControl
{
	DECLARE_DYNCREATE(CMJPegCtrlCtrl)

// 构造函数
public:
	CMJPegCtrlCtrl();

// 重写
public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();

	afx_msg LRESULT OnRefresh(WPARAM wParam,LPARAM lParam);

// 实现
protected:
	~CMJPegCtrlCtrl();

	BEGIN_OLEFACTORY(CMJPegCtrlCtrl)        // 类工厂和 guid
		virtual BOOL VerifyUserLicense();
		virtual BOOL GetLicenseKey(DWORD, BSTR FAR*);
	END_OLEFACTORY(CMJPegCtrlCtrl)

	DECLARE_OLETYPELIB(CMJPegCtrlCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CMJPegCtrlCtrl)     // 属性页 ID
	DECLARE_OLECTLTYPE(CMJPegCtrlCtrl)		// 类型名称和杂项状态

// 消息映射
	DECLARE_MESSAGE_MAP()

// 调度映射
	DECLARE_DISPATCH_MAP()

	afx_msg void AboutBox();

// 事件映射
	DECLARE_EVENT_MAP()

// 调度和事件 ID
public:
	enum {
		dispidSetURL = 5L,
		dispidGetPort = 4L,
		dispidSetPort = 3L,
		dispidSetAddress = 2,
		dispidGetAddress = 1,
	};
protected:
	ULONG m_Port;
	CString m_Server;
	CString m_URL;
	HANDLE m_hGetVideo;

public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

	static DWORD WINAPI GetVideoThread(LPVOID lpParameter);
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	int OpenRequest(HINTERNET & HSession, HINTERNET & HConnet, HINTERNET & HRequest);

public:
	BSTR GetAddress(void);
	void SetAddress(LPCTSTR HostAddr);
	void SetPort(ULONG uPort);
	ULONG GetPort(void);
	void SetURL(LPCTSTR URL);
};

