#ifndef _STDIO_H_
#include "stdafx.h"
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/imgproc/imgproc_c.h"
#include "opencv2/highgui/highgui.hpp"
#include <vector>
using namespace std;
#define _STDIO_H_

#define GrayScale 256
#define  nbit	 3//j校验位
#define  margin	 50//生成图像预留边大小
#define  margin2	10//截取预留边大小
class RecDect{
public:
	RecDect(IplImage *dst);//构造函数
	~RecDect(){
		cvReleaseImage( &img );
		cvReleaseImage( &img0 );
		//cvReleaseMemStorage( &storage );
		
	}

	int WarpPerspective();//图像透视变换
	int ImageStretchByHistogram(IplImage *src,IplImage *dst);//图像对比度增强
	int otsu(const IplImage *frame);//阈值化
	double angle( CvPoint* pt1, CvPoint* pt2, CvPoint* pt0 );//检测四边形角度
	CvSeq* findSquares4();//寻找四边形位置探测图形
	void drawSquares();	//输出位置探测图形
	int recognVersion(CvSeq* squares );	// 提取位置探测图形，识别版本，计算网格
	void RfindSquaresRect(float low,float high);//识别QR码整体轮廓并返得到粗顶点坐标,这是以矩形包含
    CvSeq* RfindSquaresP( IplImage* img );
	void vertexOrder(CvPoint pt2[]);//顶点重排
	void GetAccVertex();//获取精确QR整体轮廓顶点坐标
	double AngleDect(const IplImage* img);//利用hough进行倾斜检测
	void FitRotate (IplImage* Img_old, double angle);//图像旋转
	void drawGridaverage();//图像归一化（平均法）
	IplImage * drawGrid();
	void AreaRotate();//获取QR图像所在的区域并旋转
	int GetNonZero(const IplImage *Grayimage,int num,int type);//获取边缘数量
	int minPoint(unsigned int a,unsigned int b,unsigned int c,unsigned int d);//寻找顶点最小点（x或y）
	int maxPoint(unsigned int a,unsigned int b,unsigned int c,unsigned int d);//寻找顶点最大点（x或y）
public://存放变量
	IplImage* img;//存放三通道图像
	IplImage* img0;//存放绿色通道图像
private:
	float ModeSize;
	CvPoint pt[4];//存放矩形四个顶点
	/*说明：
	对于矩形四点坐标的约定，从右上角开始
	1******0
	*      *
	*      * 
	2******3
	对于位置探测图形的约定，从左到右，从上到下
	corner1*****corner2
	   *          *
	   *          *
	corner3*****corner4
	且其中一个必为空
	*/
	CvPoint corner1[4],corner2[4],corner3[4],corner4[4];//存放QR矩形校正图像坐标,有一个为空
	CvPoint corner1P,corner2P,corner3P,corner4P;//存放对应轮廓的周长和面积
	int number;//网格格数
	int version;//版本信息
	float WUL,WUR;//左右位置探测图形大小

};
#endif