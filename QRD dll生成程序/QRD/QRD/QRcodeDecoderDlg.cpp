// QRcodeDecoderDlg.cpp : implementation file
//

#include "stdafx.h"
#include "QRcodeDecoder.h"
#include "QRcodeDecoderDlg.h"
#include"RecDetect.h"
#include <opencv2/video/background_segm.hpp>
#include <opencv2/legacy/blobtrack.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc_c.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CQRcodeDecoderDlg dialog

CQRcodeDecoderDlg::CQRcodeDecoderDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CQRcodeDecoderDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CQRcodeDecoderDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CQRcodeDecoderDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CQRcodeDecoderDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CQRcodeDecoderDlg, CDialog)
	//{{AFX_MSG_MAP(CQRcodeDecoderDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_FILE, OnButtonFile)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CQRcodeDecoderDlg message handlers

BOOL CQRcodeDecoderDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
    flag_draw=false;

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CQRcodeDecoderDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CQRcodeDecoderDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
	if(flag_draw)//位图重绘
	{
		CDC * pDC=this->GetDC();
		pDC->StretchBlt(160, 45, nShowSize, nShowSize, QR_image->m_pDC, 0, 0, QR_image->nWidth, QR_image->nHeight, SRCCOPY);
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CQRcodeDecoderDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CQRcodeDecoderDlg::OnButtonFile() 
{
	// TODO: Add your control notification handler code here

	//选择文件对话框
	CString FilePathName;
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, 
		"支持的格式 (*.bmp)|*.bmp|All Files (*.*)|*.*||", NULL );
/*
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, 
		"支持的格式 (*.bmp *.jpg)|*.bmp;*.jpg;*.jpeg|All Files (*.*)|*.*||", NULL );
*/
	if(dlg.DoModal()==IDOK)
	{
		//获取选择的文件的路径显示
		FilePathName=dlg.GetPathName();
		GetDlgItem(IDC_EDIT_FILE)->SetWindowText(FilePathName);
				IplImage *src=0, *dst=0; 
		src=cvLoadImage(FilePathName,1);
		if( !src )
		{
			printf("Couldn't load %s\n", FilePathName );
		MessageBox(_T("红外QR码载入错误"),_T("QR码识别"));
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
			MessageBox(_T("红外QR码转化过程出错"),_T("QR码识别"));
				
		cvReleaseImage( &src );		////释放图像
		cvReleaseImage( &dst );
	
			return;
		}
		QR_image = new QRcodeImage(loadImage);
		//cvReleaseImage(&loadImage);
		QR_image->GetImageData();

		m_nVersion = QR_image->finderPattern->m_version;
		m_nCodeSize = m_nVersion * 4 +17;
		for(int i=0;i<m_nCodeSize;i++)
			for(int j=0;j<m_nCodeSize;j++)
				m_CodeData[i][j]=QR_image->bitMatrix[i][j];
		
		//缩放图像，显示在对话框中
		nShowSize=120;
		CDC * pDC=this->GetDC();
		pDC->StretchBlt(160, 45, nShowSize, nShowSize, QR_image->m_pDC, 0, 0, QR_image->nWidth, QR_image->nHeight, SRCCOPY);
		flag_draw=true;

		
		//解码
		QR_Decode = new ContentDecoder;
		QR_Decode->DecodeData(m_nCodeSize,m_nVersion,m_CodeData);

		//显示结果
		GetDlgItem(IDC_EDIT_TEXT)->SetWindowText(QR_Decode->m_strData);//"由于解码功能尚未完成，暂时无法显示!!!"
		char s[10];
		itoa(QR_Decode->m_nVersion,s,10);
		GetDlgItem(IDC_STATIC_VERSION)->SetWindowText("版本号："+(CString)s);
		CString str;
		switch(QR_Decode->m_nLevel)
		{
		case QR_LEVEL_L:str="L(%7)";break;
		case QR_LEVEL_M:str="M(%15)";break;
		case QR_LEVEL_Q:str="Q(%25)";break;
		case QR_LEVEL_H:str="H(%30)";break;
		}
		GetDlgItem(IDC_STATIC_LEVEL)->SetWindowText("纠错等级："+str);
	
		
		cvReleaseImage( &src );		////释放图像
		cvReleaseImage( &dst );
		cvReleaseImage( &loadImage );
	}
}
