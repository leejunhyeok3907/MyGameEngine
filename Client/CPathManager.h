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

	//경로를 받으면 절대경로로 가는 파트를 자르고 상대경로만 되돌려주는 함수
	wstring GetRelativePath(const wchar_t* _filepath);
};

