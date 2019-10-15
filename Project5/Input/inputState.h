#pragma once
#include <map>

enum class INPUT_ID
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
	BTN_1,
	BTN_2,
	BTN_3,
	BTN_4,
	MAX
};

using KeyPair = std::pair<int, int>;
using KeyMap = std::map<INPUT_ID, KeyPair>;

class InputState
{
public:
	InputState();
	virtual ~InputState();
	const KeyMap& state(void)const;
	const KeyPair state(INPUT_ID id)const;
private:
	KeyMap _state;
};

