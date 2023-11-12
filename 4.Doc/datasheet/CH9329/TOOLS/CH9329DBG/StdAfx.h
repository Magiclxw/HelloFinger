// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__C90ABBB3_0C8C_4F0D_B342_9833641DA8A4__INCLUDED_)
#define AFX_STDAFX_H__C90ABBB3_0C8C_4F0D_B342_9833641DA8A4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef	WINVER
#define WINVER 0x501
#endif

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT


#include	<dbt.h>
#include	<setupapi.h>
#include	"CH9329DLL.H"
extern "C"
{
#include "hidsdi.h"
}
#pragma	comment(lib,"CH9329DLL")
#pragma	comment(lib,"setupapi")
#pragma	comment(lib,"hid")

#define		MM_MYCHANGEDEVICE    WM_USER + 4
#define		MAX_DEVICE_PATH_SIZE	128			// 设备名称的最大字符数

#define		DEVICE_ARRIVAL		3		// 设备插入事件,已经插入
#define		DEVICE_REMOVE_PEND	1		// 设备将要拔出
#define		DEVICE_REMOVE			0		// 设备拔出事件,已经拔出

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__C90ABBB3_0C8C_4F0D_B342_9833641DA8A4__INCLUDED_)
