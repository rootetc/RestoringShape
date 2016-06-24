#include "stdafx.h"
#include "gitc_termp.h"
#include "gitc_termpDlg.h"
#include "afxdialogex.h"
#include <stdlib.h>
#include <time.h>
#include <io.h>
#include <fcntl.h>
#include "opengl_draw.h"
#include "ListNode.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#define value_size 20
#define theta(x,y) x*3.14159265359*2/y
#define state_one 1
#define state_two 2
#define state_three 3
#endif
double cos_buffer[3100];
double sin_buffer[3100];
unsigned int total_size;
ListNode* clptr;
// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// 대화 상자 데이터입니다.
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// Cgitc_termpDlg 대화 상자



Cgitc_termpDlg::Cgitc_termpDlg(CWnd* pParent /*=NULL*/)
: CDialogEx(Cgitc_termpDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Cgitc_termpDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, edit_pathname);
	DDX_Control(pDX, IDC_EDIT4, resolution);
	DDX_Control(pDX, IDC_EDIT2, state);
	DDX_Control(pDX, IDC_EDIT3, time);
}

BEGIN_MESSAGE_MAP(Cgitc_termpDlg, CDialogEx) // message map 부분 --> 동적 바인딩 / 매크로 처럼 동작 / 선언된 함수만 동적 바인딩.
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &Cgitc_termpDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &Cgitc_termpDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_DRAW, &Cgitc_termpDlg::OnBnClickedDraw)
	ON_BN_CLICKED(IDC_START, &Cgitc_termpDlg::OnBnClickedStart)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_Hiden, &Cgitc_termpDlg::OnBnClickedHiden)
END_MESSAGE_MAP()


// Cgitc_termpDlg 메시지 처리기

BOOL Cgitc_termpDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.
	
	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	//GetDlgItem(IDC_Hiden)->ShowWindow(SW_HIDE);//button을 보이지 않게 하기!!
	//GetDlgItem(아이디)->showwindow(false);
	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void Cgitc_termpDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void Cgitc_termpDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR Cgitc_termpDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void Cgitc_termpDlg::OnBnClickedOk()
{
	start_state = false;
	if (clptr != NULL) clptr->List_delete();//초기화
	else clptr = new ListNode;
	
	CFileDialog fd(TRUE);
	if (fd.DoModal() == IDOK){
		pathName = fd.GetPathName();
		edit_pathname.SetWindowTextA(pathName);
		UpdateData(false);
	}
	GetDlgItem(IDC_EDIT4)->GetWindowTextA(str); // str에 문자로 입력
	val_resolution = atoi((const char*)str); //atof를 사용하여 문자열에서 실수 형태로 변환
	if (strlen(fd.GetPathName()) <= 0){
		AfxMessageBox("경로를 지정 해주세요");
	}else{
		read_file = _open(fd.GetPathName(), O_RDONLY | O_BINARY);
		write_file = _open("C:\\output.txt", O_WRONLY | O_BINARY);
		if (val_resolution <= 0)
			AfxMessageBox("분해능을 설정 해주세요");
		else{
			total_size = _lseek(read_file, 0, SEEK_END);
			_lseek(read_file, 0, SEEK_SET);
			start_state = true;
		}
	}
}
void Cgitc_termpDlg::OnBnClickedCancel(){
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	AfxMessageBox("cancel");
	CDialogEx::OnCancel();
}
void Cgitc_termpDlg::OnBnClickedDraw(){
	opengl_draw dlg;
	dlg.DoModal();
}

void Cgitc_termpDlg::OnBnClickedStart(){
	if (start_state == true){
		start_state = false;
		trigonometric_array(cos_buffer, sin_buffer, val_resolution); // 삼각함수 배열 생성
		size_t start, end;
		char rho_buff[value_size];
		char theta_buff[value_size];
		char z_buff[value_size];
		buffer_init(rho_buff, theta_buff, z_buff);
		//char *output_buff = new char[total_line*line_size + 1]; //sprintf는 문자열 마지막에 null문자를 삽입한다. --> +1
		////////전체 파일의 크기를 받아온다 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		char* file_buff = new char[total_size];
		unsigned int ptr = 0;
		unsigned int controll_state = state_one;
		
		start = clock();
		if((_read(read_file, file_buff, total_size))!=-1)
		{
			for (unsigned int file_point = 0; file_point < total_size; ++file_point)
			{
				switch (controll_state)
				{
				case state_one:
					if (file_buff[file_point] != ' ')
					{
						rho_buff[ptr] = file_buff[file_point];
						++ptr;
					}
					else{
						ptr = 0;
						controll_state = state_two;
					}
					break;
				case state_two:
					if (file_buff[file_point] != ' ')
					{
						theta_buff[ptr] = file_buff[file_point];
						++ptr;
					}
					else{
						ptr = 0;
						controll_state = state_three;
					}
					break;
				case state_three:
					if (file_buff[file_point] != '\n')
					{
						z_buff[ptr] = file_buff[file_point];
						++ptr;
					}
					else{
						ptr = 0;
						controll_state = state_one;
						clptr->List_insert(0, 0, 0);
						buffer_init(rho_buff, theta_buff, z_buff);
					}
					break;
				}
			}
		}
		delete[] file_buff;
		end = clock();
		//_write(write_file, output_buff, total_line*line_size);
		str.Format("%f", (double)(end - start) / CLOCKS_PER_SEC);
		time.SetWindowTextA(str);
		str.Format("변환 완료");
		state.SetWindowTextA(str);
		UpdateData(false);
		_close(read_file);
		_close(write_file);
		start_state = true;
	}else AfxMessageBox("기본 설정을 완료해 주십시요.");
}

void Cgitc_termpDlg::OnDestroy(){
	CDialogEx::OnDestroy();
	AfxMessageBox("destory");
	clptr->List_delete();
}

void Cgitc_termpDlg::buffer_init(char*x,char*y,char*z){
	ZeroMemory(x, value_size);
	ZeroMemory(y, value_size);
	ZeroMemory(z, value_size);
}
void Cgitc_termpDlg::trigonometric_array(double* cos_buffer, double* sin_buffer, int resolution){
	for (int i = 0; i < resolution; i++){
		cos_buffer[i] = cos(theta(i, resolution));
		sin_buffer[i] = sin(theta(i, resolution));
	}
}
void Cgitc_termpDlg::OnBnClickedHiden(){
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	AfxMessageBox("2016.01.11/영남대/박승현");
}
