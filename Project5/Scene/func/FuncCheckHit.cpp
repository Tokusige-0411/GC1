#include <cmath>
#include "FuncCheckHit.h"
#include <EnemyMove.h>

bool FuncCheckHit::operator()(ActQueT actData, std::vector<sharedObj>& _objList)
{
	UNIT_ID unitID = (actData.second.unitID() == UNIT_ID::PL_BULLET ? UNIT_ID::ENEMY : UNIT_ID::PLAYER);
	for (auto data : _objList)
	{
		if (unitID == (*data).unitID() && (*data).isAlive())
		{
			vector2Dbl lenght = { (*data).pos().x - actData.second.pos().x , (*data).pos().y - actData.second.pos().y };
			if (sqrt(lenght.x * lenght.x + lenght.y * lenght.y) < (*data).size().x / 2 &&
				sqrt(lenght.x * lenght.x + lenght.y * lenght.y) < (*data).size().y / 2)
			{
				(*data).SetAlive(false);
				actData.second.SetAlive(false);
			}
		}
	}
	return true;
}
