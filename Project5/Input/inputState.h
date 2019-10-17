#pragma once
#include <map>

enum class INPUT_ID
{
	LEFT,
	RIGHT,
	UP,
	DOWN,
	BTN_1,
	BTN_2,
	BTN_3,
	BTN_4,
	MAX
};

// <¡‚Ì·°‚Ìó‘Ô, 1ÌÚ°Ñ‘O‚Ì·°‚Ìó‘Ô>
using KeyPair = std::pair<int, int>;
// <·°‚ÌID, <¡‚Ì·°‚Ìó‘Ô, 1ÌÚ°Ñ‘O‚Ì·°‚Ìó‘Ô>>
using KeyMap = std::map<INPUT_ID, KeyPair>;

class InputState
{
public:
	InputState();
	virtual ~InputState();
	const KeyMap& state(void)const;				// ·°‚Ìî•ñ‚ğ‚»‚Ì‚Ü‚Ü•Ô‚·
	const KeyPair& state(INPUT_ID id)const;		// ·°‚Ìî•ñ‚Ì’†g‚ğ•Ô‚·
	bool state(INPUT_ID id, int data);			// ·°‚Ìî•ñ‚ğ‘‚«‚Ş
private:
	KeyMap _state;
};

