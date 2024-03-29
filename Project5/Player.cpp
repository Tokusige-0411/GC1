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

void Player::Update(sharedObj Obj)
{
	if (DestroyPrpc())
	{
		return;
	}

	// ｷｰｺﾝﾌｨｸﾞのｱｯﾌﾟﾃﾞｰﾄを呼び出す
	(*_input).Update();

	// 移動処理
	// if文1個
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
	//move(_input, INPUT_ID::UP,		_pos.y,		-2);
	//move(_input, INPUT_ID::DOWN,	_pos.y,		 2);

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

	_glowID[0] = MakeScreen(static_cast<int>(_size.x * 2), static_cast<int>(_size.y * 2), false);
	_glowID[1] = MakeScreen(static_cast<int>(_size.x * 2), static_cast<int>(_size.y * 2), false);
}

void Player::Draw(void)
{
	Obj::Draw();

	SetDrawScreen(_glowID[0]);
	ClsDrawScreen();
	SetDrawBright(0, 200 + rand() % 55, 0);
	DrawRotaGraph(static_cast<int>(_size.x), static_cast<int>(_size.y), 1.25, 0, _animMap[_state][_animFrame].first, true);
	SetDrawBright(255, 255, 255);
	GraphFilter(_glowID[0], DX_GRAPH_FILTER_GAUSS, 5, 500);
	lpSceneMng.AddDrawQue({ _glowID[0], lpSceneMng.GameScreenOffset.x + _pos.x, lpSceneMng.GameScreenOffset.y + _pos.y,
		_rad, _zOrder - 1, LAYER::CHAR, DX_BLENDMODE_ADD, 255 });
}
