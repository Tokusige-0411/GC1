#include <imageMng.h>
#include "Enemy.h"

Enemy::Enemy()
{
	init();
}

Enemy::Enemy(EnemyState & enstate)
{
	_pos = std::get<static_cast<int>(ENEMY_STATE::VECTOR)>(enstate);
	_size = std::get<static_cast<int>(ENEMY_STATE::SIZE)>(enstate);
	_type = std::get<static_cast<int>(ENEMY_STATE::TYPE)>(enstate);
	init();
}


Enemy::~Enemy()
{
}

void Enemy::init(void)
{
	AnimVector data;
	data.reserve(6);

	// �����Ă���摜
	data.emplace_back(IMAGE_ID("���")[10 + static_cast<int>(_type) * 2], 30);
	data.emplace_back(IMAGE_ID("���")[11 + static_cast<int>(_type) * 2], 60);
	SetAnim(STATE::NORMAL, data);

	// ����
	data.emplace_back(IMAGE_ID("�G����")[0], 10);
	data.emplace_back(IMAGE_ID("�G����")[1], 15);
	data.emplace_back(IMAGE_ID("�G����")[2], 20);
	data.emplace_back(IMAGE_ID("�G����")[3], 25);
	data.emplace_back(IMAGE_ID("�G����")[4], 30);
	data.emplace_back(-1, 35);
	SetAnim(STATE::DETH, data);

	state(STATE::NORMAL);
}
