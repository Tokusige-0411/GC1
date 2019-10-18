#pragma once
#include <map>
#include "INPUT_ID.h"

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
	void SetOld(void);							// 1ﾌﾚｰﾑ前の情報を書き込む
private:
	KeyMap _state;			// 各ｷｰのｽﾃｰﾀｽ
};
