// QRcodeImage.cpp: implementation of the QRcodeImage class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "QRcodeDecoder.h"
#include "QRcodeImage.h"


#include<vector>
using std::vector;
#include<math.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
void FillBitmapInfo( BITMAPINFO* bmi, int width, int height, int bpp, int origin)
{
	assert( bmi && width >= 0 && height >= 0 && (bpp == 8 || bpp == 24 || bpp == 32));

	BITMAPINFOHEADER* bmih = &(bmi->bmiHeader);

	memset( bmih, 0, sizeof(*bmih));
	bmih->biSize = sizeof(BITMAPINFOHEADER);
	bmih->biWidth = width;
	bmih->biHeight = origin ? abs(height) : -abs(height);
	bmih->biPlanes = 1;
	bmih->biBitCount = (unsigned short)bpp;
	bmih->biCompression = BI_RGB;

	if( bpp == 8 )
	{
		RGBQUAD* palette = bmi->bmiColors;
		int i;
		for( i = 0; i < 256; i++ )
		{
			palette[i].rgbBlue = palette[i].rgbGreen = palette[i].rgbRed = (BYTE)i;
			palette[i].rgbReserved = 0;
		}
	}
}

CBitmap * IplImage2CBitmap(const IplImage *pImage)
{
	if( pImage && pImage->depth == IPL_DEPTH_8U )
	{
	
		HDC hDC=::GetDC(NULL);
		uchar buffer[sizeof(BITMAPINFOHEADER) + 1024];
		BITMAPINFO* bmi = (BITMAPINFO*)buffer;
		int bmp_w = pImage->width, bmp_h = pImage->height;
		FillBitmapInfo( bmi, bmp_w, bmp_h, pImage->depth*pImage->nChannels, pImage->origin );

		char *pBits=NULL;
		HBITMAP hBitmap=CreateDIBSection(hDC,bmi,DIB_RGB_COLORS,(void**)&pBits,NULL,0);
		memcpy(pBits,pImage->imageData,pImage->imageSize);
		CBitmap *pBitmap=new CBitmap;
		pBitmap->Attach(hBitmap);
		return pBitmap;
	}
	else
		return NULL;
}



QRcodeImage::QRcodeImage()
{
	DECIMAL_POINT=21;
}

QRcodeImage::QRcodeImage( IplImage *pImage)
{
	DECIMAL_POINT=21;
	//����ͼƬ����ȡλֵ
	//HBITMAP hbmp = (HBITMAP)::LoadImage(AfxGetInstanceHandle(), FilePathName, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION|LR_LOADFROMFILE);
//	m_pBitmap = new CBitmap;
	//m_pBitmap->Attach(hbmp);
	m_pBitmap =IplImage2CBitmap(pImage);
	//��ȡͼƬ��Ϣ
	BITMAP   BmpInfo;   
	m_pBitmap->GetBitmap(&BmpInfo);
	nWidth=BmpInfo.bmWidth;
	nHeight=BmpInfo.bmHeight;

	//����ͼƬ����
	//int ok=m_pBitmap->GetBitmapBits(2000,m_CodeData);

	//�����ͼ�豸
	m_pDC = new CDC;
	m_pDC->CreateCompatibleDC(NULL);
	m_pOldBitmap = m_pDC->SelectObject(m_pBitmap);
}

QRcodeImage::~QRcodeImage()
{

}

void QRcodeImage::GetImageData()
{
	DECIMAL_POINT=21;
	filterImage();
	
	finderPattern=new FinderPattern();
	finderPattern->findFinderPattern(bitmap,nWidth,nHeight,DECIMAL_POINT);

	alignmentPattern=new AlignmentPattern();
	alignmentPattern->findAlignmentPattern(bitmap,nWidth,nHeight,finderPattern,DECIMAL_POINT);


	//Creating sampling grid
	//samplingGrid = getSamplingGrid2_6(finderPattern, alignmentPattern);
	samplingGrid = getSamplingGrid(finderPattern, alignmentPattern);
	
	//Reading grid
	getQRCodeMatrix(samplingGrid);

/*	boolean[][] qRCodeMatrix = null;
	try {
		qRCodeMatrix = getQRCodeMatrix(bitmap, samplingGrid);
	} catch (ArrayIndexOutOfBoundsException e) {
		throw new SymbolNotFoundException("Sampling grid exceeded image boundary");
	}
	//canvas.drawMatrix(qRCodeMatrix);
	return new QRCodeSymbol(qRCodeMatrix);
*/
}

