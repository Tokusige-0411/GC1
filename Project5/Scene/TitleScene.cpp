#include <DxLib.h>
#include "TitleScene.h"
#include "GameScene.h"

TitleScene::TitleScene()
{
}


TitleScene::~TitleScene()
{
}

unique_Base TitleScene::Update(unique_Base own)
{
	if (CheckHitKey(KEY_INPUT_SPACE))
	{
		// ¹Ş°Ñ¼°İ‚Ì“ü‚Á‚½½Ï°ÄÎß²İÀ°‚ğ•Ô‚·
		// Û°¶Ù•Ï”‚ªÁ–Å‚·‚é@¨@Š—LŒ ‚ğ•úŠü‚·‚é
		return std::make_unique<GameScene>();
	}
	return std::move(own);
}
