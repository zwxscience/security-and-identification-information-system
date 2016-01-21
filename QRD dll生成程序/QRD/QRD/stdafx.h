// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
//

#pragma once

#include "targetver.h"
#include <afx.h>//��ΪҪ�õ�CString����Ҫ�������ͷ�ļ�
#define WIN32_LEAN_AND_MEAN             //  �� Windows ͷ�ļ����ų�����ʹ�õ���Ϣ
#include<windows.h>

//���MFC֧��
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
// TODO: �ڴ˴����ó�����Ҫ������ͷ�ļ�
/////////////////////////////////////////////////////////////////////////////
typedef struct tagRS_BLOCKINFO
{
	int ncRSBlock;		// �������
	int ncAllCodeWord;	// ����������
	int ncDataCodeWord;	// ������������������-RS��������

} RS_BLOCKINFO, *LPRS_BLOCKINFO;

/////////////////////////////////////////////////////////////////////////////
//QRcode�汾�����Ϣ
typedef struct tagQR_VERSIONINFO
{
	int nVersionNo;	   // �汾��1-40
	int ncAllCodeWord; // ��������
	int ncDataCodeWord[4];	// �������֣�������-RS���֣�

	int ncAlignPoint;	// У������
	int nAlignPoint[6];	// У��ͼ����������

	RS_BLOCKINFO RS_BlockInfo1[4]; // �������Ϣ
	RS_BLOCKINFO RS_BlockInfo2[4]; // �������Ϣ

} QR_VERSIONINFO, *LPQR_VERSIONINFO;
////////////////////////////////////////////////////
//ȫ�ֱ���
////////////////////////////////////////////////////
extern int VersionInfoBit[];
extern int FormatInfoBit[];
extern int nIndicatorLenNumeral[];
extern int nIndicatorLenAlphabet[];
extern int nIndicatorLen8Bit[];
extern int nIndicatorLenHanzi[];
extern QR_VERSIONINFO QR_VersonInfo[];
extern int ReturnVal;//����ֵ
///////////////////////////////////////////////////