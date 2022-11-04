#pragma once
#include "../Base/Base.h"

class Goal :public Base {
private:
	enum {
		eState_Goal
	};
	//画像オブジェクト
	CImage m_img;

public:
	Goal(const CVector2D& pos);
	// 移動しないためUpdate()なし
	void Updata();
	void Draw();
};

