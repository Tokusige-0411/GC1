#pragma once
#include "BeseScene.h"
#include "Obj.h"

class GameScene :
	public BaseScene
{
public:
	GameScene();
	~GameScene();
	unique_Base Update(unique_Base own) override;		// •`‰æî•ñ‚Ì±¯ÌßÃŞ°Ä
	// RunActQue‚Å•`‰æ‚Æ“¯‚¶‚æ‚¤‚È‚±‚Æ‚ğ
	void RunActQue(std::vector<ActQueT> actList);
private:
	std::vector<sharedObj> _objList;					// µÌŞ¼Şª¸Ä‚Ì”z—ñ
};

