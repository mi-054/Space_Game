#pragma once
#include "../Base/Base.h"

class Enemy :public Base {
private:
	enum {
		eState_Idle,
		eState_Attack,
		eState_Damage,
		eState_Down,
		eState_Wait,
	};
	int m_state;
	int m_cnt;

	CImage m_img;
	bool m_flip;
	bool m_is_ground;
	int m_attack_no;
	int m_damage_no;
	int m_hp;

	void StateWait();
	void StateIdle();
	void StateAttack();
	void StateDamage();
	void StateDown();
public:
	Enemy(const CVector2D& p, bool flip);
	void Update();
	void Draw();
	void Collision(Base* b);
};
