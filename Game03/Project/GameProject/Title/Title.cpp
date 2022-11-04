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
	//�S�ẴI�u�W�F�N�g��j��
	Base::KillAll();
	//�Q�[���V�[����
	Base::Add(new Play());
}


void Title::Update()
{
	m_img.ChangeAnimation(eState_Title2);
	//�A�j���[�V�����X�V
	m_img.UpdateAnimation();
	
	// �{�^��1�Ń^�C�g���j��
	if (PUSH(CInput::eButton1)) {
		SetKill();
		GameData::s_score = 0;
	}
	//�A�j���[�V�����I���`�F�b�N
	if (m_img.CheckAnimationEnd());
}

void Title::Draw()
{
	m_img.Draw();
	// �����\��
	m_title2_text.Draw(10,700, 0, 0, 0, "E�`�[���@�s���@�ɓ��@����");
	//m_title_text.Draw(640, 480, 1, 0, 0, "Z������");
}
