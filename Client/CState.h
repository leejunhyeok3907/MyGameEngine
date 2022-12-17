#pragma once

class AI;
class CMonster;

class CState
{
private:
	AI*		 m_pAI;
	MON_STATE	m_eState;

public:
	AI* GetAI() { return m_pAI; }
	MON_STATE GetType() { return m_eState; }
	CMonster* GetMonster();

public:
	virtual void Enter() PURE;
	virtual void update() PURE;
	virtual void Exit() PURE;



public:
	CState(MON_STATE _eState);
	virtual ~CState();

	friend class AI;
};

