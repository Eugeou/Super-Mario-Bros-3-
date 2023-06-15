#include "QuestionBrick.h"
#include "Mario.h"
#include "PlayScene.h"
#include "Coin.h"

CBrickQuestion::CBrickQuestion(float x, float y, int model) :CGameObject(x, y)
{
	this->model = model;
	this->ay = 0;
	this->minY = y - QUESTION_BRICK_BBOX_HEIGHT + ADJUST_UP_DOWN;
	this->startY = y;
	this->startX = x;
}

void CBrickQuestion::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - QUESTION_BRICK_BBOX_WIDTH / 2;
	top = y - QUESTION_BRICK_BBOX_HEIGHT / 2;
	right = left + QUESTION_BRICK_BBOX_WIDTH;
	bottom = top + QUESTION_BRICK_BBOX_HEIGHT;
}

void CBrickQuestion::OnNoCollision(DWORD dt)
{
	y += vy * dt;
};

void CBrickQuestion::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (x != startX) {
		x = startX;
	}
	if (!isEmpty) {
		if (y != startY) y = startY;
		if (x != startX) x = startX;
	}
	if (isUnbox) {
		vy = 0;
		ay = 0;
		vx = 0;
		y = startY;
		x = startX;
	}
	else {
		vy += ay * dt;
		if (y <= minY)
		{
			vy = QUESTION_BRICK_SPEED_DOWN;
		}
		if (y > startY + QUESTION_BRICK_BBOX_HEIGHT - ADJUST_UP_DOWN)
		{
			y = startY;
			vy = 0;
			isEmpty = true;
			isUnbox = true;
		}
	}
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}