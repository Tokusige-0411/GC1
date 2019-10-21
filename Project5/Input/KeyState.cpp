#include <DxLib.h>
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

	_keyCon = _keyConDef;

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
	GetHitKeyStateAll(_buf);	// すべてのｷｰ情報の取得
	// ﾒﾝﾊﾞｰ関数ﾎﾟｲﾝﾀ
	(this->*func)();
}

void KeyState::RefKeyData(void)
{
}

void KeyState::SetKeyConfig(void)
{
}
