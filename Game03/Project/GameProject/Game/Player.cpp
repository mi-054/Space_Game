#include "Player.h"
#include "AnimData.h"
#include "Field.h"
#include "Slash.h"
#include "Effect.h"


void Player::StateIdle()
{
	// �ړ���
	const float move_speed =6;
	// �ړ��t���O
	bool move_flag = false;
	
	// �W�����v�t���O
	bool jamp_flag = false;
	// �W�����v��
	const float jump_pow = 12;
	
	// ���ړ�
	if (HOLD(CInput::eLeft)) {
		// �ړ��ʂ�ݒ�
		m_pos.x += -move_speed;
		// ���]�t���O
		m_flip = true;
		move_flag = true;
	}
	// �E�ړ�
	if (HOLD(CInput::eRight)) {
		// �ړ��ʂ�ݒ�
		m_pos.x += move_speed;
		// ���]�t���O
		m_flip = false;
		move_flag = true;
	}
	// �W�����v
	if (m_is_ground && PUSH(CInput::eButton2)) {
		m_vec.y = -jump_pow;
		m_is_ground = false;
		jamp_flag = true;

	}
	// �U��
	if (PUSH(CInput::eButton1)) {
		// �U����Ԃֈڍs
		m_state = eState_Attack;
		m_attack_no++;	// �U������x��1������
	}
	if (move_flag) {
		// ����A�j���[�V����
		m_img.ChangeAnimation(eAnimRun);
	} else {
		// �ҋ@�A�j���[�V����
		m_img.ChangeAnimation(eAnimIdle);
	}
	if (jamp_flag) {
		m_img.ChangeAnimation(eAnimJumpUp);
	}

}

void Player::StateAttack()
{
	// �U���A�j���[�V�����֕ύX
	m_img.ChangeAnimation(eAnimAttack01, false);
	// 3�Ԗڂ̃p�^�[���Ȃ�
	if (m_img.GetIndex() == 3) {
		if (m_flip) {
			Base::Add(new Slash(m_pos + CVector2D(-64, -64), m_flip, eType_Player_Attack, m_attack_no));
			// ����U�艺�낷���ōU���I�u�W�F�N�g�𔭐�������
			// eType_Player_Attack�̓v���C���[�̍U��
		} else {
			Base::Add(new Slash(m_pos + CVector2D(64, -64), m_flip, eType_Player_Attack, m_attack_no));
		}
	}
	
	// �A�j���[�V�������I��������
	if (m_img.CheckAnimationEnd()) {
		// �ʏ��Ԃֈڍs
		m_state = eState_Idle;
	}
}

void Player::StateDamage()
{
	m_img.ChangeAnimation(eAnimDamage, false);
	if (m_img.CheckAnimationEnd()) {
		m_state = eState_Idle;
	}
}

void Player::StateDown()
{
	m_img.ChangeAnimation(eAnimDown, false);
	if (m_img.CheckAnimationEnd()) {
		Base::Add(new Effect("Effect_Smoke", m_pos + CVector2D(0, 0), m_flip));
		m_kill = true;
	}
}

Player::Player(const CVector2D& p, bool flip):Base(eType_Player)
{
	// �摜����
	m_img = COPY_RESOURCE("Player", CImage);
	// �Đ��A�j���[�V�����ݒ�
	m_img.ChangeAnimation(0);
	// ���W�ݒ�
	//m_pos_old = 
	m_pos = p;
	// ���S�ʒu�ݒ�
	m_img.SetCenter(64, 128);
	// �����蔻��Z�`
	m_rect = CRect(-54, -128, 54, 0);
	// ���]�t���O
	m_flip = flip;
	// �ʏ��Ԃ�
	m_state = eState_Idle;
	// ���n�t���O
	m_is_ground = false;
	// �U���ԍ�
	m_attack_no = rand();	// �U�����ɏd�����Ȃ��ԍ���ݒ肷��
	// �_���[�W�ԍ�
	m_damage_no = -1;
	// �q�b�g�|�C���g
	m_hp = 1500;
	
	m_hit = false;

	m_cnt = 0;
}

void Player::Update()
{
	m_cnt--;
	if (m_cnt <= 0) {
		m_hit = false;
	}
	m_pos_old = m_pos;
	switch (m_state){
	// �ʏ���
	case eState_Idle:
		StateIdle();
		break;
	// �U�����
	case eState_Attack:
		StateAttack();
		break;
	// �_���[�W���
	case eState_Damage:
		StateDamage();
		break;
	// �_�E�����
	case eState_Down:
		StateDown();
		break;
	}
	// �����Ă����痎������Ԃֈڍs
	if (m_is_ground && m_vec.y > GRAVITY * 4) {
		m_is_ground = false;
	}
	// �d�͂ɂ�闎��
	m_vec.y += GRAVITY;
	m_pos += m_vec;
	
	// �A�j���[�V�����X�V
	m_img.UpdateAnimation();

	// �X�N���[���ݒ�
	m_scroll.x = m_pos.x - 1280 / 2;
	// �c�X�N���[���Ή�
	//m_scroll.y = m_pos.y - 600;
}

void Player::Draw()
{
	// �ʒu�ݒ�
	m_img.SetPos(GetScreenPos(m_pos));
	// ���]�ݒ�
	m_img.SetFlipH(m_flip);
	// �摜�T�C�Y
	m_img.SetSize(128, 128);
	// �`��
	m_img.Draw();
	// �����蔻���`�̕\��
	//DrawRect();
}

void Player::Collision(Base* b)
{
	switch (b->m_type) {
	//�S�[������
	case eType_Goal:
		if (!Base::FindObject(eType_Boy)&& !Base::FindObject(eType_RBoy)&& !Base::FindObject(eType_Boss)) {
			if (Base::CollisionRect(this, b)) {
				b->SetKill();
			}
		}
		break;

	// �U���I�u�W�F�N�g�Ƃ̔���
	case eType_Enemy_Attack:
		// Slash�^�փL���X�g�A�^�ϊ��o������
		if (Slash* s = dynamic_cast<Slash*>(b)) {
			if (m_damage_no != s->GetAttackNo() && Base::CollisionRect(this, s)) {
				// �����U���̘A���_���[�W�h�~
				m_damage_no = s->GetAttackNo();
				m_hp -= 50;
				m_hit = true;
				m_cnt = 180;
				if (m_hp <= 0) {
					m_state = eState_Down;
				} else {
					m_state = eState_Damage;
				}
				Base::Add(new Effect("Effect_Blood", m_pos + CVector2D(0, -128), m_flip));
			}
		}
		break;
	case eType_Field:
		// Field�^�փL���X�g�A�^�ϊ��o������
		if (Field* f = dynamic_cast<Field*>(b)) {
			// �n�ʂ�艺�ɍs������
			if (m_pos.y > f->GetGroundY()) {
				// �n�ʂ̍����ɖ߂�
				m_pos.y = f->GetGroundY();
				// �������x���Z�b�g
				m_vec.y = 0;
				// �ݒu�t���OON
				m_is_ground = true;
			}
		}
		// �}�b�v�Ƃ̓����蔻��
		/*if (Map* m = dynamic_cast<Map*>(b)) {
			int t = m->CollisionMap(CVector2D(m_pos.x, m_pos_old.y));
			if (t != 0)
				m_pos.x = m_pos_old.x;
			t = m->CollisionMap(CVector2D(m_pos_old.x, m_pos.y));
			if (t != 0) {
				m_pos.y = m_pos_old.y;
				m_vec.y = 0;
				m_is_ground = true;
			}
		}
		break;*/
	}
}
