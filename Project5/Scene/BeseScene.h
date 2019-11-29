#pragma once
#include <memory>
#include <Obj.h>

class BaseScene;

enum class ACT_QUE
{
	NON,
	SHOT,
	CHECK_HIT
};

using unique_Base = std::unique_ptr<BaseScene>;
using ActQueT = std::pair<ACT_QUE, Obj&>;

class BaseScene
{
public:
	BaseScene();
	virtual ~BaseScene();
	virtual unique_Base Update(unique_Base own) = 0;
	// RunActQueの仮想関数（_actListをそのまま渡す）
	// 必ずしも全部のｼｰﾝで必要じゃないから
	virtual void RunActQue(std::vector<ActQueT> actList);		// 初期化するだけ
};

