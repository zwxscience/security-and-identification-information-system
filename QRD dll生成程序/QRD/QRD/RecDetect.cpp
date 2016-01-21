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
//CvPoint pt[4];//临时存放矩形四个顶点
//vector<CvPoint> arr;//存放实际矩形坐标
//vector<int > answer;//存放实际矩形坐标对应值
// read 4 sequence elements at a time (all vertices of a square)
//const char* wndname= "模块检测测试";
//char *result0=new char[9];//存储识别字符串
//int thresh =800;
//初始化

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
	version=1;//默认版本号1和网格21
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
	img=cvCreateImage(cvGetSize(dst),dst->depth,dst->nChannels);//灰度
	cvCopy(dst,img);  //提取G
	//转化灰度
	img0=cvCreateImage(cvGetSize(img),img->depth,1);//灰度
	cvSetImageCOI(img,1);//B色
	cvCopy(img,img0);  //提取B色
	cvSetImageCOI(img,0);//恢复
	WUL=0;//
	WUR=0;
	ModeSize=0;//模块大小
}
/*************************************************
功能:        图像增强
描述:     因为摄像头图像质量差，需要根据直方图进行图像增强，
将图像灰度的域值拉伸到0-255    
参数说明:    
src： 单通道灰度图像 
dst：返回处理后的图像
返回值:          同样大小的单通道灰度图像 
*************************************************/
int RecDect::ImageStretchByHistogram(IplImage *src,IplImage *dst)

