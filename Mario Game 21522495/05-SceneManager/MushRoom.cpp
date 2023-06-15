#include "MushRoom.h"

#include "Platform.h"
#include "PlayScene.h"
#include "Mario.h"

#define MUSHROOM_GRAVITY 0.001f
#define MUSHROOM_SPEED 0.055f
#define OUT_BRICK -0.016f

CMushRoom::CMushRoom(float x, float y) :CGameObject(x, y)
{
	this->ax = 0;
	this->ay = MUSHROOM_GRAVITY;
	vy = 0;
	model = MUSHROOM_RED;
	startY = y;
	SetState(MUSHROOM_STATE_OUTSIDE);
}

CMushRoom::CMushRoom(float x, float y, int model) :CGameObject(x, y)
{
	this->ax = 0;
	this->ay = MUSHROOM_GRAVITY;
	vy = 0;
	this->model = model;
	startY = y;
	SetState(MUSHROOM_STATE_OUTSIDE);
}

void CMushRoom::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	if (state == MUSHROOM_STATE_WALKING) {
		vy += ay * dt;
		vx += ax * dt;
	}
	else if (state == MUSHROOM_STATE_OUTSIDE) {
		if (startY - y < MUSHROOM_BBOX_HEIGHT) {
			vy = OUT_BRICK;
			vx = 0;
		}
		else SetState(MUSHROOM_STATE_WALKING);
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CMushRoom::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CMushRoom::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking() && !e->obj->IsPlatform()) return;
	if (!e->obj->IsPlayer()) {
		if (e->ny != 0)
		{
			vy = 0;
		}
		else if (e->nx != 0)
		{
			vx = -vx;
		}
	}

	if (dynamic_cast<CMushRoom*>(e->obj)) {}
	else if (dynamic_cast<CPlatform*>(e->obj))
		OnCollisionWithPlatForm(e);

}
