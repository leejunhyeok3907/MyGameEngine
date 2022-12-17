#include "pch.h"
#include "CMissile.h"
#include "CTimeManager.h"
#include "CCollider.h"

void CMissile::update()
{
	Vec2 vPos = GetPos();

	//vPos.x += 200.f * cosf(m_fTheta) * fDT;
	//vPos.y -= 200.f * sinf(m_fTheta) * fDT;

	//벡터를 이용하면 진행방향끼리의 덧셈과 뺄셈이 가능함.
	//직관적으로 방향정보를 다루기 위해 사용
	vPos.x += 200.f * m_vDir.x * fDT;
	vPos.y += 200.f * m_vDir.y * fDT;

	SetPos(vPos);
}

void CMissile::render(HDC _dc)
{
	Vec2 vPos = GetPos();
	Vec2 vScale = GetScale();

	Ellipse(_dc, (int)(vPos.x - vScale.x / 2), (int)(vPos.y - vScale.y / 2),
		(int)(vPos.x + vScale.x / 2), (int)(vPos.y + vScale.y / 2));

	Component_render(_dc);
}

void CMissile::OnCollisionEnter(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();

	if (pOtherObj->GetName() == L"Monster")
	{
		DeleteObject(this);
	}
}

CMissile::CMissile()
	: m_fTheta(M_PI / 4.f)
	, m_vDir(Vec2(1.f, 1.f))
{
	m_vDir.Normalize();
	CreateCollider();
	GetCollider()->SetScale(Vec2(15.f, 15.f));
}

CMissile::~CMissile()
{
}
