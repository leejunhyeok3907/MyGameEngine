#pragma once
#include "CObject.h"
class CUI :
    public CObject
{
private:
    vector<CUI*>    m_vecChildUI;
    CUI*            m_pParentUI;//자신의 부모UI를 가리키는 변수.

    Vec2            m_vFinalPos;

    bool            m_bCamAffected; //UI가 카메라에 영향을 받는지에 대해
    bool            m_bMouseOn;     //UI위에 마우스가 있는지
    bool            m_bLbtnDown;    //UI에 왼쪽 버튼이 눌린적있는지

public:
    Vec2 GetFinalPos() { return m_vFinalPos; }
    CUI* GetParent() { return m_pParentUI; }
    bool IsMouseOn() { return m_bMouseOn; }
    bool IsLbtnDown() { return m_bLbtnDown; }
    
    void AddChild(CUI* _pUI) { m_vecChildUI.push_back(_pUI); _pUI->m_pParentUI = this; }
    const vector<CUI*>& GetChildUI() { return m_vecChildUI; }

public:
    virtual void update();
    virtual void finalupdate();
    virtual void render(HDC _dc);

private:
    void update_child();
    void finalupdate_child();
    void render_child(HDC _dc);

    void MouseOnCheck();

public:
    virtual void MouseOn();             //UI위에 마우스가 올라갔을때

    virtual void MouseLbtnDown();       //해당 UI에서 마우스 왼쪽 버튼을 눌렀을때 호출될 함수
    virtual void MouseLbtnUp();         //해당 UI에서 마우스 왼쪽 버튼이 떼졌을때 호출될 함수
    virtual void MouseLbtnClicked();    //해당 UI에서 마우스 왼쪽 버튼을 클릭했을때 호출될 함수

    virtual CUI* Clone() PURE;

public:
    CUI(bool _bCamAff);
    CUI(const CUI& _origin);
    virtual ~CUI();

    friend class CUIManager;
};

