// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once

#include "targetver.h"
#include <afx.h>//因为要用到CString所以要包含这个头文件
#define WIN32_LEAN_AND_MEAN             //  从 Windows 头文件中排除极少使用的信息
#include<windows.h>

//添加MFC支持
#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include<string>
using namespace std;
// TODO: 在此处引用程序需要的其他头文件
/////////////////////////////////////////////////////////////////////////////
typedef struct tagRS_BLOCKINFO
{
	int ncRSBlock;		// 纠错块数
	int ncAllCodeWord;	// 块内码字数
	int ncDataCodeWord;	// 数据码字数（码字数-RS码字数）

} RS_BLOCKINFO, *LPRS_BLOCKINFO;

/////////////////////////////////////////////////////////////////////////////
//QRcode版本相关信息
typedef struct tagQR_VERSIONINFO
{
	int nVersionNo;	   // 版本号1-40
	int ncAllCodeWord; // 总码字数
	int ncDataCodeWord[4];	// 数据码字（总码字-RS码字）

	int ncAlignPoint;	// 校正点数
	int nAlignPoint[6];	// 校正图形中心坐标

	RS_BLOCKINFO RS_BlockInfo1[4]; // 纠错块信息
	RS_BLOCKINFO RS_BlockInfo2[4]; // 纠错块信息

} QR_VERSIONINFO, *LPQR_VERSIONINFO;
////////////////////////////////////////////////////
//全局变量
////////////////////////////////////////////////////
extern int VersionInfoBit[];
extern int FormatInfoBit[];
extern int nIndicatorLenNumeral[];
extern int nIndicatorLenAlphabet[];
extern int nIndicatorLen8Bit[];
extern int nIndicatorLenHanzi[];
extern QR_VERSIONINFO QR_VersonInfo[];
extern int ReturnVal;//返回值
///////////////////////////////////////////////////