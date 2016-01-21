// RecDetect.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/imgproc/imgproc_c.h"
#include "opencv2/highgui/highgui.hpp"
#include <vector>
#include "RecDetect.h"
#include <iostream>
#include <math.h>
#include <string.h>
using namespace std;
using namespace cv;

//IplImage* img = 0;
//IplImage* img0 = 0;
//CvMemStorage* storage = 0;
//CvPoint pt[4];//��ʱ��ž����ĸ�����
//vector<CvPoint> arr;//���ʵ�ʾ�������
//vector<int > answer;//���ʵ�ʾ��������Ӧֵ
// read 4 sequence elements at a time (all vertices of a square)
//const char* wndname= "ģ�������";
//char *result0=new char[9];//�洢ʶ���ַ���
//int thresh =800;
//��ʼ��

void Soble(const IplImage *sourceimg,IplImage* gradientImage)

{

	IplImage* H = cvCreateImage(cvGetSize(sourceimg),IPL_DEPTH_16S,sourceimg->nChannels);

	IplImage* V = cvCreateImage(cvGetSize(sourceimg), IPL_DEPTH_16S,sourceimg->nChannels);

	IplImage* HV = cvCreateImage(cvGetSize(sourceimg), IPL_DEPTH_16S,sourceimg->nChannels);



	//both horizontal and vertical gradient

	cvSobel(sourceimg,H,0,1,3); 
	cvSobel(sourceimg,V,1,0,3);
	//total gradient = sqrt(horizontal*horizontal+vertical*vertical)

	int i,j;

	double v1,v2,v;

	for (i=0;i<sourceimg->height;i++)

	{

		for (j=0;j<sourceimg->width;j++)

		{

			v1 = cvGetReal2D(H,i,j);

			v2 = cvGetReal2D(V,i,j);

			v = sqrt(v1*v1+v2*v2);
			cvSetReal2D(HV,i,j,v);

		}

	}

	cvNormalize(HV,gradientImage,0,255,CV_MINMAX,0);


	cvReleaseImage(&H);

	cvReleaseImage(&V);

	cvReleaseImage(&HV);

}
RecDect::RecDect(IplImage *dst){
	version=1;//Ĭ�ϰ汾��1������21
	number=21;
	memset(pt,0,sizeof(CvPoint)*4);
	memset(corner1,0,sizeof(CvPoint)*4);
	memset(corner2,0,sizeof(CvPoint)*4);
	memset(corner3,0,sizeof(CvPoint)*4);
	memset(corner4,0,sizeof(CvPoint)*4);
	//storage = cvCreateMemStorage(0);
	if (!img0)
	{
		cvReleaseImage(&img0);
	}
	if (!img)
	{
		cvReleaseImage(&img);
	}
	img=cvCreateImage(cvGetSize(dst),dst->depth,dst->nChannels);//�Ҷ�
	cvCopy(dst,img);  //��ȡG
	//ת���Ҷ�
	img0=cvCreateImage(cvGetSize(img),img->depth,1);//�Ҷ�
	cvSetImageCOI(img,1);//Bɫ
	cvCopy(img,img0);  //��ȡBɫ
	cvSetImageCOI(img,0);//�ָ�
	WUL=0;//
	WUR=0;
	ModeSize=0;//ģ���С
}
/*************************************************
����:        ͼ����ǿ
����:     ��Ϊ����ͷͼ���������Ҫ����ֱ��ͼ����ͼ����ǿ��
��ͼ��Ҷȵ���ֵ���쵽0-255    
����˵��:    
src�� ��ͨ���Ҷ�ͼ�� 
dst�����ش�����ͼ��
����ֵ:          ͬ����С�ĵ�ͨ���Ҷ�ͼ�� 
*************************************************/
int RecDect::ImageStretchByHistogram(IplImage *src,IplImage *dst)

{
	//p[]���ͼ������Ҷȼ��ĳ��ָ��ʣ�
	//p1[]��Ÿ����Ҷȼ�֮ǰ�ĸ��ʺͣ�����ֱ��ͼ�任��
	//num[]���ͼ������Ҷȼ����ֵĴ���;

	assert(src->width==dst->width);//��֤һ����
	float p[GrayScale],p1[GrayScale],num[GrayScale];
	//�����������
	memset(p,0,sizeof(p));
	memset(p1,0,sizeof(p1));
	memset(num,0,sizeof(num));

	int height=src->height;
	int width=src->width;
	long wMulh = height * width;

	//����ͼ������Ҷȼ����ֵĴ���
	// to do use openmp
	for(int x=0;x<width;x++)
	{
		for(int y=0;y<height;y++)
		{
			uchar v=((uchar*)(src->imageData + src->widthStep*y))[x];
			num[v]++;
		}
	}

	//����ͼ������Ҷȼ��ĳ��ָ���
	for(int i=0;i<GrayScale;i++)
	{
		p[i]=num[i]/wMulh;
	}

	//���Ÿ����Ҷȼ�֮ǰ�ĸ��ʺ�
	for(int i=0;i<GrayScale;i++)
	{
		for(int k=0;k<=i;k++)
			p1[i]+=p[k];
	}

	//ֱ��ͼ�任
	// to do use openmp
	for(int x=0;x<width;x++)
	{
		for(int y=0;y<height;y++)
		{
			uchar v=((uchar*)(src->imageData + src->widthStep*y))[x];
			((uchar*)(dst->imageData + dst->widthStep*y))[x]= p1[v]*255+0.5;            
		}
	}

	return 0;

}
/*************************************************
����:        ͼ��͸�ӱ任
����:    ��Ϊ������ͼƬ�ᷢ��Ť������ת�ȣ���Ҫ����У��   
����˵��:    
img�� ��Ҫ�������ͨ��ͼ�� 
����ֵ:       0
*************************************************/
int RecDect::WarpPerspective()
{

	IplImage* Img_old = cvCloneImage(img);

	float fix = 1; 
	float w = (float)Img_old->width + fix;
	float h = (float)Img_old->height + fix;

	CvPoint2D32f src_point[4];
	CvPoint2D32f dst_point[4];
	int minx=0,miny=0;
	//CvRect crt;
	//�趨Դ�۲��棬��ָ���ı��ε��ĸ�����
	//pt[2]���½�
	src_point[0].x=(float)pt[2].x-minx;             
	src_point[0].y=(float)pt[2].y-miny;
	//pt[3]���½�
	src_point[1].x=(float)pt[3].x-minx;                    
	src_point[1].y=(float)pt[3].y-miny;
	//pt[1]���Ͻ�
	src_point[2].x=(float)pt[1].x-minx; 
	src_point[2].y=(float)pt[1].y-miny;
	//pt[0]���Ͻ�
	src_point[3].x=(float)pt[0].x-minx; 
	src_point[3].y=(float)pt[0].y-miny;


	//�趨Ŀ��۲��棬��ָ���ı��ε��ĸ�����
	dst_point[0].x=-fix;               
	dst_point[0].y=h;

	dst_point[1].x=w;              
	dst_point[1].y=h;

	dst_point[2].x=-fix;
	dst_point[2].y=-fix;

	dst_point[3].x=w;
	dst_point[3].y=-fix;


	float newm[9];            
	CvMat newM = cvMat( 3, 3, CV_32F, newm );
	//���͸��ת������
	//cvWarpPerspectiveQMatrix(src_point,dst_point,&newM);
	cvGetPerspectiveTransform(src_point,dst_point,&newM);
	//͸��ת��
	cvWarpPerspective(Img_old,img,&newM,CV_INTER_LINEAR+CV_WARP_FILL_OUTLIERS, cvScalarAll(0) );
	cvSetImageCOI(img,1);//Bɫ
	cvCopy(img,img0);  //��ȡBɫ
	cvSetImageCOI(img,0);//�ָ�
	cvReleaseImage(&Img_old);
	return 0;
}
/*************************************************
����:  ͼ��OTSU��ֵ�����������ֵ
����:    ͼ������Ŀ���Ǻڰ�ͼ����Ҫ���ú���ķ������ж�ֵ��
����˵��:    
frame�� ��Ҫ����ĵ�ͨ���Ҷ�ͼ�� 
����ֵ:      ��ֵ�ָ��
*************************************************/
int RecDect::otsu(const IplImage *frame) 
{
	//frame�Ҷȼ�
	int pixelCount[GrayScale]={0};
	float pixelPro[GrayScale]={0};
	int width=frame->width;
	int height=frame->height;
	int i, j, pixelSum = width * height, threshold = 0;
	uchar* data = (uchar*)frame->imageData;
	float w0, w1, u0tmp, u1tmp, u0, u1, deltaTmp, deltaMax = 0;
	//ͳ��ÿ���Ҷȼ������صĸ���
	for(i = 0; i < height; i++)
	{
		for(j = 0;j < width;j++)
		{
			pixelCount[(int)data[i * width + j]]++;
		}
	}

	//����ÿ���Ҷȼ���������Ŀռ����ͼ��ı���
	for(i = 0; i < GrayScale; i++)
	{
		pixelPro[i] = (float)pixelCount[i] / pixelSum;
	}

	//�����Ҷȼ�[0,255],Ѱ�Һ��ʵ�threshold

	for(i = 0; i < GrayScale; i++)
	{
		w0 = w1 = u0tmp = u1tmp = u0 = u1 = deltaTmp = 0;
		for(j = 0; j < GrayScale; j++)
		{
			if(j <= i)   //��������
			{
				w0 += pixelPro[j];
				u0tmp += j * pixelPro[j];
			}
			else   //ǰ������
			{
				w1 += pixelPro[j];
				u1tmp += j * pixelPro[j];
			}
		}
		u0 = u0tmp / w0;
		u1 = u1tmp / w1;
		deltaTmp = (float)(w0 *w1* pow((u0 - u1), 2)) ;
		if(deltaTmp > deltaMax)
		{
			deltaMax = deltaTmp;
			threshold = i;
		}
	}
	return threshold;
}

/*************************************************
����: ����ı��νǶ�
����:    ����������ͼ��һ���Ǿ��Σ���Ҫ���ù����ų�
����˵��:    
pt1��  pt2��pt0����⵽��ͼ���������������
����ֵ:   ����֮��ļнǵ�����
*************************************************/
double RecDect::angle( CvPoint* pt1, CvPoint* pt2, CvPoint* pt0 )
{
	double dx1 = pt1->x - pt0->x;
	double dy1 = pt1->y - pt0->y;
	double dx2 = pt2->x - pt0->x;
	double dy2 = pt2->y - pt0->y;
	return (dx1*dx2 + dy1*dy2)/sqrt((dx1*dx1 + dy1*dy1)*(dx2*dx2 + dy2*dy2) + 1e-10);
}

