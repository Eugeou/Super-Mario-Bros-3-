#include <algorithm>
#include "debug.h"

#include "Mario.h"
#include "Game.h"

#include "Goomba.h"
#include "Coin.h"
#include "Portal.h"
#include "FireBall.h"
#include "VenusPlant.h"

#include "PlayScene.h"
#include "Collision.h"
#include "QuestionBrick.h"
#include "MushRoom.h"
#include "BrickColor.h"
#include "Leaf.h"
#include "Koopa.h"

void CMario::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	if (abs(vx) > abs(maxVx)) vx = maxVx;

	// reset untouchable timer if untouchable time has passed
	if ( GetTickCount64() - untouchable_start > MARIO_UNTOUCHABLE_TIME) 
	{
		untouchable_start = 0;
		untouchable = 0;
	}

	isOnPlatform = false;

	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CMario::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}

void CMario::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (e->ny != 0 && e->obj->IsBlocking())
	{
		vy = 0;
		if (e->ny < 0) isOnPlatform = true;
	}
	else 
	if (e->nx != 0 && e->obj->IsBlocking())
	{
		vx = 0;
	}

	if (dynamic_cast<CGoomba*>(e->obj))
		OnCollisionWithGoomba(e);
	else if (dynamic_cast<CCoin*>(e->obj))
		OnCollisionWithCoin(e);
	else if (dynamic_cast<CPortal*>(e->obj))
		OnCollisionWithPortal(e);
	else if (dynamic_cast<CFireBall*>(e->obj))
		OnCollisionWithFireBall(e);
	else if (dynamic_cast<CVenusPlant*>(e->obj))
		OnCollisionWithVenusPlant(e);
	else if (dynamic_cast<CMushRoom*>(e->obj))
		OnCollisionWithMushRoom(e);
	else if (dynamic_cast<CLeaf*>(e->obj))
		OnCollisionWithLeaf(e);
	else if (dynamic_cast<CQuestionBrick*>(e->obj))
		OnCollisionWithQuestionBrick(e);
	else if (dynamic_cast<CKoopa*>(e->obj))
		OnCollisionWithKoopa(e);

	
	
}

void CMario::OnCollisionWithGoomba(LPCOLLISIONEVENT e)
{
	CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);

	// jump on top >> kill Goomba and deflect a bit 
	if (e->ny < 0)
	{
		if (goomba->GetIsDead()) return;
		BlockIfNoBlock(goomba);
		goomba->SetVy(-0.05f);//dam bao goomba khong roi xuong khi mario jump
		goomba->SetState(GOOMBA_STATE_IS_ATTACK);
		vy -= MARIO_JUMP_DEFLECT_SPEED;
	}
	else // hit by Goomba
	{
		if (untouchable == 0)
		{
			if (goomba->GetState() != GOOMBA_STATE_DIE)
			{
				if (level > MARIO_LEVEL_SMALL)
				{
					if (level == MARIO_LEVEL_TAIL)
						level = MARIO_LEVEL_BIG;
					else
						level = MARIO_LEVEL_SMALL;
						StartUntouchable();
				}
				else
				{
					DebugOut(L">>> Mario DIE >>> \n");
					SetState(MARIO_STATE_DIE);
				}
			}
		}
	}
}

//////// ONCOLLISION WITH GAME OBJECTS /////////////

void CMario::OnCollisionWithCoin(LPCOLLISIONEVENT e)
{
	CCoin* coin1 = dynamic_cast<CCoin*>(e->obj);
	if (coin1->CanCollect()) {
		e->obj->Delete();
		score += 100;
		coin++;
	}
}

void CMario::OnCollisionWithPortal(LPCOLLISIONEVENT e)
{
	CPortal* p = (CPortal*)e->obj;
	CGame::GetInstance()->InitiateSwitchScene(p->GetSceneId());
}

void CMario::OnCollisionWithFireBall(LPCOLLISIONEVENT e) {
	if (untouchable) return;
	CFireBall* fireball = dynamic_cast<CFireBall*>(e->obj);
	fireball->SetIsDeleted(true);

	if (untouchable == 0)
	{
		if (level > MARIO_LEVEL_SMALL)
		{
			if (level == MARIO_LEVEL_TAIL)
				level = MARIO_LEVEL_BIG;
			else
				level = MARIO_LEVEL_SMALL;
				StartUntouchable();
		}
		else
		{
			DebugOut(L">>> Mario DIE >>> \n");
			SetState(MARIO_STATE_DIE);

		}
	}	
}

