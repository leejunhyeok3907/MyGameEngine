#pragma once
#include "CScene.h"
class CScene_Start :
    public CScene
{
private:
    Vec2    m_vForcePos;
    float   m_fCurRadius;
    float   m_fForceRadius;
    float   m_fForce;
    bool    m_bUseForce;

public:
    //붙이지않아도 가상함수로 인식되지만 명시적으로 적어줌.
    virtual void update();
    virtual void render(HDC _dc);
    virtual void Enter();
    virtual void Exit();

public:
    void CreateForce();

public:
    CScene_Start();
    ~CScene_Start();
};