//�Ҷȹ���
void QRcodeImage::filterImage()
{
	int x,y,i,j;

	//����ͼ�ε���
	int ** intImage=new int * [nWidth];
	for(i=0;i<nWidth;i++)
		intImage[i]=new int[nHeight];
	for (y = 0; y < nHeight; y++)
	{
		for (x = 0; x < nWidth; x++)
		{
			intImage[x][y] = m_pDC->GetPixel(x,y);
		}
	}

	int longSide = (nWidth < nHeight) ? nHeight : nWidth;
	DECIMAL_POINT = (int)(23-sqrt((float)longSide/256));
	
	//image to gray scale
	///////////////////////////////////////////////////////////////
	for (y = 0; y < nHeight; y++) {
		for (x = 0; x < nWidth; x++) {
			int r = intImage[x][y] >> 16 & 0xFF;
			int g = intImage[x][y] >> 8 & 0xFF;
			int b = intImage[x][y] & 0xFF;
			int m = (r * 30 + g * 59 + b * 11) / 100;
			intImage[x][y] = m;
		}
	}

	//get middle brightness per area
	/////////////////////////////////////////////////////////////////
	int numSqrtArea = 4;
	//obtain middle brightness((min + max) / 2) per area
	int areaWidth = nWidth / numSqrtArea;
	int areaHeight = nHeight / numSqrtArea;

	int *** minmax = new int **[numSqrtArea];
	for(i=0;i<numSqrtArea;i++)
	{
		minmax[i]=new int * [numSqrtArea];
		for(j=0;j<numSqrtArea;j++)
			minmax[i][j]=new int[2];
	}
	//int[][][] minmax = new int[numSqrtArea][numSqrtArea][2];

	int ax,ay,dy,dx;
	for (ay = 0; ay < numSqrtArea; ay++) {
		for (ax = 0; ax < numSqrtArea; ax++) {
			minmax[ax][ay][0] = 0xFF;
			for (int dy = 0; dy < areaHeight; dy++) {
				for (int dx = 0; dx < areaWidth; dx++) {
					int target = intImage[areaWidth * ax + dx][areaHeight * ay + dy];
					if (target < minmax[ax][ay][0]) minmax[ax][ay][0] = target;
					if (target > minmax[ax][ay][1]) minmax[ax][ay][1] = target;
				}
			}
			//minmax[ax][ay][0] = (minmax[ax][ay][0] + minmax[ax][ay][1]) / 2;
		}
	}

	int ** middle = new int * [numSqrtArea];
	for(i=0;i<numSqrtArea;i++)
		middle[i]=new int[numSqrtArea];
	//int[][] middle =  new int[numSqrtArea][numSqrtArea];

	for (ay = 0; ay < numSqrtArea; ay++) {
		for (ax = 0; ax < numSqrtArea; ax++) {
			middle[ax][ay] = (minmax[ax][ay][0] + minmax[ax][ay][1]) / 2;
		}
	}
	delete []minmax;
		minmax=NULL;
	//gray scale to bitmap
	///////////////////////////////////////////////////////////////
	bitmap = new BYTE *[nWidth];
	for(i=0;i<nWidth;i++)
		bitmap[i]=new BYTE[nHeight];
	//boolean[][] bitmap = new boolean[nWidth][nHeight];

	for (ay = 0; ay < numSqrtArea; ay++) {
		for (ax = 0; ax < numSqrtArea; ax++) {
			for (dy = 0; dy < areaHeight; dy++) {
				for (dx = 0; dx < areaWidth; dx++) {
					bitmap[areaWidth * ax + dx][areaHeight * ay + dy] = (intImage[areaWidth * ax + dx][areaHeight * ay + dy] < middle[ax][ay]) ? true : false;
				}
			}
		}
	}

	delete []middle;
	delete []intImage;
	middle=NULL;
	intImage=NULL;
}


