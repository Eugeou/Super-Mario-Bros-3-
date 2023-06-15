#include "VenusPlant.h"
#include "FireBall.h"
#include "Mario.h"
#include "PlayScene.h"
#

//const float VENUS_HEIGHT = 32 * 3;

CVenusPlant::CVenusPlant(float x, float y) : CGameObject(x, y)
{
	this->ax = 0;
	this->ay = 0;
	StartY = y;
	MinY = StartY - VENUSPLANT_BBOX_HEIGHT;
	SetState(VENUSPLANT_STATE_HEAD_UP);
}

void CVenusPlant::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == VENUSPLANT_STATE_DIE) return;
	left = x - VENUSPLANT_BBOX_WIDTH;
	top = y - VENUSPLANT_BBOX_HEIGHT;
	right = x + VENUSPLANT_BBOX_WIDTH;
	bottom = y + VENUSPLANT_BBOX_HEIGHT;
}

void CVenusPlant::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
	LPGAME game = CGame::GetInstance();
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	float Mx;
	Mx = mario->GetX();

	CGameObject::Update(dt, coObjects);
	if (mario->GetState() == MARIO_STATE_DIE) return;
	if (isUpping)
	{
		if (y > MinY)
		{
			vy = -VENUSPLANT_SPEED;
		}

		else
		{
			time_shoot = GetTickCount64();
			vy = 0;
			y = MinY;
			if (GetTickCount64() - time_out_pipe > TIME_OUT_PIPE)
				SetState(VENUSPLANT_STATE_HEAD_DOWN);
			else
			{
				
					if (!isShoot)
					{
						if (GetTickCount64() - time_shoot < TIME_SHOOT) {
							isShoot = true;
							bool isTop = false, isLeft = false;
							if (PositionXWithMario() == 1) { isTop = true; }
							if (PositionYWithMario() == 1) { isLeft = true; }
							if (isTop && isLeft) //Mario is standing on the top of the left of venus plant
							{
								CFireBall* fire = new CFireBall(x, y, isLeft, !isTop);
								scene->AddObject(fire);
							}
							else if (isTop && !isLeft) {
								CFireBall* fire = new CFireBall(x, y, isLeft, !isTop);
								scene->AddObject(fire);
							}
							else if (!isTop && !isLeft) {
								CFireBall* fire = new CFireBall(x, y, isLeft, !isTop);
								scene->AddObject(fire);
							}
							else if (!isTop && isLeft) {
								CFireBall* fire = new CFireBall(x, y, isLeft, !isTop);
								scene->AddObject(fire);
							}
						}
					}
				
			}
		}
	}
	else if (isDowning) {
		
		if ((y < StartY + 2))
		{
			vy = VENUSPLANT_SPEED;
		}
		else
		{
			vy = 0;
			y = StartY + 2;
			if (GetTickCount64() - time_down_pipe > TIME_DOWN_PIPE) {
				SetState(VENUSPLANT_STATE_HEAD_UP);
			}
		}
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);



	/*else if (y < 125 && x > Mx)
		SetState(VENUSPLANT_STATE_HEAD_DOWN_LEFT);
	else if (y < 125 && x < Mx)
		SetState(VENUSPLANT_STATE_HEAD_DOWN_RIGHT);
	else if (y > 170 && x < Mx)
		SetState(VENUSPLANT_STATE_HEAD_UP_RIGHT);*/

	/*if (state == VENUSPLANT_STATE_HEAD_UP_LEFT || state == VENUSPLANT_STATE_HEAD_UP_RIGHT)
		vy = -VENUSPLANT_SPEED;
	else if (state == VENUSPLANT_STATE_HEAD_DOWN_LEFT || state ==VENUSPLANT_STATE_HEAD_DOWN_RIGHT)
		vy = VENUSPLANT_SPEED;*/

	//y += vy * dt;
	
}

int CVenusPlant::PositionXWithMario() {
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	if (mario->GetX() < x) //mario left, plant right
	{
		return 1;
	}
	else return -1;
}

int CVenusPlant::PositionYWithMario() {
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	if (mario->GetY() < y) //mario top, plant under
	{
		return 1;
	}
	else return -1;
}

void CVenusPlant::Render()
{
	int aniId = -1;

	if (PositionXWithMario() == 1 && PositionYWithMario() == -1)
		if (!isShoot) aniId = ID_ANI_VENUSPLANT_LEFT_UNDER_NOT_SHOOT;
		else aniId = ID_ANI_VENUSPLANT_LEFT_UNDER_SHOOT;
	else if (PositionXWithMario() == 1 && PositionYWithMario() == 1)
		if (!isShoot) aniId = ID_ANI_VENUSPLANT_LEFT_TOP_NOT_SHOOT;
		else aniId = ID_ANI_VENUSPLANT_LEFT_TOP_SHOOT;
	else if (PositionXWithMario() == -1 && PositionYWithMario() == 1)
		if (!isShoot) aniId = ID_ANI_VENUSPLANT_RIGHT_TOP_NOT_SHOOT;
		else aniId = ID_ANI_VENUSPLANT_RIGHT_TOP_SHOOT;
	else {
		if (!isShoot) aniId = ID_ANI_VENUSPLANT_RIGHT_UNDER_NOT_SHOOT;
		else aniId = ID_ANI_VENUSPLANT_RIGHT_UNDER_SHOOT;
	}
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
}


void CVenusPlant::SetState(int state)
{
	switch (state)
	{
	case VENUSPLANT_STATE_HEAD_UP:
		
		//vy = -VENUSPLANT_SPEED;
		isUpping = true;
		isDowning = false;
		isShoot = false;
		time_out_pipe = GetTickCount64();
		time_down_pipe = 0;
		break;
	case VENUSPLANT_STATE_HEAD_DOWN:
		//vy = VENUSPLANT_SPEED;
		isShoot = false;
		isUpping = false;
		isDowning = true;
		time_down_pipe = GetTickCount64();
		time_out_pipe = 0;
		break;
	case VENUSPLANT_STATE_DIE:
		isDeleted = true;
		break;
	}
	CGameObject::SetState(state);
}

void CVenusPlant::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CVenusPlant::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CVenusPlant*>(e->obj)) return;

}