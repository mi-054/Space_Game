#pragma once
#include "../Base/Base.h"

class Slash :public Base {
private:
	// 画像オブジェクト
	CImage m_img;
	// 反転フラグ
	bool m_flip;
	// 攻撃番号
	int m_attack_no;
public:
	//　コンストラクタ(攻撃発生位置,攻撃の向き,どちらの攻撃か判別,攻撃毎のユニーク番号)
	Slash(const CVector2D& pos, bool flip, int type, int attack_no);
	void Update();
	void Draw();
	int GetAttackNo() {
		return m_attack_no;
	}
};