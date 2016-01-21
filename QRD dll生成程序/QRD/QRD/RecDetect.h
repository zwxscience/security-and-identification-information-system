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
#define  nbit	 3//jУ��λ
#define  margin	 50//����ͼ��Ԥ���ߴ�С
#define  margin2	10//��ȡԤ���ߴ�С
class RecDect{
public:
	RecDect(IplImage *dst);//���캯��
	~RecDect(){
		cvReleaseImage( &img );
		cvReleaseImage( &img0 );
		//cvReleaseMemStorage( &storage );
		
	}

	int WarpPerspective();//ͼ��͸�ӱ任
	int ImageStretchByHistogram(IplImage *src,IplImage *dst);//ͼ��Աȶ���ǿ
	int otsu(const IplImage *frame);//��ֵ��
	double angle( CvPoint* pt1, CvPoint* pt2, CvPoint* pt0 );//����ı��νǶ�
	CvSeq* findSquares4();//Ѱ���ı���λ��̽��ͼ��
	void drawSquares();	//���λ��̽��ͼ��
	int recognVersion(CvSeq* squares );	// ��ȡλ��̽��ͼ�Σ�ʶ��汾����������
	void RfindSquaresRect(float low,float high);//ʶ��QR���������������õ��ֶ�������,�����Ծ��ΰ���
    CvSeq* RfindSquaresP( IplImage* img );
	void vertexOrder(CvPoint pt2[]);//��������
	void GetAccVertex();//��ȡ��ȷQR����������������
	double AngleDect(const IplImage* img);//����hough������б���
	void FitRotate (IplImage* Img_old, double angle);//ͼ����ת
	void drawGridaverage();//ͼ���һ����ƽ������
	IplImage * drawGrid();
	void AreaRotate();//��ȡQRͼ�����ڵ�������ת
	int GetNonZero(const IplImage *Grayimage,int num,int type);//��ȡ��Ե����
	int minPoint(unsigned int a,unsigned int b,unsigned int c,unsigned int d);//Ѱ�Ҷ�����С�㣨x��y��
	int maxPoint(unsigned int a,unsigned int b,unsigned int c,unsigned int d);//Ѱ�Ҷ������㣨x��y��
public://��ű���
	IplImage* img;//�����ͨ��ͼ��
	IplImage* img0;//�����ɫͨ��ͼ��
private:
	float ModeSize;
	CvPoint pt[4];//��ž����ĸ�����
	/*˵����
	���ھ����ĵ������Լ���������Ͻǿ�ʼ
	1******0
	*      *
	*      * 
	2******3
	����λ��̽��ͼ�ε�Լ���������ң����ϵ���
	corner1*****corner2
	   *          *
	   *          *
	corner3*****corner4
	������һ����Ϊ��
	*/
	CvPoint corner1[4],corner2[4],corner3[4],corner4[4];//���QR����У��ͼ������,��һ��Ϊ��
	CvPoint corner1P,corner2P,corner3P,corner4P;//��Ŷ�Ӧ�������ܳ������
	int number;//�������
	int version;//�汾��Ϣ
	float WUL,WUR;//����λ��̽��ͼ�δ�С

};
#endif