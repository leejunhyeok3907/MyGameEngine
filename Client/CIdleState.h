#pragma once
#include "CState.h"
class CIdleState :
    public CState
{
private:

public:
    virtual void Enter();
    virtual void update();
    virtual void Exit();


public:
    CIdleState();
    ~CIdleState();

};

