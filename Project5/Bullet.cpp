#include <DxLib.h>
#include <SceneMng.h>
#include <imageMng.h>
#include "Bullet.h"

Bullet::Bullet()
{
}

Bullet::Bullet(UNIT_ID unitID, vector2Dbl pos)
{
	_unitID = unitID;
	_pos = pos;
	_zOrder = 10;
	_size = { 4,6 };
	_rad = 270 * (3.141592 / 180);
	init();
}


Bullet::~Bullet()
{
}

void Bullet::Update(sharedObj Obj)
{
	if (Bullet::DestroyPrpc())
	{
		return;
	}

	lpSceneMng.AddActQue({ ACT_QUE::CHECK_HIT, *this });

	_pos.x += cos(_rad) * 3.0;
	_pos.y += sin(_rad) * 3.0;
}

bool Bullet::DestroyPrpc(void)
{
	if (-_size.y >= _pos.y)
	{
		_alive = false;
		state(STATE::DETH);
	}
	if (Obj::DestroyPrpc())
	{
		return true;
	}
	return false;
}

void Bullet::init(void)
{
	AnimVector data;
	data.reserve(1);

	data.emplace_back(IMAGE_ID("íe")[0], 30);
	SetAnim(STATE::NORMAL, data);
	data.reserve(1);
	// DxLibÇÃédólÇ…çáÇÌÇπÇƒ
	data.emplace_back(-1, 40);
	SetAnim(STATE::DETH, data);

	state(STATE::NORMAL);
}
