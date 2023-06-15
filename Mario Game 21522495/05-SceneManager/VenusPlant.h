#pragma once
#include "GameObject.h"


#define VENUSPLANT_SPEED 0.03f
#define VENUSPLANT_SHOOT_RED 1

#define VENUSPLANT_BBOX_WIDTH 20
#define VENUSPLANT_BBOX_HEIGHT 40
//#define VENUSPLANT_BBOX_HEIGHT_DIE 7

#define TIME_OUT_PIPE 5000
#define TIME_SHOOT 100
#define TIME_DOWN_PIPE 3000


#define VENUSPLANT_STATE_HEAD_UP_LEFT 100
#define VENUSPLANT_STATE_HEAD_DOWN_LEFT 200
#define VENUSPLANT_STATE_HEAD_UP_RIGHT 300
#define VENUSPLANT_STATE_HEAD_DOWN_RIGHT 400
#define VENUSPLANT_STATE_WAIT 500


#define ID_ANI_VENUSPLANT_HEAD_UP_LEFT 7000
#define ID_ANI_VENUSPLANT_HEAD_DOWN_LEFT 7001
#define ID_ANI_VENUSPLANT_HEAD_UP_RIGHT 7002
#define ID_ANI_VENUSPLANT_HEAD_DOWN_RIGHT 7003
const float VENUS_WAIT_TIME = 1000; // Thời gian dừng lại khi lên đến vị trí cao nhất (đơn vị: milliseconds)



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
	int Model;
	

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
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
