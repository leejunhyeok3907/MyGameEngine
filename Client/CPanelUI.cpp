#include "CPanelUI.h"
#include "CKeyManager.h"

CPanelUI::CPanelUI()
	: CUI(false)
{
}

CPanelUI::~CPanelUI()
{
}


void CPanelUI::update()
{

}

void CPanelUI::render(HDC _dc)
{
	CUI::render(_dc);
}

void CPanelUI::MouseOn()
{
	//������ �� ���ķκ��� �巡����
	if (IsLbtnDown())
	{
		Vec2 vDiff = MOUSE_POS - m_vDragStart;
		Vec2 vCurPos = GetPos();

		vCurPos += vDiff;

		SetPos(vCurPos);

		m_vDragStart = MOUSE_POS;
	}
}

void CPanelUI::MouseLbtnDown()
{
	m_vDragStart = MOUSE_POS;
}

void CPanelUI::MouseLbtnUp()
{
}

