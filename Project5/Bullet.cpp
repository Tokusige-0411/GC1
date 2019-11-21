#include <DxLib.h>
#include <SceneMng.h>
#include <imageMng.h>
#include "Bullet.h"

Bullet::Bullet()
{
}

Bullet::Bullet(vector2Dbl pos)
{
	_pos = pos;
	_size = { 8,3 };
	_rad = 270 * 3.141592 / 180;
	init();
}


Bullet::~Bullet()
{
}

void Bullet::Update(void)
{

}

void Bullet::init(void)
{
	AnimVector data;
	data.reserve(1);
	data.emplace_back(IMAGE_ID("�e")[0], 0);
	SetAnim(STATE::NORMAL, data);
	data.reserve(1);
	data.emplace_back(-1, 0);
	SetAnim(STATE::DETH, data);
}