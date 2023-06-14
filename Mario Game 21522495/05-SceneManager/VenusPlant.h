#pragma once
#include "GameObject.h"


#define VENUSPLANT_SPEED 0.05f


#define VENUSPLANT_BBOX_WIDTH 20
#define VENUSPLANT_BBOX_HEIGHT 40
//#define VENUSPLANT_BBOX_HEIGHT_DIE 7

#define VENUSPLANT_UPORDOWN_TIME 600

#define VENUSPLANT_STATE_HEAD_UP 100
#define VENUSPLANT_STATE_HEAD_DOWN 200

#define ID_ANI_VENUSPLANT_HEAD_UP 7000
#define ID_ANI_VENUSPLANT_HEAD_DOWN 7001



class FireBall;
class CVenusPlant : public CGameObject
{
protected:
	float ax;
	float ay;

	ULONGLONG head_start;
	bool isHeadUp;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 0; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public:
	CVenusPlant(float x, float y);
	virtual void SetState(int state);
}; 
