// CH9329DBGDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CH9329DBG.h"
#include "CH9329DBGDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

UINT   uModType = 0;
/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About


UCHAR mCharToBcd(UCHAR iChar)
{
	UCHAR	mBCD;
	if ( iChar >= '0' && iChar <= '9' ) mBCD = iChar -'0';
	else if ( iChar >= 'A' && iChar <= 'F' ) mBCD = iChar - 'A' + 0x0a;
	else if ( iChar >= 'a' && iChar <= 'f' ) mBCD = iChar - 'a' + 0x0a;
//	else mBCD = 0xff;
	else mBCD = 0;
	return( mBCD );
}

VOID  DbgPrint (LPCTSTR lpFormat,...)
{
   CHAR TextBufferTmp[500]="";    
   
   va_list arglist;
   va_start(arglist, lpFormat);
   vsprintf(TextBufferTmp,lpFormat,arglist);
   va_end(arglist);
   strcat(TextBufferTmp,"\r\n");
   OutputDebugString(TextBufferTmp);
   return ;
}

UINT  SendThreadFunction(LPVOID lpParameter)
{

	CCH9329DBGDlg * pThis  = (CCH9329DBGDlg *)lpParameter;
	HANDLE hEventObject=CreateEvent(NULL,TRUE,TRUE,"");

	if(pThis->m_hHID==INVALID_HANDLE_VALUE)
	{
		pThis->m_ctrlStatus.SetWindowText("设备尚未连接!");
		return 0;
	}
	
	UCHAR buf[129],len;
	UCHAR OutputReport[129];
	memset(buf,0,129);
	memset(OutputReport,0,129);
	len = pThis->m_strBuf.GetLength();

	if(uModType==0)
	{
		if( len > 126)  
			len = 126;		//CH9329WriteData一次最大只能发送63个字节
		memcpy(buf,pThis->m_strBuf,len);
		UINT i = 0; 
		UINT j = 0;
		for(  ; buf[i] != 0 ; i+=2,j++)
		{
			if(!pThis->Char2ToHex((char*)&buf[i],&OutputReport[j]))
			{
				pThis->m_ctrlStatus.SetWindowText("填充内容包含无效的十六进制数,请重试!");
				goto _END;
			}
		}
		len = j;
		if(!CH9329WriteData(pThis->m_hHID,OutputReport,len,hEventObject)) 
		{
			pThis->m_ctrlStatus.SetWindowText("发送数据失败");
			goto _END;
		}
	}
	else
	{
		if( len > 63)  
			len = 63;	
		memset(buf,0,sizeof(buf));
		pThis->GetDlgItem(IDC_EDIT_SEND)->GetWindowText((char*)buf,len+1);

		if(!CH9329WriteData(pThis->m_hHID,buf,len,hEventObject)) 
		{
			pThis->m_ctrlStatus.SetWindowText("发送数据失败");
			goto _END;
		}
	}
_END:
	CloseHandle(hEventObject);
	return 0;
}	

UINT  RecvThreadFunction(LPVOID lpParameter   )
{
	UCHAR recvDataBuf[200]="";
	CCH9329DBGDlg * pThis  = (CCH9329DBGDlg *)lpParameter; 

	if(pThis->m_hHID==INVALID_HANDLE_VALUE)
	{
		pThis->m_ctrlStatus.SetWindowText("设备尚未连接!");
		return 0;
	}
	if(!CH9329InitThreadData(pThis->m_hHID)){
		pThis->m_ctrlStatus.SetWindowText("CH9329InitThreadData Error");
		return 0;
	}
	pThis->m_bStop = 0;
	pThis->m_cbRecv.EnableWindow(FALSE);
	while(!pThis->m_bStop)
	{
		ULONG len = sizeof(recvDataBuf);
		if(!CH9329ReadThreadData(pThis->m_hHID,recvDataBuf,&len) ) break;
		if(len != 0)
		{
			if(uModType==0)
			{
				CHAR tem[200*3];
				memset(tem,0,sizeof(tem));
				for(UINT i=0,j=0;i< len ;i++,j+=3)
				{
					sprintf(&tem[j],"%02X ",(UCHAR)recvDataBuf[i]);
				}
				
				pThis->m_ctrlRecv.AppendText(tem);
				CString st;
				pThis->m_uRecvED += len;
				st.Format("%d",pThis->m_uRecvED);
				pThis->m_mRecvED.SetWindowText(st);
			}
			else
			{
				pThis->m_ctrlRecv.AppendText((char*)recvDataBuf);
				CString st;
				pThis->m_uRecvED += len;
				st.Format("%d",pThis->m_uRecvED);
				pThis->m_mRecvED.SetWindowText(st);
			}
		}
		
	}
	CH9329StopThread(pThis->m_hHID);
	DbgPrint("RecvThreadFunction Exit");
	pThis->m_cbRecv.EnableWindow();
	
	return 0;
}		

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCH9329DBGDlg dialog

