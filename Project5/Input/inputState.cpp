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

const KeyPair InputState::state(INPUT_ID id) const
{
	if (id < static_cast<INPUT_ID>(0) ||
		_state.find(id) == _state.end())
	{
		return;
	}
	return;
}
