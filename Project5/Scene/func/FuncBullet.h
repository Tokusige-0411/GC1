#pragma once
#include <map>
#include <BeseScene.h>

// 関数ｵﾌﾞｼﾞｪｸﾄは基本ﾊﾟﾌﾞﾘｯｸでいい
struct FuncBullet
{
	bool operator()(ActQueT actData, void* scene);		// 弾を打つ
private:
	static std::map<UNIT_ID, int> _maxCount;	// 弾の表示最大数
};

