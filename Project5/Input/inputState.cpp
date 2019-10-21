#include <_DebugConout.h>
#include "inputState.h"

InputState::InputState()
{
	// ���̏�����
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
	// �Y������ID������ꍇ�͎Q�Ƃ��邾��
	// ID�����݂��Ȃ��ꍇ�͍���Ă��܂�
	static KeyPair defData = { 0, 0 };
	try
	{
		return (_state.at(id));
	}
	catch (...)
	{
		// �Q�ƂŕԂ��̂�۰�قō�����甲����������Ă��܂�
		// ���Q�ƂŕԂ��Ȃ��̂ł���Ή��ł�����
		// return { 0, 0 };
		// ��؂̺�Ă��Ƃ邩�A�����̒P�������Ƃ邩
		AST();
		return defData;
	}
}

bool InputState::state(INPUT_ID id, int data)
{
	// �l�����邱�Ƃ�O��ōl���Ȃ�
	if (_state.find(id) != _state.end())
	{
		_state[id].first = data;
		return true;
	}
	return false;
}

void InputState::SetOld(void)
{
	// �͈�for���̒��Ȃ̂Ŕ͈͊O�������͂��Ȃ��Ă�����
	for (auto key : INPUT_ID())
	{
		try
		{
			// �����(�����)�ɍ��̷���Ԃ�����
			_state[key].second = _state[key].first;
		}
		catch (...)
		{
			// �װ���o���ꍇ
			AST();
			_state.emplace(key, KeyPair{ 0, 1 });
		}
	}
}
