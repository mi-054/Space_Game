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
	//��ԕϐ�
	int m_state;
	int m_cnt;
	CImage m_img;
	//���]�t���O
	bool m_flip;
	//���n�t���O
	bool m_is_ground;
	bool m_hit_player;
	//�U���ԍ�
	int m_attack_no;
	// �_���[�W�ԍ�
	int m_damage_no;
	// �q�b�g�|�C���g
	int m_hp;
	//�e��Ԃł̋���
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