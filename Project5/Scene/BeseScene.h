#pragma once
#include <memory>
#include <Obj.h>

class BaseScene;

enum class ACT_QUE
{
	NON,
	SHOT,
	CHECK_HIT,
	SHAKE,
	MAX
};

using unique_Base = std::unique_ptr<BaseScene>;
using ActQueT = std::pair<ACT_QUE, Obj&>;

class BaseScene
{
public:
	BaseScene();
	// 必ずしも全部のｼｰﾝで必要じゃないから
	virtual void RunActQue(std::vector<ActQueT> actList);		// 初期化するだけ
	// RunActQueの仮想関数（_actListをそのまま渡す）
	virtual ~BaseScene();
	virtual unique_Base Update(unique_Base own) = 0;
	vector2Int _screenPos;										// 描画でｼｪｲｸする
};

