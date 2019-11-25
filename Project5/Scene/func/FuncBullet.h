#pragma once
#include <map>
#include <BeseScene.h>

// ŠÖ”µÌŞ¼Şª¸Ä‚ÍŠî–{ÊßÌŞØ¯¸‚Å‚¢‚¢
struct FuncBullet
{
	bool operator()(ActQueT actData, std::vector<sharedObj>& _objList);
private:
	static std::map<UNIT_ID, int> _maxCount;
};

