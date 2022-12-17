#pragma once

struct tEvent
{
	EVENT_TYPE	eEven;
	DWORD_PTR	lParam;
	DWORD_PTR	wParam;
};

class CEventManager
{
	SINGLE(CEventManager)
private:
	vector<tEvent> m_vecEvent;
	vector<CObject*> m_vecDeadObj;

public:
	void update();

private:
	void Execute(const tEvent& _event);

public:
	void AddEvent(const tEvent& _event) { m_vecEvent.push_back(_event); }

};