void CMario::OnCollisionWithVenusPlant(LPCOLLISIONEVENT e) {
	CVenusPlant* plant = dynamic_cast<CVenusPlant*>(e->obj);
	if (untouchable) return;

	else if (untouchable == 0)
	{
		if (plant->GetState() != VENUSPLANT_STATE_DIE)
		{
			if (level > MARIO_LEVEL_SMALL)
			{
				if (level == MARIO_LEVEL_TAIL)
					level = MARIO_LEVEL_BIG;
				else
					level = MARIO_LEVEL_SMALL;
					StartUntouchable();
			}
			else
			{
				DebugOut(L">>> Mario DIE >>> \n");
				SetState(MARIO_STATE_DIE);

			}
		}
	}
}

void CMario::OnCollisionWithMushRoom(LPCOLLISIONEVENT e)
{
	CMushRoom* mushroom = dynamic_cast<CMushRoom*>(e->obj);
	if (mushroom->GetModel() == MUSHROOM_RED) {
		if (!mushroom->IsDeleted()) {
			score += 1000;
		}
		if (GetLevel() == MARIO_LEVEL_SMALL)
		{
			isLower = false;
			SetLevel(MARIO_LEVEL_BIG);
		}
	}
	mushroom->Delete();

}

void CMario::OnCollisionWithLeaf(LPCOLLISIONEVENT e) {
	e->obj->Delete();
	score += 1000;
	if (level == MARIO_LEVEL_TAIL) {
	}
	else if (level != MARIO_LEVEL_SMALL)
	{
		SetLevel(MARIO_LEVEL_TAIL);
	}
	else SetLevel(MARIO_LEVEL_BIG);
}

void CMario::OnCollisionWithQuestionBrick(LPCOLLISIONEVENT e) {
	CQuestionBrick* questionBrick = dynamic_cast<CQuestionBrick*>(e->obj);
	CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
	BOOLEAN isUnbox, isEmpty;
	isUnbox = questionBrick->GetIsUnbox();
	isEmpty = questionBrick->GetIsEmpty();
	if (e->ny < 0) BlockIfNoBlock(questionBrick);
	else if (((e->ny > 0) || (e->nx != 0)) && !isUnbox && !isEmpty) {
		float xTemp, yTemp, minY;
		xTemp = questionBrick->GetX();
		yTemp = questionBrick->GetY();
		minY = questionBrick->GetMinY();

		questionBrick->SetState(QUESTION_BRICK_STATE_UP);

		if (questionBrick->GetModel() == QUESTION_BRICK_ITEM) {
			if (GetLevel() == MARIO_LEVEL_SMALL) {
				CMushRoom* mushroom = new CMushRoom(xTemp, yTemp);
				scene->AddObject(mushroom);
			}
			else if (GetLevel() >= MARIO_LEVEL_BIG) {
				CLeaf* leaf = new CLeaf(xTemp, yTemp);
				scene->AddObject(leaf);
			}
			questionBrick->SetIsEmpty(true);
		}
		else if (questionBrick->GetModel() == QUESTION_BRICK_COIN) {
			SetCoin(GetCoin() + 1);
			CCoin* coin = new CCoin(xTemp, yTemp);
			coin->SetState(COIN_SUMMON_STATE);
			questionBrick->SetIsEmpty(true);
			scene->AddObject(coin);
		}
		else {
			CBluePButton* button = new CBluePButton(xTemp, yTemp);
			scene->AddObject(button);
			questionBrick->SetIsEmpty(true);
		}
	}

}

