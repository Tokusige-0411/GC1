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
	// �Y������ID������ꍇ�͎Q�Ƃ��邾��
	// ID�����݂��Ȃ��ꍇ�͍���Ă��܂�
	static KeyPair defData = { 0, 0 };
	try
	{
		return (_state.at(id));
	}
	catch (...)
	{
		AST();
		// �Q�ƂŕԂ��̂�۰�قō�����甲����������Ă��܂�
		// ���Q�ƂŕԂ��Ȃ��̂ł���Ή��ł�����
		// return { 0, 0 };
		// ��؂̺�Ă��Ƃ邩�A�����̒P�������Ƃ邩
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
