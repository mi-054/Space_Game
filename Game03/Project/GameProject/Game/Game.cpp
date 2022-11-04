#include "Game.h"
#include "Field.h"
#include "Player.h"
#include "Enemy.h"
#include "../Title/Title.h"
#include "Goal.h"
#include"Boy.h"
#include"UI.h"
#include"Hametu.h"
#include"GameData.h"
#include"RBoy.h"

#include"Boss.h"
#include"../Title/GameOver.h"
#include"../Title/Gameclear.h"


Game::Game():Base(eType_Scene)
{
	
	//Base::Add(new Map());
	
	Base::Add(new Field());
	Base::Add(new Player(CVector2D(1080, 600), false));
	Base::Add(new Boy(CVector2D(900 + 400 * 1, 540), false));
	Base::Add(new Boy(CVector2D(900 + 400 * 2, 540), false));
	Base::Add(new Boy(CVector2D(900 + 400 * 3, 540), false));
	//Base::Add(new RBoy(CVector2D(1000 + 400 * 1, 540), false));
	Base::Add(new RBoy(CVector2D(1000 + 400 * 2, 540), false));
	Base::Add(new RBoy(CVector2D(1000 + 400 * 3, 540), false));
	Base::Add(new Boss(CVector2D(1000 + 400 * 5, 540), false));

	Base::Add(new Goal(CVector2D(3000, 540 - 64)));
	Base::Add(new UI());
	

}

Game::~Game()
{
	SOUND("BGM_Game")->Stop();
	SOUND("BGM_Title")->Play(true);
	//全てのオブジェクトを破棄
	Base::KillAll();
	//タイトルシーンへ
	Base::Add(new Title());
	
}

void Game::Update()
{

	//ゴールが無ければゲームシーン終了
	if (!Base::FindObject(eType_Goal)) {
		if (GameClear_flag == false) {

			//一度だけ呼び出す
			Base::Add(new GameClear);
		}
		if (PUSH(CInput::eButton1))
			SetKill();
		GameClear_flag == true;
	}
	//リセットされる（タイトルに行くと）
	
	//プレイヤー死亡　ボタン１でゲームシーン終了

	else if (!Base::FindObject(eType_Player)) {
		if (GameOver_flag == false) {
			Base::Add(new GameOver);
		}
		if (PUSH(CInput::eButton1))
			SetKill();
		GameOver_flag == true;

	}

	else if (++t2 == 60 * 60) {
		//120秒後に一度だけ呼び出し
		Base::Add(new GameOver);
	}
	//121秒以降有効
	else if (t2>=61*60&&(PUSH(CInput::eButton1))){
			SetKill();

	}
	//タイトルに戻るとリセットされる
}

