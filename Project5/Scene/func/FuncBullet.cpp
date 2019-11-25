#include <algorithm>
#include "FuncBullet.h"
#include <Bullet.h>

// mapÇÃèâä˙âª
std::map<UNIT_ID, int> FuncBullet::_maxCount = { {UNIT_ID::PL_BULLET, 2 }, {UNIT_ID::EM_BULLET, 2} };

bool FuncBullet::operator()(ActQueT actData, std::vector<sharedObj>& _objList)
{
	// UNIT_IDÇïœêîÇ…ÇµÇƒìnÇµÇƒÇ†Ç∞ÇÈ
	UNIT_ID unitID = (actData.second.unitID() == UNIT_ID::PLAYER ? UNIT_ID::PL_BULLET : UNIT_ID::EM_BULLET);
	if (_maxCount[unitID] > std::count_if(_objList.begin(), _objList.end(), [&](sharedObj obj) {return (unitID == (*obj).unitID()); }))
	{
		_objList.emplace_back(new Bullet(unitID, actData.second.pos()));
		return true;
	}
	return false;
}
