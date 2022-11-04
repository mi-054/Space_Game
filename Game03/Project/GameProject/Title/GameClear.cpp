#include "GameClear.h"
#include "Title.h"
#include"../Game/Game.h"

GameClear::GameClear():Base(eType_Scene)
{
	m_img = COPY_RESOURCE("GameClear", CImage);
}

GameClear::~GameClear()
{
	//Base::KillAll();
	//Base::Add(new Title());
}

void GameClear::Updata()
{
	
}

void GameClear::Draw()
{
	m_img.Draw();
}
