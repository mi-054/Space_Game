#include "Title.h"
#include "../Game/Game.h"
#include "../Game/AnimData.h"
#include"Play.h"
#include"../Game/GameData.h"

Title::Title() :Base(eType_Scene),m_title_text("C:\\Windows\\Fonts\\msgothic.ttc", 60), m_title2_text("C:\\Windows\\Fonts\\msgothic.ttc", 32)
{
	m_img = COPY_RESOURCE("Title", CImage);
	
	
}

Title::~Title()
{
	//全てのオブジェクトを破棄
	Base::KillAll();
	//ゲームシーンへ
	Base::Add(new Play());
}


void Title::Update()
{
	m_img.ChangeAnimation(eState_Title2);
	//アニメーション更新
	m_img.UpdateAnimation();
	
	// ボタン1でタイトル破棄
	if (PUSH(CInput::eButton1)) {
		SetKill();
		GameData::s_score = 0;
	}
	//アニメーション終了チェック
	if (m_img.CheckAnimationEnd());
}

void Title::Draw()
{
	m_img.Draw();
	// 文字表示
	m_title2_text.Draw(10,700, 0, 0, 0, "Eチーム　市原　伊藤　高尾");
	//m_title_text.Draw(640, 480, 1, 0, 0, "Zを押せ");
}