SamplingGrid QRcodeImage::getSamplingGrid(FinderPattern * finderPattern, AlignmentPattern * alignmentPattern)
{

	Point ** centers = alignmentPattern->m_centers;

	int version = finderPattern->m_version;
	int sqrtCenters = (version / 7) + 2;
	
	centers[0][0] = finderPattern->m_center[UL];
	centers[sqrtCenters-1][0] = finderPattern->m_center[UR];
	centers[0][sqrtCenters-1] = finderPattern->m_center[DL];
	//int sqrtNumModules = finderPattern.getSqrtNumModules(); /// The number of modules per one side is obtained
	int sqrtNumArea = sqrtCenters-1;
	
	SamplingGrid samplingGrid = SamplingGrid(sqrtNumArea);

	Line baseLineX, baseLineY, gridLineX, gridLineY;

	//int logicalDistance = alignmentPattern.getLogicalDistance();
	Axis axis = Axis(finderPattern->m_sincos, finderPattern->m_moduleSize[UL],DECIMAL_POINT);
	ModulePitch modulePitch;

	// for each area :
	for (int ay = 0; ay < sqrtNumArea; ay++)
	{
		for (int ax = 0; ax < sqrtNumArea; ax++)
		{
			modulePitch = ModulePitch(); // Housing to order 
			baseLineX = Line();
			baseLineY = Line();
			axis.setModulePitch(finderPattern->m_moduleSize[UL]);

			alignmentPattern->getLogicalCenter(finderPattern);
			Point ** logicalCenters= alignmentPattern->logicalCenters;

			Point upperLeftPoint	=	centers[ax][ay];
			Point upperRightPoint	=	centers[ax+1][ay];
			Point lowerLeftPoint	=	centers[ax][ay+1];
			Point lowerRightPoint	=	centers[ax+1][ay+1];

			Point logicalUpperLeftPoint	=	logicalCenters[ax][ay];
			Point logicalUpperRightPoint	=	logicalCenters[ax+1][ay];
			Point logicalLowerLeftPoint	=	logicalCenters[ax][ay+1];
			Point logicalLowerRightPoint	=	logicalCenters[ax+1][ay+1];

			if(ax==0 && ay==0) // left upper corner
			{
				if (sqrtNumArea == 1) {
					upperLeftPoint = axis.translate(upperLeftPoint,-3,-3);
					upperRightPoint = axis.translate(upperRightPoint,3,-3);
					lowerLeftPoint = axis.translate(lowerLeftPoint,-3,3);
					lowerRightPoint = axis.translate(lowerRightPoint,6,6);

					logicalUpperLeftPoint.translate(-6,-6);
					logicalUpperRightPoint.translate(3,-3);
					logicalLowerLeftPoint.translate(-3,3);						
					logicalLowerRightPoint.translate(6,6);						
				}
				else {
					upperLeftPoint = axis.translate(upperLeftPoint,-3,-3);
					upperRightPoint = axis.translate(upperRightPoint,0,-6);
					lowerLeftPoint = axis.translate(lowerLeftPoint,-6,0);

					logicalUpperLeftPoint.translate(-6,-6);
					logicalUpperRightPoint.translate(0,-6);
					logicalLowerLeftPoint.translate(-6,0);
				}
			}
			else if(ax==0 && ay==sqrtNumArea-1) // left bottom corner
			{
				upperLeftPoint = axis.translate(upperLeftPoint,-6,0);
				lowerLeftPoint = axis.translate(lowerLeftPoint,-3,3);
				lowerRightPoint = axis.translate(lowerRightPoint, 0, 6);


				logicalUpperLeftPoint.translate(-6,0);
				logicalLowerLeftPoint.translate(-6,6);
				logicalLowerRightPoint.translate(0,6);
			}
			else if(ax==sqrtNumArea-1 && ay==0) // right upper corner
			{
				upperLeftPoint = axis.translate(upperLeftPoint,0,-6);
				upperRightPoint = axis.translate(upperRightPoint,3,-3);
				lowerRightPoint = axis.translate(lowerRightPoint,6,0);

				logicalUpperLeftPoint.translate(0,-6);
				logicalUpperRightPoint.translate(6,-6);
				logicalLowerRightPoint.translate(6,0);
			}
			else if(ax==sqrtNumArea-1 && ay==sqrtNumArea-1) // right bottom corner
			{
				lowerLeftPoint = axis.translate(lowerLeftPoint,0,6);
				upperRightPoint = axis.translate(upperRightPoint,6,0);
				lowerRightPoint = axis.translate(lowerRightPoint,6,6);

				logicalLowerLeftPoint.translate(0,6);
				logicalUpperRightPoint.translate(6,0);
				logicalLowerRightPoint.translate(6,6);
			}
			else if(ax==0) // left side
			{
				upperLeftPoint = axis.translate(upperLeftPoint,-6,0);
				lowerLeftPoint = axis.translate(lowerLeftPoint,-6,0);

				logicalUpperLeftPoint.translate(-6,0);
				logicalLowerLeftPoint.translate(-6,0);

			}
			else if(ax==sqrtNumArea-1) // right
			{
				upperRightPoint = axis.translate(upperRightPoint,6,0);
				lowerRightPoint = axis.translate(lowerRightPoint,6,0);

				logicalUpperRightPoint.translate(6,0);
				logicalLowerRightPoint.translate(6,0);
			}
			else if(ay==0) // top
			{
				upperLeftPoint = axis.translate(upperLeftPoint,0,-6);
				upperRightPoint = axis.translate(upperRightPoint,0,-6);

				logicalUpperLeftPoint.translate(0,-6);
				logicalUpperRightPoint.translate(0,-6);

			}
			else if(ay==sqrtNumArea-1) // bottom
			{
				lowerLeftPoint = axis.translate(lowerLeftPoint,0,6);
				lowerRightPoint = axis.translate(lowerRightPoint,0,6);

				logicalLowerLeftPoint.translate(0,6);
				logicalLowerRightPoint.translate(0,6);
			}
			
			if(ax==0)
			{
				logicalUpperRightPoint.translate(1,0);
				logicalLowerRightPoint.translate(1,0);
			}
			else
			{
				logicalUpperLeftPoint.translate(-1,0);
				logicalLowerLeftPoint.translate(-1,0);
			}

			if(ay==0)
			{
				logicalLowerLeftPoint.translate(0,1);
				logicalLowerRightPoint.translate(0,1);
			}
			else
			{
				logicalUpperLeftPoint.translate(0,-1);
				logicalUpperRightPoint.translate(0,-1);
			}
			
			int logicalWidth=logicalUpperRightPoint.x-logicalUpperLeftPoint.x;
			int logicalHeight=logicalLowerLeftPoint.y-logicalUpperLeftPoint.y;

			if (version < 7) {
				logicalWidth += 3;
				logicalHeight += 3;
				
			}
			modulePitch.top = getAreaModulePitch(upperLeftPoint, upperRightPoint, logicalWidth-1);
			modulePitch.left = getAreaModulePitch(upperLeftPoint, lowerLeftPoint, logicalHeight-1);
			modulePitch.bottom = getAreaModulePitch(lowerLeftPoint, lowerRightPoint, logicalWidth-1);
			modulePitch.right = getAreaModulePitch(upperRightPoint, lowerRightPoint, logicalHeight-1);

			baseLineX.setP1(upperLeftPoint);
			baseLineY.setP1(upperLeftPoint);
			baseLineX.setP2(lowerLeftPoint);
			baseLineY.setP2(upperRightPoint);

			samplingGrid.initGrid(ax,ay,logicalWidth,logicalHeight);

			for (int i = 0; i < logicalWidth; i++)
			{
				gridLineX = Line(baseLineX.getP1(), baseLineX.getP2());

				axis.setOrigin(gridLineX.getP1());
				axis.setModulePitch(modulePitch.top);
				gridLineX.setP1(axis.translate(i,0));

				axis.setOrigin(gridLineX.getP2());
				axis.setModulePitch(modulePitch.bottom);
				gridLineX.setP2(axis.translate(i,0));

				samplingGrid.setXLine(ax,ay,i,gridLineX);
			}

			for (int i = 0; i < logicalHeight; i++)
			{
				gridLineY = Line(baseLineY.getP1(), baseLineY.getP2());

				axis.setOrigin(gridLineY.getP1());
				axis.setModulePitch(modulePitch.left);
				gridLineY.setP1(axis.translate(0,i));

				axis.setOrigin(gridLineY.getP2());
				axis.setModulePitch(modulePitch.right);
				gridLineY.setP2(axis.translate(0,i));

				samplingGrid.setYLine(ax,ay,i,gridLineY);
			}
		}
	}

	return samplingGrid;
}

