#include "stdafx.h"
#include "Test.h"
#include"ContentDecoder.h"
#include "QRcodeImage.h"
#include"RecDetect.h"
#ifdef _MANAGED
#pragma managed(push, off)
#endif


#ifdef _MANAGED
#pragma managed(pop)
#endif
int  add(int a,int b)
{

    return (b+a);
}
//加函数
int APIENTRY Multi(int a,int b)   // APIENTRY 此关键字不可少
{
return add(a,b)*b;
}
//减函数
int APIENTRY Subtraction(int a,int b,int i)
{
if(0==i)
    return (a-b);
else
    return (b-a);
}
EXPORTQR int _stdcall   APIENTRY GetQRversion()
{
	return QRversion;
}

EXPORTQR char _stdcall   APIENTRY GetQRLevel()
{       
	
	
	return QRLevel;
}


EXPORTQR LPWSTR _stdcall   APIENTRY GetQRstring(){
	if(QRstring==NULL)
{
	LPWSTR QRstring1=_T("译码失败，内容未知");
	return QRstring1;
}else{
	return QRstring;
}
}

LPWSTR APIENTRY Test(char* fileName)
{
	
	//LPWSTR QRstring=picxdel(fileName);
	
		 //return picxdel(fileName);
	LPWSTR QRstring1=_T("文件名不能为空");
	int version=QRversion;
		 return QRstring1;
}
LPWSTR APIENTRY picxdel(char* fileName)
{

	QRcodeImage * QR_image;
	ContentDecoder * QR_Decode;

	BYTE m_CodeData[MAX_MODULESIZE][MAX_MODULESIZE]; // 存储条形码位数据

	int m_nCodeSize;//编码区域大小
	//int m_nMoudleSize;//模块大小
	int m_nVersion;//版本号
	//int m_nLevel;//纠错等级
	//POINT leftup;
	//POINT right;
	//POINT down;
	//int nShowSize;
	try{
			if( fileName==NULL)
		{
			LPWSTR QRstring1=_T("文件名不能为空");
		 return QRstring1;
		
		}
	//IplImage *img=cvLoadImage(fileName,CV_LOAD_IMAGE_GRAYSCALE);
	//cvThreshold(img,img,50,255,CV_THRESH_BINARY_INV);
	////cvShowImage(fileName.c_str(),img);
	//cvSaveImage("D:\\1.bmp",img);
	//cvReleaseImage(&img);
IplImage *src=0, *dst=0; 
		src=cvLoadImage(fileName,1);
		if(src==NULL )
		{
			CString   s   =fileName;//或
			s=s+"文件载入错误。";

              LPCTSTR   lp   =   (LPCTSTR)(s);
			LPWSTR QRstring1=(LPWSTR)lp;
		 return QRstring1;
		}
		
		//这是图片本身的问题，有一道白色边框
		//先清理周边的点,这是为了防止区域截取时候矩形区域大于图像造成无效
		for (int y=0;y<src->height;y++)
		{
			uchar *ptr=(uchar*)(src->imageData+y*src->widthStep);
			for (int x=0;x<src->width;x++)
			{
				if(x>3&&x<(src->width-3)&&y>3&&y<(src->height-3)){
					//范围内
				}else{
					ptr[src->nChannels*x]=0;
					ptr[src->nChannels*x+1]=0;
					ptr[src->nChannels*x+2]=0;

				}

			}
		}
		if(src->width<360){
			int scale =3; //缩放倍数为3倍 
			CvSize dst_cvsize; //目标图像尺寸 
			dst_cvsize.width =scale*src->width;  //目标图像的宽为源图象宽的scale倍
			dst_cvsize.height = scale*src->height; //目标图像的高为源图象高的scale倍
			dst = cvCreateImage(dst_cvsize, src->depth, src->nChannels); //构造目标图象
		}
		else dst = cvCreateImage(cvGetSize(src), src->depth, src->nChannels); //构造目标图象
		cvResize(src, dst); //缩放源图像到目标图像
	
		RecDect *rd=new RecDect(dst);	//声明对象
	rd->RfindSquaresRect(0.1f,0.81f);//第一次调用，获取图像轮廓定点坐标:此步获取图像大概位置，然后进行区域选择
	
		/*此时已经获得pt,进行区域截取并对歪掉图像进行旋转*/
		rd->AreaRotate();
		//cvShowImage("dfdf",rd->img);
		
		int angle=rd->recognVersion(rd->findSquares4() );//位置探测图形提取并计算版本号,angle为矫正正确位置的角度
		
		if(angle!=0){//这是为旋转不到位的图像准备的
			rd->FitRotate(rd->img,angle);
			rd->FitRotate(rd->img0,angle);
			rd->RfindSquaresRect(0.36f,0.9);//获取图像轮廓定点坐标:此步获取图像大概位置,chongxin dingweidingdian pt weizhi,keyi youhua ,xianzai meishijian
			angle=rd->recognVersion(rd->findSquares4() );//位置探测图形提取并计算版本号
		}
		
		//rd->drawSquares();
		
		IplImage * loadImage=rd->drawGrid();
		if(loadImage==NULL){
		//	MessageBox(_T("红外QR码转化过程出错"),_T("QR码识别"));
				
		cvReleaseImage( &src );		////释放图像
		cvReleaseImage( &dst );
	
		LPWSTR QRstring1=_T("识别过程出现异常");
		 return QRstring1;
		}
		cvSaveImage(fileName,loadImage);
		QR_image = new QRcodeImage(loadImage);
		//cvReleaseImage(&loadImage);
		QR_image->GetImageData();

		m_nVersion = QR_image->finderPattern->m_version;
		m_nCodeSize = m_nVersion * 4 +17;
		for(int i=0;i<m_nCodeSize;i++)
			for(int j=0;j<m_nCodeSize;j++)
				m_CodeData[i][j]=QR_image->bitMatrix[i][j];
		
	
		
		//解码
		QR_Decode = new ContentDecoder;
		QR_Decode->DecodeData(m_nCodeSize,m_nVersion,m_CodeData);
		QRstring=(QR_Decode->m_strData).GetBuffer(QR_Decode->m_strData.GetLength());
		

		//显示结果
		//GetDlgItem(IDC_EDIT_TEXT)->SetWindowText(QR_Decode->m_strData);//"由于解码功能尚未完成，暂时无法显示!!!"
;
		QRversion=QR_Decode->m_nVersion; 
	
		char str;
		switch(QR_Decode->m_nLevel)
		{
		case QR_LEVEL_L:str='L';break;
		case QR_LEVEL_M:str='M';break;
		case QR_LEVEL_Q:str='Q';break;
		case QR_LEVEL_H:str='H';break;
		}
		//GetDlgItem(IDC_STATIC_LEVEL)->SetWindowText("纠错等级："+str);
	    QRLevel=str;
		
		cvReleaseImage( &src );		////释放图像
		cvReleaseImage( &dst );
		cvReleaseImage( &loadImage );
		return QRstring;
	}catch(...)
	{
		LPWSTR QRstring1=_T("识别过程出现异常");
		 return QRstring1;
	}
		
	
}

