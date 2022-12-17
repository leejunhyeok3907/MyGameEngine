#pragma once


class CAnimator;
class CTexture;

struct tAnimFrame
{
	Vec2 vLT;
	Vec2 vSlice;
	Vec2 vOffset;
	float fDuration;
};

class CAnimation
{
private:
	wstring	m_strName;
	CAnimator* m_pAnimator;
	CTexture* m_pTex;					//Animation이 사용하는 텍스쳐
	vector<tAnimFrame> m_vecFrame;		//모든 프레임 정보
	int	m_iCurFrame;					//현재 프레임 번호
	float m_fAccTime;					//시간 누적

	bool m_bFinish;						//Animation 재생 여부

private:
	void SetName(const wstring& _strName) { m_strName = _strName; }

public:
	const wstring& GetName() { return m_strName; }
	bool IsFinish() { return m_bFinish; }

	void SetFrame(int _iFrameIndex)
	{
		m_bFinish = false;
		m_iCurFrame = _iFrameIndex;
		m_fAccTime = 0.f;
	};

	tAnimFrame& GetFrame(int _iIdx) { return m_vecFrame[_iIdx]; }
	UINT GetFrameSize() { return (UINT)m_vecFrame.size(); }


public:
	void update();
	void render(HDC _dc);
	void Create(CTexture* _pTex, Vec2 _vLT, Vec2 _vSliceSize, Vec2 _vStep, float _fDuration, UINT _iFrameCount);

public:
	void Save(const wstring& _strRelativePath);
	void Load(const wstring& _strRelativePath);

public:
	CAnimation();
	~CAnimation();

	friend class CAnimator;
};