void CMario::OnCollisionWithKoopa(LPCOLLISIONEVENT e) {
	
	CKoopa* koopa = dynamic_cast<CKoopa*>(e->obj);
	if (e->ny < 0) 
	{
		koopa->SetVy(-KOOPA_ADJUST_KICKED_NOT_FALL);
		if (koopa->GetModel() != KOOPA_GREEN_WING) {
			if ((koopa->GetState() == KOOPA_STATE_WALKING) or (koopa->GetState() == KOOPA_STATE_IS_KICKED))
			{
				koopa->SetState(KOOPA_STATE_DEFEND);
				vy = -MARIO_JUMP_DEFLECT_SPEED;
			}
			else {
				koopa->SetState(KOOPA_STATE_IS_KICKED);
				vy = -MARIO_JUMP_DEFLECT_SPEED;
			}
		}
		else
		{
			if (koopa->GetState() == KOOPA_STATE_JUMP) {
				koopa->SetState(KOOPA_STATE_WALKING);
				vy = -MARIO_JUMP_DEFLECT_SPEED;
			}
			else if ((koopa->GetState() == KOOPA_STATE_WALKING) or (koopa->GetState() == KOOPA_STATE_IS_KICKED))
			{
				koopa->SetVy(KOOPA_ADJUST_KICKED_NOT_FALL);
				koopa->SetState(KOOPA_STATE_DEFEND);
				vy = -MARIO_JUMP_DEFLECT_SPEED;
			}
			else {
				koopa->SetState(KOOPA_STATE_IS_KICKED);
			}

		}
	}
	else if (e->nx != 0)
	{
		if (untouchable == 0)
		{
			if ((koopa->GetState() != KOOPA_STATE_JUMP) && (koopa->GetState() != KOOPA_STATE_ISDEAD) && (koopa->GetState() != KOOPA_STATE_WALKING) and (koopa->GetState() != KOOPA_STATE_IS_KICKED))
			{
				if (!isRunning)
				{
					koopa->SetIsHeld(false);
					isKicking = true;
					start_kick = GetTickCount64();

					koopa->SetState(KOOPA_STATE_IS_KICKED);
				}
				else {
					isHolding = true;
					koopa->SetIsHeld(true);
					start_holding = GetTickCount64();
				}
			}
			else {
				SetLevelLower();
			}
		}
	}
}



void CMario::BlockIfNoBlock(LPGAMEOBJECT gameobject) {
	if (level == MARIO_LEVEL_SMALL) {
		//SetY(platform->GetY() - 15);
		if (gameobject->GetY() - GetY() < (MARIO_SMALL_BBOX_HEIGHT + 4))
		{
			SetY(gameobject->GetY() - MARIO_SMALL_BBOX_HEIGHT - 2);
			vy = 0;
			isOnPlatform = true;
		}
	}
	else {
		if (!isSitting) {
			if (gameobject->GetY() - GetY() < MARIO_BIG_BBOX_HEIGHT)
			{
				SetY(gameobject->GetY() - MARIO_BIG_BBOX_HEIGHT + 4);
				vy = 0;
				isOnPlatform = true;
			}
		}
		else {
			if (gameobject->GetY() - GetY() < MARIO_BIG_BBOX_HEIGHT / 2 + 4)
			{
				SetY(gameobject->GetY() - MARIO_BIG_BBOX_HEIGHT / 2 - 4);
				vy = 0;
				isOnPlatform = true;
			}
		}
	}
}


