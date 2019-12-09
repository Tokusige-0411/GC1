#include <algorithm>
#include "FuncBullet.h"
#include <Bullet.h>
#include <GameScene.h>

// map‚Ì‰Šú‰»
std::map<UNIT_ID, int> FuncBullet::_maxCount = { {UNIT_ID::PL_BULLET, 2 }, {UNIT_ID::EM_BULLET, 2} };

bool FuncBullet::operator()(ActQueT actData, void* scene)
{
	// UNIT_ID‚ğ•Ï”‚É‚µ‚Ä“n‚µ‚Ä‚ ‚°‚é
	UNIT_ID unitID = (actData.second.unitID() == UNIT_ID::PLAYER ? UNIT_ID::PL_BULLET : UNIT_ID::EM_BULLET);
	if (_maxCount[unitID] > std::count_if(((GameScene*)scene)->_objList.begin(), ((GameScene*)scene)->_objList.begin(), [&](sharedObj obj) {return (unitID == (*obj).unitID()); }))
	{
		((GameScene*)scene)->_objList.emplace_back(new Bullet(unitID, actData.second.pos()));
		return true;
	}
	return false;
}
