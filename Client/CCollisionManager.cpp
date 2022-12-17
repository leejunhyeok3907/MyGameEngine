#include "pch.h"
#include "CCollisionManager.h"

#include "CSceneManager.h"
#include "CScene.h"

#include "CCollider.h"
#include "CObject.h"

CCollisionManager::CCollisionManager()
	: m_arrCheck{}
{

}

CCollisionManager::~CCollisionManager()
{

}

void CCollisionManager::init()
{
}

void CCollisionManager::update()
{
	for (UINT iRow = 0; iRow < (UINT)GROUP_TYPE::END; iRow++)
	{
		for (UINT iCol = iRow; iCol < (UINT)GROUP_TYPE::END; iCol++)
		{
			if (m_arrCheck[iRow] & (1 << iCol))
			{
				CollisionGroupUpdate((GROUP_TYPE)iRow, (GROUP_TYPE)iCol);
			}
		}
	}
}

void CCollisionManager::CheckGroup(GROUP_TYPE _eLeft, GROUP_TYPE _eRight)
{
	//더 작은 값의 그룹타입을 행으로
	//큰 값을 열(비트)로 사용
	UINT iRow = (UINT)min(_eLeft, _eRight);
	UINT iCol = (UINT)max(_eLeft, _eRight);

	if (m_arrCheck[iRow] & (1 << iCol))
	{
		m_arrCheck[iRow] &= ~(1 << iCol);
	}
	else
	{
		m_arrCheck[iRow] |= (1 << iCol);
	}
	
}

void CCollisionManager::CollisionGroupUpdate(GROUP_TYPE _eLeft, GROUP_TYPE _eRight)
{
	CScene* pCurScene = CSceneManager::GetInst()->GetCurScene();
	
	const vector<CObject*>& vecLeft = pCurScene->GetGroupObject(_eLeft);
	const vector<CObject*>& vecRight = pCurScene->GetGroupObject(_eRight);
	map<ULONGLONG, bool>::iterator iter;

	for (size_t i = 0; i < vecLeft.size(); i++)
	{
		//반복할때 충돌체가 없는 오브젝트라면
		if (nullptr == vecLeft[i]->GetCollider())
		{
			continue;
		}

		for (size_t j = 0; j < vecRight.size(); j++)
		{
			//충돌체가 없거나 자기 자신과의 충돌일경우
			if (nullptr == vecRight[j]->GetCollider()
				|| vecLeft[i] == vecRight[j])
			{
				continue;
			}

			CCollider* pLeftCol = vecLeft[i]->GetCollider();
			CCollider* pRightCol = vecRight[j]->GetCollider();

			// 두 충돌체의 조합 아이디 생성
			COLLIDER_ID ID;
			ID.iLeft_id = pLeftCol->GetID();
			ID.iRight_id = pRightCol->GetID();
			
			iter = m_mapCollisionInfo.find(ID.ID);

			if (m_mapCollisionInfo.end() == iter)//맵에 충돌정보가 등록 된적이 없다면
			{
				m_mapCollisionInfo.insert({ ID.ID, false });

				iter = m_mapCollisionInfo.find(ID.ID);
			}

			//두 물체가 충돌했을경우(현재 충돌중)
			if (IsCollision(pLeftCol, pRightCol))
			{
				//이전에도 충돌하고있었다
				if (iter->second)
				{
					if (vecLeft[i]->IsDead() || vecRight[j]->IsDead())
					{
						//둘중 하나가 삭제 예정이라면 충돌해제
						pLeftCol->OnCollisionExit(pRightCol);
						pRightCol->OnCollisionExit(pLeftCol);
						iter->second = false;
					}
					else
					{
						pLeftCol->OnCollision(pRightCol);
						pRightCol->OnCollision(pLeftCol);
					}
				}
				else //이전엔 충돌하지않았다면
				{
					if (!vecLeft[i]->IsDead() && !vecRight[j]->IsDead())
					{
						//둘중 하나가 삭제 예정이라면 충돌하지 않은것으로 취급
						pLeftCol->OnCollisionEnter(pRightCol);
						pRightCol->OnCollisionEnter(pLeftCol);
						iter->second = true;
					}
				}
			}
			else
			{
				//현재 충돌하고 있지 않다
				if (iter->second)
				{
					//충돌을 벗어난 시점
					pLeftCol->OnCollisionExit(pRightCol);
					pRightCol->OnCollisionExit(pLeftCol);
					iter->second = false;
				}
			}
		}
	}
}

bool CCollisionManager::IsCollision(CCollider* _pLeftCol, CCollider* _pRightCol)
{
	Vec2 vLeftPos = _pLeftCol->GetFinalPos();
	Vec2 vLeftScale = _pLeftCol->GetScale();

	Vec2 vRightPos = _pRightCol->GetFinalPos();
	Vec2 vRightScale = _pRightCol->GetScale();

	if (abs(vRightPos.x - vLeftPos.x) <= (vLeftScale.x + vRightScale.x) / 2.f &&
		abs(vRightPos.y - vLeftPos.y) <= (vLeftScale.y + vRightScale.y) / 2.f)
	{
		return true;
	}

	return false;
}