//
// Get animation ID for small Mario
//
int CMario::GetAniIdSmall()
{
	int aniId = -1;
	if (!isOnPlatform)
	{
		if (!isHolding) {
			if (abs(ax) == MARIO_ACCEL_RUN_X)
			{
				if (nx >= 0)
					aniId = ID_ANI_MARIO_SMALL_JUMP_RUN_RIGHT;
				else
					aniId = ID_ANI_MARIO_SMALL_JUMP_RUN_LEFT;
			}
			else
			{
				if (nx >= 0)
					aniId = ID_ANI_MARIO_SMALL_JUMP_WALK_RIGHT;
				else
					aniId = ID_ANI_MARIO_SMALL_JUMP_WALK_LEFT;
			}
		}
		else {
			if (nx >= 0) aniId = ID_ANI_MARIO_SMALL_HOLD_JUMP_RIGHT;
			else  aniId = ID_ANI_MARIO_SMALL_HOLD_JUMP_LEFT;
		}
	}
	else
		if (!isHolding) {

				if (vx == 0)
				{
					if (nx > 0) aniId = ID_ANI_MARIO_SMALL_IDLE_RIGHT;
					else aniId = ID_ANI_MARIO_SMALL_IDLE_LEFT;
				}
				else if (vx > 0)
				{
					if (ax < 0)
						aniId = ID_ANI_MARIO_SMALL_BRACE_RIGHT;
					else if (ax == MARIO_ACCEL_RUN_X) {
						aniId = ID_ANI_MARIO_SMALL_RUNNING_RIGHT;
					}
					else if (ax == MARIO_ACCEL_WALK_X)
						aniId = ID_ANI_MARIO_SMALL_WALKING_RIGHT;
				}
				else // vx < 0
				{
					if (ax > 0)
						aniId = ID_ANI_MARIO_SMALL_BRACE_LEFT;
					else if (ax == -MARIO_ACCEL_RUN_X) {
						aniId = ID_ANI_MARIO_SMALL_RUNNING_LEFT;
					}
					else if (ax == -MARIO_ACCEL_WALK_X)
						aniId = ID_ANI_MARIO_SMALL_WALKING_LEFT;
				}
			
		}
		else {
			if (vx == 0) {
				if (nx > 0) aniId = ID_ANI_MARIO_SMALL_HOLD_IDLE_RIGHT;
				else aniId = ID_ANI_MARIO_SMALL_HOLD_IDLE_LEFT;
			}
			else {
				if (nx > 0) aniId = ID_ANI_MARIO_SMALL_HOLD_RUNNING_RIGHT;
				else aniId = ID_ANI_MARIO_SMALL_HOLD_RUNNING_LEFT;
			}
		}

	if (aniId == -1) aniId = ID_ANI_MARIO_SMALL_IDLE_RIGHT;

	return aniId;
}


//
// Get animdation ID for big Mario
//
int CMario::GetAniIdBig()
{
	int aniId = -1;
	if (!isOnPlatform)
	{
		if (!isHolding) {
			if (abs(ax) == MARIO_ACCEL_RUN_X)
			{
				if (nx >= 0)
					aniId = ID_ANI_MARIO_BIG_JUMP_RUN_RIGHT;
				else
					aniId = ID_ANI_MARIO_BIG_JUMP_RUN_LEFT;
			}
			else
			{
				if (nx >= 0)
					aniId = ID_ANI_MARIO_BIG_JUMP_WALK_RIGHT;
				else
					aniId = ID_ANI_MARIO_BIG_JUMP_WALK_LEFT;
			}
		}
		else {
			if (nx >= 0) aniId = ID_ANI_MARIO_BIG_HOLD_JUMP_RIGHT;
			else  aniId = ID_ANI_MARIO_BIG_HOLD_JUMP_LEFT;
		}
	}
	else
		if (!isHolding) {
			
				if (isSitting)
				{
					if (nx > 0)
						aniId = ID_ANI_MARIO_BIG_SIT_RIGHT;
					else
						aniId = ID_ANI_MARIO_BIG_SIT_LEFT;
				}
				else
					if (vx == 0)
					{
						if (nx > 0) aniId = ID_ANI_MARIO_BIG_IDLE_RIGHT;
						else aniId = ID_ANI_MARIO_BIG_IDLE_LEFT;
					}
					else if (vx > 0)
					{
						if (ax < 0)
							aniId = ID_ANI_MARIO_BIG_BRACE_RIGHT;
						else if (ax == MARIO_ACCEL_RUN_X) {
							aniId = ID_ANI_MARIO_BIG_RUNNING_RIGHT;
						}
						else if (ax == MARIO_ACCEL_WALK_X)
							aniId = ID_ANI_MARIO_BIG_WALKING_RIGHT;
					}
					else // vx < 0
					{
						if (ax > 0)
							aniId = ID_ANI_MARIO_BIG_BRACE_LEFT;
						else if (ax == -MARIO_ACCEL_RUN_X) {
							aniId = ID_ANI_MARIO_BIG_RUNNING_LEFT;
						}
						else if (ax == -MARIO_ACCEL_WALK_X)
							aniId = ID_ANI_MARIO_BIG_WALKING_LEFT;
					}
			
			
		}
		else {
			if (vx == 0) {
				if (nx > 0) aniId = ID_ANI_MARIO_BIG_HOLD_IDLE_RIGHT;
				else aniId = ID_ANI_MARIO_BIG_HOLD_IDLE_LEFT;
			}
			else {
				if (nx > 0) aniId = ID_ANI_MARIO_BIG_HOLD_RUNNING_RIGHT;
				else aniId = ID_ANI_MARIO_BIG_HOLD_RUNNING_LEFT;
			}
		}

	if (aniId == -1) aniId = ID_ANI_MARIO_BIG_IDLE_RIGHT;

	return aniId;
}

