#pragma once
#include"../Base/Base.h"

class UI :public Base {
public:
	CImage m_img;
	int time = 0;
	int t3 = 0;
public:
	UI();
	void Draw();
};