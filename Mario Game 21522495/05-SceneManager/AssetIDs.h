#pragma once

//
// This file contains all IDs of game assets 
//

#define ID_TEX_MARIO 0
#define ID_TEX_ENEMY 10
#define ID_TEX_MISC 20


#define OBJECT_TYPE_MARIO	0
#define OBJECT_TYPE_BRICK	1
#define OBJECT_TYPE_GOOMBA	2
#define OBJECT_TYPE_KOOPAS	3
#define OBJECT_TYPE_COIN 4
#define OBJECT_TYPE_PLATFORM 5
#define OBJECT_TYPE_TRANSPARENTBLOCK 6
#define OBJECT_TYPE_FIREBALL 7
#define OBJECT_TYPE_VENUSPLANT 8
#define OBJECT_TYPE_BRICKQUESTION_COIN 9
#define OBJECT_TYPE_BRICKQUESTION_ITEM 10
#define OBJECT_TYPE_BRICKQUESTION_MUSHROOM_GREEN 11
#define OBJECT_TYPE_BRICK_COLOR_IS_COIN 12
#define OBJECT_TYPE_BRICK_COLOR_IS_NOT_COIN 13


#define OBJECT_TYPE_PORTAL	50


#pragma region MARIO 

#define ID_SPRITE_MARIO 10000
#define ID_SPRITE_MARIO_BIG (ID_SPRITE_MARIO + 1000)
#define ID_SPRITE_MARIO_BIG_IDLE (ID_SPRITE_MARIO_BIG + 100)
#define ID_SPRITE_MARIO_BIG_IDLE_LEFT (ID_SPRITE_MARIO_BIG_IDLE + 10)
#define ID_SPRITE_MARIO_BIG_IDLE_RIGHT (ID_SPRITE_MARIO_BIG_IDLE + 20)

#define ID_SPRITE_MARIO_BIG_WALKING (ID_SPRITE_MARIO_BIG + 200)
#define ID_SPRITE_MARIO_BIG_WALKING_LEFT (ID_SPRITE_MARIO_BIG_WALKING + 10)
#define ID_SPRITE_MARIO_BIG_WALKING_RIGHT (ID_SPRITE_MARIO_BIG_WALKING + 20)
#define ID_SPRITE_MARIO_BIG_RUNNING (ID_SPRITE_MARIO_BIG + 300)
#define ID_SPRITE_MARIO_BIG_RUNNING_LEFT (ID_SPRITE_MARIO_BIG_RUNNING + 10)
#define ID_SPRITE_MARIO_BIG_RUNNING_RIGHT (ID_SPRITE_MARIO_BIG_RUNNING + 20)
#define ID_SPRITE_MARIO_BIG_JUMP (ID_SPRITE_MARIO_BIG + 400)
#define ID_SPRITE_MARIO_BIG_JUMP_WALK (ID_SPRITE_MARIO_BIG_JUMP + 10)
#define ID_SPRITE_MARIO_BIG_JUMP_WALK_LEFT (ID_SPRITE_MARIO_BIG_JUMP_WALK + 2)
#define ID_SPRITE_MARIO_BIG_JUMP_WALK_RIGHT (ID_SPRITE_MARIO_BIG_JUMP_WALK + 6)
#define ID_SPRITE_MARIO_BIG_JUMP_RUN (ID_SPRITE_MARIO_BIG_JUMP + 20)
#define ID_SPRITE_MARIO_BIG_JUMP_RUN_LEFT (ID_SPRITE_MARIO_BIG_JUMP_RUN + 2)
#define ID_SPRITE_MARIO_BIG_JUMP_RUN_RIGHT (ID_SPRITE_MARIO_BIG_JUMP_RUN + 6)
#define ID_SPRITE_MARIO_BIG_SIT (ID_SPRITE_MARIO_BIG + 500)
#define ID_SPRITE_MARIO_BIG_SIT_LEFT (ID_SPRITE_MARIO_BIG_SIT + 10)
#define ID_SPRITE_MARIO_BIG_SIT_RIGHT (ID_SPRITE_MARIO_BIG_SIT + 20)
#define ID_SPRITE_MARIO_BIG_BRACE (ID_SPRITE_MARIO_BIG + 600)
#define ID_SPRITE_MARIO_BIG_BRACE_LEFT (ID_SPRITE_MARIO_BIG_BRACE + 10)
#define ID_SPRITE_MARIO_BIG_BRACE_RIGHT (ID_SPRITE_MARIO_BIG_BRACE + 20)

#define ID_SPRITE_MARIO_DIE (ID_SPRITE_MARIO + 3000)

