#include "AnimData.h"
#include "Goal.h"
Goal::Goal(const CVector2D& pos) :Base(eType_Goal) {

	//画像複製
	m_img = COPY_RESOURCE("Goal", CImage);
	// 中心位置設定
	m_img.SetCenter(32,64);
	// 当たり判定用短形設定
	m_rect = CRect(-16*2, -64*2, 16*2, 32*2);
	m_pos = pos;

	
}

void Goal::Updata()
{
	
}
void Goal::Draw() {
	m_img.ChangeAnimation(eState_Goal);
	//アニメーション更新
	m_img.UpdateAnimation();
	//アニメーション終了チェック
	if (m_img.CheckAnimationEnd());
	// 位置設定
	m_img.SetPos(GetScreenPos(m_pos));
	m_img.Draw();
	// 当たり判定矩形の表示
	//DrawRect();
}
