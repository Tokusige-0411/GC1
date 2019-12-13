#pragma once
#include <memory>
#include <tuple>
#include <vector>
#include <map>
#include <Vector2.h>
#include "BeseScene.h"
#include "LAYER_ID.h"

enum class DRAW_QUE
{
	IMAGE,
	X,
	Y,
	RAD,
	ZORDER,		// ﾚｲﾔｰ内の描画順(数値が低いほうが奥)
	LAYER,		// IDの小さいものを奥に描画
	DRAW_MODE,
	DRAW_NUM,
};

// 描画するのに必要な情報<ImageID, 座標X, 座標Y, 画像の回転角, zOrder, Layer, 描画ﾓｰﾄﾞ, 描画で渡す値>
using DrawQueT = std::tuple<int, double, double, double, int, LAYER, int, int>;

// lp ﾛﾝｸﾞﾎﾟｲﾝﾀｰ
#define lpSceneMng SceneMng::GetInstance()

class SceneMng
{
public:
	// -------------関数
	// 静的なｼﾝｸﾞﾙﾄﾝ
	//　static SceneMng& GetInstance(void)
	//　{
	//		return sInstance;
	//　}

	// 動的なｼﾝｸﾞﾙﾄﾝ
	static SceneMng& GetInstance(void)
	{
		Create();
		return *sInstance;
	}
	static void Create(void)
	{
		if (sInstance == nullptr)
		{
			sInstance = new SceneMng();
		}
	}

	// ｼﾝｸﾞﾙﾄﾝの動的ﾃﾞｽﾄﾗｸﾀ
	static void Destroy()
	{
		if (sInstance != nullptr)
		{
			delete sInstance;
		}
		sInstance = nullptr;
	}

	void Run(void);						// ｹﾞｰﾑﾙｰﾌﾟ

	// 複数の要素を1つにまとめる
	// std::pair<int, double> data1
	// std::tuple<int, int, int> 

	bool AddDrawQue(DrawQueT dQue);		// 描画ｷｭｰの追加
	bool AddActQue(ActQueT aQue);		// ｱｸｼｮﾝｷｭｰの追加

	// -------------変数
	const vector2Int ScreenSize;		// ｽｸﾘｰﾝｻｲｽﾞX,Y
	const vector2Int ScreenCenter;		// 画面の中央
	const vector2Int GameScreenSize;	// ｹﾞｰﾑｽｸﾘｰﾝｻｲｽﾞX,Y
	const vector2Int GameScreenOffset;	// ｹﾞｰﾑｽｸﾘｰﾝのｵﾌｾｯﾄ

	int gameCount;						// ｹﾞｰﾑ全体のｶｳﾝﾄ数

private:
	static SceneMng* sInstance;
	unique_Base _activeScene;			// どのｼｰﾝを走らせるか

	void Draw(void);					// すべてを描画する

	int _layerGID;

	std::vector<DrawQueT> _drawList;	// 描画ｷｭｰを管理する配列
	std::vector<ActQueT> _actList;		// ｱｸｼｮﾝｷｭｰを管理する配列

	SceneMng();
	~SceneMng();
	bool SysInit(void);					// ｼｽﾃﾑ系初期化
};

