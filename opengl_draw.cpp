// opengl_draw.cpp : 구현 파일입니다.
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

// opengl_draw 대화 상자입니다.

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


// opengl_draw 메시지 처리기입니다.

void opengl_draw::GLResize(int cx, int cy)
{
	GLfloat fAspect;
	if (cy == 0)
		cy = 1;
	glViewport(0, 0, cx, cy);
	fAspect = (GLfloat)cx / (GLfloat)cy;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity(); // 단위 형렬로 초기화 수행 / why? 사용이 끝는 buffer에 존재하는 쓰래기 값을 제거하기 위해서 glLoadIdentity()를 선언

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
	glEnable(GL_POINT_SMOOTH); // 점의 antialiasing 즉 antialiasing은 overlap 현상을 방지하는 것, 사각형으로 나타지 않는다. 
	//glEnable(GL_SMOOTH);// 값을 서서히 변화 시킨다 <->gl_flat은 마자막 vertex의 색깔로 결정된다.
	//glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	
	glPushMatrix();
	glLoadIdentity(); // matrix 초기화.
	gluLookAt(100.0, 100.0, 100.0, 0.0, 0.0, 0.0, -1.0, 1.0, -1.0);
	glTranslatef(view.TranslateX, -view.TranslateY, 0.0f);
	glScalef(view.ZoomScale, view.ZoomScale, view.ZoomScale);
	glRotatef(view.RotateX, 1.0f, 0.0f, 0.0f);
	glRotatef(view.RotateY, 0.0f, 1.0f, 0.0f);
	glRotatef(view.RotateZ, 0.0f, 0.0f, 1.0f);
	axis(); //x,y,z 축에 선 표현.	
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
	glFlush(); // buffer를 출력하는 함수이다.
}

void opengl_draw::OnSize(UINT nType, int cx, int cy){
	CDialogEx::OnSize(nType, cx, cy);
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	VERIFY(wglMakeCurrent(m_hDC, m_hRC));
	GLResize(cx, cy);
	VERIFY(wglMakeCurrent(NULL, NULL));
}

void opengl_draw::OnDestroy(){
	wglDeleteContext(m_hRC);
	::ReleaseDC(m_hWnd, m_hDC);
	CDialogEx::OnDestroy();
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}

int opengl_draw::OnCreate(LPCREATESTRUCT lpCreateStruct){
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	int nPixelFormat;
	m_hDC = ::GetDC(m_hWnd);

	static PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW | //윈도우에 그린다/
		PFD_SUPPORT_OPENGL |
		PFD_DOUBLEBUFFER,
		PFD_TYPE_RGBA,
		24, //24비트 컬러 사용
		0, 0, 0, 0, 0, 0,
		0, 0,
		0, 0, 0, 0, 0,
		32,  //depth buffer 사이즈
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
	if (IsIconic()) //윈도우가 최소화인지 아닌지를 판단하는 함수 최소화  = TRUE , 활성화 = FALSE
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.
		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);
		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON); //getsystemmetrics 현재 컴퓨터의 해상도를 구해주는 mo
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;
		// 아이콘을 그립니다.
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
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	mouse.DownPoint = point;
	mouse.LButtonDown = TRUE;
	SetCapture();
	CDialogEx::OnLButtonDown(nFlags, point);
}
void opengl_draw::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	mouse.DownPoint = CPoint(0, 0);
	mouse.LButtonDown = FALSE;
	ReleaseCapture();
	CDialogEx::OnLButtonUp(nFlags, point);
}
void opengl_draw::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (GetCapture() == this) // getcapture 마우스 pointer를 가지고 있는 window를 반환시킨다. GetCapture()==this
	{
		if (mouse.LButtonDown) //왼쪽 마우스가 눌러졌을 때
		{
			if (keyboard.KEY_Control){
				view.TranslateX += (float)((point.x - mouse.DownPoint.x) / 10.0);
				view.TranslateY += (float)((point.y - mouse.DownPoint.y) / 10.0);
			}else{
				view.RotateX += (float)((point.y - mouse.DownPoint.y) / 10.0);
				view.RotateY += (float)((point.x - mouse.DownPoint.x) / 10.0);
			}
		}
		if (mouse.RButtonDown) // 오른쪽 마우스가 눌러졌을 때
		{
			view.RotateZ += (float)((point.x - mouse.DownPoint.x) / 10.0);
		}
		Invalidate(false); //화면 갱신, false 바뀌어진 부분만 그려준다.
		mouse.DownPoint = point;
	}
	CDialogEx::OnMouseMove(nFlags, point);
}


BOOL opengl_draw::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt){
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	view.ZoomScale += (float)zDelta / 300;
	Invalidate(false);
	return CDialogEx::OnMouseWheel(nFlags, zDelta, pt);
}


void opengl_draw::OnRButtonDown(UINT nFlags, CPoint point){
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	mouse.DownPoint = point;
	mouse.RButtonDown = TRUE;
	SetCapture();
	CDialogEx::OnRButtonDown(nFlags, point);
}
void opengl_draw::OnRButtonUp(UINT nFlags, CPoint point){
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	mouse.DownPoint = CPoint(0, 0);
	mouse.RButtonDown = FALSE;
	ReleaseCapture();
	CDialogEx::OnRButtonUp(nFlags, point);
}
void opengl_draw::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags){
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
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
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
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
	glColor3f(1.0, 0.0, 0.0); // x축- 빨간색
	glVertex3f(100.0, 0.0, 0.0);
	glVertex3f(-100.0, 0.0, 0.0);
	glColor3f(0.0, 1.0, 0.0); //y축 - 초록색
	glVertex3f(0, 100.0, 0);
	glVertex3f(0, -100.0, 0);
	glColor3f(0.0, 0.0, 1.0); //z축 - 파란색
	glVertex3f(0.0, 0.0, 100.0);
	glVertex3f(0.0, 0.0, -100.0);
	glEnd();
	glPopMatrix();
}
