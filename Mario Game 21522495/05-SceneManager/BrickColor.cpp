#include "BrickColor.h"
#include "PlayScene.h"
#include "Game.h"
#include "debug.h"
#include "Coin.h"

void CBrickColor::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_BRICK_COLOR)->Render(x, y);
	//RenderBoundingBox();
}

void CBrickColor::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - BRICK_BBOX_WIDTH / 2;
	t = y - BRICK_BBOX_HEIGHT / 2;
	r = l + BRICK_BBOX_WIDTH;
	b = t + float(BRICK_BBOX_HEIGHT / 1.5);
}

void CBrickColor::SetState(int state) {
	switch (state) {
	case BRICK_STATE_DELETE:
		isBreak = true;
		break;
	case BRICK_STATE_GOLD:
		isGold = true;
		break;
	}
	CGameObject::SetState(state);
}

void CBrickColor::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
	if (isUseButton) {
		if (!isStopLoop)
		{
			SetState(BRICK_STATE_GOLD);
			isStopLoop = true;
		}
	}
	else {
		CBluePButton* button = NULL;
		for (size_t i = 0; i < scene->GetListObject().size(); i++) {
			if (scene->GetListObject()[i]->IsButton() == 1) {
				button = dynamic_cast<CBluePButton*>(scene->GetListObject()[i]);
				if (button->GetIsCollected()) isUseButton = true;
				button = NULL;
				break;
			}
		}
	}
	if (isGold) {
		CCoin* coin = new CCoin(x, y);
		scene->AddObject(coin);
		Delete();
		isGold = false;
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

