#include "FireBall.h"
#include "Mario.h"
#include "PlayScene.h"
#include "VenusPlant.h"



CFireBall::CFireBall(float x, float y, bool Up, bool Right) :CGameObject(x, y)
{

	this->ax = 0;
	this->ay = 0;
	//start = -1;
	SetState(FIREBALL_STATE_FYING);
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	if (Up)
	{
		y = y - VENUSPLANT_BBOX_HEIGHT / 2;
		vy = -BULLET_SPEED_Y;
	}
	else
	{
		y = y + VENUSPLANT_BBOX_HEIGHT / 2;
		vy = BULLET_SPEED_Y;
	}
	if (Right)
	{
		x = x + VENUSPLANT_BBOX_WIDTH;
		vx = BULLET_SPEED_X;
	}
	else
	{
		x = x - VENUSPLANT_BBOX_WIDTH;
		vx = -BULLET_SPEED_X;
	}
	start_del = GetTickCount64();

}

void CFireBall::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = left + FIREBALL_BBOX_WIDTH;
	bottom = top + FIREBALL_BBOX_HEIGHT;
	
}

void CFireBall::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CFireBall::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CFireBall*>(e->obj)) return;

}

void CFireBall::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	if (mario->GetState() == MARIO_STATE_DIE) return;
	if (GetTickCount64() - start_del > TIME_FIREBALL_DELETE) {
		isDeleted = true;
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CFireBall::Render()
{
	int aniId = ID_ANI_FIREBALL_FLYING;

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	RenderBoundingBox();
}

void CFireBall::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case FIREBALL_STATE_FYING:
		vx = BULLET_SPEED_X;
		break;
	}
}