int CMario::GetAniIdTail()
{
	int aniId = -1;
	if (!isOnPlatform)
	{
		if (!isHolding) {
			if (abs(ax) == MARIO_ACCEL_RUN_X)
			{
				if (nx >= 0)
					aniId = ID_ANI_MARIO_TAIL_JUMP_RUN_RIGHT;
				else
					aniId = ID_ANI_MARIO_TAIL_JUMP_RUN_LEFT;
			}
			else
			{
				if (nx >= 0)
					aniId = ID_ANI_MARIO_TAIL_JUMP_WALK_RIGHT;
				else
					aniId = ID_ANI_MARIO_TAIL_JUMP_WALK_LEFT;
			}
		}
		else {
			if (nx >= 0) aniId = ID_ANI_MARIO_TAIL_HOLD_JUMP_RIGHT;
			else  aniId = ID_ANI_MARIO_TAIL_HOLD_JUMP_LEFT;
		}
	}
	else
		if (!isHolding)
		{
			
				if (isSitting)
				{
					if (nx > 0)
						aniId = ID_ANI_MARIO_TAIL_SIT_RIGHT;
					else
						aniId = ID_ANI_MARIO_TAIL_SIT_LEFT;
				}
				else
					if (vx == 0)
					{
						if (nx > 0) aniId = ID_ANI_MARIO_TAIL_IDLE_RIGHT;
						else aniId = ID_ANI_MARIO_TAIL_IDLE_LEFT;
					}
					else if (vx > 0)
					{
						if (ax < 0)
							aniId = ID_ANI_MARIO_TAIL_BRACE_RIGHT;
						else if (ax == MARIO_ACCEL_RUN_X) {
							aniId = ID_ANI_MARIO_TAIL_RUNNING_RIGHT;
						}
						else if (ax == MARIO_ACCEL_WALK_X)
							aniId = ID_ANI_MARIO_TAIL_WALKING_RIGHT;
					}
					else // vx < 0
					{
						if (ax > 0)
							aniId = ID_ANI_MARIO_TAIL_BRACE_LEFT;
						else if (ax == -MARIO_ACCEL_RUN_X) {
							aniId = ID_ANI_MARIO_TAIL_RUNNING_LEFT;
						}
						else if (ax == -MARIO_ACCEL_WALK_X)
							aniId = ID_ANI_MARIO_TAIL_WALKING_LEFT;
					}
			
			
		}
		else {
			if (vx == 0) {
				if (nx > 0) aniId = ID_ANI_MARIO_TAIL_HOLD_IDLE_RIGHT;
				else aniId = ID_ANI_MARIO_TAIL_HOLD_IDLE_LEFT;
			}
			else {
				if (nx > 0) aniId = ID_ANI_MARIO_TAIL_HOLD_RUNNING_RIGHT;
				else aniId = ID_ANI_MARIO_TAIL_HOLD_RUNNING_LEFT;
			}
		}

	if (aniId == -1) aniId = ID_ANI_MARIO_TAIL_IDLE_RIGHT;

	return aniId;
}



void CMario::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	int aniId = -1;

	if (state == MARIO_STATE_DIE)
		aniId = ID_ANI_MARIO_DIE;
	else if (level == MARIO_LEVEL_BIG)
		aniId = GetAniIdBig();
	else if (level == MARIO_LEVEL_SMALL)
		aniId = GetAniIdSmall();
	else if (level == MARIO_LEVEL_TAIL)
		aniId = GetAniIdTail();

	animations->Get(aniId)->Render(x, y);

	//RenderBoundingBox();
	
	DebugOutTitle(L"Coins: %d", coin);
}

