#include <algorithm>
#include <DxLib.h>
#include <_DebugConout.h>
#include "GameScene.h"
#include <imageMng.h>
#include <Player.h>
#include <Enemy.h>

GameScene::GameScene()
{
	lpImageMng.GetID("·¬×",		"image/char.png",		{ 30, 32 },		{ 10, 10 });
	lpImageMng.GetID("’e",		"image/shot.png",		{ 8,3 },		{ 1,2 });
	lpImageMng.GetID("“G”š”­",	"image/en_blast.png",	{ 64,64 },		{ 5, 1 });
	lpImageMng.GetID("PL”š”­",	"image/pl_blast.png",	{ 64,64 },		{ 4,1 });

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

// •`‰æî•ñ‚Ì±¯ÌßÃÞ°Ä
unique_Base GameScene::Update(unique_Base own)
{
	// Obj‚ÌDraw‚É±¸¾½‚µ‚Ä•`‰æ‚Ì·­°‚ðXV‚·‚é
	for (auto data : _objList)
	{
		if (CheckHitKey(KEY_INPUT_SPACE))
		{
			(*data).SetAlive(false);
		}
		(*data).Draw();
	}

	//std::remove_if(
	//	_objList.begin(),		// Áª¯¸”ÍˆÍ‚ÌŠJŽn
	//	_objList.end(),			// Áª¯¸”ÍˆÍ‚ÌI—¹
	//	[](sharedObj&obj) {return (*obj).isDead(); }
	//);

	return std::move(own);
	//obj->Draw();
	//for (int i = 0; i < obj.size(); i++)
	//{
	//	obj[i]->Draw();
	//}
}
