#include <DxLib.h>
#include <_DebugConout.h>
#include "KeyState.h"

KeyState::KeyState()
{
	// begin(INPUT_ID());
	// end(INPUT_ID())
	// 毎回取り直すのはめんどくさい
	// 型自体はINPUT_ID型なのでｷｬｽﾄする
	_keyConDef.reserve(static_cast<size_t>(end(INPUT_ID())));
	// ｷｰの追加
	_keyConDef.emplace_back(KEY_INPUT_LEFT);		// 左
	_keyConDef.emplace_back(KEY_INPUT_RIGHT);		// 右
	_keyConDef.emplace_back(KEY_INPUT_UP);			// 上
	_keyConDef.emplace_back(KEY_INPUT_DOWN);		// 下
	_keyConDef.emplace_back(KEY_INPUT_Z);			// BTN1
	_keyConDef.emplace_back(KEY_INPUT_X);			// BTN2
	_keyConDef.emplace_back(KEY_INPUT_A);			// BTN3
	_keyConDef.emplace_back(KEY_INPUT_S);			// BTN4

	_keyCon = _keyConDef;			// ﾃﾞｰﾀを保存
	modeKeyOld = 1;
	id = INPUT_ID::LEFT;
	idOld = INPUT_ID::LEFT;

	// ﾒﾝﾊﾞｰ関数のﾎﾟｲﾝﾀはｵﾌｾｯﾄになっている
	// ｵﾌｾｯﾄなので親のｱﾄﾞﾚｽがわからない
	// 名前空間を指定してあげなければならない
	func = &KeyState::RefKeyData;
}

KeyState::~KeyState()
{
}

void KeyState::Update(void)
{
	SetOld();					// ｷｰ情報の更新
	modeKeyOld = _buf[KEY_INPUT_F1];
	GetHitKeyStateAll(_buf);	// すべてのｷｰ情報の取得
	// ﾒﾝﾊﾞｰ関数ﾎﾟｲﾝﾀ
	(this->*func)();
}

void KeyState::RefKeyData(void)
{
	// _bufのINPUT_IDの情報を_stateに書き込む
	for (auto id : INPUT_ID())
	{
		state(id, _buf[_keyCon[static_cast<int>(id)]]);
	}
	// F1ｷｰでSetKeyConfigに切り替え
	if (_buf[KEY_INPUT_F1] && !modeKeyOld)
	{
		func = &KeyState::SetKeyConfig;
		// ﾄﾚｰｽで表示
		TRACE("SetKeyConfig\n")
	}

}

void KeyState::SetKeyConfig(void)
{

	 // F1ｷｰでRefKeyDataに切り替え
	if (_buf[KEY_INPUT_F1] && !modeKeyOld)
	{
		func = &KeyState::RefKeyData;
		// ﾄﾚｰｽで表示
		TRACE("RefKeyData\n")
	}

	// ﾎﾞﾀﾝを押したらそのｷｰに設定
	// 決定したら次のｷｰに変更
	// 最後まで行ったら自動的に終了
	// 同じｷｰﾀﾞﾒ

	// 押されているｷｰを見つける
	int flag = true;
	for (int i = 0; i < 256; i++)
	{
		if (_buf[i])
		{
			// ｷｰの設定
			for (INPUT_ID findKey = INPUT_ID::LEFT; findKey <= id; ++findKey)
			{
				if (_keyCon[static_cast<int>(findKey)] == i)
				{
					flag = false;
				}
			}
			if (flag)
			{
				_keyCon[static_cast<int>(id)] = i;
				++id;
				TRACE("%d\n", id);
			}
			if (id >= INPUT_ID::MAX)
			{
				id = INPUT_ID::LEFT;
				func = &KeyState::RefKeyData;
				TRACE("RefKeyData\n")
			}
			break;
		}
	}
}
