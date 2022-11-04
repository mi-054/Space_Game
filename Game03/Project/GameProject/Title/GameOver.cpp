#include "GameOver.h"
#include"Title.h"


GameOver::GameOver():Base(eType_Scene)
{
	m_img = COPY_RESOURCE("GameOver", CImage);
}

GameOver::~GameOver()
{
	//Base::KillAll();
	//Base::Add(new Title());
}

void GameOver::Update()
{
	
}

void GameOver::Draw()
{
	m_img.Draw();
}
