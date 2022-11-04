#include "AnimData.h"


// プレイヤーのデータ
static TexAnim playerIdle[] = {
	{ 0,0 },
};
static TexAnim playerRun[] = {
	{ 0,5 },
	{ 1,5 },
	{ 2,5 },
	{ 3,5 },
};
static TexAnim playerJumpUp[] = {
	{ 10,7 },
};
static TexAnim playerJumpDown[] = {
	{ 10,7 },

};
static TexAnim playerAttack01[] = {
	{ 7,4 },
	{ 7,3 },
	{ 8,4 },
	{ 8,3 },
	{ 9,4 },
	{ 9,3 },
	{ 9,0 }
};
static TexAnim playerAttack01End[] = {
	{ 7,3 },
	{ 8,3 },
	{ 9,3 },
};
static TexAnim playerAttack02[] = {
	{ 7,3 },
	{ 8,3 },
	{ 9,3 },
};
static TexAnim playerAttack02End[] = {
	{ 7,3 },
	{ 8,3 },
	{ 9,3 },
};
static TexAnim playerAttack03[] = {
	{ 7,3 },
	{ 8,3 },
	{ 9,3 },
};
static TexAnim playerAttack03End[] = {
	{ 7,3 },
	{ 8,3 },
	{ 9,3 },
};

static TexAnim playerDamage[] = {
	{ 4,6 },
	{ 5,6 },
	{ 6,6 },
};
static TexAnim playerDamageEnd[] = {
	{ 92,2 },
	{ 93,2 },
	{ 94,2 },
	{ 95,2 },
};
static TexAnim playerDeath[] = {
	{ 96,4 },
	{ 97,4 },
	{ 98,8 },
	{ 99,4 },
	{ 100,4 },
	{ 101,4 },
	{ 102,4 },
	{ 103,4 },
};

static TexAnim playerDown[] = {
	{ 11,0 },
};
static TexAnim playerDownGround[] = {
	{ 109,4 },
	{ 110,4 },
	{ 111,4 },
};
static TexAnim playerWakeup[] = {
	{ 112,4 },
	{ 113,4 },
	{ 114,4 },
	{ 115,4 },
	{ 116,4 },
	{ 117,4 },
	{ 118,4 },
};
static TexAnim playerGuard[] = {
	//	{ 120,4 },
	//	{ 121,4 },
	{ 122,4 },
};
static TexAnim playerGuardEnd[] = {
	{ 122,4 },
	{ 121,4 },
	{ 120,4 },
};
static TexAnim playerCrash[] = {
	{ 128,4 },
	{ 129,4 },
	{ 130,4 },
	{ 131,90 },
};
static TexAnim playerCrash01End[] = {
	{ 131,4 },
	{ 130,4 },
	{ 129,4 },
	{ 128,4 },
};
static TexAnim playerExtAttack01[] = {
	{ 7,6 },
	{ 8,6 },
	{ 9,6 }
};
static TexAnim playerExtAttack01End[] = {
	{ 7,6 },
	{ 8,6 },
	{ 9,6 }
};
static TexAnim playerExtAttack02[] = {
	{ 160,2 },
	{ 161,2 },
	{ 162,2 },
	{ 163,2 },
	{ 164,2 },
	{ 165,2 },
	{ 166,2 },
	{ 167,2 },
	{ 168,2 },
};
static TexAnim playerExtAttack02End[] = {
	{ 169,16 },
	{ 170,4 },
	{ 171,4 },
};
static TexAnim playerStep[] = {
	{ 120,4 },
	{ 121,4 },
	{ 122,4 },
};
TexAnimData player_anim_data[] = {
	ANIMDATA(playerIdle),
	ANIMDATA(playerRun),
	ANIMDATA(playerJumpUp),
	ANIMDATA(playerJumpDown),
	ANIMDATA(playerAttack01),
	ANIMDATA(playerAttack01End),
	ANIMDATA(playerAttack02),
	ANIMDATA(playerAttack02End),
	ANIMDATA(playerAttack03),
	ANIMDATA(playerAttack03End),
	ANIMDATA(playerDamage),
	ANIMDATA(playerDamageEnd),
	ANIMDATA(playerDeath),
	ANIMDATA(playerDown),
	ANIMDATA(playerDownGround),
	ANIMDATA(playerWakeup),
	ANIMDATA(playerGuard),
	ANIMDATA(playerGuardEnd),
	ANIMDATA(playerCrash),
	ANIMDATA(playerCrash01End),
	ANIMDATA(playerExtAttack01),
	ANIMDATA(playerExtAttack01End),
	ANIMDATA(playerExtAttack02),
	ANIMDATA(playerExtAttack02End),
	ANIMDATA(playerStep),
};

