// gitc_termpDlg.h : ��� ����
//
#pragma once
#include "afxwin.h"
#include <vector>

// Cgitc_termpDlg ��ȭ ����
class Cgitc_termpDlg : public CDialogEx
{
// �����Դϴ�.
public:
	Cgitc_termpDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_GITC_TERMP_DIALOG };
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.
	

// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	#define array_length	2
	#define M_PI			0.01745329252f
	#define N 15

	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedDraw();
	afx_msg void OnBnClickedStart();
	afx_msg void OnDestroy();
	
	void buffer_init(char *x, char*y, char*z);
	void trigonometric_array(double* cos_buffer, double* sin_buffer,int resolution);

	CEdit edit_pathname;
	CEdit resolution;
	CEdit state;
	CEdit time;
	CString pathName;
	CString str;

	int val_resolution = 0;
	int read_file;
	int write_file;

	bool type = false;
	bool start_state = false;
	afx_msg void OnBnClickedHiden();
};