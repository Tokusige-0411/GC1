#include <_DebugConout.h>
#include "inputState.h"

InputState::InputState()
{
	// ｷｰの初期化
	for (auto id : INPUT_ID())
	{
		_state.try_emplace(id, KeyPair{ 0, 1 });
	}
}

InputState::~InputState()
{
}

const KeyMap & InputState::state(void) const
{
	return _state;
}

const KeyPair & InputState::state(INPUT_ID id) const
{
	// 該当するIDがある場合は参照するだけ
	// IDが存在しない場合は作ってしまう
	static KeyPair defData = { 0, 0 };
	try
	{
		return (_state.at(id));
	}
	catch (...)
	{
		// 参照で返すのでﾛｰｶﾙで作ったら抜けたら消えてしまう
		// ↓参照で返さないのであれば下でもいい
		// return { 0, 0 };
		// ﾒﾓﾘのｺｽﾄをとるか、処理の単純さをとるか
		AST();
		return defData;
	}
}

bool InputState::state(INPUT_ID id, int data)
{
	// 値があることを前提で考えない
	if (_state.find(id) != _state.end())
	{
		_state[id].first = data;
		return true;
	}
	return false;
}

void InputState::SetOld(void)
{
	// 範囲for文の中なので範囲外のﾁｪｯｸはしなくてもいい
	for (auto key : INPUT_ID())
	{
		try
		{
			// ｵｰﾙﾄﾞ(ｾｶﾝﾄﾞ)に今のｷｰ状態を入れる
			_state[key].second = _state[key].first;
		}
		catch (...)
		{
			// ｴﾗｰが出た場合
			AST();
			_state.emplace(key, KeyPair{ 0, 1 });
		}
	}
}
