#include "Leaf.h"
#include "Platform.h"


#define LEAF_FALL_SPEED 0.0001f
#define LEAF_SPEED 0.04f
#define ADJUST_AX_WHEN_FALL 0.0001f
#define ADJUST_MAX_VX 0.085f
#define OUT_BRICK 0.13f

CLeaf::CLeaf(float x, float y) :CGameObject(x, y)
{
	this->ax = 0;
	this->ay = LEAF_FALL_SPEED;
	vy = -OUT_BRICK;
	isOnPlatForm = false;
	SetState(LEAF_STATE_FALL);
}
CLeaf::CLeaf(float x, float y, int state) {
	this->x = x;
	this->y = y;
	this->ax = 0;
	this->state = state;
}