#pragma once

#include "../Base/Base.h"

class Title : public Base {
private:
	enum {
		eState_Title2
	};
	//�摜�I�u�W�F�N�g
	CImage m_img;
	//�����\���I�u�W�F�N�g
	CFont m_title_text;
	CFont m_title2_text;
public:
	Title();
	~Title();
	void Update();
	void Draw();

};