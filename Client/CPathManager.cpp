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
	//�����쿡�� �����ϴ� ���� ���丮�� �˷��ִ� �Լ�
	GetCurrentDirectory(255, m_szContentPath);

	//���������� �̵�
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

	//��ü ���ڿ� �ȿ��� �������� ���̺��� ��ü���ڿ�-�������� ���̸� �� ����ŭ
	wstring strRelativePath = strFilePath.substr(iAbsLen, (iFullLen - iAbsLen));

	return strRelativePath;
}