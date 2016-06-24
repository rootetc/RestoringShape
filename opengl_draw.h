#pragma once


// opengl_draw 대화 상자입니다.

class opengl_draw : public CDialogEx
{
	DECLARE_DYNAMIC(opengl_draw)

public:
	opengl_draw(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~opengl_draw();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DRAW };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	void GLResize(int cx, int cy);
	void GLRenderScene();

	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDestroy();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);

	HDC m_hDC;
	HGLRC m_hRC;	
	HICON m_hIcon;
	

	struct VIEW{
		float TranslateX;
		float TranslateY;
		float RotateX;
		float RotateY;
		float RotateZ;
		float ZoomScale;
		VIEW() :TranslateX(0), TranslateY(0), RotateX(0), RotateY(0), RotateZ(0), ZoomScale(1){};
	};

	struct MOUSE{
		CPoint DownPoint;
		BOOL LButtonDown;
		BOOL RButtonDown;
	};

	struct KEYBOARD{
		BOOL KEY_Control;
	};
	
	void opengl_draw::axis();
};
