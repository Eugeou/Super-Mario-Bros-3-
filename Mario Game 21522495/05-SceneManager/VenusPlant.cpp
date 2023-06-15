#include "VenusPlant.h"
#include "FireBall.h"
#include "Mario.h"
#include "PlayScene.h"
#

const float VENUS_HEIGHT = 32 * 3;

CVenusPlant::CVenusPlant(float x, float y) : CGameObject(x, y)
{
	this->ax = 0;
	this->ay = 0;
	StartY = y;
	MinY = StartY - VENUSPLANT_BBOX_HEIGHT;
	SetState(VENUSPLANT_STATE_HEAD_UP_LEFT);
}

void CVenusPlant::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (Model == VENUSPLANT_SHOOT_RED)
	{
		left = x - VENUSPLANT_BBOX_WIDTH;
		top = y - VENUSPLANT_BBOX_HEIGHT;
		right = x + VENUSPLANT_BBOX_WIDTH;
		bottom = y + VENUSPLANT_BBOX_HEIGHT;
	}
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
		if (y > MinY && x > Mx)
		{
			SetState(VENUSPLANT_STATE_HEAD_UP_LEFT);
		}
	}
	else
	{
		time_shoot = GetTickCount64();
		vy = 0;
		y = MinY;
		if (GetTickCount64() - time_out_pipe > TIME_OUT_PIPE)
			SetState(VENUSPLANT_STATE_HEAD_DOWN_LEFT);
		else
		{
			if (Model == VENUSPLANT_SHOOT_RED)
			{
				if (!isShoot)
				{
					if (GetTickCount64() - time_shoot < TIME_SHOOT) {
						isShoot = true;
						bool isTop = false, isLeft = false;
						if (PositionXWithMario() == 1) { isTop = true; }
						if (PositionYWithMario() == 1) { isLeft = true; }
						if (isTop && isLeft) //Mario is stading on the top of the left of venus plant
						{
							CFireBall* fire = new CFireBall()
						}


					}
				}
			}
		}
	}


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

	y += vy * dt;

	
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
	int ani = ID_ANI_VENUSPLANT_HEAD_UP_LEFT;

	if (state == VENUSPLANT_STATE_HEAD_DOWN_LEFT)
		ani = ID_ANI_VENUSPLANT_HEAD_DOWN_LEFT;

	else if (state == VENUSPLANT_STATE_HEAD_UP_LEFT)
		ani = ID_ANI_VENUSPLANT_HEAD_UP_LEFT;

	else if (state == VENUSPLANT_STATE_HEAD_DOWN_RIGHT)
		ani = ID_ANI_VENUSPLANT_HEAD_DOWN_RIGHT;

	else if (state == VENUSPLANT_STATE_HEAD_UP_RIGHT)
		ani = ID_ANI_VENUSPLANT_HEAD_UP_RIGHT;
	CAnimations::GetInstance()->Get(ani)->Render(x, y);
}


void CVenusPlant::SetState(int state)
{
	
	CGameObject::SetState(state);
	switch (state)
	{
	case VENUSPLANT_STATE_HEAD_DOWN_LEFT:
		vy = VENUSPLANT_SPEED;
		
		break;
	case VENUSPLANT_STATE_HEAD_UP_LEFT:
		
		vy = -VENUSPLANT_SPEED;
		
		break;
	case VENUSPLANT_STATE_HEAD_DOWN_RIGHT:
		vy = VENUSPLANT_SPEED;
		
		
		break;
	case VENUSPLANT_STATE_HEAD_UP_RIGHT:
		vy = -VENUSPLANT_SPEED;
		break;
	case VENUSPLANT_STATE_WAIT:
		vy = 0;
		break;
	}
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