#include "Leaf.h"
#include "Platform.h"


#define LEAF_FALL_SPEED 0.0001f
#define LEAF_SPEED 0.04f
#define ADJUST_AX_WHEN_FALL 0.0001f
#define ADJUST_MAX_VX 0.085f
#define OUT_BRICK 0.13f

CLeaf::CLeaf(float x, float y) :CGameObject(x, y)
{
	this->ax = 0;
	this->ay = LEAF_FALL_SPEED;
	vy = -OUT_BRICK;
	isOnPlatForm = false;
	SetState(LEAF_STATE_FALL);
}
CLeaf::CLeaf(float x, float y, int state) {
	this->x = x;
	this->y = y;
	this->ax = 0;
	this->state = state;
}

void CLeaf::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	
	if (isOnPlatForm) {
		vy = 0;
		ay = 0;
	}
	else {
		if (vy < MAX_VY) {
			vy += ay * dt;
		}
		else vy = ay * dt;
		if (vy > 0) {
			if (vx <= ADJUST_MAX_VX) {
				vx += ax * dt;
			}
			else vx = -vx;
		}
	}
	//	DebugOut(L"[Vy cua la cay] %f\n", vy);


	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CLeaf::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CLeaf::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking() && !e->obj->IsPlatform()) return;
	if (dynamic_cast<CLeaf*>(e->obj)) return;

	if (e->ny != 0)
	{
		isOnPlatForm = true;
		vy = 0;
		vx = 0;
	}
	else if (dynamic_cast<CPlatform*>(e->obj))
		OnCollisionWithPlatForm(e);
}