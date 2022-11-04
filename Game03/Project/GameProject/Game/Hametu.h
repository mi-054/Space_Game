#pragma once
#include"../Base/Base.h"

class Hametu :public Base {
public:
	CImage m_img;
	int m_cnt=0;
public:
	Hametu();
	void Update();
	void Draw();
};