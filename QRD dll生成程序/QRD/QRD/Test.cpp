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
//�Ӻ���
int APIENTRY Multi(int a,int b)   // APIENTRY �˹ؼ��ֲ�����
{
return add(a,b)*b;
}
//������
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
	LPWSTR QRstring1=_T("����ʧ�ܣ�����δ֪");
	return QRstring1;
}else{
	return QRstring;
}
}

LPWSTR APIENTRY Test(char* fileName)
{
	
	//LPWSTR QRstring=picxdel(fileName);
	
		 //return picxdel(fileName);
	LPWSTR QRstring1=_T("�ļ�������Ϊ��");
	int version=QRversion;
		 return QRstring1;
}
LPWSTR APIENTRY picxdel(char* fileName)
{

	QRcodeImage * QR_image;
	ContentDecoder * QR_Decode;

	BYTE m_CodeData[MAX_MODULESIZE][MAX_MODULESIZE]; // �洢������λ����

	int m_nCodeSize;//���������С
	//int m_nMoudleSize;//ģ���С
	int m_nVersion;//�汾��
	//int m_nLevel;//����ȼ�
	//POINT leftup;
	//POINT right;
	//POINT down;
	//int nShowSize;
	try{
			if( fileName==NULL)
		{
			LPWSTR QRstring1=_T("�ļ�������Ϊ��");
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
			CString   s   =fileName;//��
			s=s+"�ļ��������";

              LPCTSTR   lp   =   (LPCTSTR)(s);
			LPWSTR QRstring1=(LPWSTR)lp;
		 return QRstring1;
		}
		
		//����ͼƬ��������⣬��һ����ɫ�߿�
		//�������ܱߵĵ�,����Ϊ�˷�ֹ�����ȡʱ������������ͼ�������Ч
		for (int y=0;y<src->height;y++)
		{
			uchar *ptr=(uchar*)(src->imageData+y*src->widthStep);
			for (int x=0;x<src->width;x++)
			{
				if(x>3&&x<(src->width-3)&&y>3&&y<(src->height-3)){
					//��Χ��
				}else{
					ptr[src->nChannels*x]=0;
					ptr[src->nChannels*x+1]=0;
					ptr[src->nChannels*x+2]=0;

				}

			}
		}
		if(src->width<360){
			int scale =3; //���ű���Ϊ3�� 
			CvSize dst_cvsize; //Ŀ��ͼ��ߴ� 
			dst_cvsize.width =scale*src->width;  //Ŀ��ͼ��Ŀ�ΪԴͼ����scale��
			dst_cvsize.height = scale*src->height; //Ŀ��ͼ��ĸ�ΪԴͼ��ߵ�scale��
			dst = cvCreateImage(dst_cvsize, src->depth, src->nChannels); //����Ŀ��ͼ��
		}
		else dst = cvCreateImage(cvGetSize(src), src->depth, src->nChannels); //����Ŀ��ͼ��
		cvResize(src, dst); //����Դͼ��Ŀ��ͼ��
	
		RecDect *rd=new RecDect(dst);	//��������
	rd->RfindSquaresRect(0.1f,0.81f);//��һ�ε��ã���ȡͼ��������������:�˲���ȡͼ����λ�ã�Ȼ���������ѡ��
	
		/*��ʱ�Ѿ����pt,���������ȡ�������ͼ�������ת*/
		rd->AreaRotate();
		//cvShowImage("dfdf",rd->img);
		
		int angle=rd->recognVersion(rd->findSquares4() );//λ��̽��ͼ����ȡ������汾��,angleΪ������ȷλ�õĽǶ�
		
		if(angle!=0){//����Ϊ��ת����λ��ͼ��׼����
			rd->FitRotate(rd->img,angle);
			rd->FitRotate(rd->img0,angle);
			rd->RfindSquaresRect(0.36f,0.9);//��ȡͼ��������������:�˲���ȡͼ����λ��,chongxin dingweidingdian pt weizhi,keyi youhua ,xianzai meishijian
			angle=rd->recognVersion(rd->findSquares4() );//λ��̽��ͼ����ȡ������汾��
		}
		
		//rd->drawSquares();
		
		IplImage * loadImage=rd->drawGrid();
		if(loadImage==NULL){
		//	MessageBox(_T("����QR��ת�����̳���"),_T("QR��ʶ��"));
				
		cvReleaseImage( &src );		////�ͷ�ͼ��
		cvReleaseImage( &dst );
	
		LPWSTR QRstring1=_T("ʶ����̳����쳣");
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
		
	
		
		//����
		QR_Decode = new ContentDecoder;
		QR_Decode->DecodeData(m_nCodeSize,m_nVersion,m_CodeData);
		QRstring=(QR_Decode->m_strData).GetBuffer(QR_Decode->m_strData.GetLength());
		

		//��ʾ���
		//GetDlgItem(IDC_EDIT_TEXT)->SetWindowText(QR_Decode->m_strData);//"���ڽ��빦����δ��ɣ���ʱ�޷���ʾ!!!"
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
		//GetDlgItem(IDC_STATIC_LEVEL)->SetWindowText("����ȼ���"+str);
	    QRLevel=str;
		
		cvReleaseImage( &src );		////�ͷ�ͼ��
		cvReleaseImage( &dst );
		cvReleaseImage( &loadImage );
		return QRstring;
	}catch(...)
	{
		LPWSTR QRstring1=_T("ʶ����̳����쳣");
		 return QRstring1;
	}
		
	
}

