#pragma once
#include "CUI.h"

//맴버함수포인터 사용시 정확한 클래스 정보가 필요함. 전방선언만으로는 객체를 알수없기때문
#include "CScene.h"
#include "CObject.h"

//이런 형태의 타입을 받을수있는 함수포인터를 하나의 타입으로 지정
typedef void(*BTN_FUNC) (DWORD_PTR, DWORD_PTR);

//맴버함수포인터
//맴버함수포인터가 부모로 구현되면 상속받은 맴버또한 받을수있다.
//void(CScene_Tool::* pMemFunc)(void);
//이를 이용해서 엔진속 모든 오브젝트간의 관계가 없더라도 최상위 오브젝트를 하나 선언해두고 상속한다면 모든 맴버함수포인터를 받을수있다.
typedef void(CScene::*SCENE_MEMFUNC)(void);
typedef void(CObject::*OBJECT_MEMFUNC)(void);

class CButtonUI :
    public CUI
{
private:
    //클래스를 상속해서 기능을 따로 추가하는것보다
    //버튼에 해당 기능을 함수포인터를 이용해서 전달해주면 클래스를 추가할 필요가 없음
    BTN_FUNC    m_pFunc;
    DWORD_PTR   m_param1;
    DWORD_PTR   m_param2;

    SCENE_MEMFUNC   m_pSceneFunc;//호출할 맴버함수
    CScene*         m_pSceneInst;//함수를 호출시킬 객체



public:
    virtual void MouseOn();             //UI위에 마우스가 올라갔을때
    virtual void MouseLbtnDown();       //해당 UI에서 마우스 왼쪽 버튼을 눌렀을때 호출될 함수
    virtual void MouseLbtnUp();         //해당 UI에서 마우스 왼쪽 버튼이 떼졌을때 호출될 함수
    virtual void MouseLbtnClicked();    //해당 UI에서 마우스 왼쪽 버튼을 클릭했을때 호출될 함수

    void SetClickedCallBack(BTN_FUNC _pFunc, DWORD_PTR _param1, DWORD_PTR _param2)
    {
        m_pFunc = _pFunc;
        m_param1 = _param1;
        m_param2 = _param2;
    }

    void SetClickedCallBack(CScene* _pScene, SCENE_MEMFUNC _pSceneFunc);

    CLONE(CButtonUI)

public:
    CButtonUI();
    ~CButtonUI();
};