CCH9329DBGDlg::CCH9329DBGDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCH9329DBGDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCH9329DBGDlg)
	m_strBuf = _T("");
	m_uRecvED = 0;
	
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCH9329DBGDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCH9329DBGDlg)
	DDX_Control(pDX, IDC_BUTTON_RECV, m_cbRecv);
	DDX_Control(pDX, IDC_EDIT_RECVED, m_mRecvED);
	DDX_Control(pDX, IDC_EDIT_STATUS, m_ctrlStatus);
	DDX_Control(pDX, IDC_EDIT_RECV, m_ctrlRecv);
	DDX_Control(pDX, IDC_EDIT_CHABA, m_ctrlCHABA);
	DDX_Control(pDX, IDC_COMBO_SELECT_DEV, m_ctrlSelDev);
	DDX_Text(pDX, IDC_EDIT_SEND, m_strBuf);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CCH9329DBGDlg, CDialog)
	//{{AFX_MSG_MAP(CCH9329DBGDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(WM_DEVICECHANGE,OnDeviceNotification)
	ON_MESSAGE(MM_MYCHANGEDEVICE,OnMyChangeDevice)
	ON_BN_CLICKED(IDC_BUTTON_OPEN, OnButtonOpen)
	ON_BN_CLICKED(IDC_RADIO_MODTYPE,OnButtonMod)
	ON_BN_CLICKED(IDC_RADIO_MODTYPE2,OnButtonMod2)
	ON_BN_CLICKED(IDC_BUTTON_SEND, OnButtonSend)
	ON_BN_CLICKED(IDC_BUTTON_RECV, OnButtonRecv)
	ON_BN_CLICKED(IDC_BUTTON_STOP, OnButtonStop)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, OnButtonClear)

//	ON_BN_CLICKED(IDC_BUTTON_SET_OUTPUT, OnButtonSetOutput)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCH9329DBGDlg message handlers

BOOL CCH9329DBGDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	m_hHID = INVALID_HANDLE_VALUE;
	// TODO: Add extra initialization here
	GUID hidGuid;
	//HWND hwnd = NULL;
	CH9329GetHidGuid(&hidGuid);//取得HID类别的GUID
	{		//注意设备插拔只能在2000以后的系统上使用
		HDEVNOTIFY  m_hRegDevNotif;
		DEV_BROADCAST_DEVICEINTERFACE	mNotifyFilter;
		ZeroMemory( &mNotifyFilter, sizeof( mNotifyFilter ) );
		mNotifyFilter.dbcc_size = sizeof( mNotifyFilter );
		mNotifyFilter.dbcc_devicetype = DBT_DEVTYP_DEVICEINTERFACE;  // 设置监控的设备类型
		mNotifyFilter.dbcc_classguid = hidGuid;  // 设置监控的设备接口类:USB接口
		m_hRegDevNotif = RegisterDeviceNotification(GetSafeHwnd(), &mNotifyFilter, DEVICE_NOTIFY_WINDOW_HANDLE );  // 注册设备事件通知
		//m_hRegDevNotif = RegisterDeviceNotification(hwnd, &mNotifyFilter, DEVICE_NOTIFY_WINDOW_HANDLE );  // 注册设备事件通知
		if ( !m_hRegDevNotif ) {
				//ULONG d = GetLastError();
				return( FALSE );
		}
	}
	InitSelDev();
	((CEdit*)GetDlgItem(IDC_EDIT_SEND))->SetLimitText(126);
	((CButton*)GetDlgItem(IDC_RADIO_MODTYPE))->SetCheck(1);
	((CButton*)GetDlgItem(IDC_RADIO_MODTYPE2))->SetCheck(0);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CCH9329DBGDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CCH9329DBGDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CCH9329DBGDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
