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
	unique_Base Update(unique_Base own) override;		// 描画情報のｱｯﾌﾟﾃﾞｰﾄ
private:
	void initFunc(void);
	std::vector<sharedObj> _objList;					// ｵﾌﾞｼﾞｪｸﾄの配列
	// RunActQueで描画と同じようなことを
	void RunActQue(std::vector<ActQueT> actList);
	std::map<ACT_QUE, funcAct> funcQue;
};

