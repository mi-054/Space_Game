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
	//�S�ẴI�u�W�F�N�g��j��
	Base::KillAll();
	//�^�C�g���V�[����
	Base::Add(new Title());
	
}

void Game::Update()
{

	//�S�[����������΃Q�[���V�[���I��
	if (!Base::FindObject(eType_Goal)) {
		if (GameClear_flag == false) {

			//��x�����Ăяo��
			Base::Add(new GameClear);
		}
		if (PUSH(CInput::eButton1))
			SetKill();
		GameClear_flag == true;
	}
	//���Z�b�g�����i�^�C�g���ɍs���Ɓj
	
	//�v���C���[���S�@�{�^���P�ŃQ�[���V�[���I��

	else if (!Base::FindObject(eType_Player)) {
		if (GameOver_flag == false) {
			Base::Add(new GameOver);
		}
		if (PUSH(CInput::eButton1))
			SetKill();
		GameOver_flag == true;

	}

	else if (++t2 == 60 * 60) {
		//120�b��Ɉ�x�����Ăяo��
		Base::Add(new GameOver);
	}
	//121�b�ȍ~�L��
	else if (t2>=61*60&&(PUSH(CInput::eButton1))){
			SetKill();

	}
	//�^�C�g���ɖ߂�ƃ��Z�b�g�����
}