//get module pitch in single area
int QRcodeImage::getAreaModulePitch(Point start, Point end, int logicalDistance)
{
	Line tempLine;
	tempLine = Line(start, end);
	int realDistance = tempLine.getLength();
	int modulePitch = (realDistance << DECIMAL_POINT) / logicalDistance;
	return modulePitch;
}

//gridLines[areaX][areaY][direction(x=0,y=1)][EachLines]	
void QRcodeImage::getQRCodeMatrix(SamplingGrid gridLines)
{
	//int gridSize = gridLines.getWidth() * gridLines.getWidth(0,0);
	int gridSize = gridLines.getTotalWidth();

	Point bottomRightPoint;

	bitMatrix=new BYTE * [gridSize];
	for(int i=0;i<gridSize;i++)
		bitMatrix[i]=new BYTE[gridSize];
	//boolean[][] sampledMatrix = new boolean[gridSize][gridSize];

	for (int ay = 0; ay < gridLines.getHeight(); ay++)
	{
		for (int ax = 0; ax < gridLines.getWidth(); ax++)
		{
			//vector sampledPoints = new Vector(); //only for visualize;
			for (int y = 0; y < gridLines.getHeight(ax,ay); y++)
			{
				for (int x = 0; x < gridLines.getWidth(ax,ay); x++)
				{
					int x1 = gridLines.getXLine(ax,ay,x).getP1().x;
					int y1 = gridLines.getXLine(ax,ay,x).getP1().y;
					int x2 = gridLines.getXLine(ax,ay,x).getP2().x;
					int y2 = gridLines.getXLine(ax,ay,x).getP2().y;
					int x3 = gridLines.getYLine(ax,ay,y).getP1().x;
					int y3 = gridLines.getYLine(ax,ay,y).getP1().y;
					int x4 = gridLines.getYLine(ax,ay,y).getP2().x;
					int y4 = gridLines.getYLine(ax,ay,y).getP2().y;
					
					int e = (y2 - y1) * (x3 - x4) - (y4 - y3) * (x1 - x2);
					int f = (x1 * y2 - x2 * y1) * (x3 - x4) - (x3 * y4 - x4 * y3) * (x1 - x2);
					int g = (x3 * y4 - x4 * y3) * (y2 - y1) - (x1 * y2 - x2 * y1) * (y4 - y3);
					bitMatrix[gridLines.getX(ax, x)][gridLines.getY(ay, y)] = bitmap[f / e][g / e];
					if ((ay == gridLines.getHeight() -1 && ax == gridLines.getWidth() - 1) &&
							y == gridLines.getHeight(ax, ay) - 1 && x == gridLines.getWidth(ax, ay) -1)
						bottomRightPoint = Point(f / e,g / e);
				}
			}
		}
	}

	if ((bottomRightPoint.x>nWidth-1 || bottomRightPoint.y>nHeight-1))
	{
		//AfxMessageBox("Sampling grid pointed out of image");
		//exit(0);
	}
//	
	//return bitMatrix;
}