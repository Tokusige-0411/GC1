#pragma once
#include <map>
#include <BeseScene.h>

// ŠÖ”µÌŞ¼Şª¸Ä‚ÍŠî–{ÊßÌŞØ¯¸‚Å‚¢‚¢
struct FuncBullet
{
	bool operator()(ActQueT actData, void* scene);		// ’e‚ğ‘Å‚Â
private:
	static std::map<UNIT_ID, int> _maxCount;	// ’e‚Ì•\¦Å‘å”
};

