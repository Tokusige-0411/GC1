#include <DxLib.h>
#include "BeseScene.h"
#include <imageMng.h>
#include <SceneMng.h>

BaseScene::BaseScene()
{
	_fadeScrID = MakeScreen(lpSceneMng.ScreenSize.x, lpSceneMng.ScreenSize.y, false);
	FadeInit("White");
}

BaseScene::~BaseScene()
{
}

void BaseScene::FadeInit(std::string fadeType)
{
	GetDrawScreenGraph(0, 0, lpSceneMng.ScreenSize.x, lpSceneMng.ScreenSize.y, _fadeScrID);
	_fadeCount = 510;
	_fadeType = fadeType;
}

bool BaseScene::FadeUpdate(void)
{
	if (_fadeCount)
	{
		if (_fadeCount > 255)
		{
			lpSceneMng.AddDrawQue({ _fadeScrID, lpSceneMng.ScreenCenter.x, lpSceneMng.ScreenCenter.y, 0, 0, LAYER::EX, DX_BLENDMODE_NOBLEND, 255 });
		}
		lpSceneMng.AddDrawQue({ lpImageMng.GetID(_fadeType)[0], lpSceneMng.ScreenCenter.x, lpSceneMng.ScreenCenter.y, 0, 10, LAYER::EX,  DX_BLENDMODE_ALPHA, 255 - abs(_fadeCount - 255)});
		_fadeCount--;
	}
	return _fadeCount;
}

void BaseScene::RunActQue(std::vector<ActQueT> actList)
{
	// âΩÇ‡ÇµÇ»Ç¢èÍèäÇ»ÇÃÇ≈è¡Ç∑Ç©
	actList.clear();
}
