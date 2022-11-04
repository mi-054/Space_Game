#include "RBoy.h"
#include "AnimData.h"
#include "Field.h"
#include "Effect.h"
#include "Map.h"
#include "Slash.h"
#include"GameData.h"


void RBoy::StateIdle()
{
	// 移動量
	const float move_speed = 1;
	// 移動フラグ
	bool move_flag = false;
	// プレイヤーを検索
	Base* player = Base::FindObject(eType_Player);

	if (player) {
		//左移動
		if (player->m_pos.x < m_pos.x - 64) {
			//移動量を設定
			m_pos.x += -move_speed;
			//反転フラグ
			m_flip = true;
			move_flag = true;
		}
		else
			//右移動
			if (player->m_pos.x > m_pos.x + 64) {
				//移動量を設定
				m_pos.x += move_speed;
				//反転フラグ
				m_flip = false;
				move_flag = true;
			}
			else if (m_hit_player == false) {
				//攻撃状態へ移行
				m_state = eState_Attack;
				m_attack_no++;
			}
	}
	//移動中なら
	if (move_flag) {
		//走るアニメーション
		m_img.ChangeAnimation(eAnimRun);
	}
	else {
		//待機アニメーション
		m_img.ChangeAnimation(eAnimIdle);
		//カウント0で待機状態へ
		if (--m_cnt <= 0) {
			//待機時間3～5秒
			m_cnt = rand() % 60 + 120;
			m_state = eState_Wait;
		}
	};
}

void RBoy::StateWait()
{
	m_img.ChangeAnimation(eAnimIdle);
	//カウント0で通常状態へ
	if (--m_cnt <= 0) {
		//待機時間3～5秒
		m_cnt = rand() % 60 + 120;
		m_state = eState_Idle;
	}
}

void RBoy::StateAttack()
{
	//攻撃アニメーションへ変更
	m_img.ChangeAnimation(eAnimAttack01, false);
	if (m_img.GetIndex() == 3) {
		if (m_flip) {
			Base::Add(new Slash(m_pos + CVector2D(-64, -64), m_flip, eType_Enemy_Attack, m_attack_no));
		}
		else {
			Base::Add(new Slash(m_pos + CVector2D(64, -64), m_flip, eType_Enemy_Attack, m_attack_no));
		}
	}
	//アニメーションが終了したら
	if (m_img.CheckAnimationEnd()) {
		//通常状態へ移行
		m_state = eState_Wait;
		m_cnt = rand() % 60 + 120;
	}
}

void RBoy::StateDamage()
{
	//ダメージアニメーションへ変更
	m_img.ChangeAnimation(eAnimDamage, false);
	//アニメーションが終了したら
	if (m_img.CheckAnimationEnd()) {
		//通常状態へ移行
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
		//通常状態
	case eState_Idle:
		StateIdle();
		break;
		//待機状態
	case eState_Wait:
		StateWait();
		break;
		//攻撃状態
	case eState_Attack:
		StateAttack();
		break;
		//ダメージ状態
	case eState_Damage:
		StateDamage();
		break;
	case eState_Down:
		StateDown();
		break;
	}
	//落ちていたら落下中状態へ移行
	if (m_is_ground && m_vec.y > GRAVITY * 4)
		m_is_ground = false;
	//重力による落下
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
		// Slash型へキャスト、型変換出来たら
		if (Slash* s = dynamic_cast<Slash*>(b)) {
			if (m_damage_no != s->GetAttackNo() && Base::CollisionRect(this, s)) {
				// 同じ攻撃の連続ダメージ防止
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
