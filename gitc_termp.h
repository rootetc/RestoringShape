
// gitc_termp.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// Cgitc_termpApp:
// �� Ŭ������ ������ ���ؼ��� gitc_termp.cpp�� �����Ͻʽÿ�.
//

class Cgitc_termpApp : public CWinApp
{
public:
	Cgitc_termpApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern Cgitc_termpApp theApp;