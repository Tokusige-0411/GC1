#include <algorithm>
#include <DxLib.h>
#include <_DebugConout.h>
#include "GameScene.h"
#include <imageMng.h>
#include <Player.h>
#include <Enemy.h>
#include "SceneMng.h"

GameScene::GameScene()
{
	lpImageMng.GetID("���",		"image/char.png",		{ 30, 32 },		{ 10, 10 });
	lpImageMng.GetID("�e",		"image/shot.png",		{ 8,3 },		{ 1,2 });
	lpImageMng.GetID("�G����",	"image/en_blast.png",	{ 64,64 },		{ 5, 1 });
	lpImageMng.GetID("PL����",	"image/pl_blast.png",	{ 64,64 },		{ 4,1 });

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
									   vector2Dbl{ 400.0 - ((static_cast<double>(lpSceneMng.ScreenSize.x) * 1 / 5) * (((y * 10 + x) % 2) * 2 - 1)) , 
									  (static_cast<double>(lpSceneMng.ScreenSize.y) * 4 / 7) + ((static_cast<double>(lpSceneMng.ScreenSize.y) * 1 / 7) * (((y * 10 + x) % 6 / 4) * -2 + 1))}
									  );
			tmpMoveState.emplace_back(
									   MOVE_TYPE::SPIRAL, 
									   vector2Dbl{ 400.0 - ((static_cast<double>(lpSceneMng.ScreenSize.x) * 1 / 5) * (((y * 10 + x) % 2) * 2 - 1)) ,
									   static_cast<double>(lpSceneMng.ScreenSize.y) * 4 / 7 }
									  );
			tmpMoveState.emplace_back(MOVE_TYPE::PITIN, vector2Dbl{ static_cast<double>(35 * 7 + 32 * x), static_cast<double>(30 + y * 40) });
			tmpMoveState.emplace_back(MOVE_TYPE::LR, vector2Dbl{ 180.0, 0.0 });
			EnemyState enState = { ENEMY_TYPE::A,
								   { static_cast<double>((x % 2) * 800), static_cast<double>((y * 10 + x) % 6 / 2) * 300}, 
								   { 30, 32 } ,
								   tmpMoveState,
								 };
			_objList.emplace_back(new Enemy(enState));
		}
	}

	// ���ޯ�ޗp
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

// �`����̱����ް�
unique_Base GameScene::Update(unique_Base own)
{
	for (auto data : _objList)
	{
		(*data).Update();
	}
	// Obj��Draw�ɱ������ĕ`��̷�����X�V����
	for (auto data : _objList)
	{
		(*data).Draw();
	}

	// ���g�͂Ȃ��Ȃ邪�A�v�f���͎̂c��@���@�װ���N����
	// �Ԃ�l�͍폜�����v�f�̲�ڰ�����Ԃ��Ă���
	//auto iterator = std::remove_if(
	//					_objList.begin(),		// �����͈͂̊J�n
	//					_objList.end(),			// �����͈͂̏I��
	//					[](sharedObj& obj) {return (*obj).isDead(); }
	//					);
	//_objList.erase(iterator, _objList.end());

	_objList.erase(std::remove_if(
								_objList.begin(),		// �����͈͂̊J�n
								_objList.end(),			// �����͈͂̏I��
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
