#pragma once

//싱글톤 매크로
#define SINGLE(type) \
public:\
static type* GetInst() \
{ \
	static type mgr; \
	return &mgr; \
} \
private:\
type();\
~type();

#define CLONE(type) type* Clone() {return new type(*this);}

#define fDT CTimeManager::GetInst()->GetfDT()
#define DT CTimeManager::GetInst()->GetDT()

#define KEY_CHECK(key, state) CKeyManager::GetInst()->GetKeyState(key)==state
#define KEY_HOLD(key) KEY_CHECK(key, KEY_STATE::HOLD)
#define KEY_TAP(key) KEY_CHECK(key, KEY_STATE::TAP)
#define KEY_AWAY(key) KEY_CHECK(key, KEY_STATE::AWAY)
#define KEY_NONE(key) KEY_CHECK(key, KEY_STATE::NONE)
#define MOUSE_POS CKeyManager::GetInst()->GetMousePos()

//2의 n승수로 잘리는 숫자를 사용하는것이 GPU최적화에 유리함
#define TILE_SIZE 64

//Scene안에 있는 오브젝트들을 분류
enum class GROUP_TYPE
{
	DEFAULT,
	TILE,
	GROUND,
	PLAYER,
	MONSTER,
	PROJECTILE_PLAYER,
	PROJECTILE_MONSTER,

	UI = 31,
	END = 32,
};

enum class SCENE_TYPE
{
	TOOL,
	START,
	STAGE_01,
	STAGE_02,

	END,
};

enum class COMPONENT_TYPE
{
	COLLIDER,
	ANIMATOR,
	RIGID_BODY,
	GRAVITY,
	END,
};

enum class BRUSH_TYPE
{
	HOLLOW,
	BLACK,
	END,
};

enum class PEN_TYPE
{
	RED,
	GREEN,
	BLUE,
	END,
};

enum class EVENT_TYPE
{
	CREATE_OBJECT,
	DELETE_OBJECT,
	SCENE_CHANGE,
	CHANGE_AI_STATE,


	END,
};

enum class MON_STATE
{
	IDLE,
	PATROL,
	TRACE,
	ATTACK,
	RUN,
	DEAD,
	END,
};