/*************************************************
����: ����һϵ�м�⵽���ı���(��ѡλ��̽��ͼ��)
����:    ԭʼͼ����������������ͼ���ı���
����˵��:    
img��ԭʼ��ɫͨ��ͼ��

����ֵ:   һϵ���ı��ζ�������
*************************************************/

CvSeq* RecDect::findSquares4()
{

	IplImage *img2=cvCreateImage(cvGetSize(img0),img0->depth,img0->nChannels);//�Ҷ�
	cvCopy(img0,img2); 
		
	float length=sqrt((float)(pt[0].y-pt[1].y)*(pt[0].y-pt[1].y)+(pt[0].x-pt[1].x)*(pt[0].x-pt[1].x));
	cvAdaptiveThreshold(img2,img2,255,CV_ADAPTIVE_THRESH_GAUSSIAN_C,CV_THRESH_BINARY_INV,101,-1);
	//cvShowImage("2",img2);
	cvCanny(img2,img2,50,150,3); 
	cvSmooth(img2,img2);

		//cvShowImage("3",img2);
	cvAdaptiveThreshold(img2,img2,255,CV_ADAPTIVE_THRESH_GAUSSIAN_C,CV_THRESH_BINARY_INV,101,-1);

	CvMemStorage* storage = cvCreateMemStorage(0);
	CvSeq* contours;
	CvSeq* squares = cvCreateSeq( 0, sizeof(CvSeq), sizeof(CvPoint), storage);
	// ѡ��ͼ���������
	// find contours and store them all as a list
	cvFindContours( img2, storage, &contours, sizeof(CvContour),
		CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE, cvPoint(0,0) );
	//CvBox2D rect ;
	CvRect rect;
	CvPoint rect_pts[5], *pt1 = rect_pts;//��ʱ����ı��ε��ĸ�����,di 5ge fang zhouchang he mianji
	int npts = 4;
	while( contours )
	{

		//�ҳ�����������������С����
		//rect = cvMinAreaRect2(contours);
		rect=cvBoundingRect(contours);
		//��cvBoxPoints�ҳ����ε�4������
		//CvPoint2D32f rect_pts0[4];
		//cvBoxPoints(rect, rect_pts0);

		//��ΪcvPolyLineҪ��㼯������������CvPoint**
		//����Ҫ�� CvPoint2D32f �͵� rect_pts0 ת��Ϊ CvPoint �͵� rect_pts
		//������һ����Ӧ��ָ�� *pt1
		//for (int rp=0; rp<4; rp++)
		//rect_pts[rp]= cvPointFrom32f(rect_pts0[rp]);
		rect_pts[0].x=rect.x+rect.width;
		rect_pts[0].y=rect.y;
		rect_pts[1].x=rect.x;
		rect_pts[1].y=rect.y;
		rect_pts[2].x=rect.x;
		rect_pts[2].y=rect.y+rect.height;
		rect_pts[3].x=rect.x+rect.width;
		rect_pts[3].y=rect.y+rect.height;
		float edge1=sqrt((float)(pt1[1].x-pt1[0].x)*(pt1[1].x-pt1[0].x)+(float)(pt1[1].y-pt1[0].y)*(pt1[1].y-pt1[0].y));//�߳�
		float edge2=sqrt((float)(pt1[1].x-pt1[2].x)*(pt1[1].x-pt1[2].x)+(float)(pt1[1].y-pt1[2].y)*(pt1[1].y-pt1[2].y));//�߳�
		float area=edge1*edge2;
		if(area<length*length/9&&area>length*length/50&&fabs(edge1-edge2)<0.1*edge1){//���������߳�����������Ϊ������������
			////����Box
			int mianji=cvRound(cvContourArea(contours));
			int zhouchang=cvRound(cvContourPerimeter(contours));
			rect_pts[4].x=zhouchang;
			rect_pts[4].y=mianji;
			for( int i = 0; i < 5; i++ ){
				cvSeqPush( squares,(CvPoint*)&pt1[i]);
			}
			//������ʶ��������
			//	cvPolyLine(img, &pt1, &npts, 1, 1, CV_RGB(0,0,0), 2);
		}
		contours = contours->h_next;
	}		
	//cvShowImage("juxing",img);
	//cvWaitKey(0);
	cvReleaseImage(&img2);
	return squares;
}



/*************************************************
����: ����һϵ�е�ͼ��任����ȡQR����
����:    ԭʼͼ����������������ͼ���ı��Σ�Ҫ���Ǿ��Σ�
����˵��:    
img��ԭʼ3ͨ��ͼ��
����ֵ:   һϵ���ı���cvbox��ʽ
low:ʶ��QR���������������
high:ʶ��QR���������������
��ת�Ķ�ά����

typedef struct CvBox2D
{
CvPoint2D32f center;  ���ӵ����� 
CvSize2D32f  size;    ���ӵĳ��Ϳ� 
float angle;          ˮƽ�����һ���ߵļнǣ��û��ȱ�ʾ*
}
CvBox2D;
*************************************************/

void RecDect::RfindSquaresRect(float low,float high)
{
	IplImage *img2=cvCreateImage(cvGetSize(img0),img0->depth,img0->nChannels);//�Ҷ�
	cvCopy(img0,img2); 
	//IplImage *img2=cvCloneImage(img0);
	 IplImage * tempM = cvCreateImage(cvGetSize(img2), img2->depth,img2->nChannels);    
	cvAdaptiveThreshold(img2,img2,255,CV_ADAPTIVE_THRESH_GAUSSIAN_C,CV_THRESH_BINARY_INV,101,-5);
//	cvShowImage("��һ��erzhihua���ͼ��",img2);
	//cvSaveImage("��һ��erzhihua���ͼ��.bmp",img2);
	//cvCanny(img2,img2,50,150,3); 
	//cvShowImage("��һ��cvCanny���ͼ��",img2);
	//cvDilate(img2, img2, 0, 8);
	//cvErode( img2, img2, 0, 8);
	cvMorphologyEx(img2,img2,tempM,NULL,CV_MOP_OPEN,9);
	//cvShowImage("��һ��kai���ͼ��",img2);
	//cvSaveImage("��һ��kai���ͼ��.bmp",img2);
	cvCanny(img2,img2,50,150,3); 
	//cvShowImage("cvCanny���ͼ��",img2);
	//cvSaveImage("��һ��cvCanny���ͼ��.bmp",img2);
	cvSmooth(img2,img2);
	//cvShowImage("��1��cvSmooth���ͼ��",img2);
	//cvSaveImage("��һ��cvSmooth���ͼ��.bmp",img2);
	cvAdaptiveThreshold(img2,img2,255,CV_ADAPTIVE_THRESH_GAUSSIAN_C,CV_THRESH_BINARY_INV,101,-3);
	//cvShowImage("��2��erzhihua���ͼ��",img2);
	//cvSaveImage("��2��erzhihua���ͼ��.bmp",img2);
	IplImage *img3=cvCreateImage(cvGetSize(img2),img2->depth,img2->nChannels);//�Ҷ�
	cvCopy(img2,img3); 
	//IplImage *img3=cvCloneImage(img2);

	CvMemStorage* storage = cvCreateMemStorage(0);
	CvSeq* contours;

	// ѡ��ͼ���������
	// find contours and store them all as a list
	cvFindContours( img2, storage, &contours, sizeof(CvContour),
		CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE, cvPoint(0,0) );
	CvBox2D rect ;
	memset(pt,0,sizeof(CvPoint)*4);
	CvPoint rect_pts[4], *pt1 = rect_pts;//��ʱ����ı��ε��ĸ�����

	int flag=1;
	int npts = 4;
	float area2,edge3,edge4;//����������߳�
	vector<CvPoint> temp;
	while( contours )
	{
		double mianji=cvContourArea(contours);
		if(mianji<high*img2->width*img2->width&&mianji>low*img2->width*img2->width)
		{
		// test each contour
		//�ҳ�����������������С����
		rect = cvMinAreaRect2(contours);
		//��cvBoxPoints�ҳ����ε�4������
		CvPoint2D32f rect_pts0[4];
		cvBoxPoints(rect, rect_pts0);
		//��ΪcvPolyLineҪ��㼯������������CvPoint**
		//����Ҫ�� CvPoint2D32f �͵� rect_pts0 ת��Ϊ CvPoint �͵� rect_pts
		//������һ����Ӧ��ָ�� *pt1
		for (int rp=0; rp<4; rp++)
			rect_pts[rp]= cvPointFrom32f(rect_pts0[rp]);
		float edge1=sqrt((float)(pt1[1].x-pt1[0].x)*(pt1[1].x-pt1[0].x)+(float)(pt1[1].y-pt1[0].y)*(pt1[1].y-pt1[0].y));//�߳�
		float edge2=sqrt((float)(pt1[1].x-pt1[2].x)*(pt1[1].x-pt1[2].x)+(float)(pt1[1].y-pt1[2].y)*(pt1[1].y-pt1[2].y));//�߳�
		float area=edge1*edge2;
		if(fabs(edge1-edge2)<0.2*edge1&&area<high*img2->width*img2->width&&area>low*img2->width*img2->width){//���������߳�����������Ϊ������������
			//����Box
			temp.push_back(pt1[0]);
			temp.push_back(pt1[1]);
			temp.push_back(pt1[2]);
			temp.push_back(pt1[3]);

			if(flag==1){//�õ�һ����������������һ����Ϊ��
				pt[0]=pt1[0];	
				pt[1]=pt1[1];
				pt[2]=pt1[2];
				pt[3]=pt1[3];
				flag++;
				//	cout<<contours->total<<endl;
			}else{
				edge3=sqrt((float)(pt[1].x-pt[0].x)*(pt[1].x-pt[0].x)+(float)(pt[1].y-pt[0].y)*(pt[1].y-pt[0].y));//�߳�
				edge4=sqrt((float)(pt[1].x-pt[2].x)*(pt[1].x-pt[2].x)+(float)(pt[1].y-pt[2].y)*(pt[1].y-pt[2].y));//�߳�
				//yihui�������˭Сѡ˭
				area2=edge3*edge4;
				if (area2<=area)
				{
					//cout<<contours->total<<endl;
					pt[0]=pt1[0];	
					pt[1]=pt1[1];
					pt[2]=pt1[2];
					pt[3]=pt1[3];
					cvPolyLine(img3, &pt1, &npts, 1, 1, CV_RGB(0,0,0), 2);
				}
			}


		}

		}	
		//������һ������
		contours = contours->h_next;
	}		
	if(pt[0].x==0){
		cout<<"û���ѵ���������"<<endl;

	}
	//����Ѱ��������
	for (int i=0;i<temp.size();i+=4)
	{
		float d1=sqrt((float)(temp.at(i).x-pt[0].x)*(temp.at(i).x-pt[0].x)+(float)(temp.at(i).y-pt[0].y)*(temp.at(i).y-pt[0].y));
		float d2=sqrt((float)(temp[i+1].x-pt[1].x)*(temp[i+1].x-pt[1].x)+(float)(temp[i+1].y-pt[1].y)*(temp[i+1].y-pt[1].y));
		float d3=sqrt((float)(temp[i+2].x-pt[2].x)*(temp[i+2].x-pt[2].x)+(float)(temp[i+2].y-pt[2].y)*(temp[i+2].y-pt[2].y));
		float d4=sqrt((float)(temp[i+3].x-pt[3].x)*(temp[i+3].x-pt[3].x)+(float)(temp[i+3].y-pt[3].y)*(temp[i+3].y-pt[3].y));
		if((d1<10)&&(d2<10)&&(d3<10)&&(d4<10)&&d1!=0&&d2!=0&&d3!=0&&d4!=0)//���ڲ�
		{
			pt[0]=temp[i];	
			pt[1]=temp[i+1];
			pt[2]=temp[i+2];
			pt[3]=temp[i+3];

		}
	}

	vector<CvPoint>().swap(temp); //�ͷ�
	vertexOrder(pt);//��������
	//cvShowImage("��������",img3);
//	cvWaitKey(0);
	//cvSaveImage("buxianding��������.bmp",img3);
	cvReleaseMemStorage(&storage);
	cvReleaseImage(&img2);
	cvReleaseImage(&img3);
}

