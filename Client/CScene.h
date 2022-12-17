#pragma once

#include "CMonFactory.h"

//���漱��
//������ �ӵ��� ������ �����ʱ����� ����� ������������.
//�̿� ���� ������ ������ �� ���⶧���� ������Ÿ�����θ� ��밡����.
class CObject;

class CScene
{
private:
	//������Ʈ�� ���� �� ������ ���͸� �׷찳����ŭ ����
	vector<CObject*>	m_arrObj[(UINT)GROUP_TYPE::END];
	wstring				m_strName;

	UINT				m_iTileX;	//Ÿ�� ���� ����
	UINT				m_iTileY;	//Ÿ�� ���� ����

	CObject*			m_pPlayer;  // Player��ü

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

	//���� �����Լ�
	//��ü�� �����Ҽ� ���� �߻�Ŭ������ ��.
	virtual void Enter() PURE;//�ش� Scene�� ���Խ� ȣ��
	virtual void Exit() PURE;//�ش� Scene�� Ż��� ȣ��

public:
	//�Լ��� ����� �����ϸ� �ζ���ó���Ǿ� ȣ��Ǿ �ش� ���ÿ��� ó���Ѵ�. (�Լ� ȣ���� ����)
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

