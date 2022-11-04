#include "UI.h"
#include"Hametu.h"
#include"Goal.h"
#include"GameData.h"
//#include"../Title/GameOver.h"
//#include"../Title/GameClear.h"

UI::UI():Base(eType_UI)
{
	m_img.Load("Image/UI.png");
	time = 61*60;
}

void UI::Draw()
{
	int score = GameData::s_score;
	for (int j = 0; j < 8; j++, score /= 10) {
		int q = score % 10;
		m_img.SetRect(16 * q, 16, 16 * q + 16, 32);
		m_img.SetSize(16, 16);
		m_img.SetPos(1080 - 16 * j, 0);
		m_img.Draw();
	}
	time -= 1;
	
	int t = time / 60;
	if (time == 31 * 60) {
		Base::Add(new Hametu());

	}
	for (int i = 0; i < 8; i++, t /=10) {
		int s = t%10;
		m_img.SetRect(16 * s, 16, 16 * s+16, 32);
		m_img.SetSize(16, 16);
		m_img.SetPos(200 - 16*i , 0);
		m_img.Draw();
	}
	
	
	/*Base* Goal = Base::FindObject(eType_Goal);
	Base* player = Base::FindObject(eType_Player);

	if (player == nullptr) {
		Base* player = Base::FindObject(eType_Player);
		// プレイヤーがいなければ
			// ゲームオーバーの表示
		m_img.SetRect(0, 96, 0 + 160, 96 + 32);
		m_img.SetSize(160, 32);
		m_img.SetPos(570, 340);
		m_img.Draw();
	}
	else if (Goal == nullptr) {
		// ゴールがなければ
			// ゲームクリアの表示
		m_img.SetRect(0, 64, 0 + 160, 64 + 32);
		m_img.SetSize(160, 32);
		m_img.SetPos(570, 340);
		m_img.Draw();
	}
	else if (time <=1*60) 
		//if(++t3>=30)
	{
		m_img.SetRect(0, 96, 0 + 160, 96 + 32);
		m_img.SetSize(160, 32);
		m_img.SetPos(570, 340);
		m_img.Draw();
		



	}*/
}
