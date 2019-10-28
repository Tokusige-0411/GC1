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

	modeKeyOld = 1;					// ｷｰｺﾝﾌｨｸﾞのﾄﾘｶﾞｰ処理
	_confID = INPUT_ID::LEFT;		// ｷｰｺﾝﾌｨｸﾞ用の変数

	// ﾌｧｲﾙからｷｰ情報の読み込み
	if ((fopen_s(&filePt, "data/key.dat", "r")) == NULL)
	{
		_keyCon.resize(static_cast<size_t>(end(INPUT_ID())));
		fread(_keyCon.data(), sizeof(_keyCon[0]), static_cast<size_t>(end(INPUT_ID())), filePt);
		fclose(filePt);
	}
	else
	{
		_keyCon = _keyConDef;			// 無かった場合ﾃﾞﾌｫﾙﾄのｷｰｺﾝﾌｨｸﾞを格納
	}

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
		TRACE("ｷｰｺﾝﾌｨｸﾞの開始\n")
	}

}

void KeyState::SetKeyConfig(void)
{

	 // F1ｷｰでRefKeyDataに切り替え
	if (_buf[KEY_INPUT_F1] && !modeKeyOld)
	{
		_confID = INPUT_ID::MAX;
		func = &KeyState::RefKeyData;
		// ﾄﾚｰｽで表示
		TRACE("ｷｰｺﾝﾌｨｸﾞの終了\n")
	}

	// ﾎﾞﾀﾝを押したらそのｷｰに設定
	// 決定したら次のｷｰに変更
	// 最後まで行ったら自動的に終了
	// 同じｷｰﾀﾞﾒ

	// 初期化
	for (auto key : INPUT_ID())
	{
		state(key, 0);
	}

	// ﾗﾑﾀﾞを使って設定したｷｰの判定
	auto checkKey = [&](int id) {
		for (INPUT_ID findKey = INPUT_ID::LEFT; findKey < _confID; ++findKey)
		{
			if (_keyCon[static_cast<int>(findKey)] == id)
			{
				return false;
			}
		}
		return true;
	};

	// 押されているｷｰを見つける
	for (int id = 0; id < sizeof(_buf); id++)
	{
		if (!checkKey(id))
		{
			continue;
		}
		if (_buf[id] && (!_buf[KEY_INPUT_F1]))
		{
			// ｷｰの設定
			_keyCon[static_cast<int>(_confID)] = id;
			++_confID;
			TRACE("%d番目のｷｰ設定\n", _confID)

			// 最後のｷｰｺﾝﾌｨｸﾞが終わった
			if (_confID >= end(_confID))
			{
				if ((fopen_s(&filePt, "data/key.dat", "w")) == NULL)
				{
					fwrite(_keyCon.data(), sizeof(_keyCon[0]), static_cast<size_t>(end(INPUT_ID())), filePt);
					fclose(filePt);
				}
				else
				{
					AST();
				}
				func = &KeyState::RefKeyData;
				TRACE("ｷｰｺﾝﾌｨｸﾞの終了\n")
				break;
			}
		}
	}
}
