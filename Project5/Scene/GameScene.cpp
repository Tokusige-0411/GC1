#include <algorithm>
#include <DxLib.h>
#include <_DebugConout.h>
#include "GameScene.h"
#include <imageMng.h>
#include <Player.h>
#include <Enemy.h>
#include <Bullet.h>
#include "SceneMng.h"
#include <func\FuncBullet.h>
#include <func\FuncCheckHit.h>

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
	initFunc();

	lpImageMng.GetID("ｷｬﾗ", "image/char.png", { 30, 32 }, { 10, 10 });
	lpImageMng.GetID("弾", "image/shot.png", { 8,3 }, { 1,2 });
	lpImageMng.GetID("敵爆発", "image/en_blast.png", { 64,64 }, { 5, 1 });
	lpImageMng.GetID("PL爆発", "image/pl_blast.png", { 64,64 }, { 4,1 });

	_objList.emplace_back(
		new Player({ static_cast<double>(lpSceneMng.GameScreenSize.x / 2), static_cast<double>(lpSceneMng.GameScreenSize.y - 16) }, { 0, 0 })
	);

	for (int y = 0; y < 5; y++)
	{
		for (int x = 0; x < 10; x++)
		{
			MoveState tmpMoveState;
			//tmpMoveState.emplace_back(MOVE_TYPE::WAIT, vector2Dbl{ 30.0 * (y * 10 + x) , 0.0 });
			tmpMoveState.emplace_back(MOVE_TYPE::WAIT, vector2Dbl{ 0.0 , 0.0 });
			//tmpMoveState.emplace_back(
			//	MOVE_TYPE::SIGMOID,
			//	vector2Dbl{ (lpSceneMng.GameScreenSize.x / 2) - ((static_cast<double>(lpSceneMng.GameScreenSize.x) * 1 / 5) * (((y * 10 + x) % 2) * 2 - 1)) ,
			//   (static_cast<double>(lpSceneMng.GameScreenSize.y) * 5 / 7) + ((static_cast<double>(lpSceneMng.GameScreenSize.y) * 1 / 7) * (((y * 10 + x) % 6 / 4) * -2 + 1)) }
			//);
			//tmpMoveState.emplace_back(
			//	MOVE_TYPE::SPIRAL,
			//	vector2Dbl{ (lpSceneMng.GameScreenSize.x / 2) - ((static_cast<double>(lpSceneMng.GameScreenSize.x) * 1 / 5) * (((y * 10 + x) % 2) * 2 - 1)) ,
			//	static_cast<double>(lpSceneMng.GameScreenSize.y) * 5 / 7 }
			//);
			tmpMoveState.emplace_back(MOVE_TYPE::PITIN, vector2Dbl{ static_cast<double>(35 * 3 + 32 * x), static_cast<double>(35 + y * 40) });
			tmpMoveState.emplace_back(MOVE_TYPE::LR, vector2Dbl{ static_cast<double>(35 * 3 + 32 * x), static_cast<double>(35 + y * 40) });
			tmpMoveState.emplace_back(MOVE_TYPE::EXRATE, vector2Dbl{ static_cast<double>(((35 * 3 + 32 * 0) + (35 * 3 + 32 * 9)) / 2),  static_cast<double>(((35 + 0 * 40) + (35 + 4 * 40)) / 2) });
			tmpMoveState.emplace_back(MOVE_TYPE::ATTACK, vector2Dbl{ 180.0, 0.0 });
			tmpMoveState.emplace_back(MOVE_TYPE::PITIN, vector2Dbl{ static_cast<double>(35 * 3 + 32 * x), static_cast<double>(35 + y * 40) });

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
	// ﾌﾟﾚｲﾔｰの座標を見つける
	auto plObj = std::find_if(_objList.begin(), _objList.end(), [](sharedObj Obj) {return ((*Obj).unitID() == UNIT_ID::PLAYER); });

	// 敵にattackに移行していいか支持する
	auto setMove = [](sharedObj Obj) {
		if ((*Obj).unitID() == UNIT_ID::ENEMY)
		{
			if (rand() % 3000 == 0 && !(*Obj).exFlag())
			{
				return true;
			}
		}
		return false;
	};

	for (auto data : _objList)
	{
		if (setMove(data))
		{
			(*data).SetExFlag(true);
		}
		(*data).Update(*plObj);
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

void GameScene::initFunc(void)
{
	funcQue[ACT_QUE::SHOT] = FuncBullet();
	funcQue[ACT_QUE::CHECK_HIT] = FuncCheckHit();
}

void GameScene::RunActQue(std::vector<ActQueT> actList)
{
	for (auto actData : actList)
	{
		try
		{
			funcQue[actData.first](actData, _objList);
		}
		catch(...)
		{
			AST();
		}
	}
}
