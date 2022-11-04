#include "RBoy.h"
#include "AnimData.h"
#include "Field.h"
#include "Effect.h"
#include "Map.h"
#include "Slash.h"
#include"GameData.h"


void RBoy::StateIdle()
{
	// �ړ���
	const float move_speed = 1;
	// �ړ��t���O
	bool move_flag = false;
	// �v���C���[������
	Base* player = Base::FindObject(eType_Player);

	if (player) {
		//���ړ�
		if (player->m_pos.x < m_pos.x - 64) {
			//�ړ��ʂ�ݒ�
			m_pos.x += -move_speed;
			//���]�t���O
			m_flip = true;
			move_flag = true;
		}
		else
			//�E�ړ�
			if (player->m_pos.x > m_pos.x + 64) {
				//�ړ��ʂ�ݒ�
				m_pos.x += move_speed;
				//���]�t���O
				m_flip = false;
				move_flag = true;
			}
			else if (m_hit_player == false) {
				//�U����Ԃֈڍs
				m_state = eState_Attack;
				m_attack_no++;
			}
	}
	//�ړ����Ȃ�
	if (move_flag) {
		//����A�j���[�V����
		m_img.ChangeAnimation(eAnimRun);
	}
	else {
		//�ҋ@�A�j���[�V����
		m_img.ChangeAnimation(eAnimIdle);
		//�J�E���g0�őҋ@��Ԃ�
		if (--m_cnt <= 0) {
			//�ҋ@����3�`5�b
			m_cnt = rand() % 60 + 120;
			m_state = eState_Wait;
		}
	};
}

void RBoy::StateWait()
{
	m_img.ChangeAnimation(eAnimIdle);
	//�J�E���g0�Œʏ��Ԃ�
	if (--m_cnt <= 0) {
		//�ҋ@����3�`5�b
		m_cnt = rand() % 60 + 120;
		m_state = eState_Idle;
	}
}

void RBoy::StateAttack()
{
	//�U���A�j���[�V�����֕ύX
	m_img.ChangeAnimation(eAnimAttack01, false);
	if (m_img.GetIndex() == 3) {
		if (m_flip) {
			Base::Add(new Slash(m_pos + CVector2D(-64, -64), m_flip, eType_Enemy_Attack, m_attack_no));
		}
		else {
			Base::Add(new Slash(m_pos + CVector2D(64, -64), m_flip, eType_Enemy_Attack, m_attack_no));
		}
	}
	//�A�j���[�V�������I��������
	if (m_img.CheckAnimationEnd()) {
		//�ʏ��Ԃֈڍs
		m_state = eState_Wait;
		m_cnt = rand() % 60 + 120;
	}
}

void RBoy::StateDamage()
{
	//�_���[�W�A�j���[�V�����֕ύX
	m_img.ChangeAnimation(eAnimDamage, false);
	//�A�j���[�V�������I��������
	if (m_img.CheckAnimationEnd()) {
		//�ʏ��Ԃֈڍs
		m_state = eState_Idle;
	}
}

void RBoy::StateDown()
{
	m_img.ChangeAnimation(eAnimDown, false);
	if (m_img.CheckAnimationEnd()) {
	Base:Add(new Effect("Effect_Smoke", m_pos + CVector2D(0, 0), m_flip));
		m_kill = true;
	}
}

RBoy::RBoy(const CVector2D& p, bool flip) :Base(eType_RBoy)
{
	m_img = COPY_RESOURCE("RBoy", CImage);

	m_img.ChangeAnimation(0);

	m_is_ground = false;

	m_pos_old = m_pos = p;

	m_img.SetCenter(64, 128);

	m_rect = CRect(-54, -128, 54, 0);

	m_flip = flip;

	m_hit_player = false;

	m_hp = 150;
	m_cnt = 300;
}
void RBoy::Update()
{
	if (!p)
		p = dynamic_cast<Player*>(Base::FindObject(eType_Player));
	m_hit_player = p->m_hit;

	switch (m_state) {
		//�ʏ���
	case eState_Idle:
		StateIdle();
		break;
		//�ҋ@���
	case eState_Wait:
		StateWait();
		break;
		//�U�����
	case eState_Attack:
		StateAttack();
		break;
		//�_���[�W���
	case eState_Damage:
		StateDamage();
		break;
	case eState_Down:
		StateDown();
		break;
	}
	//�����Ă����痎������Ԃֈڍs
	if (m_is_ground && m_vec.y > GRAVITY * 4)
		m_is_ground = false;
	//�d�͂ɂ�闎��
	m_vec.y += GRAVITY;
	m_pos += m_vec;

	//m_img.ChangeAnimation(0);
	m_img.UpdateAnimation();

}
void RBoy::Draw() {
	m_img.SetPos(GetScreenPos(m_pos));

	m_img.SetFlipH(m_flip);

	m_img.SetSize(128, 128);

	m_img.Draw();

	//DrawRect();
}

void RBoy::Collision(Base* b)
{
	switch (b->m_type) {
	case eType_Player_Attack:
		// Slash�^�փL���X�g�A�^�ϊ��o������
		if (Slash* s = dynamic_cast<Slash*>(b)) {
			if (m_damage_no != s->GetAttackNo() && Base::CollisionRect(this, s)) {
				// �����U���̘A���_���[�W�h�~
				m_damage_no = s->GetAttackNo();
				m_hp -= 50;
				if (m_hp <= 0) {
					SetKill();
					GameData::s_score += 100;
				}
				else {
					m_state = eState_Damage;
				}
			}
		}
		break;

	case eType_Field:

		if (Field* f = dynamic_cast<Field*>(b)) {

			if (m_pos.y > f->GetGroundY()) {

				m_pos.y = f->GetGroundY();

				m_vec.y = 0;

				m_is_ground = true;
			}
		}
		break;
	}
}