LRESULT CCH9329DBGDlg::OnDeviceNotification(WPARAM wParam, LPARAM lParam)
{
	PDEV_BROADCAST_DEVICEINTERFACE	DevInfo;
	ULONG	mEventStatus;
	BOOL bCurrentDev = FALSE;
	//UCHAR	DevId[ MAX_DEVICE_PATH_SIZE ];
	DevInfo = (PDEV_BROADCAST_DEVICEINTERFACE)lParam;  // 设备信息
	if ( wParam == DBT_DEVICEARRIVAL || wParam == DBT_DEVICEREMOVEPENDING || wParam == DBT_DEVICEREMOVECOMPLETE ) 
	{  // 设备插入或移除
		if ( DevInfo -> dbcc_devicetype == DBT_DEVTYP_DEVICEINTERFACE ) 
		{
			
			switch( wParam ) {
				case DBT_DEVICEARRIVAL: mEventStatus = DEVICE_ARRIVAL; break;
				case DBT_DEVICEREMOVEPENDING: mEventStatus = DEVICE_REMOVE_PEND; break;
				case DBT_DEVICEREMOVECOMPLETE: mEventStatus = DEVICE_REMOVE; break;
				default: mEventStatus = DEVICE_REMOVE; break;
			}
			//CH9329GetDevicePath返回的字符串全转化成大写
			CharUpperBuff(( LPTSTR )&DevInfo -> dbcc_name,strlen(( LPTSTR )&DevInfo -> dbcc_name));
			if(strcmp(m_strDevPath,DevInfo -> dbcc_name) == 0 )
			{
				bCurrentDev = TRUE;
				
			}
			PostMessage(MM_MYCHANGEDEVICE,(DWORD)mEventStatus,(DWORD)bCurrentDev);
		}
		return 0;
	}
	return 0;
}

void CCH9329DBGDlg::log_msg(CHAR *str)
{
	CHAR  strBuf[200]="";
	sprintf(strBuf,"操作状态:%s",str);
	GetDlgItem(IDC_STATIC_STATUS)->SetWindowText(strBuf);
}

LRESULT CCH9329DBGDlg::OnMyChangeDevice(WPARAM wParam, LPARAM lParam)
{
	
	if( wParam == DEVICE_ARRIVAL )
	{
		m_ctrlCHABA.SetWindowText("有HID设备到达");
		log_msg("检测到设备已连接!");
	}
	else
	{
		m_ctrlCHABA.SetWindowText("有HID设备离开");
		if(m_hHID != INVALID_HANDLE_VALUE)
			CH9329CloseDevice(m_hHID);
		m_hHID = INVALID_HANDLE_VALUE;
		GetDlgItem(IDC_BUTTON_OPEN)->SetWindowText("打开设备");
		ClrShow();
		log_msg("检测到设备已断开连接!");
	}
	m_ctrlSelDev.ResetContent();
	InitSelDev();
	
	return 0;
}

//把两个字符转成一个字节的十六进制数值
BOOL CCH9329DBGDlg::Char2ToHex(PCHAR  pInChar,  //待转换的2个字符缓冲区
			   PUCHAR pOutChar) //转换后的十六进制数值
{
	UCHAR h,l;	

	h = pInChar[0]; //高4位
	l = pInChar[1]; //低4位
	if(l>='0' && l<='9')
	{
		l = l - '0';	
	}
	else if(l>='a' && l<='f')
	{
		l = l - 'a' + 0xa;
	}
	else if(l>='A' && l<='F')
	{
		l = l - 'A' + 0xa;
	}
	else
	{	
		return FALSE;
	}	
	if(h>='0' && h<='9')
	{
		h = h - '0';
	}
	else if(h>='a' && h<='f')
	{
		h = h - 'a' + 0xa;
	}
	else if(h>='A' &&h <='F')
	{
		h = h - 'A' + 0xa;
	}
	else
	{
		return FALSE;
	}	
	h <<= 4;
	h |= l;
	*pOutChar = h;
	return TRUE;
}
void CCH9329DBGDlg::InitSelDev()
{
	int deviceNo=0;
	CHAR buf[1024];
	HANDLE hHID;
	
	SetLastError(NO_ERROR);
	while(GetLastError()!=ERROR_NO_MORE_ITEMS)
	{
			memset(buf,0,sizeof(buf));
			if( CH9329GetDevicePath(deviceNo,buf,sizeof(buf)) )
			{
				//打开设备,并获得设备句柄
				 hHID=CreateFile(buf,
					GENERIC_READ|GENERIC_WRITE,
					FILE_SHARE_READ|FILE_SHARE_WRITE,
					NULL,OPEN_EXISTING,FILE_FLAG_OVERLAPPED,NULL);
				
				if(hHID==INVALID_HANDLE_VALUE)
				{
					deviceNo++;
					continue;
				}

				PHIDP_PREPARSED_DATA PreparsedData;
				HIDP_CAPS Capabilities;
				int featurelen = 0, OutputReportLen = 0, InputReportLen = 0;

				HidD_GetPreparsedData(hHID, &PreparsedData);
				HidP_GetCaps(PreparsedData, &Capabilities);

				OutputReportLen = Capabilities.OutputReportByteLength;
				InputReportLen = Capabilities.InputReportByteLength;
				featurelen = Capabilities.FeatureReportByteLength;

				if (featurelen == 65)
				{
					CharUpperBuff(buf, strlen(buf));
					m_ctrlSelDev.InsertString(0, (const char *)buf);
					m_ctrlCHABA.SetWindowText("有设备接入");
					CloseHandle(hHID);
				}
			}
			deviceNo++;
	}
	m_ctrlSelDev.SetCurSel(0);
}