/*************************************************
����: ����һϵ�е�ͼ��任����ȡQR��������ȡ���ǲ�������ı���
����:    ԭʼͼ����������������ͼ���ı��Σ�Ҫ�����ı��Σ�
����˵��:    
img��ԭʼͼ��
����ֵ:   һϵ���ı�������
��ת�Ķ�ά����
�����鷢�֣����е�
*************************************************/
/*
CvSeq* RecDect::RfindSquaresP( IplImage* img )
{
CvSeq* squares = cvCreateSeq( 0, sizeof(CvSeq), sizeof(CvPoint), storage );
IplImage *img2=cvCloneImage(img);
IplImage *img3=cvCloneImage(img);
CvSeq* result;
double s, t;
cvAdaptiveThreshold(img2,img2,255,CV_ADAPTIVE_THRESH_GAUSSIAN_C,CV_THRESH_BINARY_INV,251,-11);

cvSmooth(img2,img2);
cvCanny(img2,img2,50,150,3); 
cvSmooth(img2,img2);
cvDilate(img2, img2, 0, 8);
cvErode( img2, img2, 0, 8);
//cvShowImage("��һ��cany���ͺ��ͼ��",img2);

cvSmooth(img2,img2);
cvCanny(img2,img2,50,150,3); 
cvSmooth(img2,img2);
cvAdaptiveThreshold(img2,img2,255,CV_ADAPTIVE_THRESH_GAUSSIAN_C,CV_THRESH_BINARY_INV,501,-11);
cvCopy(img2,img3);
int thresh=800;
storage = cvCreateMemStorage(0);
CvSeq* contours;
//CvSeq* squares = cvCreateSeq( 0, sizeof(CvSeq), sizeof(CvPoint), storage );
// ѡ��ͼ���������
// find contours and store them all as a list
cvFindContours( img2, storage, &contours, sizeof(CvContour),
CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE, cvPoint(0,0) );
//CvBox2D rect ;
memset(pt,0,sizeof(CvPoint)*4);
CvPoint rect_pts[4];//��ʱ����ı��ε��ĸ�����
int flag=1;
int npts = 4;
CvPoint *pt1 =rect_pts;
while( contours )
{
// test each contour
//�ҳ�����������������С����
result = cvApproxPoly( contours, sizeof(CvContour), storage,
CV_POLY_APPROX_DP, cvContourPerimeter(contours)*0.02, 0 );
// ����Ҫ���ĸ���
// �ܳ���100��850
//����Ƿ���͹��
//Ҳ��������������if( result->total == 4 &&
//	fabs(cvContourArea(result,CV_WHOLE_SEQ)) > 1000 &&
//	cvCheckContourConvexity(result) )
if( result->total == 4 &&
fabs(cvContourArea(result,CV_WHOLE_SEQ)) <0.81*img2->width*img2->width&&
cvCheckContourConvexity(result) ){
//����Box
s = 0;

for( int i = 0; i < 5; i++ )
{
// find minimum angle between joint
// edges (maximum of cosine)
if( i >= 2 )
{
t = fabs(angle(
(CvPoint*)cvGetSeqElem( result, i ),
(CvPoint*)cvGetSeqElem( result, i-2 ),
(CvPoint*)cvGetSeqElem( result, i-1 )));
s = s > t ? s : t;
}
}

// �Ƕ������������ڣ�������Ƕ���arccos0.3��90��֮��
if( s < 0.3 )
for(int i = 0; i < 4; i++ )	{
CvPoint	*pt2=(CvPoint *)cvGetSeqElem( result, i );
rect_pts[i]=*pt2;
cvSeqPush( squares,
(CvPoint*)cvGetSeqElem( result, i ));

}
cvPolyLine(img3, &pt1, &npts, 1, 1, CV_RGB(0,0,0), 2);      
}


//������һ������
contours = contours->h_next;
}		
//cvShowImage("SS",img3);
cvReleaseImage(&img2);
cvReleaseImage(&img3);
return squares;
}*/
/*************************************************
����: ��ȡ������������������ʹ֮�ﵽҪ��
��������ת���������������
ʹ֮��pt��i������
2 3
1 0
���
1  0
2  3
*************************************************/
void RecDect::vertexOrder(CvPoint pt2[])//��������,�����������Ķ��㣬ͼ��λ��Ķ���
{
	CvPoint pt1[4];
	for (int i=0;i<4;i++)//��ֵ
	{
		pt1[i]=pt2[i];
	}
	float maxd=0,mind=9999;
	for(int i=0;i<4;i++){//��һ��ѡ�������С��

		float distance=sqrt((float)pt1[i].x*pt1[i].x+pt1[i].y*pt1[i].y);//��ԭ��ľ���
		if (maxd<distance)
		{
			maxd=distance;
			pt2[3]=pt1[i];
		}
		if (mind>distance)
		{
			mind=distance;
			pt2[1]=pt1[i];
		}

	}
	int xl=0,xs=9999;//ͨ��x���ж�
	for(int i=0;i<4;i++){//��2��ѡ����������
		if((pt1[i].x==pt2[3].x&&pt1[i].y==pt2[3].y)||(pt1[i].x==pt2[1].x&&pt1[i].y==pt2[1].y)){
		}else{
			if(xl<pt1[i].x){
				xl=pt1[i].x;
				pt2[0]=pt1[i];
			}
			if(xs>pt1[i].x){
				xs=pt1[i].x;
				pt2[2]=pt1[i];
			}
		}
	}

}
/*************************************************
����:���λ��̽��ͼ��
����:    ��λ��̽��ͼ�������ԭʼͼ��֮��
����˵��:    
img��ԭʼͼ��
*************************************************/
void RecDect::drawSquares()
{
	
	IplImage *img1=cvCloneImage(img0);

	cvRectangle(img1,corner1[1],corner1[3],cvScalar(0,0,255),2);
	cvRectangle(img1,corner2[1],corner2[3],cvScalar(0,0,255),2);
	cvRectangle(img1,corner3[1],corner3[3],cvScalar(0,0,255),2);
	cvRectangle(img1,corner4[1],corner4[3],cvScalar(0,0,255),2);
	//cvShowImage("����λ��̽��ͼ��", img1);
	cvReleaseImage(&img1);
}
// 
/*************************************************
����: ��ȡ��ѡ��λ��̽��ͼ�Σ�������汾�ź���������
����:  ������Сλ��̽��ͼ�Σ�ʶ��汾����������
����˵��:    
img��ԭͼ��
squares���Ѿ���������λ��̽��ͼ������
*************************************************/
int RecDect::recognVersion(CvSeq* squares)
{
	CvSeqReader reader;
	//�����ǻ�ͼר�ó���
	IplImage *img1=cvCloneImage(img0);
	cvAdaptiveThreshold(img1,img1,255,CV_ADAPTIVE_THRESH_GAUSSIAN_C,CV_THRESH_BINARY_INV,101,-7);

	// ��ʼ��ȡ���������涨�㼯
	cvStartReadSeq( squares, &reader, 0 );
	CvPoint temp[5];//��5���Ǵ�Ŷ�Ӧ�����ܳ���x���������y��
	int rotateangle=0;
	bool tag1=false;//���Ͻ�ռ�ñ�־λ����Ӧcorner1[4]
	bool tag2=false;//���Ͻ�ռ�ñ�־λ����Ӧcorner2[4]
	bool tag3=false;//���½�ռ�ñ�־λ����Ӧcorner3[4]
	bool tag4=false;//���½�ռ�ñ�־λ����Ӧcorner4[4]
	int count1=0,count2=0,count3=0,count4=0;//�ķֿ���ͼ������
	CvPoint centerl,centerr;//λ��̽��ͼ����������
	for(int i = 0; i < squares->total; i += 5 )//��5���Ǵ�ŵĶ�Ӧ�����ܳ���x���������y��
	{
		//CvPoint* rect = pt;
		int count = 4;
		// read 4 vertices
		memcpy( temp, reader.ptr, squares->elem_size );
		CV_NEXT_SEQ_ELEM( squares->elem_size, reader );
		memcpy( temp + 1, reader.ptr, squares->elem_size );
		CV_NEXT_SEQ_ELEM( squares->elem_size, reader );
		memcpy( temp + 2, reader.ptr, squares->elem_size );
		CV_NEXT_SEQ_ELEM( squares->elem_size, reader );
		memcpy( temp + 3, reader.ptr, squares->elem_size );
		CV_NEXT_SEQ_ELEM( squares->elem_size, reader );
		//ǰ���Ƕ��㣬�����������ܳ����
		memcpy( temp + 4, reader.ptr, squares->elem_size );
		CV_NEXT_SEQ_ELEM( squares->elem_size, reader );
		int numbercount=(i/5)+1;
		cout<<"һ������������"<<squares->total/4<<",�����ڸ�ͼƬ�������ĵ� "<<numbercount<<" �����Σ����ڼ������λ�ã�"<<endl;

		//�����ǻ�ͼר��
	cvRectangle(img1,corner1[1],corner1[3],cvScalar(0,0,255),2);
	cvRectangle(img1,corner2[1],corner2[3],cvScalar(0,0,255),2);
	cvRectangle(img1,corner3[1],corner3[3],cvScalar(0,0,255),2);
	cvRectangle(img1,corner4[1],corner4[3],cvScalar(0,0,255),2);
		//�������������
		//float edge1=sqrt((float)(temp[1].x-temp[0].x)*(temp[1].x-temp[0].x)+(float)(temp[1].y-temp[0].y)*(temp[1].y-temp[0].y));//�߳�1
		//float edge2=sqrt((float)(temp[2].x-temp[1].x)*(temp[2].x-temp[1].x)+(float)(temp[2].y-temp[1].y)*(temp[2].y-temp[1].y));//�߳�2
		//float areanew=edge1*edge2;
		CvPoint center;
		center.x=(temp[0].x+temp[2].x)/2;
		center.y=(temp[0].y+temp[2].y)/2;
		float dist=0;
		if(maxPoint(temp[0].x,temp[1].x,temp[2].x,temp[3].x)<0.5*img->width&&maxPoint(temp[0].y,temp[1].y,temp[2].y,temp[3].y)<0.5*img->height)//���Ͻ�
		{

			count1++;
			dist=sqrt((float)(center.x)*(center.x)+(float)(center.y)*(center.y));//�������ϽǾ���
			if (count1==1)
			{//��һ��ռ��
				for ( int index = 0; index < 4; index++ )
					corner1[ index ] =temp[ index ];
				corner1P=temp[4];//�����������ܳ������
			}else{//�ڶ���ռ��
				//float edge3=sqrt((float)(corner1[1].x-corner1[0].x)*(corner1[1].x-corner1[0].x)+(float)(corner1[1].y-corner1[0].y)*(corner1[1].y-corner1[0].y));//�߳�1
				//float edge4=sqrt((float)(corner1[2].x-corner1[1].x)*(corner1[2].x-corner1[1].x)+(float)(corner1[2].y-corner1[1].y)*(corner1[2].y-corner1[1].y));//�߳�2
				//float areaold=edge3*edge4;//���������ε����

				if ((corner1P.y>temp[4].y&&dist<img->width/4)||fabs((float)corner1[1].x-pt[1].x)>0.12*img->width||fabs((float)corner1[1].y-pt[1].y)>0.12*img->width)//�������������ԭ����С�����滻��
				{
					for ( int index = 0; index < 4; index++ )
						corner1[ index ] =temp[ index ];
						corner1P=temp[4];//�����������ܳ������
				}
			}


		}
		if(minPoint(temp[0].x,temp[1].x,temp[2].x,temp[3].x)>0.5*img->width&&maxPoint(temp[0].y,temp[1].y,temp[2].y,temp[3].y)<0.5*img->height)//���Ͻ�
		{
			count2++;
			dist=sqrt((float)(img->width-1-center.x)*(img->width-1-center.x)+(float)(center.y)*(center.y));//����you�ϽǾ���
			if (count2==1)
			{//��һ��ռ��
				for ( int index = 0; index < 4; index++ )
					corner2[ index ] =temp[ index ];
					corner2P=temp[4];//�����������ܳ������
			}else{//�ڶ���ռ��
				//float edge3=sqrt((float)(corner2[1].x-corner2[0].x)*(corner2[1].x-corner2[0].x)+(float)(corner2[1].y-corner2[0].y)*(corner2[1].y-corner2[0].y));//�߳�1
				//float edge4=sqrt((float)(corner2[2].x-corner2[1].x)*(corner2[2].x-corner2[1].x)+(float)(corner2[2].y-corner2[1].y)*(corner2[2].y-corner2[1].y));//�߳�2
				//float areaold=edge3*edge4;//�����������
				if ((corner2P.y>temp[4].y&&dist<img->width/4)||fabs((float)-corner2[0].x+pt[0].x)>0.12*img->width||fabs((float)-corner2[0].y+pt[0].y)>0.12*img->width)//�������������ԭ����С�����滻��
				{
					for ( int index = 0; index < 4; index++ )
						corner2[ index ] =temp[ index ];
						corner2P=temp[4];//�����������ܳ������
				}
			}

		}

		if(maxPoint(temp[0].x,temp[1].x,temp[2].x,temp[3].x)<0.5*img->width&&minPoint(temp[0].y,temp[1].y,temp[2].y,temp[3].y)>0.5*img->height)//���½�
		{
			count3++;
			dist=sqrt((float)(center.x)*(center.x)+(float)(img->height-1-center.y)*(img->height-1-center.y));//�������¾���
			if (count3==1)
			{//��һ��ռ��
				for ( int index = 0; index < 4; index++ )
					corner3[ index ] =temp[ index ];
					corner3P=temp[4];//�����������ܳ������
			}else{//�ڶ���ռ��
				//float edge3=sqrt((float)(corner3[1].x-corner3[0].x)*(corner3[1].x-corner3[0].x)+(float)(corner3[1].y-corner3[0].y)*(corner3[1].y-corner3[0].y));//�߳�1
				//float edge4=sqrt((float)(corner3[2].x-corner3[1].x)*(corner3[2].x-corner3[1].x)+(float)(corner3[2].y-corner3[1].y)*(corner3[2].y-corner3[1].y));//�߳�2
			//	float areaold=edge3*edge4;//�����������
				if ((corner3P.y>temp[4].y&&dist<img->width/4)||fabs((float)corner3[2].x-pt[2].x)>0.12*img->width||fabs((float)-corner3[2].y+pt[2].y)>0.12*img->width)//�������������ԭ����С�����滻��
				{
					for ( int index = 0; index < 4; index++ )
						corner3[ index ] =temp[ index ];
						corner3P=temp[4];//�����������ܳ������
				}
			}

		}
		if(minPoint(temp[0].x,temp[1].x,temp[2].x,temp[3].x)>0.5*img->width&&minPoint(temp[0].y,temp[1].y,temp[2].y,temp[3].y)>0.5*img->height)//���½�
		{
			count4++;
			dist=sqrt((float)(img->width-1-center.x)*(img->width-1-center.x)+(float)(img->height-1-center.y)*(img->height-1-center.y));//����you�¾���
			if (count4==1)
			{//��һ��ռ��
				for ( int index = 0; index < 4; index++ )
					corner4[ index ] =temp[ index ];
					corner4P=temp[4];//�����������ܳ������
			}else{//�ڶ���ռ��
				//float edge3=sqrt((float)(corner4[1].x-corner4[0].x)*(corner4[1].x-corner4[0].x)+(float)(corner4[1].y-corner4[0].y)*(corner3[1].y-corner4[0].y));//�߳�1
				//float edge4=sqrt((float)(corner4[2].x-corner4[1].x)*(corner4[2].x-corner4[1].x)+(float)(corner4[2].y-corner4[1].y)*(corner3[2].y-corner4[1].y));//�߳�2
				//float areaold=edge3*edge4;//�����������
				if ((corner4P.y>temp[4].y&&dist<img->width/4)||fabs((float)-corner4[3].x+pt[3].x)>0.12*img->width||fabs((float)-corner4[3].y+pt[3].y)>0.12*img->width)//�������������ԭ����С�����滻��
					//if (areaold>areanew&&dist<img->width/4)//�������������ԭ����С�����滻��
				{
					for ( int index = 0; index < 4; index++ )
						corner4[ index ] =temp[ index ];
						corner4P=temp[4];//�����������ܳ������
				}
			}

		}

	}
	//�����ǻ�ͼר��
	//cvShowImage("test",img1);
	int t[4];
	t[0]=count1;
	t[1]=count2;
	t[2]=count3;
	t[3]=count4;
	int tempcount=t[0];
	for(int i=0;i<4;i++){
		if(tempcount>t[i])tempcount=t[i];//ѡ�����ٵ�
	}
	if (tempcount!=count1)//����������ͼ��
	{
		tag1=true;
	}
	if (tempcount!=count2)//����������ͼ��
	{
		tag2=true;
	}
	if (tempcount!=count3)//����������ͼ��
	{
		tag3=true;
	}
	if (tempcount!=count4)//����������ͼ��
	{
		tag4=true;
	}
	//4 vertices�ṹ��
	//P2***P1
	//*     *
	//P3***P4
	//ȷ�����ĸ��Ƕ�֮����Ҫ��ÿһ��ͼ�ν��н�������У������ʶ��
	vertexOrder(corner1);
	vertexOrder(corner2);
	vertexOrder(corner3);
	vertexOrder(corner4);
	float width=sqrt((float)(pt[1].x-pt[0].x)*(pt[1].x-pt[0].x)+(pt[1].y-pt[0].y)*(pt[1].y-pt[0].y));//QRͼ����

	//����̽��ͼ�εĿ�ȣ�WUL��WUR

	if (!tag4&&tag1&&tag2&&tag3)
	{
		//P*****P
		//*     *
		//P******
		//��յ��ĸ���
		for (int i=0;i<4;i++)
		{
			corner4[i].x=0;
			corner4[i].y=0;
		}
		centerl=cvPoint((corner1[1].x+corner1[3].x)/2,(corner1[1].y+corner1[3].y)/2);
		centerr=cvPoint((corner2[1].x+corner2[3].x)/2,(corner2[1].y+corner2[3].y)/2);
		if(width==0){//˵����������δ����
			cout<<"�����������ʱ����"<<endl;
			width=sqrt((float)(centerl.x-centerr.x)*(centerl.x-centerr.x)+(centerl.y-centerr.y)*(centerl.y-centerr.y))+7.0*sqrt((float)(corner1[1].x-corner1[0].x)*(corner1[1].x-corner1[0].x)+(corner1[1].y-corner1[0].y)*(corner1[1].y-corner1[0].y))/3;
		}
		//WUL=sqrt((float)(corner1[0].x-corner1[1].x)*(corner1[0].x-corner1[1].x)+(corner1[0].y-corner1[1].y)*(corner1[0].y-corner1[1].y));
		//WUR=sqrt((float)(corner2[0].x-corner2[1].x)*(corner2[0].x-corner2[1].x)+(corner2[0].y-corner2[1].y)*(corner2[0].y-corner2[1].y));
		WUL=sqrt((float)corner1P.y);
		WUR=sqrt((float)corner2P.y);
	}
	else if (!tag3&&tag1&&tag2&&tag4)
	{
		//P*****P
		//*     *
		//******P
		for (int i=0;i<4;i++)
		{
			corner3[i].x=0;
			corner3[i].y=0;
		}
		if(width==0){//˵����������δ����
			cout<<"�����������ʱ����"<<endl;
			width=sqrt((float)(corner2[0].x-corner4[3].x)*(corner2[0].x-corner4[3].x)+(corner2[0].y-corner4[3].y)*(corner2[0].y-corner4[3].y))+4.0/3*sqrt((float)(corner1[1].x-corner1[0].x)*(corner1[1].x-corner1[0].x)+(corner1[1].y-corner1[0].y)*(corner1[1].y-corner1[0].y));
		};

		centerl=cvPoint((corner2[0].x+corner2[2].x)/2,(corner2[0].y+corner2[2].y)/2);
		centerr=cvPoint((corner4[0].x+corner4[2].x)/2,(corner4[0].y+corner4[2].y)/2);
		//WUL=sqrt((float)(corner2[3].x-corner2[0].x)*(corner2[3].x-corner2[0].x)+(corner2[3].y-corner2[0].y)*(corner2[3].y-corner2[0].y));
		//WUR=sqrt((float)(corner4[3].x-corner4[0].x)*(corner4[3].x-corner4[0].x)+(corner4[3].y-corner4[0].y)*(corner4[3].y-corner4[0].y));
		WUL=sqrt((float)corner2P.y);
		WUR=sqrt((float)corner4P.y);
		rotateangle=90;
	}
	else	if (!tag2&&tag1&&tag4&&tag3)
	{
		//P******
		//*     *
		//P*****P
		for (int i=0;i<4;i++)
		{
			corner2[i].x=0;
			corner2[i].y=0;
		}
		if(width==0){//˵����������δ����
			cout<<"�����������ʱ����"<<endl;
			width=sqrt((float)(corner3[2].x-corner1[1].x)*(corner3[2].x-corner1[1].x)+(corner3[2].y-corner1[1].y)*(corner3[2].y-corner1[1].y))+4.0/3*sqrt((float)(corner1[1].x-corner1[0].x)*(corner1[1].x-corner1[0].x)+(corner1[1].y-corner1[0].y)*(corner1[1].y-corner1[0].y));
			//};
		}
		centerl=cvPoint((corner3[0].x+corner3[2].x)/2,(corner3[0].y+corner3[2].y)/2);
		centerr=cvPoint((corner1[0].x+corner1[2].x)/2,(corner1[0].y+corner1[2].y)/2);
		//WUL=sqrt((float)(corner3[2].x-corner3[1].x)*(corner3[2].x-corner3[1].x)+(corner3[2].y-corner3[1].y)*(corner3[2].y-corner3[1].y));
		//WUR=sqrt((float)(corner1[2].x-corner1[1].x)*(corner1[2].x-corner1[1].x)+(corner1[2].y-corner1[1].y)*(corner1[2].y-corner1[1].y));
		WUL=sqrt((float)corner3P.y);
		WUR=sqrt((float)corner1P.y);
		rotateangle=270;
	}
	else if (!tag1&&tag3&&tag2&&tag4)
	{
		//******P
		//*     *
		//P*****P
		for (int i=0;i<4;i++)
		{
			corner1[i].x=0;
			corner1[i].y=0;
		}
		if(width==0){//˵����������δ����
			cout<<"�����������ʱ����"<<endl;
			width=sqrt((float)(corner4[3].x-corner3[2].x)*(corner4[3].x-corner3[2].x)+(corner4[3].y-corner3[2].y)*(corner4[3].y-corner3[2].y))+4.0/3*sqrt((float)(corner2[1].x-corner2[0].x)*(corner2[1].x-corner2[0].x)+(corner2[1].y-corner2[0].y)*(corner2[1].y-corner2[0].y));
		};
		//}
		centerl=cvPoint((corner4[1].x+corner4[3].x)/2,(corner4[1].y+corner4[3].y)/2);
		centerr=cvPoint((corner3[1].x+corner3[3].x)/2,(corner3[1].y+corner3[3].y)/2);
		//WUL=sqrt((float)(corner4[3].x-corner4[2].x)*(corner4[3].x-corner4[2].x)+(corner4[3].y-corner4[2].y)*(corner4[3].y-corner4[2].y));
		//WUR=sqrt((float)(corner3[3].x-corner3[2].x)*(corner3[3].x-corner3[2].x)+(corner3[3].y-corner3[2].y)*(corner3[3].y-corner3[2].y));
		WUL=sqrt((float)corner4P.y);
		WUR=sqrt((float)corner3P.y);
		rotateangle=180;
	}else{
		cout<<"ʶ��̽��ͼ�γ�����ɸѡ��̽��ͼ�ο��������������߲�ֻ3�������顣������Ĭ�ϰ汾��ʽ���汾1��"<<endl;
	}
	//���Ըı��ˣ���Χλ��̽��ͼ�� ���ڲ�����1:1:3:1:1,�޸�WUL��WUR
	WUL=7.0*WUL/3;
	WUR=7.0*WUR/3;
	//�õ�������Ϣ��Ϳ��Խ��а汾ȷ����	
	//����D�������Ͻ�λ��̽��ͼ�����������Ͻ�λ��̽��ͼ������֮��ľ��롣
	if (centerl.x!=0&&centerr.x!=0)
	{

		float d=sqrt((float)(centerl.x-centerr.x)*(centerl.x-centerr.x)+(centerl.y-centerr.y)*(centerl.y-centerr.y));
		//������ŵ�����ģ���ȳߴ�X
		ModeSize=(WUL+WUR)/14;
		//����ȷ�����ŵİ汾
		version =cvRound(((d/ModeSize)-10)/4);
		if (version<1)
		{
			version=1;
		}
		if(version<7){
			//7���¼�Ϊ���ǰ汾��
			switch(version){
			case 1:number=21;break;//�汾1
			case 2:number=25;break;//�汾2
			case 3:number=29;break;//�汾3
			case 4:number=33;break;//�汾4
			case 5:number=37;break;//�汾5
			case 6:number=41;break;//�汾6
			}
			//�������ȷ���ķ��Ű汾���ڻ�С��s����ô�ü���ֵ��Ϊ�汾�š��������ȷ���ķ��Ű汾���ڻ����7����ô�汾��ϢӦ�����в�������:
		}else{//������BCH����ֱ�Ӹ��ݻ��ַ�Χ���о���
			//��7�����Ͻ�λ��̽��ͼ�εĿ�ȳߴ磬�õ�ģ��ߴ�
			float modsize=WUR/7;
			int count=cvRound(width/modsize);
			if(count>43&&count<47)//�汾7
			{
				version=7;
				number=45;

			}
			if(count>47&&count<51)//�汾8
			{
				version=8;
				number=49;

			}
			if(count>51&&count<55)//�汾9
			{
				version=9;
				number=53;

			}		 
			if(count>55&&count<59)//�汾10
			{
				version=10;
				number=57;

			}		
			if(count>59&&count<63)//�汾11
			{
				version=11;
				number=61;

			}		 
			if(count>63&&count<67)//�汾12
			{
				version=12;
				number=65;

			}		 
			if(count>67&&count<71)//�汾13
			{
				version=13;
				number=69;

			}		
			if(count>71&&count<75)//�汾14
			{
				version=14;
				number=73;

			}		 
			if(count>75&&count<79)//�汾15
			{
				version=15;
				number=77;

			}		
			if(count>79&&count<83)//�汾16
			{
				version=16;
				number=81;

			}		
			if(count>83&&count<87)//�汾17
			{
				version=17;
				number=85;

			}		
			if(count>87&&count<91)//�汾18
			{
				version=18;
				number=89;

			}		 
			if(count>91&&count<95)//�汾19
			{
				version=19;
				number=93;

			}		
			if(count>95&&count<99)//�汾20
			{
				version=20;
				number=97;

			}		
			if(count>99&&count<103)//�汾21
			{
				version=21;
				number=101;

			}	 
			if(count>103&&count<107)//�汾22
			{
				version=22;
				number=105;

			}
			if(count>107&&count<111)//�汾23
			{
				version=23;
				number=109;

			}	
			if(count>111&&count<115)//�汾24
			{
				version=24;
				number=113;

			}	
			if(count>115&&count<119)//�汾25
			{
				version=25;
				number=117;

			}	
			if(count>119&&count<123)//�汾26
			{
				version=26;
				number=121;

			}	
			if(count>123&&count<127)//�汾27
			{
				version=27;
				number=125;

			}	
			if(count>127&&count<131)//�汾28
			{
				version=28;
				number=129;

			}	
			if(count>131&&count<135)//�汾29
			{
				version=29;
				number=133;

			}	
			if(count>135&&count<139)//�汾30
			{
				version=30;
				number=137;

			}	
			if(count>139&&count<143)//�汾31
			{
				version=31;
				number=141;

			}	 
			if(count>143&&count<147)//�汾32
			{
				version=32;
				number=145;

			}	 
			if(count>147&&count<151)//�汾33
			{
				version=33;
				number=149;

			}	
			if(count>151&&count<155)//�汾34
			{
				version=34;
				number=153;

			}
			if(count>155&&count<159)//�汾35
			{
				version=35;
				number=157;

			}
			if(count>159&&count<163)//�汾36
			{
				version=36;
				number=161;

			}
			if(count>163&&count<167)//�汾37
			{
				version=37;
				number=165;

			}
			if(count>167&&count<171)//�汾38
			{
				version=38;
				number=169;

			}
			if(count>171&&count<175)//�汾39
			{
				version=39;
				number=173;

			}
			if(count>175&&count<179)//�汾40
			{
				version=40;
				number=177;

			}else{
				cout<<"ȷ��QR��汾ʱ����������������Ϊ"<<count<<endl;
			}
		}

	}
	cvReleaseMemStorage(&squares->storage);
	printf("��ͼ�ΰ汾�ţ�%d����������%d",version,number);
	return rotateangle;
}
/*************************************************
����: ���QR��ͼ����ε�������С��
����:  ���QR��ͼ����ε�������С��
����˵��:    
unsigned int a,unsigned int b,unsigned int c,unsigned int d�������ĸ�����x/y����
����ֵ����С��x/yֵ
*************************************************/
int RecDect::minPoint(unsigned int a,unsigned int b,unsigned int c,unsigned int d){
	unsigned int tem1=(b>a? a:b);
	unsigned int tem2=(c>d? d:c);
	return (tem1>tem2? tem2:tem1);
}
/*************************************************
����: ���QR��ͼ����ε���������
����:  ���QR��ͼ����ε���������
����˵��:    
unsigned int a,unsigned int b,unsigned int c,unsigned int d�������ĸ�����x/y����
����ֵ������x/yֵ
*************************************************/
int RecDect::maxPoint(unsigned int a,unsigned int b,unsigned int c,unsigned int d){
	unsigned int tem1=(b>a? b:a);
	unsigned int tem2=(c>d? c:d);
	return (tem1>tem2? tem1:tem2);
}
/*************************************************
����: ��ȡ��ȷQR����������������
����: ��ԭ��������������Ͻ��о�ϸ��ȡ
����˵��:    
�Ѿ���׽��һ����ŵĶ��㼯����Ҫ����ϸ����
������ֵ����T��x��=ÿ��/ÿ�лҶ�ֵΪ0������������maxP=max��T��x����
��i=1��ʼɨ�裬һֱ��i=30(ʵ��ƫ�벻���ܳ���30)(546/21=26,ѡ30)
��T(x)>1/2maxPʱ����Ϊ�Ѿ�ɨ�赽��
*************************************************/
void RecDect::GetAccVertex()
{
	IplImage *temp=cvCloneImage(img0);
	cvAdaptiveThreshold(img0,temp,255,CV_ADAPTIVE_THRESH_GAUSSIAN_C,CV_THRESH_BINARY_INV,101,-3);//��ֵ��

	int max=0;
	int depth=100;
	//����벿��
	for (int i=0;i<depth;i++)//Ѱ��max
	{
		uchar *ptr=(uchar *)(temp->imageData+i*temp->widthStep);
		int num=0;
		for(int j=0;j<temp->width/2;j++){
			if(ptr[temp->nChannels*j]==0)num++;
		}
		if (num>max)
		{
			max=num;
		}

	}
	//��ʼ����ɨ����
	for (int i=0;i<depth;i++)//
	{
		uchar *ptr=(uchar *)(temp->imageData+i*temp->widthStep);
		int num=0;
		for(int j=0;j<temp->width/2;j++){
			if(ptr[temp->nChannels*j]==0)num++;//ͳ��
		}
		if (num>max/3)
		{
			pt[1].y=i;
			//pt[0].y=i;
			break;
		}

	}
	//��ʼ����ɨ����
	for (int i=temp->height-1;i>=temp->height-1-depth;i--)
	{
		uchar *ptr=(uchar *)(temp->imageData+i*temp->widthStep);
		int num=0;
		for(int j=0;j<temp->width/2;j++){
			if(ptr[temp->nChannels*j]==0)num++;//ͳ��
		}
		if (num>max/3)
		{
			pt[2].y=i;
			//pt[3].y=i;
			break;
		}

	}
	//��ʼ����ɨ����
	for (int j=0;j<depth;j++)//
	{

		int num=0;
		for(int i=0;i<temp->height;i++){
			uchar ptr=(uchar )*(temp->imageData+i*temp->widthStep+j*temp->nChannels);
			if(ptr==0)num++;//ͳ��
		}
		if (num>max/3)
		{
			pt[1].x=j;
			pt[2].x=j;
			break;
		}

	}
	//�Ұ벿��
	//��you�벿��
	//��ʼ����ɨ����
	for (int i=0;i<depth;i++)//Ѱ��max
	{
		uchar *ptr=(uchar *)(temp->imageData+i*temp->widthStep);
		int num=0;
		for(int j=temp->width-1;j>temp->width/2;j--){
			if(ptr[temp->nChannels*j]==0)num++;
		}
		if (num>max)
		{
			max=num;
		}

	}
	for (int i=0;i<depth;i++)//
	{
		uchar *ptr=(uchar *)(temp->imageData+i*temp->widthStep);
		int num=0;
		for(int j=temp->width-1;j>temp->width/2;j--){
			if(ptr[temp->nChannels*j]==0)num++;//ͳ��
		}
		if (num>max/3)
		{
			pt[0].y=i;
			break;
		}

	}
	//��ʼ����ɨ����
	for (int i=temp->height-1;i>=temp->height-1-depth;i--)
	{
		uchar *ptr=(uchar *)(temp->imageData+i*temp->widthStep);
		int num=0;
		for(int j=temp->width-1;j>temp->width/2;j--){
			if(ptr[temp->nChannels*j]==0)num++;//ͳ��
		}
		if (num>max/3)
		{

			pt[3].y=i;
			break;
		}

	}


	//��ʼ����ɨ����
	for (int j=temp->width-1;j>=temp->width-depth;j--)//
	{

		int num=0;
		for(int i=0;i<temp->height;i++){
			uchar ptr=(uchar )*(temp->imageData+i*temp->widthStep+j*temp->nChannels);
			if(ptr==0)num++;//ͳ��
		}
		if (num>max/3)
		{
			pt[0].x=j;
			pt[3].x=j;
			break;
		}

	}
	cvReleaseImage(&temp);


}
/*************************************************
����: ���QR��ͼ����б�̶�
����:  ͨ��Hough�任��ȡ��б�ǣ���Ҫ֮ǰ���ж�ֵ����Ե����
����˵��:    
IplImage* img��Դͼ��
����ֵ��ͼ����б�Ƕ�
*************************************************/
double RecDect::AngleDect(const IplImage* img){
	IplImage *src =cvCloneImage(img); 
	IplImage* dst;
	IplImage* color_dst;
	CvMemStorage* storage = cvCreateMemStorage(0);
	CvSeq* lines = 0;
	int i;
	float theta ;//��ת�Ƕ�
	dst = cvCreateImage( cvGetSize(src), 8, 1 );
	color_dst = cvCreateImage( cvGetSize(src), 8, 3 );
	//cvShowImage("Դͼ��",img0);
	if( !src )
		return 0;
	cvAdaptiveThreshold(src,src,255,CV_ADAPTIVE_THRESH_GAUSSIAN_C,CV_THRESH_BINARY_INV,101,-11);
	cvCanny(src,src,50,150,3); 
	cvDilate(src, src, 0, 13);
	cvErode( src, src, 0, 13);
	cvCanny(src,src,50,150,3); 
	cvSmooth(src,src);
	cvCvtColor( src, color_dst, CV_GRAY2BGR );
	//cvShowImage( "Hough1", color_dst );
	lines = cvHoughLines2(src, storage, CV_HOUGH_STANDARD, 1, CV_PI/180, 50, 0, 0 );//��ͳ
	//cout << MIN(lines->total,100) << endl;
	for( i = 0; i < MIN(lines->total,1); i++ )//����һ��ֱ��
	{
		float* line = (float*)cvGetSeqElem(lines,i);
		float rho = line[0];
		theta = line[1];
		CvPoint pt1, pt2;
		double a = cos(theta), b = sin(theta);
		double x0 = a*rho, y0 = b*rho;
		pt1.x = cvRound(x0 + 1000*(-b));
		pt1.y = cvRound(y0 + 1000*(a));
		pt2.x = cvRound(x0 - 1000*(-b));
		pt2.y = cvRound(y0 - 1000*(a));
		cvLine( color_dst, pt1, pt2, CV_RGB(255,0,0), 1, CV_AA, 0 );
	}
	//cvNamedWindow( "Hough", 1 );
	//cvShowImage( "Hough", color_dst );
	return theta;
}
/*************************************************
����: ͼ����ת
����:  ���ö��β�ֵ������ͼ����ת
����˵��:    
Imgm��Դͼ��
alpha��ͼ����б�Ƕ�
*************************************************/
void RecDect::FitRotate (IplImage* Img_old, double angle)
{

	IplImage* src=cvCreateImage(cvGetSize(Img_old),Img_old->depth,Img_old->nChannels);
	cvCopy(Img_old,src);
	int  delta = 1;
	double factor;
	float m[6];
	// Matrix m looks like:
	//
	// [ m0  m1  m2 ] ===>  [ A11  A12   b1 ]
	// [ m3  m4  m5 ]       [ A21  A22   b2 ]
	// 
	CvMat M  = cvMat( 2, 3, CV_32F, m );


	int w = src->width;
	int h = src->height;
	factor = 1;

	m[0] = (float)(factor*cos(-angle*CV_PI/180.));
	m[1] = (float)(factor*sin(-angle*CV_PI/180.));
	m[3] = -m[1];
	m[4] = m[0];
	// ����ת��������ͼ���м�
	m[2] = w*0.5f;  
	m[5] = h*0.5f;  
	//  dst(x,y) = A * src(x,y) + b
	cvGetQuadrangleSubPix( src, Img_old,&M);
	cvReleaseImage(&src);

}
/*************************************************
����: ƽ������������
����:  ����QR�汾�Ż�������
����˵��:    
Imgm��Դͼ��

*************************************************/
void RecDect::drawGridaverage()//ͼ���һ��
{
	CvSize QRSize;
	QRSize.height=number*20;
	QRSize.width=number*20;
	IplImage *QRImage=cvCreateImage(QRSize,img0->depth,img0->nChannels);
	cvResize(img0, QRImage); //����Դͼ��Ŀ��ͼ��
	cvAdaptiveThreshold(QRImage,QRImage,255,CV_ADAPTIVE_THRESH_GAUSSIAN_C,CV_THRESH_BINARY_INV,101,0);//��ֵ��
	IplImage *img2=cvCloneImage(QRImage);
	int modeWidth=img2->width/number;//ģ����
	int modeHeight=img2->height/number;//ģ��߶�

	//��������鿴�����¿�ɾ��
	for (int y=0,j=0;j<=number;y=cvRound(modeHeight*j),j++)
	{
		//cout<<"��"<<j<<"�����"<<y<<endl;
		CvPoint pst,pend;
		pst=cvPoint(0,y);
		pend=cvPoint(img2->width-1,y);
		cvLine(img2,pst,pend,cvScalarAll(0));

	}
	for (int x=0,i=0;i<=number;x=cvRound(modeWidth*i),i++)
	{
		//cout<<"��"<<i<<"�����"<<x<<endl;
		CvPoint pst,pend;
		pst=cvPoint(x,0);
		pend=cvPoint(x,img2->height);
		cvLine(img2,pst,pend,cvScalarAll(0));
	}
	//cvShowImage("Grid1",img2);
	//��������鿴�����Ͽ�ɾ��

	cvCopy(QRImage,img2);
	for (int y=0,j=1;j<=number;y=cvRound(modeHeight*j),j++)
	{
		uchar *ptr=(uchar *)(img2->imageData+cvRound(y+0.5*modeHeight)*img2->widthStep);

		for (int x=0,i=1;i<=number;x=cvRound(modeWidth*i),i++)
		{

			//cout<<"��("<<x<<","<<y<<")�����"<<x<<endl;
			int centerval=ptr[img2->nChannels*cvRound(x+0.5*modeWidth)];
			CvRect cr=cvRect(x,y,modeWidth,modeHeight);
			cvSetImageROI(img2,cr);
			if(centerval>10){//��ɫ
				cvSet(img2,cvScalarAll(255));
			}else{
				cvZero(img2);
			}
			cvResetImageROI(img2);

		}
	}
	/*������Ҫ�ػ�����λ��̽��ͼ��(�����ܱ߰���)*/
	//���Ͻ�
	for (int y=0,j=1;j<=8;y=cvRound(modeHeight*j),j++)
	{

		for (int x=0,i=1;i<=8;x=cvRound(modeWidth*i),i++)
		{

			CvRect cr=cvRect(x,y,modeWidth,modeHeight);///* ���ε�����ǵ�x-����  */ /* ���ε����ϻ������½ǵ�y-���� */����ʵ����ô�����½�
			cvSetImageROI(img2,cr);
			if((i==1&&j!=8)||(j==1&&i!=8)||(i==7&&j!=8)||(j==7&&i!=8)||(i>2&&i<=5&&j>2&&j<=5)){
				cvZero(img2);
			}
			else{//��ɫ
				cvSet(img2,cvScalarAll(255));
			}
			cvResetImageROI(img2);
		}
	}
	//���Ͻ�
	for (int y=0,j=1;j<=8;y=cvRound(modeHeight*j),j++)
	{

		for (int x=img2->width-1,i=1;i<=9;x=img2->width-1-cvRound(modeWidth*i),i++)
		{

			CvRect cr=cvRect(x,y,modeWidth,modeHeight);///* ���ε�����ǵ�x-����  */ /* ���ε����ϻ������½ǵ�y-���� */����ʵ����ô�����½�
			cvSetImageROI(img2,cr);
			if((i<=2&&j!=8)||(j==1&&i!=9)||(i==8&&j!=8)||(j==7&&i!=9)||(i>=4&&i<=6&&j>=3&&j<6)){
				cvZero(img2);
			}
			else{//��ɫ
				cvSet(img2,cvScalarAll(255));
			}
			cvResetImageROI(img2);
		}
	}
	//���½�
	for (int y=img2->height-1,j=1;j<=9;y=img2->height-1-cvRound(modeHeight*j),j++)
	{

		for (int x=0,i=1;i<=8;x=cvRound(modeWidth*i),i++)
		{

			CvRect cr=cvRect(x,y,modeWidth,modeHeight);///* ���ε�����ǵ�x-����  */ /* ���ε����ϻ������½ǵ�y-���� */����ʵ����ô�����½�
			cvSetImageROI(img2,cr);
			if((i==1&&j!=9)||(j<=2&&i!=8)||(i==7&&j!=9)||(j==8&&i!=8)||(i>2&&i<=5&&j>3&&j<=6)){
				cvZero(img2);
			}
			else{//��ɫ
				cvSet(img2,cvScalarAll(255));
			}
			cvResetImageROI(img2);
		}
	}

	/*������Ҫ����߾�*/
	cvReleaseImage(&QRImage);
	QRImage=cvCreateImage(cvSize(img2->width+100,img2->height+100),img2->depth,img2->nChannels);
	cvSet(QRImage,cvScalarAll(255));
	CvRect content=cvRect(50,50,img2->width,img2->height);
	cvSetImageROI(QRImage,content);
	cvCopy(img2,QRImage);
	cvResetImageROI(QRImage);
	cvReleaseImage(&img2);
	//cvShowImage("Grid",QRImage);
	//cvSaveImage("result.bmp",QRImage);
	cvReleaseImage(&QRImage);
}