static TexAnim enemyIdle[] = {
	{ 1,0 }
};
static TexAnim enemyRun[] = {
	{ 1,0 },
};
static TexAnim enemyJumpUp[] = {
	{ 0,0 },
};
static TexAnim enemyJumpDown[] = {
	{ 0,0 },
};

static TexAnim enemyAttack01[] = {
	{ 0,7 },
	{ 1,7 },
	{ 2,7 },
	{ 3,7 },
};
static TexAnim enemyAttack01End[] = {
	{ 0,3 },
	{ 1,3 },
	{ 2,3 },
	{ 3,3 },
};
static TexAnim enemyAttack02[] = {
	{ 0,10 },
};
static TexAnim enemyAttack02End[] = {
	{ 0,10 },
};
static TexAnim enemyAttack03[] = {
	{ 0,10 },
};
static TexAnim enemyAttack03End[] = {
	{ 0,10 },
};
static TexAnim enemyDamage[] = {
	{ 4,10 },
};
static TexAnim enemyDamageEnd[] = {
	{ 4,10 },
};
static TexAnim enemyDeath[] = {
	{ 96,4 },
	{ 97,4 },
	{ 98,8 },
	{ 99,4 },
	{ 100,4 },
	{ 101,4 },
	{ 102,4 },
	{ 103,4 },
};

static TexAnim enemyDown[] = {
	{ 104,4 },
	{ 105,4 },
	{ 106,4 },
	{ 107,4 },
	{ 108,4 },
};
static TexAnim enemyDownGround[] = {
	{ 109,4 },
	{ 110,4 },
	{ 111,4 },
};
static TexAnim enemyWakeup[] = {
	{ 112,4 },
	{ 113,4 },
	{ 114,4 },
	{ 115,4 },
	{ 116,4 },
	{ 117,4 },
	{ 118,4 },
};
static TexAnim enemyGuard[] = {
	{ 0,4 },
};
static TexAnim enemyGuardEnd[] = {
	{ 0,4 },
};
static TexAnim enemyCrash[] = {
	{ 128,4 },
	{ 129,4 },
	{ 130,4 },
	{ 131,60 },
};
static TexAnim enemyCrash01End[] = {
	{ 131,4 },
	{ 130,4 },
	{ 129,4 },
	{ 128,4 },
};
static TexAnim enemyExt01Attack[] = {
	{ 0,4 },
};
static TexAnim enemyExtAttack01End[] = {
	{ 0,4 },
};
TexAnimData enemy_anim_data[] = {
	ANIMDATA(enemyIdle),
	ANIMDATA(enemyRun),
	ANIMDATA(enemyJumpUp),
	ANIMDATA(enemyJumpDown),
	ANIMDATA(enemyAttack01),
	ANIMDATA(enemyAttack01End),
	ANIMDATA(enemyAttack02),
	ANIMDATA(enemyAttack02End),
	ANIMDATA(enemyAttack03),
	ANIMDATA(enemyAttack03End),
	ANIMDATA(enemyDamage),
	ANIMDATA(enemyDamageEnd),
	ANIMDATA(enemyDeath),
	ANIMDATA(enemyDown),
	ANIMDATA(enemyDownGround),
	ANIMDATA(enemyWakeup),
	ANIMDATA(enemyGuard),
	ANIMDATA(enemyGuardEnd),
	ANIMDATA(enemyCrash),
	ANIMDATA(enemyCrash01End),
	ANIMDATA(enemyExt01Attack),
	ANIMDATA(enemyExtAttack01End),
};




static TexAnim _effect_blood[] = {
	{ 0,1 },
	{ 1,1 },
	{ 2,1 },
	{ 3,1 },
};
TexAnimData effect_blood_anim_data[] = {
	ANIMDATA(_effect_blood),
};
static TexAnim _effect_smoke[] = {
	{ 0,2 },
	{ 1,2 },
	{ 2,2 },
	{ 3,2 },
	{ 4,2 },
};
TexAnimData effect_smoke_anim_data[] = {
	ANIMDATA(_effect_smoke),
};

static TexAnim _effect_bomb[] = {
	{ 0,2 },
	{ 1,2 },
	{ 2,2 },
	{ 3,2 },
	{ 4,2 },
};
TexAnimData effect_bomb_anim_data[] = {
	ANIMDATA(_effect_smoke),
};
static TexAnim _effect_slash[] = {
	{ 0,4 },
	{ 1,4 },
	{ 2,4 },
	{ 3,4 },
	{ 4,4 },
};
TexAnimData effect_slash_anim_data[] = {
	ANIMDATA(_effect_slash),
};
static TexAnim _Title[] = {
	{0,30},
	{1,30},
	{2,30},
	{3,30},
};
TexAnimData Title_anim_data[] = {
	ANIMDATA(_Title),
};
static TexAnim _Goal[] = {
	{0,30},
	{1,30},
	{2,30},
};
TexAnimData Goal_anim_data[] = {
	ANIMDATA(_Goal),
};