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
	_size = { 4,6 };
	_rad = 270 * (3.141592 / 180);
	init();
}


Bullet::~Bullet()
{
}

void Bullet::Update(void)
{
	if (Bullet::DestroyPrpc())
	{
		return;
	}
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
	return true;
}

void Bullet::init(void)
{
	AnimVector data;
	data.reserve(1);

	data.emplace_back(IMAGE_ID("’e")[0], 30);
	SetAnim(STATE::NORMAL, data);
	data.reserve(1);
	// DxLib‚Ìd—l‚É‡‚í‚¹‚Ä
	data.emplace_back(-1, 40);
	SetAnim(STATE::DETH, data);
}
