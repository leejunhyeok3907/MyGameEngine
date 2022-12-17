#pragma once
#include "CState.h"
class CTraceState :
    public CState
{
private:

public:
    virtual void Enter();
    virtual void update();
    virtual void Exit();


public:
    CTraceState();
    ~CTraceState();
};

