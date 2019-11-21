#pragma once
#include "BeseScene.h"
#include "Obj.h"

class GameScene :
	public BaseScene
{
public:
	GameScene();
	~GameScene();
	unique_Base Update(unique_Base own) override;		// 描画情報のｱｯﾌﾟﾃﾞｰﾄ
	// RunActQueで描画と同じようなことを
	void RunActQue(std::vector<ActQueT> actList);
private:
	std::vector<sharedObj> _objList;					// ｵﾌﾞｼﾞｪｸﾄの配列
};

