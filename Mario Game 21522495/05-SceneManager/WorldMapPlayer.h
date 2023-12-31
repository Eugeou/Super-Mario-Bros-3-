
#include "GameObject.h"
#include "Grass.h"

#define SPEED_MARIO 0.1f
#define MARIO_WORLD_MAP_BBOX_WIDTH 8
#define MARIO_WORLD_MAP_BBOX_HEIGHT 8


#define ID_ANI_MARIO_WORLD_MAP 1661
#define ID_ANI_MARIO_BIG_WORLD_MAP	1061
#define ID_ANI_MARIO_FIRE_WORLD_MAP 2361
#define ID_ANI_MARIO_TAIL_WORLD_MAP 3421
#define MARIO_STATE_NOT_MOVE 100
#define MARIO_STATE_GO_LEFT 200
#define MARIO_STATE_GO_TOP 300
#define MARIO_STATE_GO_RIGHT 400
#define MARIO_STATE_GO_UNDER 500

#define MARIO_STATE_GO_WORLD_1 600

#define TIME_DISPLAY_HUD_SUB 3000
#pragma once

class CWorldMapPlayer : public CGameObject
{
	ULONGLONG start_stop_hud_sub;
	int saveDoorProcess = 0;
	int sceneChange = 0;
	bool isCanGoWorld = false;
	float startX, startY;
	bool isGoingNodeX = false;
	bool isGoingNodeY = false;
	bool isAllowLeft;
	bool isAllowRight;
	bool isAllowTop;
	bool isAllowBottom;

	void OnCollisionWithDoor(LPCOLLISIONEVENT e);
	void OnCollisionWithOtherObject(LPCOLLISIONEVENT e);
public:
	CWorldMapPlayer(float x, float y) : CGameObject(x, y) {
		CDataGame* data = CGame::GetInstance()->GetDataGame();
		start_stop_hud_sub = GetTickCount64();
		isAllowLeft = data->GetAllowKeyLeft();
		isAllowTop = data->GetAllowKeyTop();
		isAllowRight = data->GetAllowKeyRight();
		isAllowBottom = data->GetAllowKeyBottom();
	}
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	int IsCollidable() { return 1; }
	int IsBlocking() { return 1; }
	virtual void OnNoCollision(DWORD dt);
	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

	virtual void SetState(int state);
	bool GetAllowLeft() { return isAllowLeft; }
	bool GetAllowTop() { return isAllowTop; }
	bool GetAllowRight() { return isAllowRight; }
	bool GetAllowBottom() { return isAllowBottom; }

	int CanActive() { return !vx && !vy; }
	void Go1NodeX(LPGAMEOBJECT gameobject);
	void Go1NodeY(LPGAMEOBJECT gameobject);
	void SaveData();
};