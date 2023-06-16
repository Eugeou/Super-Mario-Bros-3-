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