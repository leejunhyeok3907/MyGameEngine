#include "pch.h"
#include "CCore.h"
#include "CObject.h"
#include "CTimeManager.h"
#include "CKeyManager.h"
#include "CSceneManager.h"
#include "CPathManager.h"
#include "CCollisionManager.h"
#include "CEventManager.h"
#include "CResourceManager.h"
#include "CCamera.h"
#include "CUIManager.h"
#include "CSoundManager.h"

#include "CTexture.h"
#include "CSound.h"

#include "SelectGDI.h"

#include "resource.h"

//CCore* CCore::g_pInst = nullptr;


CCore::CCore()
	: m_hWnd(0)
	, m_ptResolution{}
	, m_hDC(0)
	, m_arrBrush{}
	, m_arrPen{}
{
}

CCore::~CCore()
{
	ReleaseDC(m_hWnd, m_hDC);

	for (int i = 0; i < (UINT)PEN_TYPE::END; i++)
	{
		DeleteObject(m_arrPen[i]);
	}

	DestroyMenu(m_hMenu);
}


int CCore::init(HWND _hWnd, POINT _ptResolution)
{
	m_hWnd = _hWnd;
	m_ptResolution = _ptResolution;

	ChangeWindowSize(Vec2((float)_ptResolution.x, (float)_ptResolution.y), false);

	//�޴��� ����
	m_hMenu = LoadMenu(nullptr, MAKEINTRESOURCEW(IDC_CLIENT));


	m_hDC = GetDC(m_hWnd);
	//���� ���۸� �뵵�� �ؽ��� ������ �����.
	m_pMenTex = CResourceManager::GetInst()->CreateTexture(L"BackBuffer", (UINT)m_ptResolution.x, (UINT)m_ptResolution.y);	

	//���� ����� �귯�� �� �� ����
	CreateBrushPen();

	//Manager�ʱ�ȭ
	CPathManager::GetInst()->init();
	CTimeManager::GetInst()->init();
	CKeyManager::GetInst()->init();
	CCamera::GetInst()->init();
	CSoundManager::GetInst()->init();
	CSceneManager::GetInst()->init();

	CResourceManager::GetInst()->LoadSound(L"Music", L"sound\\TOP GUN ANTHEM.wav");
	CSound* pNewSound = CResourceManager::GetInst()->FindSound(L"Music");

	//pNewSound->Play();

	//pNewSound->SetPosition(80.f);
	pNewSound->PlayToBGM(true);
	pNewSound->SetVolume(100.f);

	return S_OK;
}

void CCore::Progress()
{
	// =============
	// Manager Update
	// =============
	CTimeManager::GetInst()->update();
	CKeyManager::GetInst()->update();
	CCamera::GetInst()->update();

	// ==============
	// Scene Update
	// ==============
	CSceneManager::GetInst()->update();

	//�浹 üũ
	CCollisionManager::GetInst()->update();

	//UI �̺�Ʈ üũ
	CUIManager::GetInst()->update();
	

	//=========
	//Rendering
	//=========
	//ȭ�� Clear

	Clear();

	CSceneManager::GetInst()->render(m_pMenTex->GetDC());
	CCamera::GetInst()->render(m_pMenTex->GetDC());

	//���� ���۸�. m_memDC�� �ϼ��� DC�� ����DC�� �ű�.
	BitBlt(m_hDC, 0, 0, m_ptResolution.x, m_ptResolution.y,
		m_pMenTex->GetDC(), 0, 0, SRCCOPY);


	CTimeManager::GetInst()->render();

	// ===============
	//�̺�Ʈ ����ó��
	// ===============
	CEventManager::GetInst()->update();
}

void CCore::Clear()
{
	SelectGDI GDI(m_pMenTex->GetDC(), BRUSH_TYPE::BLACK);
	Rectangle(m_pMenTex->GetDC(), -1, -1, m_ptResolution.x + 1, m_ptResolution.y + 1);
}

void CCore::CreateBrushPen()
{
	//Brush
	m_arrBrush[(UINT)BRUSH_TYPE::HOLLOW] = (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	m_arrBrush[(UINT)BRUSH_TYPE::BLACK] = (HBRUSH)GetStockObject(BLACK_BRUSH);

	//pen
	m_arrPen[(UINT)PEN_TYPE::RED] = (HPEN)CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	m_arrPen[(UINT)PEN_TYPE::GREEN] = (HPEN)CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	m_arrPen[(UINT)PEN_TYPE::BLUE] = (HPEN)CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
}

void CCore::DockMenu()
{
	SetMenu(m_hWnd, m_hMenu);
	ChangeWindowSize(GetResolution(), true);
}

void CCore::DiviedMenu()
{
	SetMenu(m_hWnd, nullptr);
	ChangeWindowSize(GetResolution(), false);
}

void CCore::ChangeWindowSize(Vec2 _vResolution, bool _bMenu)
{
	//�ػ󵵿� �°� ������ ũ�� ����
	RECT rt = { 0, 0, (long)_vResolution.x, (long)_vResolution.y};
	//���ϰ��� �������� �޸𸮿� ��ܼ� ��ȯ�Ǵµ�
	//�ʹ� ū ����ü�� ��� �ǵ����ٰ�� �������ϰ� �����.
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, _bMenu);

	SetWindowPos(m_hWnd, nullptr, 100, 100, rt.right - rt.left, rt.bottom - rt.top, 0);
}
