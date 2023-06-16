#include "Platform.h"
#include "Scene.h"
#include "Game.h"
#include "PlayScene.h"
#include "debug.h"

#include "Koopa.h"
#include "Goomba.h"
#include "Mario.h"
#include "VenusPlant.h"
#include "BrickColor.h"
#include "QuestionBrick.h"
#include "MushRoom.h"
#include "Leaf.h"
#include "Coin.h"
#include "PlayScene.h"

CKoopa::CKoopa(float x, float y, int model) :CGameObject(x, y)
{
	this->ax = 0;
	this->ay = KOOPA_GRAVITY;
	this->model = model;
	defend_start = -1;
	isHeld = false;
	if (model == KOOPA_GREEN_WING) {
		isWing = true;
		SetState(KOOPA_STATE_JUMP);
	}
	else {
		isWing = false;
		SetState(KOOPA_STATE_WALKING);
	}

	isComeback = false;
	isDefend = false;
	isKicked = false;
	isOnPlatform = false;
	isHeld = false;
	isUpside = false;
	isDead = false;
}

void CKoopa::Render() {
	int aniId;
	if (model == KOOPA_RED) {
		aniId = GetAniRed();
	}
	else aniId = GetAniGreen();
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
}

void CKoopa::OnNoCollision(DWORD dt) {
	x += vx * dt;
	y += vy * dt;
}

int CKoopa::PositionWithMario() {
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	if (mario->GetX() < GetX()) return 1;
	else return -1;

}

int CKoopa::GetAniRed() {
	int aniId;
	if (isUpside) {
		if (isComeback) aniId = ID_ANI_RED_UPSIDE_COMEBACK;
		else if (isKicked) aniId = ID_ANI_RED_UPSIDE_KICKED;
		else aniId = ID_ANI_RED_UPSIDE;
	}
	else {
		if (isDefend) {
			if (isComeback) aniId = ID_ANI_RED_COMEBACK;
			else if (isKicked) aniId = ID_ANI_RED_DEFEND;//ID_ANI_RED_KICKED;
			else aniId = ID_ANI_RED_DEFEND;
		}
		else
		{
			if (vx > 0) aniId = ID_ANI_RED_WALK_RIGHT;
			else aniId = ID_ANI_RED_WALK_LEFT;
		}
	}
	return aniId;
}

int CKoopa::GetAniGreen() {
	int aniId = -1;
	if (!isWing) {
		if (isUpside) {
			if (isComeback) aniId = ID_ANI_GREEN_UPSIDE_COMEBACK;
			else if (isKicked) aniId = ID_ANI_GREEN_UPSIDE_KICKED;
			else aniId = ID_ANI_GREEN_UPSIDE;
		}
		else {
			if (isDefend) {
				if (isComeback) aniId = ID_ANI_GREEN_COMEBACK;
				else if (isKicked) aniId = ID_ANI_GREEN_DEFEND;//ID_ANI_GREEN_KICKED;
				else aniId = ID_ANI_GREEN_DEFEND;
			}
			else
			{
				if (vx > 0) aniId = ID_ANI_GREEN_WALK_RIGHT;
				else aniId = ID_ANI_GREEN_WALK_LEFT;
			}
		}
	}
	else {
		if (vx > 0) aniId = ID_ANI_GREEN_WING_RIGHT;
		else aniId = ID_ANI_GREEN_WING_LEFT;
	}
	return aniId;
}

void CKoopa::GetBoundingBox(float& left, float& top, float& right, float& bottom) {
	if ((state == KOOPA_STATE_ISDEAD) || (state == KOOPA_STATE_DEAD_UPSIDE)) return;
	if (isDefend || isUpside) {
		left = x - KOOPA_BBOX_WIDTH / 2;
		top = y - KOOPA_BBOX_HEIGHT_DEFEND / 2;
		right = left + KOOPA_BBOX_WIDTH;
		bottom = top + KOOPA_BBOX_HEIGHT_DEFEND;
	}
	else {
		left = x - KOOPA_BBOX_WIDTH / 2;
		top = y - KOOPA_BBOX_HEIGHT / 2;
		right = left + KOOPA_BBOX_WIDTH;
		bottom = top + KOOPA_BBOX_HEIGHT;
	}
}