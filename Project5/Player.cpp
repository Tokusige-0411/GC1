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

	// ·°ºİÌ¨¸Ş‚Ì±¯ÌßÃŞ°Ä‚ğŒÄ‚Ño‚·
	(*_input).Update();

	// ˆÚ“®ˆ—
	// if•¶1ŒÂ
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
	_input = std::make_unique<KeyState>();

	// ÌßÚ²Ô°‚Ìî•ñ‚ğNORMAL‚Éİ’è
	state(STATE::NORMAL);
}
