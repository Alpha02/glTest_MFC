
// ChildView.cpp : CChildView 类的实现
//

#include "stdafx.h"
#include "glTest_MFC.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
	//========OpenGL--------
	m_hRC=NULL;
	m_pDC=NULL;
	//========OpenGL--------
	m_wide = 0;
	m_height = 0;
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_SIZE()
//	ON_WM_DRAWITEM()
END_MESSAGE_MAP()



// CChildView 消息处理程序

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), NULL);

	return TRUE;
}

void CChildView::OnPaint() 
{
	CPaintDC dc(this); // 用于绘制的设备上下文
	
	// TODO: 在此处添加消息处理程序代码
	RenderScene();
	// 不要为绘制消息而调用 CWnd::OnPaint()
}
//========OpenGL--------
BOOL CChildView::SetupPixelFormat()  
{  
	static PIXELFORMATDESCRIPTOR pfd =   
	{  
		sizeof(PIXELFORMATDESCRIPTOR),  // pfd结构的大小   
		1,                              // 版本号   
		PFD_DRAW_TO_WINDOW |            // 支持在窗口中绘图   
		PFD_SUPPORT_OPENGL |            // 支持 OpenGL   
		PFD_DOUBLEBUFFER,               // 双缓存模式   
		PFD_TYPE_RGBA,                  // RGBA 颜色模式   
		24,                             // 24 位颜色深度   
		0, 0, 0, 0, 0, 0,               // 忽略颜色位   
		0,                              // 没有非透明度缓存   
		0,                              // 忽略移位位   
		0,                              // 无累计缓存   
		0, 0, 0, 0,                     // 忽略累计位   
		32,                             // 32 位深度缓存       
		0,                              // 无模板缓存   
		0,                              // 无辅助缓存   
		PFD_MAIN_PLANE,                 // 主层   
		0,                              // 保留   
		0, 0, 0                         // 忽略层,可见性和损毁掩模   

	};  
	int pixelFormat;  
	// 为设备描述表得到最匹配的像素格式   
	if((pixelFormat = ChoosePixelFormat(m_pDC->GetSafeHdc(), &pfd)) == 0)  
	{  
		MessageBox( _T("ChoosePixelFormat failed") );  
		return FALSE;  
	}  
	// 设置最匹配的像素格式为当前的像素格式   
	if(SetPixelFormat(m_pDC->GetSafeHdc(), pixelFormat, &pfd) == FALSE)  
	{  
		MessageBox( _T("SetPixelFormat failed") );  
		return FALSE;  
	}  
	return TRUE;  
}  
BOOL CChildView::InitializeOpenGL(void)  
{  
	PIXELFORMATDESCRIPTOR pfd;  
	int n;  
	m_pDC=new CClientDC(this);  
	ASSERT(m_pDC != NULL);  
	// 设置当前的绘图像素格式  
	if(!SetupPixelFormat())  
	{  
		return FALSE;  
	}  

	n=::GetPixelFormat(m_pDC->GetSafeHdc());  
	::DescribePixelFormat(m_pDC->GetSafeHdc(), n,sizeof(pfd),&pfd);  
	// 创建绘图描述表  
	m_hRC=wglCreateContext(m_pDC->GetSafeHdc());  
	if(m_hRC == NULL)  
	{  
		return FALSE;  
	}  
	// 使绘图描述表为当前调用现程的当前绘图描述表  
	if( wglMakeCurrent(m_pDC->GetSafeHdc(),m_hRC) == FALSE)  
	{  
		return FALSE;  
	}  
	glClearDepth(1.0f);  
	glEnable(GL_DEPTH_TEST);  
	return TRUE;  
}  
//========OpenGL--------

int CChildView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:
	//========OpenGL--------
	if ( InitializeOpenGL())  
	{  
		return 0;  
	}  
	//========OpenGL--------
	return 0;
}



void CChildView::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码  
	m_wide = cx;    //m_wide为在CVCOpenGL2View类中添加的表示视口宽度的成员变量  
	m_height = cy;  //m_height为在CVCOpenGL2View类中添加的表示视口高度的成员变量  
	//避免除数为0  
	if(m_height==0)  
	{  
		m_height=1;  
	}  
	//设置视口与窗口的大小  
	glViewport(0,0,m_wide,m_height);  
}  
//绘制一个正方体
void CChildView::RenderScene(void)  
{  
    //设置清屏颜色为黑色  
    glClearColor(0.0f,0.0f,0.0f,0.0f);  
    //清除颜色缓冲区和深度缓冲区  
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  
    //透视投影变换  
	double m_tFovy=45;
	double m_zNear=0.1,m_zFar=1000;
    glMatrixMode(GL_PROJECTION);  
    glLoadIdentity();  
    gluPerspective(m_tFovy, (double)m_wide/(double)m_height,m_zNear,m_zFar);  
    //视角变换  
    glMatrixMode(GL_MODELVIEW);  
    glLoadIdentity();  
    gluLookAt(1,1,2,0,0,0,0,1,0);  
    //矩阵堆栈函数，和glPopMatrix()相对应  
    glPushMatrix();  
  
    glBegin( GL_LINES );  
    glColor3d(1.0, 0.0, 0.0);   // X轴 红色  
    glVertex3d(0.0, 0.0, 0.0);   
    glVertex3d(2.0, 0.0, 0.0);  
    glColor3d(0.0, 1.0, 0.0);   // Y轴 绿色  
    glVertex3d(0.0, 0.0, 0.0);  
    glVertex3d(0.0, 2.0, 0.0);  
    glColor3d(0.0, 0.0, 1.0);   // Z轴 蓝色  
    glVertex3d(0.0, 0.0, 0.0);   
    glVertex3d(0.0, 0.0, 2.0);  
    glEnd();  
  
    glColor3f(1.0, 1.0, 1.0);  
	glutWireCube(0.5);
  
    glPopMatrix();
    glFinish();  
    SwapBuffers(wglGetCurrentDC());  
}  

