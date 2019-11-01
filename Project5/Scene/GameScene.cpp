#include <algorithm>
#include <DxLib.h>
#include <_DebugConout.h>
#include "GameScene.h"
#include <imageMng.h>
#include <Player.h>
#include <Enemy.h>

GameScene::GameScene()
{
	lpImageMng.GetID("ｷｬﾗ",		"image/char.png",		{ 30, 32 },		{ 10, 10 });
	lpImageMng.GetID("弾",		"image/shot.png",		{ 8,3 },		{ 1,2 });
	lpImageMng.GetID("敵爆発",	"image/en_blast.png",	{ 64,64 },		{ 5, 1 });
	lpImageMng.GetID("PL爆発",	"image/pl_blast.png",	{ 64,64 },		{ 4,1 });

	_objList.emplace_back(
		new Player({ 0, 0 }, { 0, 0 })
	);

	for (int y = 0; y < 5; y++)
	{
		for (int x = 0; x < 5; x++)
		{
			MoveState tmpMoveState;
			tmpMoveState.emplace_back(MOVE_TYPE::WAIT, vector2Dbl{ 180.0, 0.0 });
			tmpMoveState.emplace_back(MOVE_TYPE::LR, vector2Dbl{ 180.0, 0.0 });
			EnemyState enState = { ENEMY_TYPE::A,
								   { static_cast<double>(100 + x * 60), static_cast<double>(100 + y * 64) }, 
								   { 0, 0 } ,
								   tmpMoveState,
								 };
			_objList.emplace_back(new Enemy(enState));
		}
	}
}

GameScene::~GameScene()
{
}

// 描画情報のｱｯﾌﾟﾃﾞｰﾄ
unique_Base GameScene::Update(unique_Base own)
{
	for (auto data : _objList)
	{
		(*data).Update();
	}
	// ObjのDrawにｱｸｾｽして描画のｷｭｰを更新する
	for (auto data : _objList)
	{
		(*data).Draw();
	}

	// 中身はなくなるが、要素自体は残る　→　ｴﾗｰが起こる
	// 返り値は削除した要素のｲﾃﾚｰﾀｰが返ってくる
	//auto iterator = std::remove_if(
	//					_objList.begin(),		// ﾁｪｯｸ範囲の開始
	//					_objList.end(),			// ﾁｪｯｸ範囲の終了
	//					[](sharedObj& obj) {return (*obj).isDead(); }
	//					);
	//_objList.erase(iterator, _objList.end());

	_objList.erase(std::remove_if(
								_objList.begin(),		// ﾁｪｯｸ範囲の開始
								_objList.end(),			// ﾁｪｯｸ範囲の終了
								[](sharedObj& obj) {return (*obj).isDead(); }
							),
								_objList.end());

	return std::move(own);
	//obj->Draw();
	//for (int i = 0; i < obj.size(); i++)
	//{
	//	obj[i]->Draw();
	//}
}
