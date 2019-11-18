#include <algorithm>
#include <DxLib.h>
#include <_DebugConout.h>
#include "GameScene.h"
#include <imageMng.h>
#include <Player.h>
#include <Enemy.h>
#include "SceneMng.h"

vector2Int firstPos[6] = {
	{ -15, 15 },
	{ lpSceneMng.GameScreenSize.x + 15, 15 },
	{ -15, (lpSceneMng.GameScreenSize.y - 32) / 2 },
	{ lpSceneMng.GameScreenSize.x + 15,  (lpSceneMng.GameScreenSize.y - 32) / 2 },
	{ -15, lpSceneMng.GameScreenSize.y - 48 },
	{ lpSceneMng.GameScreenSize.x + 15, lpSceneMng.GameScreenSize.y - 48},
};

GameScene::GameScene()
{
	lpImageMng.GetID("ｷｬﾗ",		"image/char.png",		{ 30, 32 },		{ 10, 10 });
	lpImageMng.GetID("弾",		"image/shot.png",		{ 8,3 },		{ 1,2 });
	lpImageMng.GetID("敵爆発",	"image/en_blast.png",	{ 64,64 },		{ 5, 1 });
	lpImageMng.GetID("PL爆発",	"image/pl_blast.png",	{ 64,64 },		{ 4,1 });

	_objList.emplace_back(
		new Player({ 0, 0 }, { 0, 0 })
	);

	int posCnt;
	posCnt = 0;

	for (int y = 0; y < 5; y++)
	{
		for (int x = 0; x < 10; x++)
		{
			MoveState tmpMoveState;
			tmpMoveState.emplace_back(MOVE_TYPE::WAIT, vector2Dbl{ 30.0 * (y * 10 + x) , 0.0 });
			//tmpMoveState.emplace_back(MOVE_TYPE::WAIT, vector2Dbl{ 0.0 , 0.0 });
			tmpMoveState.emplace_back(
									   MOVE_TYPE::SIGMOID, 
									   vector2Dbl{ (lpSceneMng.GameScreenSize.x / 2) - ((static_cast<double>(lpSceneMng.GameScreenSize.x) * 1 / 5) * (((y * 10 + x) % 2) * 2 - 1)) ,
									  (static_cast<double>(lpSceneMng.GameScreenSize.y) * 5 / 7) + ((static_cast<double>(lpSceneMng.GameScreenSize.y) * 1 / 7) * (((y * 10 + x) % 6 / 4) * -2 + 1))}
									  );
			tmpMoveState.emplace_back(
									   MOVE_TYPE::SPIRAL, 
									   vector2Dbl{ (lpSceneMng.GameScreenSize.x / 2) - ((static_cast<double>(lpSceneMng.GameScreenSize.x) * 1 / 5) * (((y * 10 + x) % 2) * 2 - 1)) ,
									   static_cast<double>(lpSceneMng.GameScreenSize.y) * 5 / 7 }
									  );
			tmpMoveState.emplace_back(MOVE_TYPE::PITIN, vector2Dbl{ static_cast<double>(35 * 3 + 32 * x), static_cast<double>(25 + y * 40) });
			tmpMoveState.emplace_back(MOVE_TYPE::LR, vector2Dbl{ static_cast<double>(35 * 3 + 32 * x), static_cast<double>(25 + y * 40) });

			EnemyState enState = { 
				ENEMY_TYPE::A,
				{ static_cast<double>(firstPos[(y * 10 + x) % 6].x), static_cast<double>(firstPos[(y * 10 + x) % 6].y)},
				{ 30, 32 } ,
				tmpMoveState,
			};

			_objList.emplace_back(new Enemy(enState));
		}
	}

	// ﾃﾞﾊﾞｯｸﾞ用
	//MoveState tmpMoveState;
	//tmpMoveState.emplace_back(MOVE_TYPE::WAIT, vector2Dbl{ 30.0 , 0.0 });
	//tmpMoveState.emplace_back(MOVE_TYPE::SIGMOID, vector2Dbl{ 600.0,400.0 });
	//EnemyState enState = { ENEMY_TYPE::A,
	//{ 0 , 0 },
	//{ 30, 32 } ,
	//	tmpMoveState,
	//};
	//_objList.emplace_back(new Enemy(enState));
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
