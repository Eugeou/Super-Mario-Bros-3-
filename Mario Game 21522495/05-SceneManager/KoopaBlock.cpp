#include "KoopaBlock.h"
#include "Textures.h"

CKoopaBlock::CKoopaBlock(float x, float y) : CGameObject(x, y)
{
	this->ay = GRAVITY;
}

void CKoopaBlock::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}

void CKoopaBlock::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (e->obj->IsBlocking()) return;

	if (e->ny < 0 && e->obj->IsBlocking())
	{
		vy = 0;
	}
}

void CKoopaBlock::Render()
{
	RenderBoundingBox();
}

void CKoopaBlock::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CKoopaBlock::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - FALL_CELL_WIDTH / 2;
	t = y - FALL_CELL_HEIGHT / 2;
	r = l + FALL_CELL_WIDTH;
	b = t + FALL_CELL_HEIGHT;
}