void CCH9329DBGDlg::OnButtonOpen() 
{
	CString strDev;
	USHORT VID,PID,VER;
	CHAR version[100]="";
	USHORT inportlen,outportlen;

	GetDlgItem(IDC_BUTTON_OPEN)->GetWindowText(version,20);
	if(strcmp(version,"打开设备")==0)         //将要打开设备
	{
		if( m_ctrlSelDev.GetCount() == 0 ) 
		{
			log_msg("当前系统没有可打开的HID设备!");
			return;
		}
		
		if( m_ctrlSelDev.GetCurSel() == -1 )
		{
			log_msg("请选择一个HID设备!");
			return;
		}
		if(m_hHID != INVALID_HANDLE_VALUE )
		{
			log_msg("该设备已打开!");
			return;
		}
		m_ctrlSelDev.GetLBText(m_ctrlSelDev.GetCurSel(),strDev);
		
		m_hHID = CH9329OpenDevicePath((PCHAR)LPCTSTR (strDev));
		
		if(m_hHID==INVALID_HANDLE_VALUE)
		{
			log_msg("打开HID设备失败!");
			return;
		}
		
		//获取厂商ID和设备ID
		if(!CH9329GetAttributes(m_hHID,&VID,&PID,&VER))
		{
			CH9329CloseDevice(m_hHID);
			log_msg("获取设备VID、PID失败!");
			return;
		}
		memset(version,0,100);
		sprintf(version,"设备已连接,VID=%XPID=%X VER=%X ",VID,PID,VER);
		m_ctrlStatus.SetWindowText(version);
		CH9329GetBufferLen(m_hHID,&inportlen,&outportlen);
		CH9329SetTimeOut(m_hHID,3000,3000);
	
		log_msg("打开设备成功!");
		GetDlgItem(IDC_BUTTON_OPEN)->SetWindowText("关闭设备");
	}
	else
	{
		m_ctrlSelDev.GetLBText(m_ctrlSelDev.GetCurSel(),strDev);	
		CH9329CloseDevice(m_hHID);
		/*if(m_hHID!=INVALID_HANDLE_VALUE)
		{
			CH9329CloseDevice(m_hHID);
		}*/
		m_hHID = INVALID_HANDLE_VALUE;
		log_msg("关闭设备成功!");
		ClrShow();
		GetDlgItem(IDC_BUTTON_OPEN)->SetWindowText("打开设备");
	}

}

void CCH9329DBGDlg::OnButtonMod()
{
	uModType = 0;
	GetDlgItem(IDC_STATIC_INFO)->SetWindowText("发送数据(输入的数据是16进制,中间没空格,个数少于126个)");
	((CEdit*)GetDlgItem(IDC_EDIT_SEND))->SetLimitText(126);
}

void CCH9329DBGDlg::OnButtonMod2()
{
	uModType = 2;
	GetDlgItem(IDC_STATIC_INFO)->SetWindowText("发送数据(输入的数据是ASCII字符,个数少于63个)");
	((CEdit*)GetDlgItem(IDC_EDIT_SEND))->SetLimitText(63);	
}

void CCH9329DBGDlg::OnButtonSend() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	AfxBeginThread(SendThreadFunction,this,THREAD_PRIORITY_NORMAL,0,0,NULL); 
}

void CCH9329DBGDlg::OnButtonRecv() 
{
	// TODO: Add your control notification handler code here
	AfxBeginThread(RecvThreadFunction,this,THREAD_PRIORITY_NORMAL,0,0,NULL); 
}

void CCH9329DBGDlg::OnButtonStop() 
{
	// TODO: Add your control notification handler code here
	m_bStop = 1;
}

void CCH9329DBGDlg::OnButtonClear() 
{
	// TODO: Add your control notification handler code here
	CString st;
	m_uRecvED = 0;
	st.Format("%d",m_uRecvED);
	m_mRecvED.SetWindowText(st);

	m_ctrlRecv.SetWindowText("");
}

void CCH9329DBGDlg::ClrShow()
{
	GetDlgItem(IDC_EDIT_STATUS)->SetWindowText("");
}
