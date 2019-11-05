#pragma once
#include "BeseScene.h"
#include "Obj.h"

#define GAME_SCREEN_X 30
#define GAME_SCREEN_Y (32 * 7)


class GameScene :
	public BaseScene
{
public:
	GameScene();
	~GameScene();
	unique_Base Update(unique_Base own) override;		// •`‰æî•ñ‚Ì±¯ÌßÃŞ°Ä
private:
	std::vector<sharedObj> _objList;					// µÌŞ¼Şª¸Ä‚Ì”z—ñ
};

