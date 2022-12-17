#pragma once
class CPathManager
{
	SINGLE(CPathManager)

private:
	wchar_t		m_szContentPath[256];
	wchar_t		m_szRelativePath[256];

public:
	void init();
	const wchar_t* GetContentPath() { return m_szContentPath; }

	//��θ� ������ �����η� ���� ��Ʈ�� �ڸ��� ����θ� �ǵ����ִ� �Լ�
	wstring GetRelativePath(const wchar_t* _filepath);
};

