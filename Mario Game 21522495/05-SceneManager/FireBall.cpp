#include "FireBall.h"
#include "Mario.h"
#include "PlayScene.h"
#include "Animation.h"
#include "VenusPlant.h"
#include "Pipe.h"
#include "Map.h"

CFireBall::CFireBall(float bx, float by, bool Up, bool Right)
{
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();

	if (Up)
	{
		y = by - VENUSPLANT_BBOX_HEIGHT / 2;
		vy = -BULLET_SPEED_Y_PLANT;
	}
	else
	{
		y = by + VENUSPLANT_BBOX_HEIGHT / 2;
		vy = BULLET_SPEED_Y_PLANT;
	}


	if (Right)
	{
		x = bx + VENUSPLANT_BBOX_WIDTH;
		vx = BULLET_SPEED_X_PLANT;
	}
	else
	{
		x = bx - VENUSPLANT_BBOX_WIDTH;
		vx = -BULLET_SPEED_X_PLANT;
	}
	start_deleted = GetTickCount64();
}
void CFireBall::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (!checkObjectInCamera(this)) return;

	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	if (mario->GetIsChanging() || mario->GetState() == MARIO_STATE_DIE) return;
	if (GetTickCount64() - start_deleted > TIME_BULLET_DELETE) {
		isDeleted = true;
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}
void CFireBall::Render()
{
	if (!checkObjectInCamera(this)) return;

	CAnimations* animations = CAnimations::GetInstance();

	int aniId = 0;
	if (vx > 0)
		aniId = ID_ANI_BULLET_RIGHT;
	else
		aniId = ID_ANI_BULLET_LEFT;
	animations->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
}
void CFireBall::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + BULLET_BBOX_WIDTH_PLANT;
	b = y + BULLET_BBOX_HEIGHT_PLANT;
}

void CFireBall::OnCollisionWith(LPCOLLISIONEVENT e) {
	if (dynamic_cast<CPipe*>(e->obj)) return;
	if (e->obj->IsPlatform() && e->obj->IsBlocking()) isDeleted = true;

}