#include "Hametu.h"
#include"UI.h"

Hametu::Hametu() :Base(eType_Hametu)
{
	m_img.Load("Image/Hametu.png");
	SOUND("SE_’ˆÓ")->Play(true);
}
void Hametu::Update()
{
	if (++m_cnt >= 180) {
		//‘Ò‹@ŽžŠÔ3•b`‚T•b
		SetKill();
		SOUND("SE_’ˆÓ")->Stop();
	}
}
void Hametu::Draw()
{
	m_img.Draw();
	m_img.SetPos(400, 0);
}



