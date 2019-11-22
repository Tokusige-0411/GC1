#pragma once
#include <functional>
#include <map>
#include "BeseScene.h"
#include "Obj.h"

using funcAct = std::function<bool(ActQueT&, std::vector<sharedObj>&)>;

class GameScene :
	public BaseScene
{
public:
	GameScene();
	~GameScene();
	unique_Base Update(unique_Base own) override;		// •`‰æî•ñ‚Ì±¯ÌßÃŞ°Ä
private:
	std::vector<sharedObj> _objList;					// µÌŞ¼Şª¸Ä‚Ì”z—ñ
	// RunActQue‚Å•`‰æ‚Æ“¯‚¶‚æ‚¤‚È‚±‚Æ‚ğ
	void RunActQue(std::vector<ActQueT> actList);
	std::map<ACT_QUE, funcAct> funcQue;
};

