#pragma once
#include "GameObject.h"

#include "Animation.h"
#include "Animations.h"

#include "debug.h"

#define MARIO_WALKING_SPEED		0.1f
#define MARIO_RUNNING_SPEED		0.2f

#define MARIO_ACCEL_WALK_X	0.0005f
#define MARIO_ACCEL_RUN_X	0.0007f

#define MARIO_JUMP_SPEED_Y		0.5f
#define MARIO_JUMP_RUN_SPEED_Y	0.6f

#define MARIO_GRAVITY			0.002f

#define MARIO_JUMP_DEFLECT_SPEED  0.4f

#define MARIO_STATE_DIE				-10
#define MARIO_STATE_IDLE			0
#define MARIO_STATE_WALKING_RIGHT	100
#define MARIO_STATE_WALKING_LEFT	200

#define MARIO_STATE_JUMP			300
#define MARIO_STATE_RELEASE_JUMP    301

#define MARIO_STATE_RUNNING_RIGHT	400
#define MARIO_STATE_RUNNING_LEFT	500

#define MARIO_STATE_SIT				600
#define MARIO_STATE_SIT_RELEASE		601


#pragma region ANIMATION_ID

//BIG MARIO
#define ID_ANI_MARIO_BIG_IDLE_RIGHT 400
#define ID_ANI_MARIO_BIG_IDLE_LEFT 401

#define ID_ANI_MARIO_BIG_WALKING_RIGHT 500
#define ID_ANI_MARIO_BIG_WALKING_LEFT 501

#define ID_ANI_MARIO_BIG_RUNNING_RIGHT 600
#define ID_ANI_MARIO_BIG_RUNNING_LEFT 601

#define ID_ANI_MARIO_BIG_JUMP_WALK_RIGHT 700
#define ID_ANI_MARIO_BIG_JUMP_WALK_LEFT 701

#define ID_ANI_MARIO_BIG_JUMP_RUN_RIGHT 800
#define ID_ANI_MARIO_BIG_JUMP_RUN_LEFT 801

#define ID_ANI_MARIO_BIG_SIT_RIGHT 900
#define ID_ANI_MARIO_BIG_SIT_LEFT 901

#define ID_ANI_MARIO_BIG_KICK_RIGHT 1021
#define ID_ANI_MARIO_BIG_KICK_LEFT 1020

#define ID_ANI_MARIO_BIG_BRACE_RIGHT 1000
#define ID_ANI_MARIO_BIG_BRACE_LEFT 1001

#define ID_ANI_MARIO_BIG_HOLD_RUNNING_LEFT 1010
#define ID_ANI_MARIO_BIG_HOLD_RUNNING_RIGHT 1011

#define ID_ANI_MARIO_BIG_HOLD_IDLE_LEFT 1040
#define ID_ANI_MARIO_BIG_HOLD_IDLE_RIGHT 1041

#define ID_ANI_MARIO_BIG_HOLD_JUMP_LEFT 1050
#define ID_ANI_MARIO_BIG_HOLD_JUMP_RIGHT 1051




#define ID_ANI_MARIO_DIE 999

// SMALL MARIO
#define ID_ANI_MARIO_SMALL_IDLE_RIGHT 1100
#define ID_ANI_MARIO_SMALL_IDLE_LEFT 1102

#define ID_ANI_MARIO_SMALL_WALKING_RIGHT 1200
#define ID_ANI_MARIO_SMALL_WALKING_LEFT 1201

#define ID_ANI_MARIO_SMALL_RUNNING_RIGHT 1300
#define ID_ANI_MARIO_SMALL_RUNNING_LEFT 1301

#define ID_ANI_MARIO_SMALL_BRACE_RIGHT 1400
#define ID_ANI_MARIO_SMALL_BRACE_LEFT 1401

#define ID_ANI_MARIO_SMALL_JUMP_WALK_RIGHT 1500
#define ID_ANI_MARIO_SMALL_JUMP_WALK_LEFT 1501

#define ID_ANI_MARIO_SMALL_JUMP_RUN_RIGHT 1600
#define ID_ANI_MARIO_SMALL_JUMP_RUN_LEFT 1601




#define ID_ANI_MARIO_SMALL_HOLD_RUNNING_LEFT 1610
#define ID_ANI_MARIO_SMALL_HOLD_RUNNING_RIGHT 1611

#define ID_ANI_MARIO_SMALL_KICK_RIGHT 1621
#define ID_ANI_MARIO_SMALL_KICK_LEFT  1620

#define ID_ANI_MARIO_SMALL_HOLD_IDLE_LEFT 1640
#define ID_ANI_MARIO_SMALL_HOLD_IDLE_RIGHT 1641

#define ID_ANI_MARIO_SMALL_HOLD_JUMP_LEFT 1650
#define ID_ANI_MARIO_SMALL_HOLD_JUMP_RIGHT 1651

//Tail Mario
#define ID_ANI_MARIO_TAIL_IDLE_RIGHT 2401
#define ID_ANI_MARIO_TAIL_IDLE_LEFT 2400

#define ID_ANI_MARIO_TAIL_WALKING_RIGHT 2501
#define ID_ANI_MARIO_TAIL_WALKING_LEFT 2500

