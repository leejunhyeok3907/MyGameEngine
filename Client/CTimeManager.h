#pragma once
class CTimeManager
{
	SINGLE(CTimeManager)

private:
	LARGE_INTEGER	m_llCurCount;
	LARGE_INTEGER	m_llPrevCount;
	LARGE_INTEGER	m_llFrequency;

	double			m_dDeltaTime;	//������ ������ �ð���
	double			m_dAcc;			//1�� üũ�� ���� ���� �ð�
	UINT			m_iCallCount;	//�Լ� ȣ�� Ƚ��
	UINT			m_iFPS;			//�ʴ� ȣ�� Ƚ��

	//FPS (Frame Per Second)
	//1�����Ӵ� �ð� (Delta Time)

public:
	void init();
	void update();
	void render();

public:
	double GetDT() { return m_dDeltaTime; }
	float GetfDT() { return (float)m_dDeltaTime; }
};

