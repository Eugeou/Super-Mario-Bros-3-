#include "TransparentBlock.h"

void CTransparentBlock::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_TRANSPARENTBLOCK)->Render(x, y);
	RenderBoundingBox();
}

void CTransparentBlock::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - TRANSPARENTBLOCK_BBOX_WIDTH / 2;
	t = y - TRANSPARENTBLOCK_BBOX_HEIGHT / 2;
	r = l + TRANSPARENTBLOCK_BBOX_WIDTH;
	b = t + TRANSPARENTBLOCK_BBOX_HEIGHT;
}