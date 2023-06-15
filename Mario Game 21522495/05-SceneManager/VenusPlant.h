#pragma once
#include "GameObject.h"


#define VENUSPLANT_SPEED 0.03f


#define VENUSPLANT_BBOX_WIDTH 15
#define VENUSPLANT_BBOX_HEIGHT 40
//#define VENUSPLANT_BBOX_HEIGHT_DIE 7

#define TIME_OUT_PIPE 3000
#define TIME_SHOOT 100
#define TIME_DOWN_PIPE 2000


#define VENUSPLANT_STATE_HEAD_UP 100
#define VENUSPLANT_STATE_HEAD_DOWN 200
#define VENUSPLANT_STATE_DIE 300

//To avoid misunderstanding,I use UNDER means Look down and TOP means Look up
#define ID_ANI_VENUSPLANT_LEFT_UNDER_NOT_SHOOT	301 //Venus look down on the left and keep mounth shut
#define ID_ANI_VENUSPLANT_LEFT_UNDER_SHOOT 302 
#define ID_ANI_VENUSPLANT_LEFT_TOP_NOT_SHOOT 303 //Venus look up......
#define ID_ANI_VENUSPLANT_LEFT_TOP_SHOOT 304
#define ID_ANI_VENUSPLANT_RIGHT_UNDER_NOT_SHOOT	305 //Venus look down on the right and keep mounth shut
#define ID_ANI_VENUSPLANT_RIGHT_UNDER_SHOOT 306
#define ID_ANI_VENUSPLANT_RIGHT_TOP_NOT_SHOOT 307 //Venus look up......
#define ID_ANI_VENUSPLANT_RIGHT_TOP_SHOOT 308



class FireBall;
class CVenusPlant : public CGameObject
{
protected:
	float ax;
	float ay;
	float StartY;
	float MinY;
	bool isShoot = false;
	ULONGLONG time_out_pipe;
	ULONGLONG time_shoot;
	ULONGLONG time_down_pipe;
	bool isUpping, isDowning;
	

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 0; };
	virtual int IsBlocking() { return 0; }
	virtual int IsEnemy() { return 1; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
	int PositionYWithMario(); //1 if mario on top plant, -1 if mario underplant
	int PositionXWithMario(); //1 if mario left to plant, -1 if mario right to plant


public:
	CVenusPlant(float x, float y);
	virtual void SetState(int state);
}; 
