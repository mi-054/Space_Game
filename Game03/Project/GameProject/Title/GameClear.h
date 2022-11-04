#pragma once
#include"../Base/Base.h"

class GameClear :public Base {
private:
	CImage m_img;

public:
	GameClear();
	GameClear::~GameClear();

	void Updata();
	void Draw();

};