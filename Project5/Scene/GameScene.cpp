#include <algorithm>
#include <DxLib.h>
#include <_DebugConout.h>
#include "GameScene.h"
#include <imageMng.h>
#include <Player.h>
#include <Enemy.h>

GameScene::GameScene()
{
	lpImageMng.GetID("���",		"image/char.png",		{ 30, 32 },		{ 10, 10 });
	lpImageMng.GetID("�e",		"image/shot.png",		{ 8,3 },		{ 1,2 });
	lpImageMng.GetID("�G����",	"image/en_blast.png",	{ 64,64 },		{ 5, 1 });
	lpImageMng.GetID("PL����",	"image/pl_blast.png",	{ 64,64 },		{ 4,1 });

	_objList.emplace_back(
		new Player({ 100, 100 }, { 0, 0 })
	);
	_objList.emplace_back(
		new Player({ 0, 0 }, { 0, 0 })
	);
}

GameScene::~GameScene()
{
}

// �`����̱����ް�
unique_Base GameScene::Update(unique_Base own)
{
	// Obj��Draw�ɱ������ĕ`��̷�����X�V����
	for (auto data : _objList)
	{
		if (CheckHitKey(KEY_INPUT_SPACE))
		{
			(*data).SetAlive(false);
		}
		(*data).Draw();
	}

	//std::remove_if(
	//	_objList.begin(),		// �����͈͂̊J�n
	//	_objList.end(),			// �����͈͂̏I��
	//	[](sharedObj&obj) {return (*obj).isDead(); }
	//);

	return std::move(own);
	//obj->Draw();
	//for (int i = 0; i < obj.size(); i++)
	//{
	//	obj[i]->Draw();
	//}
}
