#include "VenusPlant.h"
#include "FireBall.h"

const float VENUS_HEIGHT = 32 * 3;

CVenusPlant::CVenusPlant(float x, float y) : CGameObject(x, y)
{
	this->ax = 0;
	this->ay = 0;
	SetState(VENUSPLANT_STATE_HEAD_UP);
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
	
	if (y < 125)
		SetState(VENUSPLANT_STATE_HEAD_DOWN);
	else if (y > 170)
		SetState(VENUSPLANT_STATE_HEAD_UP);

	if (state == VENUSPLANT_STATE_HEAD_UP)
		vy = -VENUSPLANT_SPEED;
	else if (state == VENUSPLANT_STATE_HEAD_DOWN)
		vy = VENUSPLANT_SPEED;

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
	int ani = ID_ANI_VENUSPLANT_HEAD_UP;
	if (state == VENUSPLANT_STATE_HEAD_DOWN)
		ani = ID_ANI_VENUSPLANT_HEAD_DOWN;
	else if (state == VENUSPLANT_STATE_HEAD_UP)
		ani = ID_ANI_VENUSPLANT_HEAD_UP;

	CAnimations::GetInstance()->Get(ani)->Render(x, y);
}

void CVenusPlant::SetState(int state)
{
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