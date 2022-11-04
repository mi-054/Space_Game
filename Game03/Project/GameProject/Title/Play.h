#pragma once
#include "../Base/Base.h"

class Play :public Base {
private:
	
	CImage m_img;
	
public:
	
	Play();

	Play::~Play();

	void Update();
	void Draw();
};
