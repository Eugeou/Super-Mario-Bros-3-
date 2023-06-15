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
	wait = 0;
	SetState(VENUSPLANT_STATE_HEAD_UP_LEFT);
}

void CVenusPlant::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - VENUSPLANT_BBOX_WIDTH;
	top = y - VENUSPLANT_BBOX_HEIGHT;
	right = x + VENUSPLANT_BBOX_WIDTH;
	bottom = y + VENUSPLANT_BBOX_HEIGHT;
}

void CVenusPlant::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	LPGAME game = CGame::GetInstance();
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	float Mx;
	Mx = mario->GetX();

	CGameObject::Update(dt, coObjects);
	if (y == 125)
	{
		SetState(VENUSPLANT_STATE_WAIT);
		
	}
	else if (y < 125 && x > Mx && (GetTickCount64() - wait > VENUSPLANT_WAIT_TIME))
	{
		SetState(VENUSPLANT_STATE_HEAD_DOWN_LEFT);
	}
	else if (y > 170 && x > Mx)
		SetState(VENUSPLANT_STATE_HEAD_UP_LEFT);
	else if (y < 125 && x < Mx)
		SetState(VENUSPLANT_STATE_HEAD_DOWN_RIGHT);
	else if (y > 170 && x < Mx)
		SetState(VENUSPLANT_STATE_HEAD_UP_RIGHT);

	/*if (state == VENUSPLANT_STATE_HEAD_UP_LEFT || state == VENUSPLANT_STATE_HEAD_UP_RIGHT)
		vy = -VENUSPLANT_SPEED;
	else if (state == VENUSPLANT_STATE_HEAD_DOWN_LEFT || state ==VENUSPLANT_STATE_HEAD_DOWN_RIGHT)
		vy = VENUSPLANT_SPEED;*/

	y += vy * dt;

	// Kiểm tra xem danh sách đối tượng trong scene đã chứa Venus Plant chưa
	bool isVenusPlantInScene = false;
	for (size_t i = 0; i < coObjects->size(); i++)
	{
		LPGAMEOBJECT obj = coObjects->at(i);
		if (dynamic_cast<CVenusPlant*>(obj))
		{
			isVenusPlantInScene = true;
			break;
		}
	}

	

	// Nếu Venus Plant không có trong scene, thì mới tạo một viên đạn mới và thêm vào danh sách
	if (!isVenusPlantInScene)
	{
		LPGAMEOBJECT fireball = new CFireBall(x, y);
		coObjects->push_back(fireball);
	}
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
	wait = 0;
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
		wait = GetTickCount64();
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