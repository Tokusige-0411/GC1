#include "FuncBullet.h"
#include <Bullet.h>

bool FuncBullet::operator()(ActQueT actData, std::vector<sharedObj> _objList)
{
	// UNIT_ID��ϐ��ɂ��ēn���Ă�����
	UNIT_ID unitID = (actData.second.unitID() == UNIT_ID::PLAYER ? UNIT_ID::PL_BULLET : UNIT_ID::EM_BULLET);
	_objList.emplace_back(new Bullet(unitID, actData.second.pos()));
	return false;
}