void CMario::SetState(int state)
{
	// DIE is the end state, cannot be changed! 
	if (this->state == MARIO_STATE_DIE) return; 

	switch (state)
	{
	case MARIO_STATE_RUNNING_RIGHT:
		if (isSitting) break;
		maxVx = MARIO_RUNNING_SPEED;
		ax = MARIO_ACCEL_RUN_X;
		nx = 1;
		break;
	case MARIO_STATE_RUNNING_LEFT:
		if (isSitting) break;
		maxVx = -MARIO_RUNNING_SPEED;
		ax = -MARIO_ACCEL_RUN_X;
		nx = -1;
		break;
	case MARIO_STATE_WALKING_RIGHT:
		if (isSitting) break;
		maxVx = MARIO_WALKING_SPEED;
		ax = MARIO_ACCEL_WALK_X;
		nx = 1;
		break;
	case MARIO_STATE_WALKING_LEFT:
		if (isSitting) break;
		maxVx = -MARIO_WALKING_SPEED;
		ax = -MARIO_ACCEL_WALK_X;
		nx = -1;
		break;
	case MARIO_STATE_JUMP:
		if (isSitting) break;
		if (isOnPlatform)
		{
			if (abs(this->vx) == MARIO_RUNNING_SPEED)
				vy = -MARIO_JUMP_RUN_SPEED_Y;
			else
				vy = -MARIO_JUMP_SPEED_Y;
		}
		break;

	case MARIO_STATE_RELEASE_JUMP:
		if (vy < 0) vy += MARIO_JUMP_SPEED_Y / 2;
		break;

	case MARIO_STATE_SIT:
		if (isOnPlatform && level != MARIO_LEVEL_SMALL)
		{
			state = MARIO_STATE_IDLE;
			isSitting = true;
			vx = 0; vy = 0.0f;
			y +=MARIO_SIT_HEIGHT_ADJUST;
		}
		break;

	case MARIO_STATE_SIT_RELEASE:
		if (isSitting)
		{
			isSitting = false;
			state = MARIO_STATE_IDLE;
			y -= MARIO_SIT_HEIGHT_ADJUST;
		}
		break;

	case MARIO_STATE_IDLE:
		ax = 0.0f;
		vx = 0.0f;
		break;

	case MARIO_STATE_DIE:
		vy = -MARIO_JUMP_DEFLECT_SPEED;
		vx = 0;
		ax = 0;
		break;
	}

	CGameObject::SetState(state);
}

void CMario::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	if (level==MARIO_LEVEL_BIG || level == MARIO_LEVEL_TAIL)
	{
		if (isSitting)
		{
			left = x - MARIO_BIG_SITTING_BBOX_WIDTH / 2;
			top = y - MARIO_BIG_SITTING_BBOX_HEIGHT / 2;
			right = left + MARIO_BIG_SITTING_BBOX_WIDTH;
			bottom = top + MARIO_BIG_SITTING_BBOX_HEIGHT;
		}
		else 
		{
			left = x - MARIO_BIG_BBOX_WIDTH/2;
			top = y - MARIO_BIG_BBOX_HEIGHT/2;
			right = left + MARIO_BIG_BBOX_WIDTH;
			bottom = top + MARIO_BIG_BBOX_HEIGHT;
		}
	}
	else
	{
		left = x - MARIO_SMALL_BBOX_WIDTH/2;
		top = y - MARIO_SMALL_BBOX_HEIGHT/2;
		right = left + MARIO_SMALL_BBOX_WIDTH;
		bottom = top + MARIO_SMALL_BBOX_HEIGHT;
	}
}

void CMario::SetLevel(int l)
{
	// Adjust position to avoid falling off platform
	if (this->level == MARIO_LEVEL_SMALL)
	{
		y -= (MARIO_BIG_BBOX_HEIGHT - MARIO_SMALL_BBOX_HEIGHT) / 2;
	}
	level = l;
}

void CMario::SetLevelLower() {
	isLower = true;

	if (level > MARIO_LEVEL_SMALL)
	{
		StartUntouchable();
		if (level == MARIO_LEVEL_BIG) {

			SetLevel(MARIO_LEVEL_SMALL);
		}
		else if (level == MARIO_LEVEL_TAIL)
		{
			SetLevel(MARIO_LEVEL_BIG);
		}
	}
	else
	{
		SetState(MARIO_STATE_DIE);
	}
}


float CMario::GetPosition()
{
	return x;
	return y;
}

float CMario::GetX()
{
	return x;
}

float CMario::GetY()
{
	return y;
}