/*************************************************
����: ����������
����:  ����QR�汾�Ż�������
����˵��:    
Imgm��Դͼ��

*************************************************/
IplImage * RecDect::drawGrid()//ͼ���һ��
{
	//�ж�������λͼ���Ƿ���ȷʶ��
	if (ModeSize>0)
	{	

	}else{
		cout<<"ModeSizeΪ0����һ������ʧ��"<<endl;
		return NULL;
	}
	CvSize QRSize;
	int msize=10;//��ͼ��ģ���С
	QRSize.height=number*msize;//ÿ��ģ����10������
	QRSize.width=number*msize;
	IplImage *QRImage=cvCreateImage(QRSize,img0->depth,img0->nChannels);
	
	CvRect QRcontent=cvRect(pt[1].x,pt[1].y,pt[0].x-pt[1].x+10,pt[2].y-pt[1].y+10);
	cvSetImageROI(img0,QRcontent);
	IplImage *canyImage=cvCreateImage(cvSize(462,462),img0->depth,img0->nChannels);

	ModeSize=462/(number);
	//cvCopy(img0,canyImage);
	cvResize(img0, canyImage); //����Դͼ��Ŀ��ͼ��
	cvResetImageROI(img0);
	cvAdaptiveThreshold(canyImage,canyImage,255,CV_ADAPTIVE_THRESH_GAUSSIAN_C,CV_THRESH_BINARY_INV,101,0);//��ֵ��
	IplImage *smapleImg=cvCloneImage(canyImage);
	/*Soble(canyImage,canyImage);
	cvShowImage("1",canyImage);
	cvWaitKey(0);*/
	cvCanny(canyImage,canyImage,10,255);
 // cvShowImage("1",canyImage);
	int startx,starty;//��ʼɨ��λ��
	//����:���ϵ��£���������
	int i=0,j=0;
	while (GetNonZero(canyImage,i,0)<50&&i<canyImage->height)
	{
		i++;
	}
	starty=i;
	while (GetNonZero(canyImage,j,1)<40&&j<canyImage->width)
	{
		j++;
	}
	startx=j;
	//cvLine(canyImage,cvPoint(0,starty),cvPoint(canyImage->width-1,starty),cvScalar(255,0,0),3);
	//cvLine(canyImage,cvPoint(startx,0),cvPoint(startx,canyImage->height-1),cvScalar(255,0,0),3);
	vector<int>line;//�洢������Χ����
	vector<int>rows;//�洢��ֵ
	vector<int>cols;//�洢��ֵ
	rows.push_back(starty);//����ʼ�з���
	cols.push_back(startx);
	//�����¼�� 
	int modeHeight=(int)ModeSize;
	int range=3;//ȡ������Χ
	int count=0;//���߼���
	//hangɨ��
	for(int i=modeHeight+starty;count<number;i=rows[count+1]+modeHeight,count++){
		if (count==number-1)
		{
			range=6;//ȡ������Χ
		}
		for (int j=i-range/2;j<i+range;j++)
		{
			line.push_back(j);//����λ��
		}
		int t=i-range;//t��ʱ�������
		if (t>=canyImage->height)
		{
			t=canyImage->height-1;
		}else{
			for (int i=0;i<line.size();i++)
			{
				int temp=line[i];
				if (temp>=canyImage->height)
				{
					temp=canyImage->height-1;
				}
				if(GetNonZero(canyImage,t,0)<GetNonZero(canyImage,temp,0))
					t=line[i];
			}	}  
		line.clear();//ÿѭ��һ�Σ��ͷ�һ��
		rows.push_back(t);//�������ֵ

	}
	//lieɨ��
	line.clear();//
	int modeWidth=(int)ModeSize;
	count=0;
	for(int i=modeWidth+starty;count<number;i=cols[count+1]+modeWidth,count++){
		if (count==number-1)
		{
			range=6;//ȡ������Χ
		}
		for (int j=i-range/2;j<i+range;j++)
		{
			line.push_back(j);//����λ��
		}
		int t=i-range;
		if (t>=canyImage->width)
		{
			t=canyImage->width-1;
		}else{
			for (int i=0;i<line.size();i++)
			{int temp=line[i];
			if (temp>=canyImage->width)
			{
				temp=canyImage->width-1;
			}
			if(GetNonZero(canyImage,t,1)<GetNonZero(canyImage,temp,1))
				t=line[i];
			}	}  
		line.clear();//ÿѭ��һ�Σ��ͷ�һ��
		cols.push_back(t);//�������ֵ

	}
	//line.clear();//ÿѭ��һ�Σ��ͷ�һ��
	vector<int>().swap(line); //�ͷ�
	/*x��������и�Ч��*/
	IplImage *tst=cvCloneImage(smapleImg);
	for(int i=0;i<rows.size();i++)
	{
		int temp=rows[i];
		CvPoint pst,pend;
		pst=cvPoint(0,temp);
		pend=cvPoint(canyImage->width-1,temp);
		cvLine(tst,pst,pend,cvScalarAll(55));

	}
	for(int i=0;i<cols.size();i++)
	{
		int temp=cols[i];
		CvPoint pst,pend;
		pst=cvPoint(temp,0);
		pend=cvPoint(temp,canyImage->height-1);
		cvLine(tst,pst,pend,cvScalarAll(55));

	}

	//cvShowImage("1",smapleImg);
	cvReleaseImage(&canyImage);

	//uchar *ptr=(uchar *)(temp->imageData+i*temp->widthStep);
	for (int j=0;j<number;j++)	
	{
		for (int i=0;i<number;i++)
		{
			CvPoint center;
			center.y=(rows[j]+rows[j+1])/2;
			center.x=(cols[i]+cols[i+1])/2;
			uchar *cenptr=(uchar *)(smapleImg->imageData+center.y*smapleImg->widthStep+center.x);//�������ĵ�
			//uchar *cenptrlup=(uchar *)(smapleImg->imageData+(rows[j]+msize/4)*smapleImg->widthStep+cols[i]+msize/4);//�������ĵ�����
			//uchar *cenptrldo=(uchar *)(smapleImg->imageData+(rows[j+1]-msize/4)*smapleImg->widthStep+cols[i]+msize/4);//�������ĵ�����
			//uchar *cenptrrup=(uchar *)(smapleImg->imageData+(center.y-4)*smapleImg->widthStep+cols[i+1]-msize/4);//�������ĵ�����
			uchar *cenptrrdo=(uchar *)(smapleImg->imageData+(center.y+2)*smapleImg->widthStep+center.x+2);//�������ĵ�����
			for (int y=j*msize;y<(j+1)*msize;y++)
			{
				uchar *ptr=(uchar *)(QRImage->imageData+y*QRImage->widthStep);

				for (int x=i*msize;x<(i+1)*msize;x++)
				{
					ptr[x]=*cenptr;
					if (ptr[x]==0&&*cenptrrdo==255)
					{
						ptr[x]=255;
					}
				}
			}
			cvRectangle(tst,cvPoint(center.x-2,center.y-2),cvPoint(center.x+2,center.y+2),cvScalarAll(120),1);

		}
	}

	vector<int>().swap(cols); //�ͷ�
	vector<int>().swap(rows); //�ͷ�
	/*������Ҫ�ػ�����λ��̽��ͼ��(�����ܱ߰���)*/
	//���Ͻ�
	//int ModeSize
	for (int y=0,j=1;j<=8;y=cvRound(msize*j),j++)
	{

		for (int x=0,i=1;i<=8;x=cvRound(msize*i),i++)
		{

			CvRect cr=cvRect(x,y,msize,msize);///* ���ε�����ǵ�x-����  */ /* ���ε����ϻ������½ǵ�y-���� */����ʵ����ô�����½�
			cvSetImageROI(QRImage,cr);
			if((i==1&&j!=8)||(j==1&&i!=8)||(i==7&&j!=8)||(j==7&&i!=8)||(i>2&&i<=5&&j>2&&j<=5)){
				cvZero(QRImage);
			}
			else{//��ɫ
				cvSet(QRImage,cvScalarAll(255));
			}
			cvResetImageROI(QRImage);
		}
	}
	//���Ͻ�
	for (int y=0,j=1;j<=8;y=cvRound(msize*j),j++)
	{

		for (int x=QRImage->width-1,i=1;i<=9;x=QRImage->width-1-cvRound(msize*i),i++)
		{

			CvRect cr=cvRect(x,y,msize,msize);///* ���ε�����ǵ�x-����  */ /* ���ε����ϻ������½ǵ�y-���� */����ʵ����ô�����½�
			cvSetImageROI(QRImage,cr);
			if((i<=2&&j!=8)||(j==1&&i!=9)||(i==8&&j!=8)||(j==7&&i!=9)||(i>=4&&i<=6&&j>=3&&j<6)){
				cvZero(QRImage);
			}
			else{//��ɫ
				cvSet(QRImage,cvScalarAll(255));
			}
			cvResetImageROI(QRImage);
		}
	}
	//���½�
	for (int y=QRImage->height-1,j=1;j<=9;y=QRImage->height-1-cvRound(msize*j),j++)
	{

		for (int x=0,i=1;i<=8;x=cvRound(msize*i),i++)
		{

			CvRect cr=cvRect(x,y,msize,msize);///* ���ε�����ǵ�x-����  */ /* ���ε����ϻ������½ǵ�y-���� */����ʵ����ô�����½�
			cvSetImageROI(QRImage,cr);
			if((i==1&&j!=9)||(j<=2&&i!=8)||(i==7&&j!=9)||(j==8&&i!=8)||(i>2&&i<=5&&j>3&&j<=6)){
				cvZero(QRImage);
			}
			else{//��ɫ
				cvSet(QRImage,cvScalarAll(255));
			}
			cvResetImageROI(QRImage);
		}
	}

	//cvNamedWindow("Grid2",1);
	//cvShowImage("Grid2",tst);

	cvReleaseImage(&smapleImg);
	IplImage *result=cvCloneImage(QRImage);//��ʱ���
	///*������Ҫ����߾�*/
	cvReleaseImage(&QRImage);
	QRImage=cvCreateImage(cvSize(result->width+30,result->height+30),result->depth,result->nChannels);
	cvSet(QRImage,cvScalarAll(255));
	CvRect content=cvRect(15,15,result->width,result->height);
	cvSetImageROI(QRImage,content);
	cvCopy(result,QRImage);
	cvResetImageROI(QRImage);
	cvReleaseImage(&result);
	//cvNamedWindow("Grid",1);
//	cvShowImage("Grid",QRImage);
	//cvWaitKey(0);
	cvReleaseImage(&tst);
	//cvSaveImage("result.bmp",QRImage);
//	cvReleaseImage(&QRImage);
return QRImage;
}


