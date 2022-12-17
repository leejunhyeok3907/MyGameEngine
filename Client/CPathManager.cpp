#include "pch.h"
#include "CPathManager.h"
#include "CCore.h"

CPathManager::CPathManager()
	: m_szContentPath{}
{
}

CPathManager::~CPathManager()
{
}


void CPathManager::init()
{
	//윈도우에서 제공하는 현재 디렉토리를 알려주는 함수
	GetCurrentDirectory(255, m_szContentPath);

	//상위폴더로 이동
	int iLen = (int)wcslen(m_szContentPath);

	for (int i = iLen - 1; 0 <= i; i--)
	{
		if ('\\' == m_szContentPath[i])
		{
			m_szContentPath[i] = '\0';
			break;
		}
	}

	// + bin\\content\\

	wcscat_s(m_szContentPath, 255, L"\\bin\\content\\");
}

wstring CPathManager::GetRelativePath(const wchar_t* _filepath)
{
	wstring strFilePath = _filepath;

	size_t iAbsLen = wcslen(m_szContentPath);
	size_t iFullLen = strFilePath.length();

	//전체 문자열 안에서 절대경로의 길이부터 전체문자열-절대경로의 길이를 뺀 값만큼
	wstring strRelativePath = strFilePath.substr(iAbsLen, (iFullLen - iAbsLen));

	return strRelativePath;
}