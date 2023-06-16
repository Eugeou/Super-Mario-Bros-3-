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
#include "BluePButton.h"
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

void CKoopa::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	if (mario->GetState() == MARIO_STATE_DIE) return;
	vy += ay * dt;
	vx += ax * dt;

	if (mario->GetIsHolding() && isHeld) {
		this->x = mario->GetX() + mario->GetNx() * (MARIO_BIG_BBOX_WIDTH - 3);
		this->y = mario->GetY() - 3;

		vx = mario->GetVx();
		vy = mario->GetVy();
	}
	else {
		if (this->isHeld) {
			ay = KOOPA_GRAVITY;
			SetState(KOOPA_STATE_IS_KICKED);
		}
	}

	if (isDead && isUpside) {
		if (GetTickCount64() - die_start > KOOPA_DIE_TIME)
		{
			isDeleted = true;
			return;
		}
	}
	if (!isDead) {
		if (!isKicked) {
			if (GetTickCount64() - defend_start > KOOPA_COMBACK_START && (isDefend || isUpside) && !isKicked) {
				isComeback = true;
			}
			if ((GetTickCount64() - defend_start > KOOPA_DEFEND_TIMEOUT && (isDefend || isUpside) && !isKicked)) {
				if (isComeback) {
					SetState(KOOPA_STATE_WALKING);
					vy = -KOOPA_ADJUST_NOT_FALL;
					defend_start = -1;
				}
			}
		}
		else { isComeback = false; }
	}
	if (state == KOOPA_STATE_UPSIDE && !isOnPlatform) {
		vx = -KOOPA_WALKING_SPEED;
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CKoopa::OnCollisionWithBrickColor(LPCOLLISIONEVENT e) {
	CBrickColor* brick = dynamic_cast<CBrickColor*>(e->obj);
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();

	if ((isKicked) && (e->nx != 0)) {
		mario->SetScore(mario->GetScore() + 100);
		brick->SetState(BRICK_STATE_DELETE);
	}
}
void CKoopa::OnCollisionWithVenusPlant(LPCOLLISIONEVENT e) {
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();

	CVenusPlant* plant = dynamic_cast<CVenusPlant*>(e->obj);
	if (isKicked)
	{
		plant->SetState(VENUSPLANT_STATE_DIE);
	}
}
void CKoopa::OnCollisionWithKoopa(LPCOLLISIONEVENT e) {
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();

	CKoopa* koopa = dynamic_cast<CKoopa*>(e->obj);
	if (isHeld) {
		SetState(KOOPA_STATE_DEAD_UPSIDE);
		koopa->SetState(KOOPA_STATE_DEAD_UPSIDE);
	}
	else if (isKicked) 
	{
		koopa->SetState(KOOPA_STATE_DEAD_UPSIDE);
	}
}

void CKoopa::OnCollisionWithBrickQuestion(LPCOLLISIONEVENT e) {
	CQuestionBrick* questionBrick = dynamic_cast<CQuestionBrick*>(e->obj);
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();

	if (e->nx != 0) {
		if (isKicked) {
			if (!questionBrick->GetIsEmpty() || !questionBrick->GetIsUnbox()) {
				if (questionBrick->GetModel() == QUESTION_BRICK_ITEM) {
					if (mario->GetLevel() == MARIO_LEVEL_SMALL) {
						CMushRoom* mushroom = new CMushRoom(questionBrick->GetX(), questionBrick->GetY());
						scene->AddObject(mushroom);
					}
					else if (mario->GetLevel() >= MARIO_LEVEL_BIG) {
						CLeaf* leaf = new CLeaf(questionBrick->GetX(), questionBrick->GetY());
						scene->AddObject(leaf);
					}
				}
				else if (questionBrick->GetModel() == QUESTION_BRICK_COIN) {
					mario->SetCoin(mario->GetCoin() + 1);
					CCoin* coin = new CCoin(questionBrick->GetX(), questionBrick->GetY());
					coin->SetState(COIN_SUMMON_STATE);
					scene->AddObject(coin);
				}
				else {
					CBluePButton* button = new CBluePButton(questionBrick->GetX(), questionBrick->GetY());
					scene->AddObject(button);
				}
				questionBrick->SetIsEmpty(true);
				questionBrick->SetIsUnbox(true);
			}
		}
	}
}
void CKoopa::OnCollisionWithGoomba(LPCOLLISIONEVENT e) {

	CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);

	if (isKicked) {
		CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
		goomba->SetState(GOOMBA_STATE_DIE);
	}

}
void CKoopa::OnCollisionWithPlatform(LPCOLLISIONEVENT e) {
	CPlatform* platform = dynamic_cast<CPlatform*>(e->obj);
	if (e->ny < 0) {
		if (!platform->isCanNotBlockKoopa()) {
			isOnPlatform = true;
			if (!isDefend && !isUpside) {
				SetY(platform->GetY() - KOOPA_BBOX_HEIGHT + 4);
			}
			else
			{
				SetY(platform->GetY() - KOOPA_BBOX_HEIGHT / 2 - 3);
			}
			if ((model == KOOPA_GREEN_WING) && (state == KOOPA_STATE_JUMP)) {
				vy = -KOOPA_JUMP_SPEED;
			}
		}
	}
	if ((model == KOOPA_RED) && (state == KOOPA_STATE_WALKING))
	{
		if (platform->GetX() - KOOPA_BBOX_WIDTH / 2 > GetX()) {
			SetX(platform->GetX() - KOOPA_BBOX_WIDTH / 2);
			vx = -vx;
		}
		if ((GetX() > (platform->GetX() + (platform->GetLength() - 0.5) * KOOPA_BBOX_WIDTH))) {
			SetX(platform->GetX() + (float(platform->GetLength() - 0.5)) * KOOPA_BBOX_WIDTH);
			vx = -vx;
		}


	}
}