/*************************************************
����: ��ȡQRͼ�����ڵ�����
����:  ���״λ��QR������������ʱ����Ҫ��ȡ��λ��Ȼ����չ��ԭͼ��С
��ʱ�Ѿ����pt,���������ȡ
pt vertices�ṹ��
P2***P1
*     *
P3***P4
ȷ�����ĸ��Ƕ�֮����Ҫ��ÿһ��ͼ�ν��н�������У������ʶ��
*************************************************/
void RecDect::AreaRotate()//��ȡQRͼ�����ڵ�����
{
	int w=img->width;//ԭ��ͼ����
	int h=img->height;//ԭ��ͼ����
	int *t=new int[10];
	CvRect crt;
	crt.x=minPoint(pt[0].x,pt[1].x,pt[2].x,pt[3].x);
	//expand
	crt.x=(crt.x-margin2)>0?(crt.x-margin2):0;
	crt.y=minPoint(pt[0].y,pt[1].y,pt[2].y,pt[3].y);
	crt.y=(crt.y-margin2)>0?(crt.y-margin2):0;
	crt.height=maxPoint(pt[0].y,pt[1].y,pt[2].y,pt[3].y)-crt.y+2*margin2;
	crt.height=(crt.height+crt.y)>(img->height)?(img->height-crt.y):crt.height;
	crt.width=maxPoint(pt[0].x,pt[1].x,pt[2].x,pt[3].x)-crt.x+2*margin2;
	crt.width=(crt.width+crt.x)>(img->width)?(img->width-crt.x):crt.width;
	//�����Ѿ���ȡ�������򣬽�������
	if (crt.x<0||crt.y<0||crt.height<0||crt.width<0||crt.x>=img->width||crt.y>=img->height)
	{
		cout<<"QR�ֶ�λ�������ν�ȡʧ��."<<endl;
		return;
	}
	IplImage *cpy=cvCreateImage(cvSize(crt.width,crt.height),img->depth,img->nChannels);
	cvSetImageROI(img,crt);
	cvCopy(img,cpy);
	cvResetImageROI(img);

	cvReleaseImage(&img);
	cvReleaseImage(&img0);

	img=cvCreateImage(cvSize(400,400),cpy->depth,cpy->nChannels);
	img0=cvCreateImage(cvSize(400,400),cpy->depth,1);
	//cvCopy(cpy,img);
	cvResize(cpy, img); //����Դͼ��Ŀ��ͼ��
	cvReleaseImage(&cpy);
	/*��������תУ�����򣬼�ǿʶ����*/
	double angle;
	//angle=CV_PI/2-AngleDect(img0);//ȷ����ת�Ƕ�,�Ŵ�ȷ��
	double q=atan((double)(pt[2].y-pt[1].y)/(pt[2].x-pt[1].x));
	//	
	if(q<0)//����
		angle=(CV_PI/2+q)*180.0/CV_PI;
	else 
		angle=-(CV_PI/2-q)*180.0/CV_PI;
	if(fabs(q)<0.005||fabs(fabs(q)-CV_PI/2.0)<0.005){	
		cvSetImageCOI(img,1);//Bɫ
		cvCopy(img,img0);  //��ȡBɫ
		cvSetImageCOI(img,0);//�ָ�
		angle=0;
		//if(fabs(angle)<0.05||fabs(fabs(angle)-1.57)<0.05){
		//ͼ��houghֱ��ˮƽ������ֱʱ����δ��⵽б��
	}else 
	{	

		FitRotate (img,angle);
		//cvShowImage("��ת���ͼ��",img);
		//ת���Ҷ�
		cvSetImageCOI(img,1);//Bɫ
		cvCopy(img,img0);  //��ȡBɫ
		cvSetImageCOI(img,0);//�ָ�
		//	/*ͼ���Ѿ���תУ����ʣ������г���*/
	}	
	RfindSquaresRect(0.36f,0.9);//��ȡͼ��������������:�˲���ȡͼ����λ��,chongxin dingweidingdian pt weizhi,keyi youhua ,xianzai meishijian
	//���Գ����·�����λ���㣬����ͼ��Ҫ�ı䣬��ͼ��������
	//for(int i=0;i<4;i++)
	//{
	//	pt[i].x=400*(pt[i].x*cos(angle*CV_PI/180.)-pt[i].y*sin(angle*CV_PI/180.)+0.5*w)/w;
	//	pt[i].y=400*(pt[i].x*sin(angle*CV_PI/180.)+pt[i].y*cos(angle*CV_PI/180.)+0.5*h)/h;
	//}
	//printf("%d",pt[0].x);
	//cvShowImage("��ȡ����ת��ͼ��",img0);//cishi huidutu

}
/*
��������GetNonZero
˵������canny���ͼ�����ÿ�У��У��ı�Ե���أ�����ͼ���һ�����񻮷ֲ���
������
Grayimage��canny���ͼ��
num��Ҫ������У��У�
type:0��ʾͳ��ÿ�У�1��ʾͳ��ÿ��
����ֵ��ÿ�У��У��ı�Ե���أ�255���ĸ���
*/
int RecDect::GetNonZero(const IplImage *Grayimage,int num,int type){
	int number=0;

	if(type){//type==0ȡ�еķ���ֵ
		if (num<0||num>=Grayimage->height)
		{
			cout<<"��ȡ��������ʱ������Χ"<<endl;

			return 0;
		}
		uchar *ptr=(uchar *)(Grayimage->imageData);
		for (int y=0;y<Grayimage->height;y++){
			if(ptr[(y)*Grayimage->widthStep+num]==255)
				number++;
		}

		return number;
	}else{//type==0ȡ�еķ���ֵ
		if (num<0||num>=Grayimage->width)
		{
			cout<<"��ȡ��������ʱ������Χ"<<endl;

			return 0;
		}
		uchar *ptr=(uchar *)(Grayimage->imageData+(num)*Grayimage->widthStep);
		for (int x=0;x<Grayimage->width;x++){
			if(ptr[x]==255) number++;
		}

		return number;
	}

}