#define ID_SPRITE_MARIO_SMALL (ID_SPRITE_MARIO + 2000)
#define ID_SPRITE_MARIO_SMALL_IDLE (ID_SPRITE_MARIO_SMALL + 100)
#define ID_SPRITE_MARIO_SMALL_IDLE_LEFT (ID_SPRITE_MARIO_SMALL_IDLE + 10)
#define ID_SPRITE_MARIO_SMALL_IDLE_RIGHT (ID_SPRITE_MARIO_SMALL_IDLE + 20)

#define ID_SPRITE_MARIO_SMALL_WALKING (ID_SPRITE_MARIO_SMALL + 200)
#define ID_SPRITE_MARIO_SMALL_WALKING_LEFT (ID_SPRITE_MARIO_SMALL_WALKING + 10)
#define ID_SPRITE_MARIO_SMALL_WALKING_RIGHT (ID_SPRITE_MARIO_SMALL_WALKING + 20)
#define ID_SPRITE_MARIO_SMALL_RUNNING (ID_SPRITE_MARIO_SMALL + 300)
#define ID_SPRITE_MARIO_SMALL_RUNNING_LEFT (ID_SPRITE_MARIO_SMALL_RUNNING + 10)
#define ID_SPRITE_MARIO_SMALL_RUNNING_RIGHT (ID_SPRITE_MARIO_SMALL_RUNNING + 20)
#define ID_SPRITE_MARIO_SMALL_JUMP (ID_SPRITE_MARIO_SMALL + 400)
#define ID_SPRITE_MARIO_SMALL_JUMP_WALK (ID_SPRITE_MARIO_SMALL_JUMP + 10)
#define ID_SPRITE_MARIO_SMALL_JUMP_WALK_LEFT (ID_SPRITE_MARIO_SMALL_JUMP_WALK + 2)
#define ID_SPRITE_MARIO_SMALL_JUMP_WALK_RIGHT (ID_SPRITE_MARIO_SMALL_JUMP_WALK + 6)
#define ID_SPRITE_MARIO_SMALL_JUMP_RUN (ID_SPRITE_MARIO_SMALL_JUMP + 20)
#define ID_SPRITE_MARIO_SMALL_JUMP_RUN_LEFT (ID_SPRITE_MARIO_SMALL_JUMP_RUN + 2)
#define ID_SPRITE_MARIO_SMALL_JUMP_RUN_RIGHT (ID_SPRITE_MARIO_SMALL_JUMP_RUN + 6)

#define ID_SPRITE_MARIO_SMALL_SIT (ID_SPRITE_MARIO_SMALL + 500)
#define ID_SPRITE_MARIO_SMALL_SIT_LEFT (ID_SPRITE_MARIO_SMALL_SIT + 10)
#define ID_SPRITE_MARIO_SMALL_SIT_RIGHT (ID_SPRITE_MARIO_SMALL_SIT + 20)

#define ID_SPRITE_MARIO_SMALL_BRACE (ID_SPRITE_MARIO_SMALL + 500)
#define ID_SPRITE_MARIO_SMALL_BRACE_LEFT (ID_SPRITE_MARIO_SMALL_BRACE + 10)
#define ID_SPRITE_MARIO_SMALL_BRACE_RIGHT (ID_SPRITE_MARIO_SMALL_BRACE + 20)

#pragma endregion 

#define ID_SPRITE_BRICK 20000

#define ID_SPRITE_GOOMBA 30000
#define ID_SPRITE_GOOMBA_WALK (ID_SPRITE_GOOMBA + 1000)
#define ID_SPRITE_GOOMBA_DIE (ID_SPRITE_GOOMBA + 2000)

#define ID_SPRITE_COIN 40000

#define ID_SPRITE_CLOUD 50000
#define ID_SPRITE_CLOUD_BEGIN (ID_SPRITE_CLOUD+1000)
#define ID_SPRITE_CLOUD_MIDDLE (ID_SPRITE_CLOUD+2000)
#define ID_SPRITE_CLOUD_END (ID_SPRITE_CLOUD+3000)

#define ID_SPRITE_GROUND 60000
#define ID_SPRITE_GROUD_BEGIN (ID_SPRITE_GROUND+1000)
#define ID_SPRITE_GROUD_MIDDLE (ID_SPRITE_GROUND+2000)
#define ID_SPRITE_GROUD_END (ID_SPRITE_GROUND+3000)

#define ID_SPRITE_BIGTREES 70000
#define ID_SPRITE_BIGTREES_BEGIN (ID_SPRITE_BIGTREES+1000)
#define ID_SPRITE_BIGTREES_MIDDLE (ID_SPRITE_BIGTREES+2000)
#define ID_SPRITE_BIGTREES_END (ID_SPRITE_BIGTREES+3000)

