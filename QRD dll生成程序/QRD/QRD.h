// QRD.h : main header file for the QRD DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CQRDApp
// See QRD.cpp for the implementation of this class
//

class CQRDApp : public CWinApp
{
public:
	CQRDApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
