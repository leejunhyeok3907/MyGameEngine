#pragma once

//싱글톤 패턴
//객체의 생성을 1개로 제한함
//어디서든 쉽게 접근해야함.
//class CCore
//{
//private:
//	static CCore* g_pInst;
//
//public:
//	static CCore* GetInstance()
//	{
//		//최초로 호출된 경우 객체를 생성한다.
//		if (g_pInst == nullptr)
//		{
//			g_pInst = new CCore;
//		}
//
//		//이후의 호출시
//		return g_pInst;
//	}
//
//	static void Release()
//	{
//		if (g_pInst != nullptr)
//		{
//			delete g_pInst;
//			g_pInst = nullptr;
//		}
//	}
//
//
//private:
//	CCore();
//	~CCore();
//};

class CTexture;

class CCore
{
	SINGLE(CCore);

private:
	HWND	m_hWnd;				//메인 윈도우 핸들
	POINT	m_ptResolution;		//메인 윈도우 해상도
	HDC		m_hDC;				//메인 윈도우에 Draw할 DC

	CTexture* m_pMenTex;		// 백버퍼 텍스쳐

	//자주 사용할 GDI Object
	HBRUSH	m_arrBrush[(UINT)BRUSH_TYPE::END];
	HPEN	m_arrPen[(UINT)PEN_TYPE::END];

	HMENU	m_hMenu; // tool Scene에서만 사용


public:
	int init(HWND _hWnd, POINT _ptResolution);
	void Progress();

private:
	void Clear();
	void CreateBrushPen();

public:
	void DockMenu();
	void DiviedMenu();
	void ChangeWindowSize(Vec2 _vResolution, bool _bMenu);

public:
	HWND	GetMainHwnd() { return m_hWnd; }
	POINT	GetResolution() { return m_ptResolution; }
	HDC		GetMainDC() { return m_hDC; }
	HBRUSH	GetBrush(BRUSH_TYPE _eType) { return m_arrBrush[(UINT)_eType]; }
	HPEN	GetPen(PEN_TYPE _eType) { return m_arrPen[(UINT)_eType]; }
};
