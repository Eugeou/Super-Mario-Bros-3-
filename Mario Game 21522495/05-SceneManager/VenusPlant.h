﻿#pragma once
#include "GameObject.h"

#define VENUSPLANT_SPEED 0.025f

#define TIME_OUT_PIPE 5000
#define TIME_SHOOT 100
#define TIME_DOWN_PIPE 3000

#define VENUSPLANT_SHOOT_RED 1
#define VENUSPLANT_SHOOT_GREEN 2
#define VENUSPLANT_NOT_SHOOT 3


#define VENUSPLANT_BBOX_WIDTH 12
#define VENUSPLANT_BBOX_HEIGHT_SMALL 24
#define VENUSPLANT_BBOX_HEIGHT 32

#define VENUSPLANT_STATE_UP 100
#define VENUSPLANT_STATE_DOWN 200
#define VENUSPLANT_STATE_DEATH 300

//Top - nhìn lên ; Under  - nhìn xuống để tránh trùng với up và down
#define ID_ANI_VENUSPLANT_LEFT_UNDER_NOT_SHOOT	301 //Venus nhìn xuống phía trái và ko bắn đạn
#define ID_ANI_VENUSPLANT_LEFT_UNDER_SHOOT 302
#define ID_ANI_VENUSPLANT_LEFT_TOP_NOT_SHOOT 303 //Venus nhìn lên phía trái và ko bắn đạn
#define ID_ANI_VENUSPLANT_LEFT_TOP_SHOOT 304
#define ID_ANI_VENUSPLANT_RIGHT_UNDER_NOT_SHOOT	305
#define ID_ANI_VENUSPLANT_RIGHT_UNDER_SHOOT 306
#define ID_ANI_VENUSPLANT_RIGHT_TOP_NOT_SHOOT 307
#define ID_ANI_VENUSPLANT_RIGHT_TOP_SHOOT 308

//Green venus - Piranha plant
#define ID_ANI_PLANT_LEFT_UNDER_NOT_SHOOT_GREEN	321
#define ID_ANI_PLANT_LEFT_UNDER_SHOOT_GREEN 322
#define ID_ANI_PLANT_LEFT_TOP_NOT_SHOOT_GREEN 323
#define ID_ANI_PLANT_LEFT_TOP_SHOOT_GREEN 324
#define ID_ANI_PLANT_RIGHT_UNDER_NOT_SHOOT_GREEN 325
#define ID_ANI_PLANT_RIGHT_UNDER_SHOOT_GREEN 326
#define ID_ANI_PLANT_RIGHT_TOP_NOT_SHOOT_GREEN 327
#define ID_ANI_PLANT_RIGHT_TOP_SHOOT_GREEN 328

#define ID_ANI_PLANT_NOT_SHOOT 311
#define DISTANCE_PIPE_LONG_SHORT 8


class CVenusPlant : public CGameObject
{
protected:
	float startY;
	float minY;
	bool isShoot = false;
	int model;
	bool isUpping, isDowning;
	ULONGLONG time_out_pipe;
	ULONGLONG time_shoot;
	ULONGLONG time_down_pipe;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	int PositionYWithMario(); //1 if mario on top plant, -1 if mario underplant
	int PositionXWithMario(); //1 if mario left to plant, -1 if mario right to plant

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual int IsEnemy() { return 1; }

	virtual void OnNoCollision(DWORD dt);

public:

	CVenusPlant(float x, float y, int model);
	virtual void SetState(int state);
	void SetModel(int model) { this->model = model; }
	int GetModel() { return model; }
};

