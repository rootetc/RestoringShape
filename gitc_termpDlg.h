// gitc_termpDlg.h : 헤더 파일
//
#pragma once
#include "afxwin.h"
#include <vector>

// Cgitc_termpDlg 대화 상자
class Cgitc_termpDlg : public CDialogEx
{
// 생성입니다.
public:
	Cgitc_termpDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
	enum { IDD = IDD_GITC_TERMP_DIALOG };
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.
	

// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
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