#define ID_ANI_MARIO_TAIL_RUNNING_RIGHT 2601
#define ID_ANI_MARIO_TAIL_RUNNING_LEFT 2600

#define ID_ANI_MARIO_TAIL_JUMP_WALK_RIGHT 2701
#define ID_ANI_MARIO_TAIL_JUMP_WALK_LEFT 2700

#define ID_ANI_MARIO_TAIL_JUMP_RUN_RIGHT 2801
#define ID_ANI_MARIO_TAIL_JUMP_RUN_LEFT 2800

#define ID_ANI_MARIO_TAIL_SIT_RIGHT 2901
#define ID_ANI_MARIO_TAIL_SIT_LEFT 2900

#define ID_ANI_MARIO_TAIL_BRACE_RIGHT 3001
#define ID_ANI_MARIO_TAIL_BRACE_LEFT 3000

#define ID_ANI_MARIO_TAIL_HOLD_RUNNING_RIGHT 3011
#define ID_ANI_MARIO_TAIL_HOLD_RUNNING_LEFT 3010

#define ID_ANI_MARIO_TAIL_KICK_RIGHT 3021
#define ID_ANI_MARIO_TAIL_KICK_LEFT 3020

#define ID_ANI_MARIO_TAIL_ATTACK 3100

#define ID_ANI_MARIO_TAIL_HOLD_IDLE_RIGHT 3041
#define ID_ANI_MARIO_TAIL_HOLD_IDLE_LEFT 3040

#define ID_ANI_MARIO_TAIL_HOLD_JUMP_RIGHT 3051
#define ID_ANI_MARIO_TAIL_HOLD_JUMP_LEFT 3050



#pragma endregion

#define GROUND_Y 160.0f




#define	MARIO_LEVEL_SMALL	1
#define	MARIO_LEVEL_BIG		2
#define MARIO_LEVEL_TAIL	3


#define MARIO_BIG_BBOX_WIDTH  14
#define MARIO_BIG_BBOX_HEIGHT 24
#define MARIO_BIG_SITTING_BBOX_WIDTH  14
#define MARIO_BIG_SITTING_BBOX_HEIGHT 16

#define MARIO_SIT_HEIGHT_ADJUST ((MARIO_BIG_BBOX_HEIGHT-MARIO_BIG_SITTING_BBOX_HEIGHT)/2)

#define MARIO_SMALL_BBOX_WIDTH  13
#define MARIO_SMALL_BBOX_HEIGHT 12


#define MARIO_UNTOUCHABLE_TIME 2500
#define TIME_MAX_HOLDING 6000

class CMario : public CGameObject
{
	BOOLEAN isSitting;
	float maxVx;
	float ax;				// acceleration on x 
	float ay;				// acceleration on y 

	int level; 
	int untouchable; 

	ULONGLONG untouchable_start;
	ULONGLONG start_kick;
	ULONGLONG start_holding;

	BOOLEAN isOnPlatform;
	bool isLower;
	bool isHolding;
	bool isKicking;
	bool isRunning;
	bool isChanging;
	int coin; 
	int score;

	void OnCollisionWithGoomba(LPCOLLISIONEVENT e);
	void OnCollisionWithCoin(LPCOLLISIONEVENT e);
	void OnCollisionWithPortal(LPCOLLISIONEVENT e);
	void OnCollisionWithFireBall(LPCOLLISIONEVENT e);
	void OnCollisionWithVenusPlant(LPCOLLISIONEVENT e);
	void OnCollisionWithQuestionBrick(LPCOLLISIONEVENT e);
	void OnCollisionWithMushRoom(LPCOLLISIONEVENT e);
	void OnCollisionWithLeaf(LPCOLLISIONEVENT e);
	void OnCollisionWithKoopa(LPCOLLISIONEVENT e);


	int GetAniIdBig();
	int GetAniIdSmall();
	int GetAniIdTail();

public:
	CMario(float x, float y) : CGameObject(x, y)
	{
		isSitting = false;
		isHolding = false;
		isChanging = false;
		isKicking = false;
		maxVx = 0.0f;
		ax = 0.0f;
		ay = MARIO_GRAVITY; 
		isLower = false;
		isRunning = false;
		level = MARIO_LEVEL_SMALL;
		untouchable = 0;
		untouchable_start = -1;
		isOnPlatform = false;
		coin = 0;
		score = 0;
	}
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void SetState(int state);
	void BlockIfNoBlock(LPGAMEOBJECT gameobject);
	int IsCollidable()
	{ 
		return (state != MARIO_STATE_DIE); 
	}

	int IsBlocking() { return (state != MARIO_STATE_DIE && untouchable==0); }

	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);

	void SetLevel(int l);
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount64(); }

	//get functions
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	float GetPosition();
	float GetX();
	float GetY();
	int GetLevel() { return level; }
	int GetCoin() { return this->coin; }
	int GetScore() { return score; }
	bool GetIsHolding() { return isHolding; }
	bool GetIsKicking() { return isKicking; }

	//set functions
	//void AddScore(float xTemp, float yTemp, int scoreAdd);
	void SetCoin(int coin) { this->coin = coin; }
	void SetScore(int l) { score = l; }
	void SetLevelLower();
	void SetIsHolding(bool b) { isHolding = b; }
	void SetIsKicking(bool b) { isKicking = b; }
	void AdjustHoldingKoopa();

	


};