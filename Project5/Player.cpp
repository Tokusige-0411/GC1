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

	// ·°ºİÌ¨¸Ş‚Ì±¯ÌßÃŞ°Ä‚ğŒÄ‚Ño‚·
	(*_input).Update();

	// ˆÚ“®ˆ—
	// if•¶1ŒÂ
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
	// ¶‚«‚Ä‚¢‚é
	data.emplace_back(IMAGE_ID("·¬×")[0], 30);
	data.emplace_back(IMAGE_ID("·¬×")[1], 60);
	SetAnim(STATE::NORMAL, data);

	data.emplace_back(IMAGE_ID("·¬×")[0], 10);
	SetAnim(STATE::EX, data);

	// ©‹@”š”­
	data.emplace_back(IMAGE_ID("PL”š”­")[0], 20);
	data.emplace_back(IMAGE_ID("PL”š”­")[1], 25);
	data.emplace_back(IMAGE_ID("PL”š”­")[2], 30);
	data.emplace_back(IMAGE_ID("PL”š”­")[3], 35);
	data.emplace_back(-1, 45);
	SetAnim(STATE::DETH, data);

	// _input(“n‚µ‚½‚¢‚à‚Ì)
	// _input.’‡‰îl(“n‚µ‚½‚¢‚à‚Ì)

	// _input‚ÉKeyState‚ğÕÆ°¸Îß²İÀ‚Åì‚é
	// _input.reset(new KeyState());
	_input = std::make_shared<KeyState>();

	// ÌßÚ²Ô°‚Ìî•ñ‚ğNORMAL‚Éİ’è
	state(STATE::NORMAL);
}
