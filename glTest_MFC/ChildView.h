
// ChildView.h : CChildView 类的接口
//


#pragma once


// CChildView 窗口

class CChildView : public CWnd
{
// 构造
public:
	CChildView();
	//========OpenGL--------
	HGLRC m_hRC;    //Rendering Context着色描述表  
	CClientDC* m_pDC;        //Device Context设备描述表  
	BOOL InitializeOpenGL();    //初始化 OpenGL  
	BOOL SetupPixelFormat();    //设置像素格式  
	void RenderScene();         //绘制场景 
	//--------OpenGL--------
// 特性
public:

// 操作
public:

// 重写
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 实现
public:
	virtual ~CChildView();

	// 生成的消息映射函数
protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	int m_wide;
	int m_height;
//	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
};

