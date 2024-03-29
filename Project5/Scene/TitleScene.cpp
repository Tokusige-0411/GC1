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
		// ｹﾞｰﾑｼｰﾝの入ったｽﾏｰﾄﾎﾟｲﾝﾀｰを返す
		// ﾛｰｶﾙ変数が消滅する　→　所有権を放棄する
		return std::make_unique<GameScene>();
	}
	return std::move(own);
}
