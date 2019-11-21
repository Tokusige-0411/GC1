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
	LAYER		// IDの小さいものを奥に描画
};

// 描画するのに必要な情報<ImageID, 座標X, 座標Y, 画像の回転角>
using DrawQueT = std::tuple<int, double, double, double, int, LAYER>;

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

	bool AddDrawQue(DrawQueT dQue);		// ｷｭｰの追加
	bool AddActQue(ActQueT aQue);

	// -------------変数
	const vector2Int ScreenSize;		// ｽｸﾘｰﾝｻｲｽﾞX,Y
	const vector2Int ScreenCenter;
	const vector2Int GameScreenSize;
	const vector2Int GameScreenOffset;

	int gameCount;						// ｹﾞｰﾑ全体のｶｳﾝﾄ数

private:
	static SceneMng* sInstance;
	unique_Base _activeScene;

	void Draw(void);					// すべてを描画する

	std::map<LAYER, int > _screenID;	// 描画する画面を指定する

	std::vector<DrawQueT> _drawList;	// ｷｭｰの追加
	std::vector<ActQueT> _actList;

	SceneMng();
	~SceneMng();
	bool SysInit(void);					// ｼｽﾃﾑ系初期化
};

