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