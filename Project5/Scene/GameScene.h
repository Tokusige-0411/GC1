#pragma once
#include <functional>
#include <map>
#include "BeseScene.h"
#include "Obj.h"

// ’†g‚¢‚¶‚éê‡‚ÍÍ¯ÀŞ°‚ğ²İ¸Ù°ÄŞ‚µ‚È‚¢‚Æ‚¢‚¯‚È‚¢‚ªA‚»‚¤‚¶‚á‚È‚¢ê‡‚Í‰¼éŒ¾‚Å‚¢‚¢
struct FuncCheckHit;
struct FuncBullet;
struct FuncShake;

using funcAct = std::function<bool(ActQueT&, void*)>;

class GameScene :
	public BaseScene
{
public:
	GameScene();
	~GameScene();
	unique_Base Update(unique_Base own) override;		// •`‰æî•ñ‚Ì±¯ÌßÃŞ°Ä
private:
	// ÌÚİÄŞ“o˜^
	friend FuncCheckHit;
	friend FuncBullet;
	friend FuncShake;

	void initFunc(void);
	std::vector<sharedObj> _objList;					// µÌŞ¼Şª¸Ä‚Ì”z—ñ
	// RunActQue‚Å•`‰æ‚Æ“¯‚¶‚æ‚¤‚È‚±‚Æ‚ğ
	void RunActQue(std::vector<ActQueT> actList);		// ”­ËA“–‚½‚è”»’è‚ğ‚·‚é
	std::map<ACT_QUE, funcAct> funcQue;					// Act‚ğŠÇ—‚·‚é
	int _shakeCount;									// 
};

