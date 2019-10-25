#include <DxLib.h>
#include <imageMng.h>
#include "Player.h"
#include <KeyState.h>

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

void Player::Update(void)
{
	if (DestroyPrpc())
	{
		return;
	}

	// ｷｰｺﾝﾌｨｸﾞのｱｯﾌﾟﾃﾞｰﾄを呼び出す
	(*_input).Update();

	// 移動処理
	// if文1個
	auto move = [](std::weak_ptr<InputState> keyData, const INPUT_ID id, int& pNum, const int speed) {
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
}

Player::~Player()
{
}

void Player::init(void)
{
	AnimVector data;
	data.reserve(4);
	// 生きている時
	data.emplace_back(IMAGE_ID("ｷｬﾗ")[0], 30);
	data.emplace_back(IMAGE_ID("ｷｬﾗ")[1], 60);
	SetAnim(STATE::NORMAL, data);

	data.emplace_back(IMAGE_ID("ｷｬﾗ")[0], 10);
	SetAnim(STATE::EX, data);

	// 自機爆発
	data.emplace_back(IMAGE_ID("PL爆発")[0], 20);
	data.emplace_back(IMAGE_ID("PL爆発")[1], 25);
	data.emplace_back(IMAGE_ID("PL爆発")[2], 30);
	data.emplace_back(IMAGE_ID("PL爆発")[3], 35);
	data.emplace_back(-1, 45);
	SetAnim(STATE::DETH, data);

	// _input(渡したいもの)
	// _input.仲介人(渡したいもの)

	// _inputにKeyStateをﾕﾆｰｸﾎﾟｲﾝﾀで作る
	// _input.reset(new KeyState());
	_input = std::make_shared<KeyState>();

	// ﾌﾟﾚｲﾔｰの情報をNORMALに設定
	state(STATE::NORMAL);
}
