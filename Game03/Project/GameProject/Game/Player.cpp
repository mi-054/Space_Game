#include "Player.h"
#include "AnimData.h"
#include "Field.h"
#include "Slash.h"
#include "Effect.h"


void Player::StateIdle()
{
	// 移動量
	const float move_speed =6;
	// 移動フラグ
	bool move_flag = false;
	
	// ジャンプフラグ
	bool jamp_flag = false;
	// ジャンプ力
	const float jump_pow = 12;
	
	// 左移動
	if (HOLD(CInput::eLeft)) {
		// 移動量を設定
		m_pos.x += -move_speed;
		// 反転フラグ
		m_flip = true;
		move_flag = true;
	}
	// 右移動
	if (HOLD(CInput::eRight)) {
		// 移動量を設定
		m_pos.x += move_speed;
		// 反転フラグ
		m_flip = false;
		move_flag = true;
	}
	// ジャンプ
	if (m_is_ground && PUSH(CInput::eButton2)) {
		m_vec.y = -jump_pow;
		m_is_ground = false;
		jamp_flag = true;

	}
	// 攻撃
	if (PUSH(CInput::eButton1)) {
		// 攻撃状態へ移行
		m_state = eState_Attack;
		m_attack_no++;	// 攻撃する度に1増える
	}
	if (move_flag) {
		// 走るアニメーション
		m_img.ChangeAnimation(eAnimRun);
	} else {
		// 待機アニメーション
		m_img.ChangeAnimation(eAnimIdle);
	}
	if (jamp_flag) {
		m_img.ChangeAnimation(eAnimJumpUp);
	}

}

void Player::StateAttack()
{
	// 攻撃アニメーションへ変更
	m_img.ChangeAnimation(eAnimAttack01, false);
	// 3番目のパターンなら
	if (m_img.GetIndex() == 3) {
		if (m_flip) {
			Base::Add(new Slash(m_pos + CVector2D(-64, -64), m_flip, eType_Player_Attack, m_attack_no));
			// 剣を振り下ろす所で攻撃オブジェクトを発生させる
			// eType_Player_Attackはプレイヤーの攻撃
		} else {
			Base::Add(new Slash(m_pos + CVector2D(64, -64), m_flip, eType_Player_Attack, m_attack_no));
		}
	}
	
	// アニメーションが終了したら
	if (m_img.CheckAnimationEnd()) {
		// 通常状態へ移行
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
	// 画像複製
	m_img = COPY_RESOURCE("Player", CImage);
	// 再生アニメーション設定
	m_img.ChangeAnimation(0);
	// 座標設定
	//m_pos_old = 
	m_pos = p;
	// 中心位置設定
	m_img.SetCenter(64, 128);
	// 当たり判定短形
	m_rect = CRect(-54, -128, 54, 0);
	// 反転フラグ
	m_flip = flip;
	// 通常状態へ
	m_state = eState_Idle;
	// 着地フラグ
	m_is_ground = false;
	// 攻撃番号
	m_attack_no = rand();	// 攻撃毎に重複しない番号を設定する
	// ダメージ番号
	m_damage_no = -1;
	// ヒットポイント
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
	// 通常状態
	case eState_Idle:
		StateIdle();
		break;
	// 攻撃状態
	case eState_Attack:
		StateAttack();
		break;
	// ダメージ状態
	case eState_Damage:
		StateDamage();
		break;
	// ダウン状態
	case eState_Down:
		StateDown();
		break;
	}
	// 落ちていたら落下中状態へ移行
	if (m_is_ground && m_vec.y > GRAVITY * 4) {
		m_is_ground = false;
	}
	// 重力による落下
	m_vec.y += GRAVITY;
	m_pos += m_vec;
	
	// アニメーション更新
	m_img.UpdateAnimation();

	// スクロール設定
	m_scroll.x = m_pos.x - 1280 / 2;
	// 縦スクロール対応
	//m_scroll.y = m_pos.y - 600;
}

void Player::Draw()
{
	// 位置設定
	m_img.SetPos(GetScreenPos(m_pos));
	// 反転設定
	m_img.SetFlipH(m_flip);
	// 画像サイズ
	m_img.SetSize(128, 128);
	// 描画
	m_img.Draw();
	// 当たり判定矩形の表示
	//DrawRect();
}

void Player::Collision(Base* b)
{
	switch (b->m_type) {
	//ゴール判定
	case eType_Goal:
		if (!Base::FindObject(eType_Boy)&& !Base::FindObject(eType_RBoy)&& !Base::FindObject(eType_Boss)) {
			if (Base::CollisionRect(this, b)) {
				b->SetKill();
			}
		}
		break;

	// 攻撃オブジェクトとの判定
	case eType_Enemy_Attack:
		// Slash型へキャスト、型変換出来たら
		if (Slash* s = dynamic_cast<Slash*>(b)) {
			if (m_damage_no != s->GetAttackNo() && Base::CollisionRect(this, s)) {
				// 同じ攻撃の連続ダメージ防止
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
		// Field型へキャスト、型変換出来たら
		if (Field* f = dynamic_cast<Field*>(b)) {
			// 地面より下に行ったら
			if (m_pos.y > f->GetGroundY()) {
				// 地面の高さに戻す
				m_pos.y = f->GetGroundY();
				// 落下速度リセット
				m_vec.y = 0;
				// 設置フラグON
				m_is_ground = true;
			}
		}
		// マップとの当たり判定
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
