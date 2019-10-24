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
	//auto move = [](const int keyID, int& pNum, const int speed) {
	//	if (CheckHitKey(keyID))
	//	{
	//		pNum += speed;
	//	}
	//};
	//move(KEY_INPUT_LEFT,	_pos.x,		-2);
	//move(KEY_INPUT_RIGHT,	_pos.x,		 2);
	//move(KEY_INPUT_UP,	_pos.y,		-2);
	//move(KEY_INPUT_DOWN,	_pos.y,		 2);
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
	_input = std::make_unique<KeyState>();

	// ﾌﾟﾚｲﾔｰの情報をNORMALに設定
	state(STATE::NORMAL);
}
