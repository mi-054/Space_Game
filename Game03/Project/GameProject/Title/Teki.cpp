#include "Teki.h"
#include"../Game/Game.h"

Teki::Teki():Base(eType_Scene)
{
	m_img = COPY_RESOURCE("Teki", CImage);
}

Teki::~Teki()
{
	SOUND("BGM_Title")->Stop();
	SOUND("BGM_Game")->Play(true);
	Base::KillAll();
	Base::Add(new Game());
}


void Teki::Update()
{
	if (PUSH(CInput::eButton1))
		SetKill();
}

void Teki::Draw()
{
	m_img.Draw();
}
