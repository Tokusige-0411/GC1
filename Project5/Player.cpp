#include <DxLib.h>
#include <imageMng.h>
#include "Player.h"

Player::Player()
{
	init();
}

Player::Player(Vector2 pos, Vector2 size)
{
	_pos = pos;
	_size = size;
	init();
}

Player::~Player()
{
}

void Player::init(void)
{
	AnimVector data;
	data.reserve(4);
	// �����Ă��鎞
	data.emplace_back(IMAGE_ID("���")[0], 30);
	data.emplace_back(IMAGE_ID("���")[1], 60);
	SetAnim(STATE::NORMAL, data);

	data.emplace_back(IMAGE_ID("���")[0], 10);
	SetAnim(STATE::EX, data);

	// ���@����
	data.emplace_back(IMAGE_ID("PL����")[0], 20);
	data.emplace_back(IMAGE_ID("PL����")[1], 25);
	data.emplace_back(IMAGE_ID("PL����")[2], 30);
	data.emplace_back(IMAGE_ID("PL����")[3], 35);
	data.emplace_back(-1, 45);
	SetAnim(STATE::DETH, data);

	state(STATE::NORMAL);
}
