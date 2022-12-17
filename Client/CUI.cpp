#include "CUI.h"
#include "CKeyManager.h"
#include "SelectGDI.h"

CUI::CUI(bool _bCamAff)
	: m_pParentUI(nullptr)
	, m_bCamAffected(_bCamAff)
	, m_bMouseOn(false)
	, m_bLbtnDown(false)
{
}

//기본 복사 생성자는 부모쪽의 복사생성자를 자동으로 호출해주나
//복사생성자를 직접 구현해버리는 순간 부모쪽의 복사생성자를 자동으로 호출해주지않는다.

CUI::CUI(const CUI& _origin)
	: CObject(_origin)//명시를 정확하게 해주어야함.
	, m_pParentUI(nullptr)
	, m_bCamAffected(_origin.m_bCamAffected)
	, m_bMouseOn(false)
	, m_bLbtnDown(false)

{
	for (size_t i = 0; i < _origin.m_vecChildUI.size(); i++)
	{
		AddChild(_origin.m_vecChildUI[i]->Clone());
	}
}

CUI::~CUI()
{
	Safe_Delete_Vec(m_vecChildUI);
}


void CUI::update()
{
	//부모->자식 순서로 계층적으로 내려가며 업데이트

	update_child();
}

void CUI::finalupdate()//자기자신의 최종 위치를 결정함
{
	CObject::finalupdate();

	//UI의 최종 좌표를 구한다.
	m_vFinalPos = GetPos();

	if (GetParent())//부모가 있다면 부모의 위치로부터 offset위치
	{
		Vec2 vParentPos = GetParent()->GetFinalPos();
		m_vFinalPos += vParentPos;
	}

	//UI Mouse체크
	MouseOnCheck();

	finalupdate_child();
}

void CUI::render(HDC _dc)
{
	Vec2 vPos = GetFinalPos();
	Vec2 vScale = GetScale();

	if (m_bCamAffected)
	{
		vPos = CCamera::GetInst()->GetRenderPos(vPos);
	}

	if (m_bLbtnDown)
	{
		SelectGDI select(_dc, PEN_TYPE::GREEN);

		Rectangle(_dc,
			(int)(vPos.x),
			(int)(vPos.y),
			(int)(vPos.x + vScale.x),
			(int)(vPos.y + vScale.y));
	}
	else
	{
		Rectangle(_dc,
			(int)(vPos.x),
			(int)(vPos.y),
			(int)(vPos.x + vScale.x),
			(int)(vPos.y + vScale.y));
	}

	render_child(_dc);
}

void CUI::update_child()
{
	for (size_t i = 0; i < m_vecChildUI.size(); i++)
	{
		m_vecChildUI[i]->update();
	}
}

void CUI::finalupdate_child()
{
	for (size_t i = 0; i < m_vecChildUI.size(); i++)
	{
		m_vecChildUI[i]->finalupdate();
	}
}

void CUI::render_child(HDC _dc)
{
	for (size_t i = 0; i < m_vecChildUI.size(); i++)
	{
		m_vecChildUI[i]->render(_dc);
	}
}

void CUI::MouseOnCheck()
{
	Vec2 vMousePos = MOUSE_POS;
	Vec2 vScale = GetScale();

	if (m_bCamAffected)
	{
		vMousePos = CCamera::GetInst()->GetRenderPos(vMousePos);
	}

	if (m_vFinalPos.x <= vMousePos.x && vMousePos.x <= m_vFinalPos.x + vScale.x
		&& m_vFinalPos.y <= vMousePos.y && vMousePos.y <= m_vFinalPos.y + vScale.y)
	{
		m_bMouseOn = true;
	}
	else
	{
		m_bMouseOn = false;
	}
}

void CUI::MouseOn()
{
}

void CUI::MouseLbtnDown()
{

}

void CUI::MouseLbtnUp()
{
}

void CUI::MouseLbtnClicked()
{
}
