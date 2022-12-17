#pragma once
class CTimeManager
{
	SINGLE(CTimeManager)

private:
	LARGE_INTEGER	m_llCurCount;
	LARGE_INTEGER	m_llPrevCount;
	LARGE_INTEGER	m_llFrequency;

	double			m_dDeltaTime;	//프레임 사이의 시간값
	double			m_dAcc;			//1초 체크를 위한 누적 시간
	UINT			m_iCallCount;	//함수 호출 횟수
	UINT			m_iFPS;			//초당 호출 횟수

	//FPS (Frame Per Second)
	//1프레임당 시간 (Delta Time)

public:
	void init();
	void update();
	void render();

public:
	double GetDT() { return m_dDeltaTime; }
	float GetfDT() { return (float)m_dDeltaTime; }
};

