// CH9329DBGDlg.h : header file
//

#if !defined(AFX_CH9329DBGDLG_H__EE13AD28_B5B5_4998_864A_98A1E0F4B5E3__INCLUDED_)
#define AFX_CH9329DBGDLG_H__EE13AD28_B5B5_4998_864A_98A1E0F4B5E3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "MyEdit.h"
/////////////////////////////////////////////////////////////////////////////
// CCH9329DBGDlg dialog

class CCH9329DBGDlg : public CDialog
{
// Construction
public:

	void InitSelDev();
	HANDLE m_hHID;
	CHAR  m_strDevPath[512];
	UCHAR m_ucInterval;
	BOOL  m_bStop;
	UINT  m_uRecvED;
	BOOL  Char2ToHex(PCHAR  pInChar,PUCHAR pOutChar); 
	CCH9329DBGDlg(CWnd* pParent = NULL);	// standard constructor
	void log_msg(CHAR *str);
	void ClrShow();
// Dialog Data
	//{{AFX_DATA(CCH9329DBGDlg)
	enum { IDD = IDD_CH9329DBG_DIALOG };
	CButton	m_cbRecv;
	CEdit	m_mRecvED;
	CEdit	m_ctrlStatus;
	CMyEdit	m_ctrlRecv;
	CEdit	m_ctrlCHABA;
	CComboBox	m_ctrlSelDev;
	CString	m_strBuf;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCH9329DBGDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CCH9329DBGDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg LRESULT OnDeviceNotification(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMyChangeDevice(WPARAM wParam, LPARAM lParam);
	afx_msg void OnButtonOpen();
	afx_msg void OnButtonSend();
	afx_msg void OnButtonRecv();
	afx_msg void OnButtonStop();
	afx_msg void OnButtonClear();
	afx_msg void OnButtonMod();
	afx_msg void OnButtonMod2();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CH9329DBGDLG_H__EE13AD28_B5B5_4998_864A_98A1E0F4B5E3__INCLUDED_)
