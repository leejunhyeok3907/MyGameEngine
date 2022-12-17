#pragma once
#include "CUI.h"
class CPanelUI :
    public CUI
{
private:
    Vec2    m_vDragStart;

public:
    virtual void update();
    virtual void render(HDC _dc);

    virtual void MouseOn();             //UI���� ���콺�� �ö�����
    virtual void MouseLbtnDown();       //�ش� UI���� ���콺 ���� ��ư�� �������� ȣ��� �Լ�
    virtual void MouseLbtnUp();         //�ش� UI���� ���콺 ���� ��ư�� �������� ȣ��� �Լ�

    CLONE(CPanelUI)

public:
    CPanelUI();
    ~CPanelUI();
};

