#pragma once

class CObject;

class CRigidBody
{
private:
	CObject*	m_pOwner;

	Vec2		m_vForce;	//크기, 방향
	Vec2		m_vAccel;	//가속도
	Vec2		m_vAccel_A;	//추가 가속도
	Vec2		m_vVelocity;//속도(크기: 속력, 방향)
	Vec2		m_vMaxVelocity;	//최대 속력//(x와 y의 제한을 다르게 하기위해 방향성 정보가 포함된 Vec으로)

	float		m_fMass;	//질량

	float		m_fFrictionCoef; //마찰 계수


	//F = M * A
	//V += A * DT

public:
	virtual void finalupdate();

public:
	//힘 누적
	void AddForce(Vec2 _vF) { m_vForce += _vF; }
	void SetMass(float _fMass) { m_fMass = _fMass; }
	float GetMass() { return m_fMass; }
	float GetSpeed() { return m_vVelocity.Length(); }
	Vec2 GetVelocity() { return m_vVelocity; }

	void SetVelocity(Vec2 _v) { m_vVelocity = _v; }
	void AddVelocity(Vec2 _v) { m_vVelocity += _v; }
	void SetMaxVelocity(Vec2 _v) { m_vMaxVelocity = _v; }
	void SetAccelAlpha(Vec2 _vAccel) { m_vAccel_A = _vAccel; }

private:
	void Move();


public:
	CRigidBody();
	~CRigidBody();

	friend class CObject;
};

