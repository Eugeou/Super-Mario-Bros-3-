#include "VenusPlant.h"
#include "FireBall.h"

CVenusPlant::CVenusPlant(float x, float y) : CGameObject(x, y)
{
	this->ax = 0;
	this->ay = 0;
	head_start = 0;
	isHeadUp = false;
	SetState(VENUSPLANT_STATE_HEAD_DOWN);
}

void CVenusPlant::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - VENUSPLANT_BBOX_WIDTH / 2;
	top = y - VENUSPLANT_BBOX_HEIGHT / 2;
	right = x + VENUSPLANT_BBOX_WIDTH / 2;
	bottom = y + VENUSPLANT_BBOX_HEIGHT / 2;
}

void CVenusPlant::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);

	if (isHeadUp)
	{
		if (head_start >= 2 * VENUSPLANT_UPORDOWN_TIME)
		{
			head_start = 0;
			isHeadUp = false;
			SetState(VENUSPLANT_STATE_HEAD_DOWN);
		}
	}
	else
	{
		if (head_start >= VENUSPLANT_UPORDOWN_TIME)
		{
			head_start = 0;
			isHeadUp = true;
			SetState(VENUSPLANT_STATE_HEAD_UP);

			// Tạo một fireball và thêm vào danh sách đối tượng trong scene
			LPGAMEOBJECT fireball = new CFireBall(x, y);
			coObjects->push_back(fireball);
		}
	}

	// Tăng giá trị của head_start sau mỗi frame
	head_start += dt;
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

void CVenusPlant::Render()
{
	int ani = ID_ANI_VENUSPLANT_HEAD_UP;
	if (state == VENUSPLANT_STATE_HEAD_DOWN)
		ani = ID_ANI_VENUSPLANT_HEAD_DOWN;
	else if (state == VENUSPLANT_STATE_HEAD_UP)
		ani = ID_ANI_VENUSPLANT_HEAD_UP;
	CAnimations::GetInstance()->Get(ani)->Render(x, y);
	//RenderBoundingBox();
	
}

void CVenusPlant::SetState(int state)
{
	CGameObject::SetState(state);

	switch (state)
	{
	case VENUSPLANT_STATE_HEAD_DOWN:
		vy = 0;
		break;
	case VENUSPLANT_STATE_HEAD_UP:
		vy = -VENUSPLANT_SPEED;
		break;
	}
}
