#pragma once
#include <BeseScene.h>
// 関数ｵﾌﾞｼﾞｪｸﾄは基本ﾊﾟﾌﾞﾘｯｸでいい
struct FuncBullet
{
	bool operator()(ActQueT actData, std::vector<sharedObj> _objList);
};

