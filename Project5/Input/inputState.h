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

// <今のｷｰの状態, 1ﾌﾚｰﾑ前のｷｰの状態>
using KeyPair = std::pair<int, int>;
// <ｷｰのID, <今のｷｰの状態, 1ﾌﾚｰﾑ前のｷｰの状態>>
using KeyMap = std::map<INPUT_ID, KeyPair>;

class InputState
{
public:
	InputState();
	virtual ~InputState();
	const KeyMap& state(void)const;				// ｷｰの情報をそのまま返す
	const KeyPair& state(INPUT_ID id)const;		// ｷｰの情報の中身を返す
	bool state(INPUT_ID id, int data);			// ｷｰの情報を書き込む
private:
	KeyMap _state;
};

