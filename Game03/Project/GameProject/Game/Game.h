#pragma once

#include "../Base/Base.h"

class Game : public Base {
public:
	bool GameClear_flag = 0;
	bool GameOver_flag=0;
	int t2 = 0;
	int t4 = 0;
	Game();
	~Game();
	void Update();
};