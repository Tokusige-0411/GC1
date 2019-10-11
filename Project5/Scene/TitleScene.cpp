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
		// �ްѼ�݂̓������ϰ��߲�����Ԃ�
		// ۰�ٕϐ������ł���@���@���L�����������
		return std::make_unique<GameScene>();
	}
	return std::move(own);
}
