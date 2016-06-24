// opengl_draw.cpp : ���� �����Դϴ�.
//
#include "stdafx.h"
#include "gitc_termp.h"
#include "opengl_draw.h"
#include "afxdialogex.h"
#include "gitc_termpDlg.h"
#include <vector>
#include"ListNode.h"


extern unsigned int total_size;
extern ListNode* clptr;

opengl_draw::KEYBOARD keyboard;
opengl_draw::VIEW view;
opengl_draw::MOUSE mouse;

// opengl_draw ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(opengl_draw, CDialogEx)

opengl_draw::opengl_draw(CWnd* pParent /*=NULL*/)
: CDialogEx(opengl_draw::IDD, pParent)
{

}

opengl_draw::~opengl_draw()
{
}

void opengl_draw::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(opengl_draw, CDialogEx)
	ON_WM_SIZE()
	ON_WM_DESTROY()
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSEWHEEL()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_KEYUP()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()


// opengl_draw �޽��� ó�����Դϴ�.

void opengl_draw::GLResize(int cx, int cy)
{
	GLfloat fAspect;
	if (cy == 0)
		cy = 1;
	glViewport(0, 0, cx, cy);
	fAspect = (GLfloat)cx / (GLfloat)cy;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity(); // ���� ���ķ� �ʱ�ȭ ���� / why? ����� ���� buffer�� �����ϴ� ������ ���� �����ϱ� ���ؼ� glLoadIdentity()�� ����

	gluPerspective(60.0f, fAspect, 1.0f, 10000.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void opengl_draw::GLRenderScene()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_POINT_SMOOTH); // ���� antialiasing �� antialiasing�� overlap ������ �����ϴ� ��, �簢������ ��Ÿ�� �ʴ´�. 
	//glEnable(GL_SMOOTH);// ���� ������ ��ȭ ��Ų�� <->gl_flat�� ���ڸ� vertex�� ����� �����ȴ�.
	//glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	
	glPushMatrix();
	glLoadIdentity(); // matrix �ʱ�ȭ.
	gluLookAt(100.0, 100.0, 100.0, 0.0, 0.0, 0.0, -1.0, 1.0, -1.0);
	glTranslatef(view.TranslateX, -view.TranslateY, 0.0f);
	glScalef(view.ZoomScale, view.ZoomScale, view.ZoomScale);
	glRotatef(view.RotateX, 1.0f, 0.0f, 0.0f);
	glRotatef(view.RotateY, 0.0f, 1.0f, 0.0f);
	glRotatef(view.RotateZ, 0.0f, 0.0f, 1.0f);
	axis(); //x,y,z �࿡ �� ǥ��.	
	glColor3f(1.0, 1.0, 1.0);
	//Cgitc_termpDlg::ListNode* ptr;
	Node* tmp_ptr = clptr->head;
	glBegin(GL_POINTS);
	while (tmp_ptr != NULL){
		glVertex3f(tmp_ptr->x, tmp_ptr->y, tmp_ptr->z);
		tmp_ptr = tmp_ptr->next;
	}
	glEnd();
	glPopMatrix();
	glFlush(); // buffer�� ����ϴ� �Լ��̴�.
}

void opengl_draw::OnSize(UINT nType, int cx, int cy){
	CDialogEx::OnSize(nType, cx, cy);
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
	VERIFY(wglMakeCurrent(m_hDC, m_hRC));
	GLResize(cx, cy);
	VERIFY(wglMakeCurrent(NULL, NULL));
}

void opengl_draw::OnDestroy(){
	wglDeleteContext(m_hRC);
	::ReleaseDC(m_hWnd, m_hDC);
	CDialogEx::OnDestroy();
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
}

int opengl_draw::OnCreate(LPCREATESTRUCT lpCreateStruct){
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  ���⿡ Ư��ȭ�� �ۼ� �ڵ带 �߰��մϴ�.
	int nPixelFormat;
	m_hDC = ::GetDC(m_hWnd);

	static PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW | //�����쿡 �׸���/
		PFD_SUPPORT_OPENGL |
		PFD_DOUBLEBUFFER,
		PFD_TYPE_RGBA,
		24, //24��Ʈ �÷� ���
		0, 0, 0, 0, 0, 0,
		0, 0,
		0, 0, 0, 0, 0,
		32,  //depth buffer ������
		0,
		0,
		PFD_MAIN_PLANE,
		0,
		0, 0, 0
	};
	nPixelFormat = ChoosePixelFormat(m_hDC, &pfd);
	VERIFY(SetPixelFormat(m_hDC, nPixelFormat, &pfd));
	m_hRC = wglCreateContext(m_hDC);
	VERIFY(wglMakeCurrent(m_hDC, m_hRC));
	wglMakeCurrent(NULL, NULL);
	return 0;
}

