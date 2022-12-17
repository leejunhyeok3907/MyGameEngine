#pragma once

#include "pch.h"
#include "CCamera.h"

class CCollider;
class CAnimator;
class CRigidBody;
class CGravity;

class CObject
{
private:
	wstring m_strName;

	Vec2 m_vPos;
	Vec2 m_vScale;

	//Component
	CCollider*	m_pCollider;
	CAnimator*	m_pAnimator;
	CRigidBody* m_pRigidBody;
	CGravity*	m_pGravity;

	bool m_bAlive;

public:
	void SetPos(Vec2 _vPos) { m_vPos = _vPos; }
	void SetScale(Vec2 _vScale) { m_vScale = _vScale; }
	void SetName(const wstring& _strName) { m_strName = _strName; }

	Vec2 GetPos() { return m_vPos; }
	Vec2 GetScale() { return m_vScale; }
	const wstring& GetName() { return m_strName; }

	bool IsDead() { return !m_bAlive; }

	CCollider*	GetCollider() { return m_pCollider; }
	CAnimator*	GetAnimator() { return m_pAnimator; }
	CRigidBody* GetRigidBody() { return m_pRigidBody; }
	CGravity*	GetGravity() { return m_pGravity; }

	void CreateCollider();
	void CreateAnimator();
	void CreateRigidBody();
	void CreateGravity();

	virtual void OnCollision(CCollider* _pOther) {}
	virtual void OnCollisionEnter(CCollider* _pOther) {}
	virtual void OnCollisionExit(CCollider* _pOther) {}

private:
	//오직 EventManager에서만 오브젝트의 상태를 바꿀수있게 private로 놓아둠.
	void SetDead() { m_bAlive = false; }

public:
	virtual void init() {};//Scene이 시작되기 직전에 호출되는 함수
	virtual void update() PURE;
	virtual void finalupdate();
	virtual void render(HDC _dc);

	void Component_render(HDC _dc);

	virtual CObject* Clone() PURE;

public:
	CObject();
	CObject(const CObject& _origin);
	virtual ~CObject();

	friend class CEventManager;
};

