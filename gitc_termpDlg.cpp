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
// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	// �����Դϴ�.
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


// Cgitc_termpDlg ��ȭ ����



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

BEGIN_MESSAGE_MAP(Cgitc_termpDlg, CDialogEx) // message map �κ� --> ���� ���ε� / ��ũ�� ó�� ���� / ����� �Լ��� ���� ���ε�.
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


// Cgitc_termpDlg �޽��� ó����

BOOL Cgitc_termpDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
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

	// �� ��ȭ ������ �������� �����մϴ�.  ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.
	
	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	//GetDlgItem(IDC_Hiden)->ShowWindow(SW_HIDE);//button�� ������ �ʰ� �ϱ�!!
	//GetDlgItem(���̵�)->showwindow(false);
	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
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

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void Cgitc_termpDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR Cgitc_termpDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void Cgitc_termpDlg::OnBnClickedOk()
{
	start_state = false;
	if (clptr != NULL) clptr->List_delete();//�ʱ�ȭ
	else clptr = new ListNode;
	
	CFileDialog fd(TRUE);
	if (fd.DoModal() == IDOK){
		pathName = fd.GetPathName();
		edit_pathname.SetWindowTextA(pathName);
		UpdateData(false);
	}
	GetDlgItem(IDC_EDIT4)->GetWindowTextA(str); // str�� ���ڷ� �Է�
	val_resolution = atoi((const char*)str); //atof�� ����Ͽ� ���ڿ����� �Ǽ� ���·� ��ȯ
	if (strlen(fd.GetPathName()) <= 0){
		AfxMessageBox("��θ� ���� ���ּ���");
	}else{
		read_file = _open(fd.GetPathName(), O_RDONLY | O_BINARY);
		write_file = _open("C:\\output.txt", O_WRONLY | O_BINARY);
		if (val_resolution <= 0)
			AfxMessageBox("���ش��� ���� ���ּ���");
		else{
			total_size = _lseek(read_file, 0, SEEK_END);
			_lseek(read_file, 0, SEEK_SET);
			start_state = true;
		}
	}
}
void Cgitc_termpDlg::OnBnClickedCancel(){
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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
		trigonometric_array(cos_buffer, sin_buffer, val_resolution); // �ﰢ�Լ� �迭 ����
		size_t start, end;
		char rho_buff[value_size];
		char theta_buff[value_size];
		char z_buff[value_size];
		buffer_init(rho_buff, theta_buff, z_buff);
		//char *output_buff = new char[total_line*line_size + 1]; //sprintf�� ���ڿ� �������� null���ڸ� �����Ѵ�. --> +1
		////////��ü ������ ũ�⸦ �޾ƿ´� //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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
		str.Format("��ȯ �Ϸ�");
		state.SetWindowTextA(str);
		UpdateData(false);
		_close(read_file);
		_close(write_file);
		start_state = true;
	}else AfxMessageBox("�⺻ ������ �Ϸ��� �ֽʽÿ�.");
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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	AfxMessageBox("2016.01.11/������/�ڽ���");
}
