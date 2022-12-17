#pragma once

class CObject;

class CCollider
{
private:
	static	UINT g_iNextID;		//충돌체의 다음 ID값

	CObject*	m_pOwner;		//collider을 소유하고 있는 object

	Vec2		m_vOffsetPos;	//object로부터의 상대적인 위치
	Vec2		m_vFinalPos;	//final update에서 매 프레임마다 계산되는 최종 위치
	Vec2		m_vScale;		//충돌체의 크기

	UINT		m_iID;			//충돌체의 고유한 ID값
	int			m_iCol;

	bool		m_bActive;		//충돌체의 활성화 여부

public:
	void SetOffsetPos(Vec2 _vPos) { m_vOffsetPos = _vPos; }
	void SetScale(Vec2 _vScale) { m_vScale = _vScale; }

	Vec2 GetOffsetPos() { return m_vScale; }
	Vec2 GetScale() { return m_vScale; }
	Vec2 GetFinalPos() { return m_vFinalPos; }

	UINT GetID() { return m_iID; }

	CObject* GetObj() { return m_pOwner; }

public:
	void finalupdate();
	void render(HDC _dc);

public:
	void OnCollision(CCollider* _pOther);//충돌 중인 경우 호출되는 함수
	void OnCollisionEnter(CCollider* _pOther);//충돌 진입시
	void OnCollisionExit(CCollider* _pOther);//충돌 해제시

	CCollider& operator=(CCollider& _origin) = delete;

public:
	CCollider();
	CCollider(const CCollider& _origin);
	~CCollider();

	friend class CObject;

};

