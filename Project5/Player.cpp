#include <DxLib.h>
#include <imageMng.h>
#include <BeseScene.h>
#include "Player.h"
#include <KeyState.h>
#include <SceneMng.h>

Player::Player()
{
	init();
}

Player::Player(vector2Dbl pos, vector2Dbl size)
{
	_pos = pos;
	_size = size;
	_unitID = UNIT_ID::PLAYER;
	init();
}

void Player::Update(void)
{
	if (DestroyPrpc())
	{
		return;
	}

	// ����̨�ނ̱����ްĂ��Ăяo��
	(*_input).Update();

	// �ړ�����
	// if��1��
	auto move = [](std::weak_ptr<InputState> keyData, const INPUT_ID id, double& pNum, const int speed) {
		if (!keyData.expired())
		{
			if ((*keyData.lock()).state(id).first)
			{
				pNum += speed;
			}
		}
	};

	move(_input, INPUT_ID::LEFT,	_pos.x,		-2);
	move(_input, INPUT_ID::RIGHT,	_pos.x,		 2);
	move(_input, INPUT_ID::UP,		_pos.y,		-2);
	move(_input, INPUT_ID::DOWN,	_pos.y,		 2);

	if ((*_input).state(INPUT_ID::BTN_1).first && !((*_input).state(INPUT_ID::BTN_1).second))
	{
		lpSceneMng.AddActQue({ ACT_QUE::SHOT, *this });
	}
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

	// _input(�n����������)
	// _input.����l(�n����������)

	// _input��KeyState���ư��߲���ō��
	// _input.reset(new KeyState());
	_input = std::make_shared<KeyState>();

	// ��ڲ԰�̏���NORMAL�ɐݒ�
	state(STATE::NORMAL);
}