{
	//p[]存放图像各个灰度级的出现概率；
	//p1[]存放各个灰度级之前的概率和，用于直方图变换；
	//num[]存放图象各个灰度级出现的次数;

	assert(src->width==dst->width);//保证一致性
	float p[GrayScale],p1[GrayScale],num[GrayScale];
	//清空三个数组
	memset(p,0,sizeof(p));
	memset(p1,0,sizeof(p1));
	memset(num,0,sizeof(num));

	int height=src->height;
	int width=src->width;
	long wMulh = height * width;

	//求存放图象各个灰度级出现的次数
	// to do use openmp
	for(int x=0;x<width;x++)
	{
		for(int y=0;y<height;y++)
		{
			uchar v=((uchar*)(src->imageData + src->widthStep*y))[x];
			num[v]++;
		}
	}

	//求存放图像各个灰度级的出现概率
	for(int i=0;i<GrayScale;i++)
	{
		p[i]=num[i]/wMulh;
	}

	//求存放各个灰度级之前的概率和
	for(int i=0;i<GrayScale;i++)
	{
		for(int k=0;k<=i;k++)
			p1[i]+=p[k];
	}

	//直方图变换
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
功能:        图像透视变换
描述:    因为处理后的图片会发生扭曲，旋转等，需要将其校正   
参数说明:    
img： 需要处理的三通道图像 
返回值:       0
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
	//设定源观察面，即指定四边形的四个顶点
	//pt[2]左下角
	src_point[0].x=(float)pt[2].x-minx;             
	src_point[0].y=(float)pt[2].y-miny;
	//pt[3]右下角
	src_point[1].x=(float)pt[3].x-minx;                    
	src_point[1].y=(float)pt[3].y-miny;
	//pt[1]左上角
	src_point[2].x=(float)pt[1].x-minx; 
	src_point[2].y=(float)pt[1].y-miny;
	//pt[0]右上角
	src_point[3].x=(float)pt[0].x-minx; 
	src_point[3].y=(float)pt[0].y-miny;


	//设定目标观察面，即指定四边形的四个顶点
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
	//获得透视转换矩阵
	//cvWarpPerspectiveQMatrix(src_point,dst_point,&newM);
	cvGetPerspectiveTransform(src_point,dst_point,&newM);
	//透视转换
	cvWarpPerspective(Img_old,img,&newM,CV_INTER_LINEAR+CV_WARP_FILL_OUTLIERS, cvScalarAll(0) );
	cvSetImageCOI(img,1);//B色
	cvCopy(img,img0);  //提取B色
	cvSetImageCOI(img,0);//恢复
	cvReleaseImage(&Img_old);
	return 0;
}
/*************************************************
功能:  图像OTSU二值化，大津法求阈值
描述:    图像最终目的是黑白图，需要利用合理的方法进行二值化
参数说明:    
frame： 需要处理的单通道灰度图像 
返回值:      阈值分割点
*************************************************/
int RecDect::otsu(const IplImage *frame) 
{
	//frame灰度级
	int pixelCount[GrayScale]={0};
	float pixelPro[GrayScale]={0};
	int width=frame->width;
	int height=frame->height;
	int i, j, pixelSum = width * height, threshold = 0;
	uchar* data = (uchar*)frame->imageData;
	float w0, w1, u0tmp, u1tmp, u0, u1, deltaTmp, deltaMax = 0;
	//统计每个灰度级中像素的个数
	for(i = 0; i < height; i++)
	{
		for(j = 0;j < width;j++)
		{
			pixelCount[(int)data[i * width + j]]++;
		}
	}

	//计算每个灰度级的像素数目占整幅图像的比例
	for(i = 0; i < GrayScale; i++)
	{
		pixelPro[i] = (float)pixelCount[i] / pixelSum;
	}

	//遍历灰度级[0,255],寻找合适的threshold

	for(i = 0; i < GrayScale; i++)
	{
		w0 = w1 = u0tmp = u1tmp = u0 = u1 = deltaTmp = 0;
		for(j = 0; j < GrayScale; j++)
		{
			if(j <= i)   //背景部分
			{
				w0 += pixelPro[j];
				u0tmp += j * pixelPro[j];
			}
			else   //前景部分
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
功能: 检查四边形角度
描述:    轮廓检索的图像不一定是矩形，需要利用规则排除
参数说明:    
pt1：  pt2：pt0：检测到的图形三个顶点的坐标
返回值:   他们之间的夹角的余弦
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
功能: 返回一系列检测到的四边形(备选位置探测图形)
描述:    原始图像利用轮廓检索的图像四边形
参数说明:    
img：原始绿色通道图像

返回值:   一系列四边形顶点坐标
*************************************************/

CvSeq* RecDect::findSquares4()
{

	IplImage *img2=cvCreateImage(cvGetSize(img0),img0->depth,img0->nChannels);//灰度
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
	// 选择图像最大区域
	// find contours and store them all as a list
	cvFindContours( img2, storage, &contours, sizeof(CvContour),
		CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE, cvPoint(0,0) );
	//CvBox2D rect ;
	CvRect rect;
	CvPoint rect_pts[5], *pt1 = rect_pts;//临时存放四边形的四个顶点,di 5ge fang zhouchang he mianji
	int npts = 4;
	while( contours )
	{

		//找出完整包含轮廓的最小矩形
		//rect = cvMinAreaRect2(contours);
		rect=cvBoundingRect(contours);
		//用cvBoxPoints找出矩形的4个顶点
		//CvPoint2D32f rect_pts0[4];
		//cvBoxPoints(rect, rect_pts0);

		//因为cvPolyLine要求点集的输入类型是CvPoint**
		//所以要把 CvPoint2D32f 型的 rect_pts0 转换为 CvPoint 型的 rect_pts
		//并赋予一个对应的指针 *pt1
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
		float edge1=sqrt((float)(pt1[1].x-pt1[0].x)*(pt1[1].x-pt1[0].x)+(float)(pt1[1].y-pt1[0].y)*(pt1[1].y-pt1[0].y));//边长
		float edge2=sqrt((float)(pt1[1].x-pt1[2].x)*(pt1[1].x-pt1[2].x)+(float)(pt1[1].y-pt1[2].y)*(pt1[1].y-pt1[2].y));//边长
		float area=edge1*edge2;
		if(area<length*length/9&&area>length*length/50&&fabs(edge1-edge2)<0.1*edge1){//如果不满足边长条件，则认为不是整体轮廓
			////画出Box
			int mianji=cvRound(cvContourArea(contours));
			int zhouchang=cvRound(cvContourPerimeter(contours));
			rect_pts[4].x=zhouchang;
			rect_pts[4].y=mianji;
			for( int i = 0; i < 5; i++ ){
				cvSeqPush( squares,(CvPoint*)&pt1[i]);
			}
			//下面是识别结果测试
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
功能: 经过一系列的图像变换后提取QR轮廓
描述:    原始图像利用轮廓检索的图像四边形（要求是矩形）
参数说明:    
img：原始3通道图像
返回值:   一系列四边形cvbox形式
low:识别QR码轮廓面积的下限
high:识别QR码轮廓面积的上限
旋转的二维盒子

typedef struct CvBox2D
{
CvPoint2D32f center;  盒子的中心 
CvSize2D32f  size;    盒子的长和宽 
float angle;          水平轴与第一个边的夹角，用弧度表示*
}
CvBox2D;
*************************************************/

void RecDect::RfindSquaresRect(float low,float high)
{
	IplImage *img2=cvCreateImage(cvGetSize(img0),img0->depth,img0->nChannels);//灰度
	cvCopy(img0,img2); 
	//IplImage *img2=cvCloneImage(img0);
	 IplImage * tempM = cvCreateImage(cvGetSize(img2), img2->depth,img2->nChannels);    
	cvAdaptiveThreshold(img2,img2,255,CV_ADAPTIVE_THRESH_GAUSSIAN_C,CV_THRESH_BINARY_INV,101,-5);
//	cvShowImage("第一次erzhihua后的图像",img2);
	//cvSaveImage("第一次erzhihua后的图像.bmp",img2);
	//cvCanny(img2,img2,50,150,3); 
	//cvShowImage("第一次cvCanny后的图像",img2);
	//cvDilate(img2, img2, 0, 8);
	//cvErode( img2, img2, 0, 8);
	cvMorphologyEx(img2,img2,tempM,NULL,CV_MOP_OPEN,9);
	//cvShowImage("第一次kai后的图像",img2);
	//cvSaveImage("第一次kai后的图像.bmp",img2);
	cvCanny(img2,img2,50,150,3); 
	//cvShowImage("cvCanny后的图像",img2);
	//cvSaveImage("第一次cvCanny后的图像.bmp",img2);
	cvSmooth(img2,img2);
	//cvShowImage("第1次cvSmooth后的图像",img2);
	//cvSaveImage("第一次cvSmooth后的图像.bmp",img2);
	cvAdaptiveThreshold(img2,img2,255,CV_ADAPTIVE_THRESH_GAUSSIAN_C,CV_THRESH_BINARY_INV,101,-3);
	//cvShowImage("第2次erzhihua后的图像",img2);
	//cvSaveImage("第2次erzhihua后的图像.bmp",img2);
	IplImage *img3=cvCreateImage(cvGetSize(img2),img2->depth,img2->nChannels);//灰度
	cvCopy(img2,img3); 
	//IplImage *img3=cvCloneImage(img2);

	CvMemStorage* storage = cvCreateMemStorage(0);
	CvSeq* contours;

	// 选择图像最大区域
	// find contours and store them all as a list
	cvFindContours( img2, storage, &contours, sizeof(CvContour),
		CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE, cvPoint(0,0) );
	CvBox2D rect ;
	memset(pt,0,sizeof(CvPoint)*4);
	CvPoint rect_pts[4], *pt1 = rect_pts;//临时存放四边形的四个顶点

	int flag=1;
	int npts = 4;
	float area2,edge3,edge4;//最大面积及其边长
	vector<CvPoint> temp;
	while( contours )
	{
		double mianji=cvContourArea(contours);
		if(mianji<high*img2->width*img2->width&&mianji>low*img2->width*img2->width)
		{
		// test each contour
		//找出完整包含轮廓的最小矩形
		rect = cvMinAreaRect2(contours);
		//用cvBoxPoints找出矩形的4个顶点
		CvPoint2D32f rect_pts0[4];
		cvBoxPoints(rect, rect_pts0);
		//因为cvPolyLine要求点集的输入类型是CvPoint**
		//所以要把 CvPoint2D32f 型的 rect_pts0 转换为 CvPoint 型的 rect_pts
		//并赋予一个对应的指针 *pt1
		for (int rp=0; rp<4; rp++)
			rect_pts[rp]= cvPointFrom32f(rect_pts0[rp]);
		float edge1=sqrt((float)(pt1[1].x-pt1[0].x)*(pt1[1].x-pt1[0].x)+(float)(pt1[1].y-pt1[0].y)*(pt1[1].y-pt1[0].y));//边长
		float edge2=sqrt((float)(pt1[1].x-pt1[2].x)*(pt1[1].x-pt1[2].x)+(float)(pt1[1].y-pt1[2].y)*(pt1[1].y-pt1[2].y));//边长
		float area=edge1*edge2;
		if(fabs(edge1-edge2)<0.2*edge1&&area<high*img2->width*img2->width&&area>low*img2->width*img2->width){//如果不满足边长条件，则认为不是整体轮廓
			//画出Box
			temp.push_back(pt1[0]);
			temp.push_back(pt1[1]);
			temp.push_back(pt1[2]);
			temp.push_back(pt1[3]);

			if(flag==1){//用第一个填充结果，如果仅有一个则为此
				pt[0]=pt1[0];	
				pt[1]=pt1[1];
				pt[2]=pt1[2];
				pt[3]=pt1[3];
				flag++;
				//	cout<<contours->total<<endl;
			}else{
				edge3=sqrt((float)(pt[1].x-pt[0].x)*(pt[1].x-pt[0].x)+(float)(pt[1].y-pt[0].y)*(pt[1].y-pt[0].y));//边长
				edge4=sqrt((float)(pt[1].x-pt[2].x)*(pt[1].x-pt[2].x)+(float)(pt[1].y-pt[2].y)*(pt[1].y-pt[2].y));//边长
				//yihui比面积：谁小选谁
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
		//采用下一个轮廓
		contours = contours->h_next;
	}		
	if(pt[0].x==0){
		cout<<"没有搜到整体轮廓"<<endl;

	}
	//现在寻求内轮廓
	for (int i=0;i<temp.size();i+=4)
	{
		float d1=sqrt((float)(temp.at(i).x-pt[0].x)*(temp.at(i).x-pt[0].x)+(float)(temp.at(i).y-pt[0].y)*(temp.at(i).y-pt[0].y));
		float d2=sqrt((float)(temp[i+1].x-pt[1].x)*(temp[i+1].x-pt[1].x)+(float)(temp[i+1].y-pt[1].y)*(temp[i+1].y-pt[1].y));
		float d3=sqrt((float)(temp[i+2].x-pt[2].x)*(temp[i+2].x-pt[2].x)+(float)(temp[i+2].y-pt[2].y)*(temp[i+2].y-pt[2].y));
		float d4=sqrt((float)(temp[i+3].x-pt[3].x)*(temp[i+3].x-pt[3].x)+(float)(temp[i+3].y-pt[3].y)*(temp[i+3].y-pt[3].y));
		if((d1<10)&&(d2<10)&&(d3<10)&&(d4<10)&&d1!=0&&d2!=0&&d3!=0&&d4!=0)//找内部
		{
			pt[0]=temp[i];	
			pt[1]=temp[i+1];
			pt[2]=temp[i+2];
			pt[3]=temp[i+3];

		}
	}

	vector<CvPoint>().swap(temp); //释放
	vertexOrder(pt);//顶点重排
	//cvShowImage("整体轮廓",img3);
//	cvWaitKey(0);
	//cvSaveImage("buxianding整体轮廓.bmp",img3);
	cvReleaseMemStorage(&storage);
	cvReleaseImage(&img2);
	cvReleaseImage(&img3);
}

/*************************************************
功能: 经过一系列的图像变换后提取QR轮廓，提取的是不规则的四边形
描述:    原始图像利用轮廓检索的图像四边形（要求是四边形）
参数说明:    
img：原始图像
返回值:   一系列四边形坐标
旋转的二维盒子
经试验发现，其中的
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
//cvShowImage("第一次cany膨胀后的图像",img2);

cvSmooth(img2,img2);
cvCanny(img2,img2,50,150,3); 
cvSmooth(img2,img2);
cvAdaptiveThreshold(img2,img2,255,CV_ADAPTIVE_THRESH_GAUSSIAN_C,CV_THRESH_BINARY_INV,501,-11);
cvCopy(img2,img3);
int thresh=800;
storage = cvCreateMemStorage(0);
CvSeq* contours;
//CvSeq* squares = cvCreateSeq( 0, sizeof(CvSeq), sizeof(CvPoint), storage );
// 选择图像最大区域
// find contours and store them all as a list
cvFindContours( img2, storage, &contours, sizeof(CvContour),
CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE, cvPoint(0,0) );
//CvBox2D rect ;
memset(pt,0,sizeof(CvPoint)*4);
CvPoint rect_pts[4];//临时存放四边形的四个顶点
int flag=1;
int npts = 4;
CvPoint *pt1 =rect_pts;
while( contours )
{
// test each contour
//找出完整包含轮廓的最小矩形
result = cvApproxPoly( contours, sizeof(CvContour), storage,
CV_POLY_APPROX_DP, cvContourPerimeter(contours)*0.02, 0 );
// 区块要有四个边
// 周长在100到850
//检测是否是凸型
//也可以利用面积求解if( result->total == 4 &&
//	fabs(cvContourArea(result,CV_WHOLE_SEQ)) > 1000 &&
//	cvCheckContourConvexity(result) )
if( result->total == 4 &&
fabs(cvContourArea(result,CV_WHOLE_SEQ)) <0.81*img2->width*img2->width&&
cvCheckContourConvexity(result) ){
//画出Box
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

// 角度在允许区域内，即允许角度在arccos0.3到90度之间
if( s < 0.3 )
for(int i = 0; i < 4; i++ )	{
CvPoint	*pt2=(CvPoint *)cvGetSeqElem( result, i );
rect_pts[i]=*pt2;
cvSeqPush( squares,
(CvPoint*)cvGetSeqElem( result, i ));

}
cvPolyLine(img3, &pt1, &npts, 1, 1, CV_RGB(0,0,0), 2);      
}


//采用下一个轮廓
contours = contours->h_next;
}		
//cvShowImage("SS",img3);
cvReleaseImage(&img2);
cvReleaseImage(&img3);
return squares;
}*/
/*************************************************
功能: 读取轮廓顶点后进行重排序，使之达到要求
本函数是转换顶点坐标的排序
使之从pt【i】坐标
2 3
1 0
变成
1  0
2  3
*************************************************/
void RecDect::vertexOrder(CvPoint pt2[])//顶点重排,可以是轮廓的定点，图像定位点的顶点
{
	CvPoint pt1[4];
	for (int i=0;i<4;i++)//赋值
	{
		pt1[i]=pt2[i];
	}
	float maxd=0,mind=9999;
	for(int i=0;i<4;i++){//第一次选出最大最小点

		float distance=sqrt((float)pt1[i].x*pt1[i].x+pt1[i].y*pt1[i].y);//与原点的距离
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
	int xl=0,xs=9999;//通过x点判断
	for(int i=0;i<4;i++){//第2次选出另外两个
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
功能:输出位置探测图形
描述:    将位置探测图形输出到原始图像之中
参数说明:    
img：原始图像
*************************************************/
void RecDect::drawSquares()
{
	
	IplImage *img1=cvCloneImage(img0);

	cvRectangle(img1,corner1[1],corner1[3],cvScalar(0,0,255),2);
	cvRectangle(img1,corner2[1],corner2[3],cvScalar(0,0,255),2);
	cvRectangle(img1,corner3[1],corner3[3],cvScalar(0,0,255),2);
	cvRectangle(img1,corner4[1],corner4[3],cvScalar(0,0,255),2);
	//cvShowImage("三个位置探测图形", img1);
	cvReleaseImage(&img1);
}
// 
/*************************************************
功能: 提取并选择位置探测图形，并计算版本号和网格条数
描述:  计算最小位置探测图形，识别版本，计算网格
参数说明:    
img：原图像
squares：已经检测出来的位置探测图形序列
*************************************************/
int RecDect::recognVersion(CvSeq* squares)
{
	CvSeqReader reader;
	//下面是绘图专用程序
	IplImage *img1=cvCloneImage(img0);
	cvAdaptiveThreshold(img1,img1,255,CV_ADAPTIVE_THRESH_GAUSSIAN_C,CV_THRESH_BINARY_INV,101,-7);

	// 初始读取的序列里面定点集
	cvStartReadSeq( squares, &reader, 0 );
	CvPoint temp[5];//第5个是存放对应轮廓周长（x）和面积（y）
	int rotateangle=0;
	bool tag1=false;//左上角占用标志位，对应corner1[4]
	bool tag2=false;//右上角占用标志位，对应corner2[4]
	bool tag3=false;//左下角占用标志位，对应corner3[4]
	bool tag4=false;//右下角占用标志位，对应corner4[4]
	int count1=0,count2=0,count3=0,count4=0;//四分块内图形数量
	CvPoint centerl,centerr;//位置探测图形中心坐标
	for(int i = 0; i < squares->total; i += 5 )//第5个是存放的对应轮廓周长（x）和面积（y）
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
		//前面是顶点，后面是轮廓周长面积
		memcpy( temp + 4, reader.ptr, squares->elem_size );
		CV_NEXT_SEQ_ELEM( squares->elem_size, reader );
		int numbercount=(i/5)+1;
		cout<<"一共搜索到矩形"<<squares->total/4<<",这是在该图片搜索到的第 "<<numbercount<<" 个矩形，现在检测他的位置："<<endl;

		//下面是绘图专用
	cvRectangle(img1,corner1[1],corner1[3],cvScalar(0,0,255),2);
	cvRectangle(img1,corner2[1],corner2[3],cvScalar(0,0,255),2);
	cvRectangle(img1,corner3[1],corner3[3],cvScalar(0,0,255),2);
	cvRectangle(img1,corner4[1],corner4[3],cvScalar(0,0,255),2);
		//下面用面积代替
		//float edge1=sqrt((float)(temp[1].x-temp[0].x)*(temp[1].x-temp[0].x)+(float)(temp[1].y-temp[0].y)*(temp[1].y-temp[0].y));//边长1
		//float edge2=sqrt((float)(temp[2].x-temp[1].x)*(temp[2].x-temp[1].x)+(float)(temp[2].y-temp[1].y)*(temp[2].y-temp[1].y));//边长2
		//float areanew=edge1*edge2;
		CvPoint center;
		center.x=(temp[0].x+temp[2].x)/2;
		center.y=(temp[0].y+temp[2].y)/2;
		float dist=0;
		if(maxPoint(temp[0].x,temp[1].x,temp[2].x,temp[3].x)<0.5*img->width&&maxPoint(temp[0].y,temp[1].y,temp[2].y,temp[3].y)<0.5*img->height)//左上角
		{

			count1++;
			dist=sqrt((float)(center.x)*(center.x)+(float)(center.y)*(center.y));//中心左上角距离
			if (count1==1)
			{//第一次占用
				for ( int index = 0; index < 4; index++ )
					corner1[ index ] =temp[ index ];
				corner1P=temp[4];//最后存入轮廓周长和面积
			}else{//第二次占用
				//float edge3=sqrt((float)(corner1[1].x-corner1[0].x)*(corner1[1].x-corner1[0].x)+(float)(corner1[1].y-corner1[0].y)*(corner1[1].y-corner1[0].y));//边长1
				//float edge4=sqrt((float)(corner1[2].x-corner1[1].x)*(corner1[2].x-corner1[1].x)+(float)(corner1[2].y-corner1[1].y)*(corner1[2].y-corner1[1].y));//边长2
				//float areaold=edge3*edge4;//计算存入矩形的面积

				if ((corner1P.y>temp[4].y&&dist<img->width/4)||fabs((float)corner1[1].x-pt[1].x)>0.12*img->width||fabs((float)corner1[1].y-pt[1].y)>0.12*img->width)//如果计算的面积比原来的小，则替换掉
				{
					for ( int index = 0; index < 4; index++ )
						corner1[ index ] =temp[ index ];
						corner1P=temp[4];//最后存入轮廓周长和面积
				}
			}


		}
		if(minPoint(temp[0].x,temp[1].x,temp[2].x,temp[3].x)>0.5*img->width&&maxPoint(temp[0].y,temp[1].y,temp[2].y,temp[3].y)<0.5*img->height)//右上角
		{
			count2++;
			dist=sqrt((float)(img->width-1-center.x)*(img->width-1-center.x)+(float)(center.y)*(center.y));//中心you上角距离
			if (count2==1)
			{//第一次占用
				for ( int index = 0; index < 4; index++ )
					corner2[ index ] =temp[ index ];
					corner2P=temp[4];//最后存入轮廓周长和面积
			}else{//第二次占用
				//float edge3=sqrt((float)(corner2[1].x-corner2[0].x)*(corner2[1].x-corner2[0].x)+(float)(corner2[1].y-corner2[0].y)*(corner2[1].y-corner2[0].y));//边长1
				//float edge4=sqrt((float)(corner2[2].x-corner2[1].x)*(corner2[2].x-corner2[1].x)+(float)(corner2[2].y-corner2[1].y)*(corner2[2].y-corner2[1].y));//边长2
				//float areaold=edge3*edge4;//计算存入的面积
				if ((corner2P.y>temp[4].y&&dist<img->width/4)||fabs((float)-corner2[0].x+pt[0].x)>0.12*img->width||fabs((float)-corner2[0].y+pt[0].y)>0.12*img->width)//如果计算的面积比原来的小，则替换掉
				{
					for ( int index = 0; index < 4; index++ )
						corner2[ index ] =temp[ index ];
						corner2P=temp[4];//最后存入轮廓周长和面积
				}
			}

		}

		if(maxPoint(temp[0].x,temp[1].x,temp[2].x,temp[3].x)<0.5*img->width&&minPoint(temp[0].y,temp[1].y,temp[2].y,temp[3].y)>0.5*img->height)//左下角
		{
			count3++;
			dist=sqrt((float)(center.x)*(center.x)+(float)(img->height-1-center.y)*(img->height-1-center.y));//中心左下距离
			if (count3==1)
			{//第一次占用
				for ( int index = 0; index < 4; index++ )
					corner3[ index ] =temp[ index ];
					corner3P=temp[4];//最后存入轮廓周长和面积
			}else{//第二次占用
				//float edge3=sqrt((float)(corner3[1].x-corner3[0].x)*(corner3[1].x-corner3[0].x)+(float)(corner3[1].y-corner3[0].y)*(corner3[1].y-corner3[0].y));//边长1
				//float edge4=sqrt((float)(corner3[2].x-corner3[1].x)*(corner3[2].x-corner3[1].x)+(float)(corner3[2].y-corner3[1].y)*(corner3[2].y-corner3[1].y));//边长2
			//	float areaold=edge3*edge4;//计算存入的面积
				if ((corner3P.y>temp[4].y&&dist<img->width/4)||fabs((float)corner3[2].x-pt[2].x)>0.12*img->width||fabs((float)-corner3[2].y+pt[2].y)>0.12*img->width)//如果计算的面积比原来的小，则替换掉
				{
					for ( int index = 0; index < 4; index++ )
						corner3[ index ] =temp[ index ];
						corner3P=temp[4];//最后存入轮廓周长和面积
				}
			}

		}
		if(minPoint(temp[0].x,temp[1].x,temp[2].x,temp[3].x)>0.5*img->width&&minPoint(temp[0].y,temp[1].y,temp[2].y,temp[3].y)>0.5*img->height)//右下角
		{
			count4++;
			dist=sqrt((float)(img->width-1-center.x)*(img->width-1-center.x)+(float)(img->height-1-center.y)*(img->height-1-center.y));//中心you下距离
			if (count4==1)
			{//第一次占用
				for ( int index = 0; index < 4; index++ )
					corner4[ index ] =temp[ index ];
					corner4P=temp[4];//最后存入轮廓周长和面积
			}else{//第二次占用
				//float edge3=sqrt((float)(corner4[1].x-corner4[0].x)*(corner4[1].x-corner4[0].x)+(float)(corner4[1].y-corner4[0].y)*(corner3[1].y-corner4[0].y));//边长1
				//float edge4=sqrt((float)(corner4[2].x-corner4[1].x)*(corner4[2].x-corner4[1].x)+(float)(corner4[2].y-corner4[1].y)*(corner3[2].y-corner4[1].y));//边长2
				//float areaold=edge3*edge4;//计算存入的面积
				if ((corner4P.y>temp[4].y&&dist<img->width/4)||fabs((float)-corner4[3].x+pt[3].x)>0.12*img->width||fabs((float)-corner4[3].y+pt[3].y)>0.12*img->width)//如果计算的面积比原来的小，则替换掉
					//if (areaold>areanew&&dist<img->width/4)//如果计算的面积比原来的小，则替换掉
				{
					for ( int index = 0; index < 4; index++ )
						corner4[ index ] =temp[ index ];
						corner4P=temp[4];//最后存入轮廓周长和面积
				}
			}

		}

	}
	//下面是绘图专用
	//cvShowImage("test",img1);
	int t[4];
	t[0]=count1;
	t[1]=count2;
	t[2]=count3;
	t[3]=count4;
	int tempcount=t[0];
	for(int i=0;i<4;i++){
		if(tempcount>t[i])tempcount=t[i];//选出最少的
	}
	if (tempcount!=count1)//有至少三个图形
	{
		tag1=true;
	}
	if (tempcount!=count2)//有至少三个图形
	{
		tag2=true;
	}
	if (tempcount!=count3)//有至少三个图形
	{
		tag3=true;
	}
	if (tempcount!=count4)//有至少三个图形
	{
		tag4=true;
	}
	//4 vertices结构：
	//P2***P1
	//*     *
	//P3***P4
	//确定了四个角度之后需要对每一个图形进行进行区域校正采样识别
	vertexOrder(corner1);
	vertexOrder(corner2);
	vertexOrder(corner3);
	vertexOrder(corner4);
	float width=sqrt((float)(pt[1].x-pt[0].x)*(pt[1].x-pt[0].x)+(pt[1].y-pt[0].y)*(pt[1].y-pt[0].y));//QR图像宽度

	//两个探测图形的宽度，WUL和WUR

	if (!tag4&&tag1&&tag2&&tag3)
	{
		//P*****P
		//*     *
		//P******
		//清空第四个角
		for (int i=0;i<4;i++)
		{
			corner4[i].x=0;
			corner4[i].y=0;
		}
		centerl=cvPoint((corner1[1].x+corner1[3].x)/2,(corner1[1].y+corner1[3].y)/2);
		centerr=cvPoint((corner2[1].x+corner2[3].x)/2,(corner2[1].y+corner2[3].y)/2);
		if(width==0){//说明整体轮廓未检测出
			cout<<"整体轮廓检测时出错"<<endl;
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
		if(width==0){//说明整体轮廓未检测出
			cout<<"整体轮廓检测时出错"<<endl;
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
		if(width==0){//说明整体轮廓未检测出
			cout<<"整体轮廓检测时出错"<<endl;
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
		if(width==0){//说明整体轮廓未检测出
			cout<<"整体轮廓检测时出错"<<endl;
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
		cout<<"识别探测图形出错，经筛选后探测图形可能少于三个或者不只3个，请检查。将采用默认版本格式（版本1）"<<endl;
	}
	//策略改变了，包围位置探测图形 的内部根据1:1:3:1:1,修改WUL，WUR
	WUL=7.0*WUL/3;
	WUR=7.0*WUR/3;
	//得到以上信息后就可以进行版本确定了	
	//距离D，是左上角位置探测图形中心与右上角位置探测图形中心之间的距离。
	if (centerl.x!=0&&centerr.x!=0)
	{

		float d=sqrt((float)(centerl.x-centerr.x)*(centerl.x-centerr.x)+(centerl.y-centerr.y)*(centerl.y-centerr.y));
		//计算符号的名义模块宽度尺寸X
		ModeSize=(WUL+WUR)/14;
		//初步确定符号的版本
		version =cvRound(((d/ModeSize)-10)/4);
		if (version<1)
		{
			version=1;
		}
		if(version<7){
			//7以下即为真是版本号
			switch(version){
			case 1:number=21;break;//版本1
			case 2:number=25;break;//版本2
			case 3:number=29;break;//版本3
			case 4:number=33;break;//版本4
			case 5:number=37;break;//版本5
			case 6:number=41;break;//版本6
			}
			//如果初步确定的符号版本等于或小于s，那么该计算值即为版本号。如果初步确定的符号版本等于或大于7，那么版本信息应按下列步骤译码:
		}else{//不采用BCH纠错，直接根据划分范围进行纠错
			//用7除右上角位置探测图形的宽度尺寸，得到模块尺寸
			float modsize=WUR/7;
			int count=cvRound(width/modsize);
			if(count>43&&count<47)//版本7
			{
				version=7;
				number=45;

			}
			if(count>47&&count<51)//版本8
			{
				version=8;
				number=49;

			}
			if(count>51&&count<55)//版本9
			{
				version=9;
				number=53;

			}		 
			if(count>55&&count<59)//版本10
			{
				version=10;
				number=57;

			}		
			if(count>59&&count<63)//版本11
			{
				version=11;
				number=61;

			}		 
			if(count>63&&count<67)//版本12
			{
				version=12;
				number=65;

			}		 
			if(count>67&&count<71)//版本13
			{
				version=13;
				number=69;

			}		
			if(count>71&&count<75)//版本14
			{
				version=14;
				number=73;

			}		 
			if(count>75&&count<79)//版本15
			{
				version=15;
				number=77;

			}		
			if(count>79&&count<83)//版本16
			{
				version=16;
				number=81;

			}		
			if(count>83&&count<87)//版本17
			{
				version=17;
				number=85;

			}		
			if(count>87&&count<91)//版本18
			{
				version=18;
				number=89;

			}		 
			if(count>91&&count<95)//版本19
			{
				version=19;
				number=93;

			}		
			if(count>95&&count<99)//版本20
			{
				version=20;
				number=97;

			}		
			if(count>99&&count<103)//版本21
			{
				version=21;
				number=101;

			}	 
			if(count>103&&count<107)//版本22
			{
				version=22;
				number=105;

			}
			if(count>107&&count<111)//版本23
			{
				version=23;
				number=109;

			}	
			if(count>111&&count<115)//版本24
			{
				version=24;
				number=113;

			}	
			if(count>115&&count<119)//版本25
			{
				version=25;
				number=117;

			}	
			if(count>119&&count<123)//版本26
			{
				version=26;
				number=121;

			}	
			if(count>123&&count<127)//版本27
			{
				version=27;
				number=125;

			}	
			if(count>127&&count<131)//版本28
			{
				version=28;
				number=129;

			}	
			if(count>131&&count<135)//版本29
			{
				version=29;
				number=133;

			}	
			if(count>135&&count<139)//版本30
			{
				version=30;
				number=137;

			}	
			if(count>139&&count<143)//版本31
			{
				version=31;
				number=141;

			}	 
			if(count>143&&count<147)//版本32
			{
				version=32;
				number=145;

			}	 
			if(count>147&&count<151)//版本33
			{
				version=33;
				number=149;

			}	
			if(count>151&&count<155)//版本34
			{
				version=34;
				number=153;

			}
			if(count>155&&count<159)//版本35
			{
				version=35;
				number=157;

			}
			if(count>159&&count<163)//版本36
			{
				version=36;
				number=161;

			}
			if(count>163&&count<167)//版本37
			{
				version=37;
				number=165;

			}
			if(count>167&&count<171)//版本38
			{
				version=38;
				number=169;

			}
			if(count>171&&count<175)//版本39
			{
				version=39;
				number=173;

			}
			if(count>175&&count<179)//版本40
			{
				version=40;
				number=177;

			}else{
				cout<<"确定QR码版本时出错，划分网格数量为"<<count<<endl;
			}
		}

	}
	cvReleaseMemStorage(&squares->storage);
	printf("此图形版本号：%d，网格数：%d",version,number);
	return rotateangle;
}
/*************************************************
功能: 检测QR码图像矩形的坐标最小点
描述:  检测QR码图像矩形的坐标最小点
参数说明:    
unsigned int a,unsigned int b,unsigned int c,unsigned int d：矩形四个顶点x/y坐标
返回值：最小的x/y值
*************************************************/
int RecDect::minPoint(unsigned int a,unsigned int b,unsigned int c,unsigned int d){
	unsigned int tem1=(b>a? a:b);
	unsigned int tem2=(c>d? d:c);
	return (tem1>tem2? tem2:tem1);
}
/*************************************************
功能: 检测QR码图像矩形的坐标最大点
描述:  检测QR码图像矩形的坐标最大点
参数说明:    
unsigned int a,unsigned int b,unsigned int c,unsigned int d：矩形四个顶点x/y坐标
返回值：最大的x/y值
*************************************************/
int RecDect::maxPoint(unsigned int a,unsigned int b,unsigned int c,unsigned int d){
	unsigned int tem1=(b>a? b:a);
	unsigned int tem2=(c>d? c:d);
	return (tem1>tem2? tem1:tem2);
}
/*************************************************
功能: 获取精确QR整体轮廓顶点坐标
描述: 在原来顶点坐标基础上进行精细获取
描述说明:    
已经捕捉了一个大概的顶点集，需要进行细化。
定义阈值函数T（x）=每行/每列灰度值为0的数量，定义maxP=max（T（x））
从i=1开始扫描，一直到i=30(实际偏离不可能超过30)(546/21=26,选30)
当T(x)>1/2maxP时，认为已经扫描到了
*************************************************/
void RecDect::GetAccVertex()
{
	IplImage *temp=cvCloneImage(img0);
	cvAdaptiveThreshold(img0,temp,255,CV_ADAPTIVE_THRESH_GAUSSIAN_C,CV_THRESH_BINARY_INV,101,-3);//二值化

	int max=0;
	int depth=100;
	//从左半部分
	for (int i=0;i<depth;i++)//寻找max
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
	//开始进行扫描上
	for (int i=0;i<depth;i++)//
	{
		uchar *ptr=(uchar *)(temp->imageData+i*temp->widthStep);
		int num=0;
		for(int j=0;j<temp->width/2;j++){
			if(ptr[temp->nChannels*j]==0)num++;//统计
		}
		if (num>max/3)
		{
			pt[1].y=i;
			//pt[0].y=i;
			break;
		}

	}
	//开始进行扫描下
	for (int i=temp->height-1;i>=temp->height-1-depth;i--)
	{
		uchar *ptr=(uchar *)(temp->imageData+i*temp->widthStep);
		int num=0;
		for(int j=0;j<temp->width/2;j++){
			if(ptr[temp->nChannels*j]==0)num++;//统计
		}
		if (num>max/3)
		{
			pt[2].y=i;
			//pt[3].y=i;
			break;
		}

	}
	//开始进列扫描左
	for (int j=0;j<depth;j++)//
	{

		int num=0;
		for(int i=0;i<temp->height;i++){
			uchar ptr=(uchar )*(temp->imageData+i*temp->widthStep+j*temp->nChannels);
			if(ptr==0)num++;//统计
		}
		if (num>max/3)
		{
			pt[1].x=j;
			pt[2].x=j;
			break;
		}

	}
	//右半部分
	//从you半部分
	//开始进行扫描上
	for (int i=0;i<depth;i++)//寻找max
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
			if(ptr[temp->nChannels*j]==0)num++;//统计
		}
		if (num>max/3)
		{
			pt[0].y=i;
			break;
		}

	}
	//开始进行扫描下
	for (int i=temp->height-1;i>=temp->height-1-depth;i--)
	{
		uchar *ptr=(uchar *)(temp->imageData+i*temp->widthStep);
		int num=0;
		for(int j=temp->width-1;j>temp->width/2;j--){
			if(ptr[temp->nChannels*j]==0)num++;//统计
		}
		if (num>max/3)
		{

			pt[3].y=i;
			break;
		}

	}


	//开始进列扫描右
	for (int j=temp->width-1;j>=temp->width-depth;j--)//
	{

		int num=0;
		for(int i=0;i<temp->height;i++){
			uchar ptr=(uchar )*(temp->imageData+i*temp->widthStep+j*temp->nChannels);
			if(ptr==0)num++;//统计
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
功能: 检测QR码图像倾斜程度
描述:  通过Hough变换获取倾斜角，需要之前进行二值化边缘检测等
参数说明:    
IplImage* img：源图像
返回值：图像倾斜角度
*************************************************/
double RecDect::AngleDect(const IplImage* img){
	IplImage *src =cvCloneImage(img); 
	IplImage* dst;
	IplImage* color_dst;
	CvMemStorage* storage = cvCreateMemStorage(0);
	CvSeq* lines = 0;
	int i;
	float theta ;//旋转角度
	dst = cvCreateImage( cvGetSize(src), 8, 1 );
	color_dst = cvCreateImage( cvGetSize(src), 8, 3 );
	//cvShowImage("源图像",img0);
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
	lines = cvHoughLines2(src, storage, CV_HOUGH_STANDARD, 1, CV_PI/180, 50, 0, 0 );//传统
	//cout << MIN(lines->total,100) << endl;
	for( i = 0; i < MIN(lines->total,1); i++ )//返回一条直线
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
功能: 图像旋转
描述:  利用二次差值法进行图像旋转
参数说明:    
Imgm：源图像
alpha：图像倾斜角度
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
	// 将旋转中心移至图像中间
	m[2] = w*0.5f;  
	m[5] = h*0.5f;  
	//  dst(x,y) = A * src(x,y) + b
	cvGetQuadrangleSubPix( src, Img_old,&M);
	cvReleaseImage(&src);

}
/*************************************************
功能: 平均法划分网格
描述:  利用QR版本号划分网格
参数说明:    
Imgm：源图像

*************************************************/
void RecDect::drawGridaverage()//图像归一化
{
	CvSize QRSize;
	QRSize.height=number*20;
	QRSize.width=number*20;
	IplImage *QRImage=cvCreateImage(QRSize,img0->depth,img0->nChannels);
	cvResize(img0, QRImage); //缩放源图像到目标图像
	cvAdaptiveThreshold(QRImage,QRImage,255,CV_ADAPTIVE_THRESH_GAUSSIAN_C,CV_THRESH_BINARY_INV,101,0);//二值化
	IplImage *img2=cvCloneImage(QRImage);
	int modeWidth=img2->width/number;//模块宽度
	int modeHeight=img2->height/number;//模块高度

	//利用网格查看，以下可删掉
	for (int y=0,j=0;j<=number;y=cvRound(modeHeight*j),j++)
	{
		//cout<<"第"<<j<<"个间隔"<<y<<endl;
		CvPoint pst,pend;
		pst=cvPoint(0,y);
		pend=cvPoint(img2->width-1,y);
		cvLine(img2,pst,pend,cvScalarAll(0));

	}
	for (int x=0,i=0;i<=number;x=cvRound(modeWidth*i),i++)
	{
		//cout<<"第"<<i<<"个间隔"<<x<<endl;
		CvPoint pst,pend;
		pst=cvPoint(x,0);
		pend=cvPoint(x,img2->height);
		cvLine(img2,pst,pend,cvScalarAll(0));
	}
	//cvShowImage("Grid1",img2);
	//利用网格查看，以上可删掉

	cvCopy(QRImage,img2);
	for (int y=0,j=1;j<=number;y=cvRound(modeHeight*j),j++)
	{
		uchar *ptr=(uchar *)(img2->imageData+cvRound(y+0.5*modeHeight)*img2->widthStep);

		for (int x=0,i=1;i<=number;x=cvRound(modeWidth*i),i++)
		{

			//cout<<"第("<<x<<","<<y<<")个间隔"<<x<<endl;
			int centerval=ptr[img2->nChannels*cvRound(x+0.5*modeWidth)];
			CvRect cr=cvRect(x,y,modeWidth,modeHeight);
			cvSetImageROI(img2,cr);
			if(centerval>10){//白色
				cvSet(img2,cvScalarAll(255));
			}else{
				cvZero(img2);
			}
			cvResetImageROI(img2);

		}
	}
	/*现在需要重绘三个位置探测图形(加上周边白线)*/
	//左上角
	for (int y=0,j=1;j<=8;y=cvRound(modeHeight*j),j++)
	{

		for (int x=0,i=1;i<=8;x=cvRound(modeWidth*i),i++)
		{

			CvRect cr=cvRect(x,y,modeWidth,modeHeight);///* 方形的最左角的x-坐标  */ /* 方形的最上或者最下角的y-坐标 */但是实际怎么是右下角
			cvSetImageROI(img2,cr);
			if((i==1&&j!=8)||(j==1&&i!=8)||(i==7&&j!=8)||(j==7&&i!=8)||(i>2&&i<=5&&j>2&&j<=5)){
				cvZero(img2);
			}
			else{//白色
				cvSet(img2,cvScalarAll(255));
			}
			cvResetImageROI(img2);
		}
	}
	//右上角
	for (int y=0,j=1;j<=8;y=cvRound(modeHeight*j),j++)
	{

		for (int x=img2->width-1,i=1;i<=9;x=img2->width-1-cvRound(modeWidth*i),i++)
		{

			CvRect cr=cvRect(x,y,modeWidth,modeHeight);///* 方形的最左角的x-坐标  */ /* 方形的最上或者最下角的y-坐标 */但是实际怎么是右下角
			cvSetImageROI(img2,cr);
			if((i<=2&&j!=8)||(j==1&&i!=9)||(i==8&&j!=8)||(j==7&&i!=9)||(i>=4&&i<=6&&j>=3&&j<6)){
				cvZero(img2);
			}
			else{//白色
				cvSet(img2,cvScalarAll(255));
			}
			cvResetImageROI(img2);
		}
	}
	//左下角
	for (int y=img2->height-1,j=1;j<=9;y=img2->height-1-cvRound(modeHeight*j),j++)
	{

		for (int x=0,i=1;i<=8;x=cvRound(modeWidth*i),i++)
		{

			CvRect cr=cvRect(x,y,modeWidth,modeHeight);///* 方形的最左角的x-坐标  */ /* 方形的最上或者最下角的y-坐标 */但是实际怎么是右下角
			cvSetImageROI(img2,cr);
			if((i==1&&j!=9)||(j<=2&&i!=8)||(i==7&&j!=9)||(j==8&&i!=8)||(i>2&&i<=5&&j>3&&j<=6)){
				cvZero(img2);
			}
			else{//白色
				cvSet(img2,cvScalarAll(255));
			}
			cvResetImageROI(img2);
		}
	}

	/*现在需要扩充边距*/
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
功能: 法划分网格
描述:  利用QR版本号划分网格
参数说明:    
Imgm：源图像

*************************************************/
IplImage * RecDect::drawGrid()//图像归一化
{
	//判断三个定位图形是否正确识别
	if (ModeSize>0)
	{	

	}else{
		cout<<"ModeSize为0，归一化操作失败"<<endl;
		return NULL;
	}
	CvSize QRSize;
	int msize=10;//新图像模块大小
	QRSize.height=number*msize;//每个模块是10个像素
	QRSize.width=number*msize;
	IplImage *QRImage=cvCreateImage(QRSize,img0->depth,img0->nChannels);
	
	CvRect QRcontent=cvRect(pt[1].x,pt[1].y,pt[0].x-pt[1].x+10,pt[2].y-pt[1].y+10);
	cvSetImageROI(img0,QRcontent);
	IplImage *canyImage=cvCreateImage(cvSize(462,462),img0->depth,img0->nChannels);

	ModeSize=462/(number);
	//cvCopy(img0,canyImage);
	cvResize(img0, canyImage); //缩放源图像到目标图像
	cvResetImageROI(img0);
	cvAdaptiveThreshold(canyImage,canyImage,255,CV_ADAPTIVE_THRESH_GAUSSIAN_C,CV_THRESH_BINARY_INV,101,0);//二值化
	IplImage *smapleImg=cvCloneImage(canyImage);
	/*Soble(canyImage,canyImage);
	cvShowImage("1",canyImage);
	cvWaitKey(0);*/
	cvCanny(canyImage,canyImage,10,255);
 // cvShowImage("1",canyImage);
	int startx,starty;//开始扫描位置
	//横向:从上到下，从左至右
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
	vector<int>line;//存储滑动范围坐标
	vector<int>rows;//存储行值
	vector<int>cols;//存储行值
	rows.push_back(starty);//将开始行放入
	cols.push_back(startx);
	//横向记录点 
	int modeHeight=(int)ModeSize;
	int range=3;//取滑动范围
	int count=0;//划线计数
	//hang扫描
	for(int i=modeHeight+starty;count<number;i=rows[count+1]+modeHeight,count++){
		if (count==number-1)
		{
			range=6;//取滑动范围
		}
		for (int j=i-range/2;j<i+range;j++)
		{
			line.push_back(j);//放入位置
		}
		int t=i-range;//t临时存放坐标
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
		line.clear();//每循环一次，释放一次
		rows.push_back(t);//放入最大值

	}
	//lie扫描
	line.clear();//
	int modeWidth=(int)ModeSize;
	count=0;
	for(int i=modeWidth+starty;count<number;i=cols[count+1]+modeWidth,count++){
		if (count==number-1)
		{
			range=6;//取滑动范围
		}
		for (int j=i-range/2;j<i+range;j++)
		{
			line.push_back(j);//放入位置
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
		line.clear();//每循环一次，释放一次
		cols.push_back(t);//放入最大值

	}
	//line.clear();//每循环一次，释放一次
	vector<int>().swap(line); //释放
	/*x下面进行切割效果*/
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
			uchar *cenptr=(uchar *)(smapleImg->imageData+center.y*smapleImg->widthStep+center.x);//采样中心点
			//uchar *cenptrlup=(uchar *)(smapleImg->imageData+(rows[j]+msize/4)*smapleImg->widthStep+cols[i]+msize/4);//采样中心点左上
			//uchar *cenptrldo=(uchar *)(smapleImg->imageData+(rows[j+1]-msize/4)*smapleImg->widthStep+cols[i]+msize/4);//采样中心点左下
			//uchar *cenptrrup=(uchar *)(smapleImg->imageData+(center.y-4)*smapleImg->widthStep+cols[i+1]-msize/4);//采样中心点右上
			uchar *cenptrrdo=(uchar *)(smapleImg->imageData+(center.y+2)*smapleImg->widthStep+center.x+2);//采样中心点右下
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

	vector<int>().swap(cols); //释放
	vector<int>().swap(rows); //释放
	/*现在需要重绘三个位置探测图形(加上周边白线)*/
	//左上角
	//int ModeSize
	for (int y=0,j=1;j<=8;y=cvRound(msize*j),j++)
	{

		for (int x=0,i=1;i<=8;x=cvRound(msize*i),i++)
		{

			CvRect cr=cvRect(x,y,msize,msize);///* 方形的最左角的x-坐标  */ /* 方形的最上或者最下角的y-坐标 */但是实际怎么是右下角
			cvSetImageROI(QRImage,cr);
			if((i==1&&j!=8)||(j==1&&i!=8)||(i==7&&j!=8)||(j==7&&i!=8)||(i>2&&i<=5&&j>2&&j<=5)){
				cvZero(QRImage);
			}
			else{//白色
				cvSet(QRImage,cvScalarAll(255));
			}
			cvResetImageROI(QRImage);
		}
	}
	//右上角
	for (int y=0,j=1;j<=8;y=cvRound(msize*j),j++)
	{

		for (int x=QRImage->width-1,i=1;i<=9;x=QRImage->width-1-cvRound(msize*i),i++)
		{

			CvRect cr=cvRect(x,y,msize,msize);///* 方形的最左角的x-坐标  */ /* 方形的最上或者最下角的y-坐标 */但是实际怎么是右下角
			cvSetImageROI(QRImage,cr);
			if((i<=2&&j!=8)||(j==1&&i!=9)||(i==8&&j!=8)||(j==7&&i!=9)||(i>=4&&i<=6&&j>=3&&j<6)){
				cvZero(QRImage);
			}
			else{//白色
				cvSet(QRImage,cvScalarAll(255));
			}
			cvResetImageROI(QRImage);
		}
	}
	//左下角
	for (int y=QRImage->height-1,j=1;j<=9;y=QRImage->height-1-cvRound(msize*j),j++)
	{

		for (int x=0,i=1;i<=8;x=cvRound(msize*i),i++)
		{

			CvRect cr=cvRect(x,y,msize,msize);///* 方形的最左角的x-坐标  */ /* 方形的最上或者最下角的y-坐标 */但是实际怎么是右下角
			cvSetImageROI(QRImage,cr);
			if((i==1&&j!=9)||(j<=2&&i!=8)||(i==7&&j!=9)||(j==8&&i!=8)||(i>2&&i<=5&&j>3&&j<=6)){
				cvZero(QRImage);
			}
			else{//白色
				cvSet(QRImage,cvScalarAll(255));
			}
			cvResetImageROI(QRImage);
		}
	}

	//cvNamedWindow("Grid2",1);
	//cvShowImage("Grid2",tst);

	cvReleaseImage(&smapleImg);
	IplImage *result=cvCloneImage(QRImage);//临时存放
	///*现在需要扩充边距*/
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
功能: 获取QR图像所在的区域
描述:  当首次获得QR所在区域坐标时候，需要截取其位置然后扩展到原图大小
此时已经获得pt,进行区域截取
pt vertices结构：
P2***P1
*     *
P3***P4
确定了四个角度之后需要对每一个图形进行进行区域校正采样识别
*************************************************/
void RecDect::AreaRotate()//获取QR图像所在的区域
{
	int w=img->width;//原来图像宽度
	int h=img->height;//原来图像宽度
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
	//现在已经获取到了区域，进行区域
	if (crt.x<0||crt.y<0||crt.height<0||crt.width<0||crt.x>=img->width||crt.y>=img->height)
	{
		cout<<"QR粗定位出错：矩形截取失败."<<endl;
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
	cvResize(cpy, img); //缩放源图像到目标图像
	cvReleaseImage(&cpy);
	/*下面是旋转校正程序，加强识别率*/
	double angle;
	//angle=CV_PI/2-AngleDect(img0);//确定旋转角度,放大确定
	double q=atan((double)(pt[2].y-pt[1].y)/(pt[2].x-pt[1].x));
	//	
	if(q<0)//右倾
		angle=(CV_PI/2+q)*180.0/CV_PI;
	else 
		angle=-(CV_PI/2-q)*180.0/CV_PI;
	if(fabs(q)<0.005||fabs(fabs(q)-CV_PI/2.0)<0.005){	
		cvSetImageCOI(img,1);//B色
		cvCopy(img,img0);  //提取B色
		cvSetImageCOI(img,0);//恢复
		angle=0;
		//if(fabs(angle)<0.05||fabs(fabs(angle)-1.57)<0.05){
		//图像hough直线水平或者竖直时或者未检测到斜率
	}else 
	{	

		FitRotate (img,angle);
		//cvShowImage("旋转后的图像",img);
		//转化灰度
		cvSetImageCOI(img,1);//B色
		cvCopy(img,img0);  //提取B色
		cvSetImageCOI(img,0);//恢复
		//	/*图像已经旋转校正，剩下则进行抽样*/
	}	
	RfindSquaresRect(0.36f,0.9);//获取图像轮廓定点坐标:此步获取图像大概位置,chongxin dingweidingdian pt weizhi,keyi youhua ,xianzai meishijian
	//可以尝试新方法定位顶点，不过图像要改变，因图像缩放了
	//for(int i=0;i<4;i++)
	//{
	//	pt[i].x=400*(pt[i].x*cos(angle*CV_PI/180.)-pt[i].y*sin(angle*CV_PI/180.)+0.5*w)/w;
	//	pt[i].y=400*(pt[i].x*sin(angle*CV_PI/180.)+pt[i].y*cos(angle*CV_PI/180.)+0.5*h)/h;
	//}
	//printf("%d",pt[0].x);
	//cvShowImage("截取后旋转的图像",img0);//cishi huidutu

}
/*
函数名：GetNonZero
说明：对canny后的图像计算每行（列）的边缘像素，用于图像归一化网格划分部分
参数：
Grayimage：canny后的图像
num：要计算的行（列）
type:0表示统计每行，1表示统计每列
返回值：每行（列）的边缘像素（255）的个数
*/
int RecDect::GetNonZero(const IplImage *Grayimage,int num,int type){
	int number=0;

	if(type){//type==0取列的非零值
		if (num<0||num>=Grayimage->height)
		{
			cout<<"读取非零数据时超出范围"<<endl;

			return 0;
		}
		uchar *ptr=(uchar *)(Grayimage->imageData);
		for (int y=0;y<Grayimage->height;y++){
			if(ptr[(y)*Grayimage->widthStep+num]==255)
				number++;
		}

		return number;
	}else{//type==0取行的非零值
		if (num<0||num>=Grayimage->width)
		{
			cout<<"读取非零数据时超出范围"<<endl;

			return 0;
		}
		uchar *ptr=(uchar *)(Grayimage->imageData+(num)*Grayimage->widthStep);
		for (int x=0;x<Grayimage->width;x++){
			if(ptr[x]==255) number++;
		}

		return number;
	}

}



