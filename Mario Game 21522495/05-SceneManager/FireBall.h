#pragma once
#include "GameObject.h"


#define FIREBALL_FLYING_SPEED 0.05f
#define FIREBALL_BBOX_WIDTH 6
#define FIREBALL_BBOX_HEIGHT 6


#define FIREBALL_STATE_FYING 100


#define ID_ANI_FIREBALL_FLYING 6000


class CFireBall : public CGameObject
{
protected:
	float ax;
	float ay;

	//ULONGLONG start;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 0; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public:
	CFireBall(float x, float y);
	virtual void SetState(int state);
};