#pragma once
#include <memory>
#include <tuple>
#include <vector>
#include <Vector2.h>
#include "BeseScene.h"

// 描画するのに必要な情報<ImageID, 座標X, 座標Y>
using DrawQuwT = std::tuple<int, int, int>;

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

	bool AddDrawQue(DrawQuwT dQue);		// ｷｭｰの追加

	// -------------変数
	const vector2Int screenSize;		// ｽｸﾘｰﾝｻｲｽﾞX,Y
private:
	static SceneMng* sInstance;
	unique_Base _activeScene;

	void Draw(void);					// すべてを描画する

	std::vector<DrawQuwT> _drawList;	// ｷｭｰの追加

	SceneMng();
	~SceneMng();
	bool SysInit(void);					// ｼｽﾃﾑ系初期化
};

