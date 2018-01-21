#pragma once

#include <wininet.h>

#define WM_REFRESH (WM_USER+1)

// CMJPegCtrlCtrl : �й�ʵ�ֵ���Ϣ������� MJPegCtrlCtrl.cpp��

class CMJPegCtrlCtrl : public COleControl
{
	DECLARE_DYNCREATE(CMJPegCtrlCtrl)

// ���캯��
public:
	CMJPegCtrlCtrl();

// ��д
public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();

	afx_msg LRESULT OnRefresh(WPARAM wParam,LPARAM lParam);

// ʵ��
protected:
	~CMJPegCtrlCtrl();

	BEGIN_OLEFACTORY(CMJPegCtrlCtrl)        // �๤���� guid
		virtual BOOL VerifyUserLicense();
		virtual BOOL GetLicenseKey(DWORD, BSTR FAR*);
	END_OLEFACTORY(CMJPegCtrlCtrl)

	DECLARE_OLETYPELIB(CMJPegCtrlCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CMJPegCtrlCtrl)     // ����ҳ ID
	DECLARE_OLECTLTYPE(CMJPegCtrlCtrl)		// �������ƺ�����״̬

// ��Ϣӳ��
	DECLARE_MESSAGE_MAP()

// ����ӳ��
	DECLARE_DISPATCH_MAP()

	afx_msg void AboutBox();

// �¼�ӳ��
	DECLARE_EVENT_MAP()

// ���Ⱥ��¼� ID
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

