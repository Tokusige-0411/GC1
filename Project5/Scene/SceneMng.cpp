#include <DxLib.h>
#include <algorithm>
#include <_DebugDispOut.h>
#include <imageMng.h>
#include "SceneMng.h"
#include "GameScene.h"
#include "TitleScene.h"

SceneMng* SceneMng::sInstance = nullptr;

void SceneMng::Draw(void)
{
	_dbgAddDraw();

	// _drawListのLAYERを昇順に
	std::sort(_drawList.begin(), _drawList.end(),
		[](const DrawQuwT& x, const DrawQuwT& y) 
	{return ((std::get<static_cast<int>(DRAW_QUE::LAYER)>(x)) < (std::get<static_cast<int>(DRAW_QUE::LAYER)>(y))); });

	SetDrawScreen(DX_SCREEN_BACK);
	ClsDrawScreen();

	// ｽﾀｯｸにたまっているQueを描画する
	// 範囲for文
	for (auto dQue : _drawList)
	{
		DrawRotaGraph(
			static_cast<int>(std::get<static_cast<int>(DRAW_QUE::X)>(dQue)),
			static_cast<int>(std::get<static_cast<int>(DRAW_QUE::Y)>(dQue)),
			1.0,
			std::get<static_cast<int>(DRAW_QUE::RAD)>(dQue),
			std::get<static_cast<int>(DRAW_QUE::IMAGE)>(dQue),
			true);
	}

	// ｲﾃﾚｰﾀｰを使ったfor文
	// auto = std::vector<DrawQuwT>::iterator
	//for (auto dQue = _drawList.begin(); dQue != _drawList.end(); dQue++)
	//{
	//	DrawGraph(
	//		std::get<static_cast<int>(DRAW_QUE::X)>(*dQue),
	//		std::get<static_cast<int>(DRAW_QUE::Y)>(*dQue),
	//		std::get<static_cast<int>(DRAW_QUE::IMAGE)>(*dQue),
	//		true);
	//}

	//for (int i = 0; i < _drawList.size(); i++)
	//{
	//	DrawGraph(
	//		std::get<static_cast<int>(DRAW_QUE::X)>(_drawList[i]),
	//		std::get<static_cast<int>(DRAW_QUE::Y)>(_drawList[i]),
	//		std::get<static_cast<int>(DRAW_QUE::IMAGE)>(_drawList[i]),
	//		true);
	//}

	ScreenFlip();
}

SceneMng::SceneMng() : ScreenSize{800,600}		// constになる直前に値を初期化する
{
}

SceneMng::~SceneMng()
{
}

void SceneMng::Run(void)
{
	SysInit();
	_activeScene = std::make_unique<GameScene>();
	while (!ProcessMessage() && !CheckHitKey(KEY_INPUT_ESCAPE))
	{
		_dbgStartDraw();
		_drawList.clear();
		lpSceneMng.AddDrawQue({ IMAGE_ID("枠")[0], ScreenSize.x / 2, ScreenSize.y / 2, 0.0, 0, LAYER::UI });
		// ﾒﾓﾘｰを直接管理するべきではない(getをあまり使わないように)
		// [(*_activeScene).] = [_activeScene->]
		// 所有権を渡す(ｺﾋﾟｰを作らない)
		_activeScene = (*_activeScene).Update(std::move(_activeScene));
		Draw();
	}
}

bool SceneMng::AddDrawQue(DrawQuwT dQue)
{
	// static_cast<ｷｬｽﾄしたい型>(ｷｬｽﾄしたい対象物)
	if (std::get<static_cast<int>(DRAW_QUE::IMAGE)>(dQue) <= 0)
	{
		// 画像IDが不正なので、追加しない
		return false;
	}
	// Queを追加
	//_drawList.push_back();
	_drawList.emplace_back(dQue);
	return true;
}

bool SceneMng::SysInit(void)
{
	// ｼｽﾃﾑ処理
	SetWindowText("kadai5");
	SetGraphMode(ScreenSize.x, ScreenSize.y, 16);		// 320*600ﾄﾞｯﾄ、65536色ﾓｰﾄﾞに設定
	ChangeWindowMode(true);								// true:window false:ﾌﾙｽｸﾘｰﾝ
	if (DxLib_Init() == -1)								// DXﾗｲﾌﾞﾗﾘの初期化処理
	{
		return false;
	}

	SetDrawScreen(DX_SCREEN_BACK);						// 描画先をﾊﾞｯｸﾊﾞｯﾌｧに設定
	_dbgSetup(255);
	lpImageMng.GetID("枠", "image/frame.png");

	return false;
}
