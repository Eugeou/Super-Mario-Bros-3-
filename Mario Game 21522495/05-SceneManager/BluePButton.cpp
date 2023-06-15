#include "BluePButton.h"
#include "debug.h"

CBluePButton::CBluePButton(float x, float y) : CGameObject(x, y) {
	ay = -BUTTON_QUICKLY_Y;
	firstYPosition = y;
}

void CBluePButton::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	if ((firstYPosition - y < BUTTON_BBOX_HEIGHT - 1) && !isCollected) //Nếu Nếu khoảng cách giữa vị trí ban đầu và vị trí hiện tại của nút màu xanh biển nhỏ hơn chiều cao của nút trừ 1 (BUTTON_BBOX_HEIGHT - 1) và nút chưa được thu thập (!isCollected), thì nút sẽ di chuyển lên theo trục y với tốc độ ay * dt.
	{
		vy = ay * dt;
	}
	else vy = 0; //Nếu nút đã được thu thập(isCollected), thì vị trí y của nút sẽ được đặt lại để nút nằm ở phía trên vị trí ban đầu(firstYPosition - BUTTON_BBOX_HEIGHT / 2 - 2).
	if (isCollected)
	{
		y = firstYPosition - BUTTON_BBOX_HEIGHT / 2 - 2;
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CBluePButton::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	int aniId = -1;
	if (!isCollected) aniId = ID_ANI_BUTTON_NOT_COLLECTED;
	else aniId = ID_ANI_BUTTON_COLLECTED;
	animations->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
}
void CBluePButton::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};
void CBluePButton::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - BUTTON_BBOX_WIDTH / 2;
	t = y - BUTTON_BBOX_HEIGHT / 2;
	r = l + BUTTON_BBOX_WIDTH;
	b = t + BUTTON_BBOX_HEIGHT;
}