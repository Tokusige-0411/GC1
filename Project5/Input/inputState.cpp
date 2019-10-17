#include <_DebugConout.h>
#include "inputState.h"

InputState::InputState()
{
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
		AST();
		// 参照で返すのでﾛｰｶﾙで作ったら抜けたら消えてしまう
		// ↓参照で返さないのであれば下でもいい
		// return { 0, 0 };
		// ﾒﾓﾘのｺｽﾄをとるか、処理の単純さをとるか
		return defData;
	}
}

bool InputState::state(INPUT_ID id, int data)
{
	if (_state.find(id) != _state.end())
	{
		_state[id].first = data;
		return true;
	}
	return false;
}
