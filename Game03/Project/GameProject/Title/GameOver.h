#pragma once
#include"../Base/Base.h"

class GameOver :public Base {
private:
	CImage m_img;

public:
	GameOver();
	GameOver::~GameOver();

	void Update();
	void Draw();
};