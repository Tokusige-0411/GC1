#include "BeseScene.h"

BaseScene::BaseScene()
{
}

BaseScene::~BaseScene()
{
}

void BaseScene::RunActQue(std::vector<ActQueT> actList)
{
	// 何もしない場所なので消すか
	actList.clear();
}