#define ID_SPRITE_SMALLTREES 80000
#define ID_SPRITE_SMALLTREES_BEGIN (ID_SPRITE_SMALLTREES+1000)
#define ID_SPRITE_SMALLTREES_MIDDLE (ID_SPRITE_SMALLTREES+2000)
#define ID_SPRITE_SMALLTREES_END (ID_SPRITE_SMALLTREES+3000)

#define ID_SPRITE_PINKBOX 90000
#define ID_SPRITE_PINKBOX_BEGIN (ID_SPRITE_PINKBOX+1000)
#define ID_SPRITE_PINKBOX_MIDDLE (ID_SPRITE_PINKBOX+2000)
#define ID_SPRITE_PINKBOX_END (ID_SPRITE_PINKBOX+3000)

#define ID_SPRITE_BLUEBOX 100000
#define ID_SPRITE_BLUEBOX_BEGIN (ID_SPRITE_BLUEBOX+1000)
#define ID_SPRITE_BLUEBOX_MIDDLE (ID_SPRITE_BLUEBOX+2000)
#define ID_SPRITE_BLUEBOX_END (ID_SPRITE_BLUEBOX+3000)

#define ID_SPRITE_LONGGREENPIPE 110000
#define ID_SPRITE_LONGGREENPIPE_BEGIN (ID_SPRITE_LONGGREENPIPE+1000)
#define ID_SPRITE_LONGGREENPIPE_MIDDLE (ID_SPRITE_LONGGREENPIPE+2000)
#define ID_SPRITE_LONGGREENPIPE_END (ID_SPRITE_LONGGREENPIPE+3000)

#define ID_SPRITE_GREENBOX1 120000
#define ID_SPRITE_GREENBOX1_BEGIN (ID_SPRITE_GREENBOX1+1000)
#define ID_SPRITE_GREENBOX1_MIDDLE (ID_SPRITE_GREENBOX1+2000)
#define ID_SPRITE_GREENBOX1_END (ID_SPRITE_GREENBOX1+3000)

#define ID_SPRITE_PINKBOX2 130000
#define ID_SPRITE_PINKBOX2_BEGIN (ID_SPRITE_PINKBOX2+1000)
#define ID_SPRITE_PINKBOX2_MIDDLE (ID_SPRITE_PINKBOX2+2000)
#define ID_SPRITE_PINKBOX2_END (ID_SPRITE_PINKBOX2+3000)

#define ID_SPRITE_WHITEBOX 140000
#define ID_SPRITE_WHITEBOX_BEGIN (ID_SPRITE_WHITEBOX+1000)
#define ID_SPRITE_WHITEBOX_MIDDLE (ID_SPRITE_WHITEBOX+2000)
#define ID_SPRITE_WHITEBOX_END (ID_SPRITE_WHITEBOX+3000)

#define ID_SPRITE_GREENBOX2 150000
#define ID_SPRITE_GREENBOX2_BEGIN (ID_SPRITE_GREENBOX2+1000)
#define ID_SPRITE_GREENBOX2_MIDDLE (ID_SPRITE_GREENBOX2+2000)
#define ID_SPRITE_GREENBOX2_END (ID_SPRITE_GREENBOX2+3000)

#define ID_SPRITE_GROUND2 160000
#define ID_SPRITE_GROUND2_BEGIN (ID_SPRITE_GROUND2+1000)
#define ID_SPRITE_GROUND2_MIDDLE (ID_SPRITE_GROUND2+2000)
#define ID_SPRITE_GROUND2_END (ID_SPRITE_GROUND2+3000)

#define ID_SPRITE_BRICK 170000

#define ID_SPRITE_SMILECLOUDS 180000
#define ID_SPRITE_SMILECLOUDS_BEGIN (ID_SPRITE_SMILECLOUDS+1000)
#define ID_SPRITE_SMILECLOUDS_MIDDLE (ID_SPRITE_SMILECLOUDS+2000)
#define ID_SPRITE_SMILECLOUDS_END (ID_SPRITE_SMILECLOUDS+3000)

#define ID_SPRITE_SMILECLOUD 190000
#define ID_SPRITE_SMILECLOUD_BEGIN (ID_SPRITE_SMILECLOUD+1000)
#define ID_SPRITE_SMILECLOUD_MIDDLE (ID_SPRITE_SMILECLOUD+2000)
#define ID_SPRITE_SMILECLOUD_END (ID_SPRITE_SMILECLOUD+3000)

#define ID_SPRITE_FIREBALL 190000
#define ID_SPRITE_FIREBALL_FLY (ID_SPRITE_FIREBALL + 1000)

#define ID_SPRITE_VENUSPLANT 200000
#define ID_SPRITE_VENUSPLANT_HEAD_UP (ID_SPRITE_VENUSPLANT+1000)
#define ID_SPRITE_VENUSPLANT_HEAD_DOWN (ID_SPRITE_VENUSPLANT+2000)







