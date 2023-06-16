﻿#pragma once
#include"GameObject.h"

#define KOOPA_GRAVITY 0.001f
#define KOOPA_WALKING_SPEED 0.04f
#define KOOPA_IS_KICKED_SPEED 0.18f
#define KOOPA_JUMP_DEATH 0.4f
#define KOOPA_ADJUST_NOT_FALL 0.1f
#define KOOPA_ADJUST_KICKED_NOT_FALL 0.1f
#define KOOPA_KICKED_NOT_FALL 0.04f

#define KOOPA_GRAVITY_WING 0.0005f
#define KOOPA_JUMP_SPEED 0.2f
#define KOOPA_JUMP_IS_ATTACKED 0.4f

#define KOOPA_DEFEND_TIMEOUT 8000 // hết thời gian defend ( ra khỏi mai rùa và bắt đầu đi)
#define KOOPA_COMBACK_START 6000 //thời gian tính từ lúc defend đến lúc có hiệu ứng comeback

#define KOOPA_DIE_TIME 10000

#define KOOPA_BBOX_WIDTH 16
#define KOOPA_BBOX_HEIGHT 26
#define KOOPA_BBOX_HEIGHT_DEFEND 16


//Red
#define ID_ANI_RED_WALK_RIGHT 6101
#define ID_ANI_RED_WALK_LEFT 6102
#define ID_ANI_RED_DEFEND 6103
#define ID_ANI_RED_KICKED 6104
#define ID_ANI_RED_UPSIDE 6105
#define ID_ANI_RED_COMEBACK 6106
#define ID_ANI_RED_UPSIDE_KICKED 6107
#define ID_ANI_RED_UPSIDE_COMEBACK 6108


#define KOOPA_RED 2


#define KOOPA_STATE_WALKING 100
#define KOOPA_STATE_DEFEND 200
#define KOOPA_STATE_IS_KICKED 300
#define KOOPA_STATE_UPSIDE 400
#define KOOPA_STATE_JUMP 500
#define KOOPA_STATE_ISDEAD 600
#define KOOPA_STATE_DEAD_UPSIDE 700


class CKoopa : public CGameObject
{
protected:
	float ax;
	float ay;
	int model;
	ULONGLONG defend_start;
	ULONGLONG die_start;
	ULONGLONG comeback_start;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return !isDead; };
	int PositionWithMario();
	virtual int IsBlocking() { return 0; }
	virtual int IsEnemy() { return 1; }
	virtual void OnNoCollision(DWORD dt);

	bool isDead;
};