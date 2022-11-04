#pragma once
#include "../Base/Base.h"
#include "../Game/Player.h"
class Boy :public Base {
private:
	enum {
		eState_Idle,
		eState_Wait,
		eState_Attack,
		eState_Damage,
		eState_Down,
		
	};
	Player* p;
	//状態変数
	int m_state;
	int m_cnt;
	CImage m_img;
	//反転フラグ
	bool m_flip;
	//着地フラグ
	bool m_is_ground;
	bool m_hit_player;
	//攻撃番号
	int m_attack_no;
	// ダメージ番号
	int m_damage_no;
	// ヒットポイント
	int m_hp;
	//各状態での挙動
	void StateIdle();
	void StateWait();
	void StateAttack();
	void StateDamage();
	void StateDown();

public:
	Boy::Boy(const CVector2D& p, bool flip);
	void Update();
	void Draw();
	void Collision(Base* b);
};