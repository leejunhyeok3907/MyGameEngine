#pragma once

#include "CMonFactory.h"

//전방선언
//컴파일 속도에 영향을 주지않기위해 헤더를 참조하지않음.
//이에 대한 내용을 참조할 수 없기때문에 포인터타입으로만 사용가능함.
class CObject;

class CScene
{
private:
	//오브젝트를 저장 및 관리할 벡터를 그룹개수만큼 선언
	vector<CObject*>	m_arrObj[(UINT)GROUP_TYPE::END];
	wstring				m_strName;

	UINT				m_iTileX;	//타일 가로 개수
	UINT				m_iTileY;	//타일 세로 개수

	CObject*			m_pPlayer;  // Player객체

public:
	void SetName(const wstring& _strName) { m_strName = _strName; }
	const wstring& GetName() { return m_strName; }

	UINT GetTileX() { return m_iTileX; }
	UINT GetTileY() { return m_iTileY; }

	CObject* GetPlayer() { return m_pPlayer; }

	virtual void init();
	virtual void update();
	virtual void finalupdate();
	virtual void render(HDC _dc);

	//순수 가상함수
	//객체를 생성할수 없는 추상클래스가 됨.
	virtual void Enter() PURE;//해당 Scene에 진입시 호출
	virtual void Exit() PURE;//해당 Scene의 탈출시 호출

public:
	//함수를 헤더에 구현하면 인라인처리되어 호출되어도 해당 스택에서 처리한다. (함수 호출비용 없음)
	void AddObject(CObject* _pObj, GROUP_TYPE _eType)
	{
		m_arrObj[(UINT)_eType].push_back(_pObj);
	}

	void RegisterPlayer(CObject* _pPlayer) { m_pPlayer = _pPlayer; }

	const vector<CObject*>& GetGroupObject(GROUP_TYPE _eType)
	{
		return m_arrObj[(UINT)_eType];
	}

	void DeleteGroup(GROUP_TYPE _eType);
	void DeleteAll();

	void CreateTile(UINT _iXCount, UINT _iYCount);
	void LoadTile(const wstring& _strRelativePath);
	void render_tile(HDC _dc);

	vector<CObject*>& GetUIGroup() { return m_arrObj[(UINT)GROUP_TYPE::UI]; }

public:
	CScene();
	virtual ~CScene();
};

