#include "pch.h"
#include "CRigidBody.h"
#include "CTimeManager.h"
#include "CObject.h"

CRigidBody::CRigidBody()
	: m_pOwner(nullptr)
	, m_fMass(1.f)
	, m_fFrictionCoef(100.f)
	, m_vMaxVelocity(Vec2(200.f, 600.f))
{
}

CRigidBody::~CRigidBody()
{
}

void CRigidBody::finalupdate()
{
	m_vForce;

	//���� ũ��
	float fForce = m_vForce.Length();

	//�־��� ���� ���� ����
	if (0.f != fForce)
	{
		//���� ����
		m_vForce.Normalize();

		//���ӵ��� ũ��(���� ũ��/����)
		float m_fAccel = fForce / m_fMass;

		//���ӵ�
		m_vAccel = m_vForce * m_fAccel;
	}

	//���� �ֵ� ���簣�� �߰� ���ӵ��� ����Ǿ�� ��
	m_vAccel += m_vAccel_A;

	//�ӵ�
	m_vVelocity += m_vAccel * fDT;

	// �����¿� ���� �ݴ���������� ���ӵ�
	if (!m_vVelocity.IsZero())
	{
		Vec2 vFricDir = -m_vVelocity;
		Vec2 vFriction = vFricDir.Normalize() * m_fFrictionCoef * fDT;
		if (m_vVelocity.Length() <= vFriction.Length())
		{
			//���� ���ӵ��� ���� �ӵ����� �� ū ���
			m_vVelocity = Vec2(0.f, 0.f);
		}
		else
		{
			m_vVelocity += vFriction;
		}
	}

	// �ӵ� ���� �˻�
	// ��� �����̵� �ִ� ��ġ�� �̾߱��ϹǷ� ���밪���� �˻�
	if (abs(m_vMaxVelocity.x) < abs(m_vVelocity.x))
	{
		//�ڽ��� ���밪���� ������� ���⼺ ������ �����Ե�(-1, 1)
		m_vVelocity.x /= abs(m_vVelocity.x);
		//���⼺ ������ �ִ� �ӷ� ����
		m_vVelocity.x *= m_vMaxVelocity.x;
	}

	if (abs(m_vMaxVelocity.y) < abs(m_vVelocity.y))
	{
		m_vVelocity.y /= abs(m_vVelocity.y);
		m_vVelocity.y *= m_vMaxVelocity.y;
	}

	//�ӵ��� ���� �̵�
	Move();

	//�� �ʱ�ȭ
	m_vForce = Vec2(0.f, 0.f);

	//���ӵ� �ʱ�ȭ
	m_vAccel = Vec2(0.f, 0.f);
	m_vAccel_A = Vec2(0.f, 0.f);
}

void CRigidBody::Move()
{
	//�̵� �ӷ�
	float fSpeed = m_vVelocity.Length();

	if (0.f != fSpeed)
	{
		//�̵� ����
		Vec2 vDir = m_vVelocity;
		vDir.Normalize();

		Vec2 vPos = m_pOwner->GetPos();

		//vPos += vDir * fSpeed * fDT;
		vPos += m_vVelocity * fDT;

		m_pOwner->SetPos(vPos);
	}
}