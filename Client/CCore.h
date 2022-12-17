#pragma once

//�̱��� ����
//��ü�� ������ 1���� ������
//��𼭵� ���� �����ؾ���.
//class CCore
//{
//private:
//	static CCore* g_pInst;
//
//public:
//	static CCore* GetInstance()
//	{
//		//���ʷ� ȣ��� ��� ��ü�� �����Ѵ�.
//		if (g_pInst == nullptr)
//		{
//			g_pInst = new CCore;
//		}
//
//		//������ ȣ���
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
	HWND	m_hWnd;				//���� ������ �ڵ�
	POINT	m_ptResolution;		//���� ������ �ػ�
	HDC		m_hDC;				//���� �����쿡 Draw�� DC

	CTexture* m_pMenTex;		// ����� �ؽ���

	//���� ����� GDI Object
	HBRUSH	m_arrBrush[(UINT)BRUSH_TYPE::END];
	HPEN	m_arrPen[(UINT)PEN_TYPE::END];

	HMENU	m_hMenu; // tool Scene������ ���


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
