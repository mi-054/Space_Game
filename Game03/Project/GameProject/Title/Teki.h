#pragma once
#include"../Base/Base.h"

class Teki :public Base {
private:
	CImage m_img;
public:
	Teki();
	Teki::~Teki();

	void Update();
	void Draw();
};