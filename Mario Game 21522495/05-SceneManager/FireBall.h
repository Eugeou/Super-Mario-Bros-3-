#pragma once
#include "GameObject.h"


#define BULLET_SPEED_X	0.05f
#define BULLET_SPEED_Y	0.07f
#define TIME_FIREBALL_DELETE 4000
#define FIREBALL_BBOX_WIDTH 6
#define FIREBALL_BBOX_HEIGHT 6


#define FIREBALL_STATE_FYING 100


#define ID_ANI_FIREBALL_FLYING 6000


class CFireBall : public CGameObject
{
protected:
	float ax;
	float ay;

	ULONGLONG start_del;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 0; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public:
	CFireBall(float x, float y, bool Up, bool Right);
	virtual void SetState(int state);
};