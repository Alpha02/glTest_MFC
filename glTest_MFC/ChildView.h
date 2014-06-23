
// ChildView.h : CChildView ��Ľӿ�
//


#pragma once


// CChildView ����

class CChildView : public CWnd
{
// ����
public:
	CChildView();
	//========OpenGL--------
	HGLRC m_hRC;    //Rendering Context��ɫ������  
	CClientDC* m_pDC;        //Device Context�豸������  
	BOOL InitializeOpenGL();    //��ʼ�� OpenGL  
	BOOL SetupPixelFormat();    //�������ظ�ʽ  
	void RenderScene();         //���Ƴ��� 
	//--------OpenGL--------
// ����
public:

// ����
public:

// ��д
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// ʵ��
public:
	virtual ~CChildView();

	// ���ɵ���Ϣӳ�亯��
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

