#ifndef DllTest_01
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/imgproc/imgproc_c.h"
#include "opencv2/highgui/highgui.hpp"
#define DllTest_01

#define EXPORTQR extern "C" __declspec(dllexport)
//两个参数做加法
EXPORTQR int _stdcall Multi(int iNum1=0,int iNum2=0);
//两个参数做减法
EXPORTQR int _stdcall Subtraction(int iNum1=0,int iNum2=0,int iMethod=0);
EXPORTQR LPWSTR _stdcall   APIENTRY Test(char* fileName);
EXPORTQR LPWSTR _stdcall   APIENTRY picxdel(char* fileName);
EXPORTQR int _stdcall   APIENTRY GetQRversion();
EXPORTQR char _stdcall   APIENTRY GetQRLevel();
EXPORTQR LPWSTR _stdcall   APIENTRY GetQRstring();
  int     QRversion;
   char    QRLevel;
   LPWSTR QRstring;
#endif