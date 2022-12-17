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

    virtual void MouseOn();             //UI위에 마우스가 올라갔을때
    virtual void MouseLbtnDown();       //해당 UI에서 마우스 왼쪽 버튼을 눌렀을때 호출될 함수
    virtual void MouseLbtnUp();         //해당 UI에서 마우스 왼쪽 버튼이 떼졌을때 호출될 함수

    CLONE(CPanelUI)

public:
    CPanelUI();
    ~CPanelUI();
};