void opengl_draw::OnPaint(){
	if (IsIconic()) //�����찡 �ּ�ȭ���� �ƴ����� �Ǵ��ϴ� �Լ� �ּ�ȭ  = TRUE , Ȱ��ȭ = FALSE
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.
		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);
		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON); //getsystemmetrics ���� ��ǻ���� �ػ󵵸� �����ִ� mo
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;
		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}else{
		CDialogEx::OnPaint();
		wglMakeCurrent(m_hDC, m_hRC);
		GLRenderScene();
		SwapBuffers(m_hDC);
		wglMakeCurrent(m_hDC, NULL);
	}
}
void opengl_draw::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	mouse.DownPoint = point;
	mouse.LButtonDown = TRUE;
	SetCapture();
	CDialogEx::OnLButtonDown(nFlags, point);
}
void opengl_draw::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	mouse.DownPoint = CPoint(0, 0);
	mouse.LButtonDown = FALSE;
	ReleaseCapture();
	CDialogEx::OnLButtonUp(nFlags, point);
}
void opengl_draw::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	if (GetCapture() == this) // getcapture ���콺 pointer�� ������ �ִ� window�� ��ȯ��Ų��. GetCapture()==this
	{
		if (mouse.LButtonDown) //���� ���콺�� �������� ��
		{
			if (keyboard.KEY_Control){
				view.TranslateX += (float)((point.x - mouse.DownPoint.x) / 10.0);
				view.TranslateY += (float)((point.y - mouse.DownPoint.y) / 10.0);
			}else{
				view.RotateX += (float)((point.y - mouse.DownPoint.y) / 10.0);
				view.RotateY += (float)((point.x - mouse.DownPoint.x) / 10.0);
			}
		}
		if (mouse.RButtonDown) // ������ ���콺�� �������� ��
		{
			view.RotateZ += (float)((point.x - mouse.DownPoint.x) / 10.0);
		}
		Invalidate(false); //ȭ�� ����, false �ٲ���� �κи� �׷��ش�.
		mouse.DownPoint = point;
	}
	CDialogEx::OnMouseMove(nFlags, point);
}


BOOL opengl_draw::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt){
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	view.ZoomScale += (float)zDelta / 300;
	Invalidate(false);
	return CDialogEx::OnMouseWheel(nFlags, zDelta, pt);
}


void opengl_draw::OnRButtonDown(UINT nFlags, CPoint point){
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	mouse.DownPoint = point;
	mouse.RButtonDown = TRUE;
	SetCapture();
	CDialogEx::OnRButtonDown(nFlags, point);
}
void opengl_draw::OnRButtonUp(UINT nFlags, CPoint point){
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	mouse.DownPoint = CPoint(0, 0);
	mouse.RButtonDown = FALSE;
	ReleaseCapture();
	CDialogEx::OnRButtonUp(nFlags, point);
}
void opengl_draw::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags){
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	switch (nChar)
	{
	case VK_CONTROL:
		keyboard.KEY_Control = FALSE;
		break;
	}
	CDialogEx::OnKeyUp(nChar, nRepCnt, nFlags);
}

void opengl_draw::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	switch (nChar)
	{
	case VK_CONTROL:
		keyboard.KEY_Control = TRUE;
		break;
	}
	CDialogEx::OnKeyDown(nChar, nRepCnt, nFlags);
}
void opengl_draw::axis(){
	glPushMatrix();
	glBegin(GL_LINES);
	glColor3f(1.0, 0.0, 0.0); // x��- ������
	glVertex3f(100.0, 0.0, 0.0);
	glVertex3f(-100.0, 0.0, 0.0);
	glColor3f(0.0, 1.0, 0.0); //y�� - �ʷϻ�
	glVertex3f(0, 100.0, 0);
	glVertex3f(0, -100.0, 0);
	glColor3f(0.0, 0.0, 1.0); //z�� - �Ķ���
	glVertex3f(0.0, 0.0, 100.0);
	glVertex3f(0.0, 0.0, -100.0);
	glEnd();
	glPopMatrix();
}
