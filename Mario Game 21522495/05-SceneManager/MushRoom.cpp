#include "MushRoom.h"

#include "Platform.h"
#include "PlayScene.h"
#include "Mario.h"

#define MUSHROOM_GRAVITY 0.001f
#define MUSHROOM_SPEED 0.055f
#define OUT_BRICK -0.016f

CMushRoom::CMushRoom(float x, float y) :CGameObject(x, y)
{
	this->ax = 0;
	this->ay = MUSHROOM_GRAVITY;
	vy = 0;
	model = MUSHROOM_RED;
	startY = y;
	SetState(MUSHROOM_STATE_OUTSIDE);
}
CMushRoom::CMushRoom(float x, float y, int model) :CGameObject(x, y)
{
	this->ax = 0;
	this->ay = MUSHROOM_GRAVITY;
	vy = 0;
	this->model = model;
	startY = y;
	SetState(MUSHROOM_STATE_OUTSIDE);
}