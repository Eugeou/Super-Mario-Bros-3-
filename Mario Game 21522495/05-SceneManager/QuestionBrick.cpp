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

