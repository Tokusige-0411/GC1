#include <DxLib.h>
#include "SceneMng.h"
#include "GameScene.h"
#include "TitleScene.h"


SceneMng* SceneMng::sInstance = nullptr;

enum class DRAW_QUE
{
	IMAGE,
	X,
	Y,
	RAD
};

void SceneMng::Draw(void)
{
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

SceneMng::SceneMng() : screenSize{800,600}		// constになる直前に値を初期化する
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
		_drawList.clear();
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
	SetGraphMode(screenSize.x, screenSize.y, 16);		// 320*600ﾄﾞｯﾄ、65536色ﾓｰﾄﾞに設定
	ChangeWindowMode(true);								// true:window false:ﾌﾙｽｸﾘｰﾝ
	if (DxLib_Init() == -1)								// DXﾗｲﾌﾞﾗﾘの初期化処理
	{
		return false;
	}

	SetDrawScreen(DX_SCREEN_BACK);						// 描画先をﾊﾞｯｸﾊﾞｯﾌｧに設定

	return false;
}
