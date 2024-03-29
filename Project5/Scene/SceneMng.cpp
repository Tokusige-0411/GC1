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
		[](const DrawQueT& x, const DrawQueT& y) {
		// tieを使って複数条件をしていく
		// 左側の要素から順番に比べて、条件に合わなかったら次の要素を比べていく
		return std::tie(std::get<static_cast<int>(DRAW_QUE::LAYER)>(x), std::get<static_cast<int>(DRAW_QUE::ZORDER)>(x))
			< std::tie(std::get<static_cast<int>(DRAW_QUE::LAYER)>(y), std::get<static_cast<int>(DRAW_QUE::ZORDER)>(y));
	});

	SetDrawScreen(DX_SCREEN_BACK);
	ClsDrawScreen();

	// ﾚｲﾔｰやﾓｰﾄﾞの初期値を設定
	LAYER drawLayer = begin(LAYER());
	int blendMode = DX_BLENDMODE_NOBLEND;
	int blendModeNum = 255;

	// 描画先を設定
	SetDrawScreen(_layerGID);
	ClsDrawScreen();
	SetDrawBlendMode(blendMode, blendModeNum);

	// ｽﾀｯｸにたまっているQueを描画する
	// 範囲for文
	for (auto dQue : _drawList)
	{
		double x, y, rad;
		int id;
		LAYER layer;

		// 1個前の情報を保存する
		int blendModeOld = blendMode;
		int blendModeNumOld = blendModeNum;

		// tupluの内容をバラシて入れられる
		std::tie(id, x, y, rad, std::ignore, layer, blendMode, blendModeNum) = dQue;

		// 今のﾚｲﾔｰに合わせて描画先を変える
		if ((layer != drawLayer) || (blendModeOld != blendMode) || (blendModeNum != blendModeNumOld))
		{
			// layerGIDに描いた内容をﾊﾞｯｸﾊﾞｯﾌｧに描画する
			SetDrawScreen(DX_SCREEN_BACK);
			SetDrawBlendMode(blendModeOld, blendModeNumOld);
			auto layPos = ScreenCenter + (*_activeScene)._screenPos;
			DrawRotaGraph(layPos.x, layPos.y, 1.0, 0.0, _layerGID, true);

			// 描画先を_layerGIDに設定
			SetDrawScreen(_layerGID);
			SetDrawBlendMode(blendMode, blendModeNum);
			ClsDrawScreen();
		}

		DrawRotaGraph(static_cast<int>(x), static_cast<int>(y), 1.0, rad, id, true);
	}

	SetDrawScreen(DX_SCREEN_BACK);
	SetDrawBlendMode(blendMode, blendModeNum);

	DrawRotaGraph(ScreenCenter.x, ScreenCenter.y, 1.0, 0, _layerGID, true);


	ScreenFlip();

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
}

SceneMng::SceneMng() : 
	// constになる直前に値を初期化する
	ScreenSize{ 800,600 }, 
	GameScreenSize{ 500,390 }, 
	ScreenCenter{ ScreenSize / 2 }, 
	GameScreenOffset{ (ScreenSize - GameScreenSize) / 2 }
{
}

SceneMng::~SceneMng()
{
}

void SceneMng::Run(void)
{
	SysInit();
	_activeScene = std::make_unique <TitleScene> ();
	while (!ProcessMessage() && !CheckHitKey(KEY_INPUT_ESCAPE))
	{
		_dbgStartDraw();
		_drawList.clear();
		lpSceneMng.AddDrawQue({ IMAGE_ID("枠")[0], ScreenSize.x / 2, ScreenSize.y / 2, 0.0, 0, LAYER::UI, DX_BLENDMODE_NOBLEND, 255});
		// ﾒﾓﾘｰを直接管理するべきではない(getをあまり使わないように)
		// [(*_activeScene).] = [_activeScene->]
		// 所有権を渡す(ｺﾋﾟｰを作らない)
		_activeScene = (*_activeScene).Update(std::move(_activeScene));
		// 結果的にListは削除されているが、削除が必要かどうか判断するようにする
		(*_activeScene).RunActQue(std::move(_actList));
		Draw();
		gameCount++;
	}
}

bool SceneMng::AddDrawQue(DrawQueT dQue)
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

bool SceneMng::AddActQue(ActQueT aQue)
{
	_actList.emplace_back(aQue);
	return true;
}

bool SceneMng::SysInit(void)
{
	// ｼｽﾃﾑ処理
	SetWindowText("kadai5");
	SetGraphMode(ScreenSize.x, ScreenSize.y, 16);		// 800*600ﾄﾞｯﾄ、65536色ﾓｰﾄﾞに設定
	ChangeWindowMode(true);								// true:window false:ﾌﾙｽｸﾘｰﾝ
	if (DxLib_Init() == -1)								// DXﾗｲﾌﾞﾗﾘの初期化処理
	{
		return false;
	}

	SetDrawScreen(DX_SCREEN_BACK);						// 描画先をﾊﾞｯｸﾊﾞｯﾌｧに設定

	// 作ってあれば作らない
	_layerGID = MakeScreen(ScreenSize.x, ScreenSize.y, true);

	_dbgSetup(255);										// ﾃﾞﾊﾞｯｸﾞ用ｾｯﾄｱｯﾌﾟ
	lpImageMng.GetID("枠", "image/frame.png");			// ﾌﾚｰﾑ画像登録
	lpImageMng.GetID("Black", "image/black.png");
	lpImageMng.GetID("White", "image/white.png");

	return false;
}
