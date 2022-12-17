#pragma once
#include "CUI.h"

//�ɹ��Լ������� ���� ��Ȯ�� Ŭ���� ������ �ʿ���. ���漱�����δ� ��ü�� �˼����⶧��
#include "CScene.h"
#include "CObject.h"

//�̷� ������ Ÿ���� �������ִ� �Լ������͸� �ϳ��� Ÿ������ ����
typedef void(*BTN_FUNC) (DWORD_PTR, DWORD_PTR);

//�ɹ��Լ�������
//�ɹ��Լ������Ͱ� �θ�� �����Ǹ� ��ӹ��� �ɹ����� �������ִ�.
//void(CScene_Tool::* pMemFunc)(void);
//�̸� �̿��ؼ� ������ ��� ������Ʈ���� ���谡 ������ �ֻ��� ������Ʈ�� �ϳ� �����صΰ� ����Ѵٸ� ��� �ɹ��Լ������͸� �������ִ�.
typedef void(CScene::*SCENE_MEMFUNC)(void);
typedef void(CObject::*OBJECT_MEMFUNC)(void);

class CButtonUI :
    public CUI
{
private:
    //Ŭ������ ����ؼ� ����� ���� �߰��ϴ°ͺ���
    //��ư�� �ش� ����� �Լ������͸� �̿��ؼ� �������ָ� Ŭ������ �߰��� �ʿ䰡 ����
    BTN_FUNC    m_pFunc;
    DWORD_PTR   m_param1;
    DWORD_PTR   m_param2;

    SCENE_MEMFUNC   m_pSceneFunc;//ȣ���� �ɹ��Լ�
    CScene*         m_pSceneInst;//�Լ��� ȣ���ų ��ü



public:
    virtual void MouseOn();             //UI���� ���콺�� �ö�����
    virtual void MouseLbtnDown();       //�ش� UI���� ���콺 ���� ��ư�� �������� ȣ��� �Լ�
    virtual void MouseLbtnUp();         //�ش� UI���� ���콺 ���� ��ư�� �������� ȣ��� �Լ�
    virtual void MouseLbtnClicked();    //�ش� UI���� ���콺 ���� ��ư�� Ŭ�������� ȣ��� �Լ�

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

