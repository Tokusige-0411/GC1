#pragma once
#include <vector>
#include "InputState.h"

class KeyState :
	public InputState
{
public:
	KeyState();
	~KeyState();
	void Update(void) override;
private:
	void RefKeyData(void);				// ﾌｧｲﾙからｺﾝﾌｨｸﾞﾃﾞｰﾀを読み込む
	void SetKeyConfig(void);			// 
	void (KeyState::*func)(void);

	char _buf[256];
	std::vector<int> _keyCon;
	std::vector<int> _keyConDef;		// ﾃﾞﾌｫﾙﾄのｷｰｺﾝﾌｨｸﾞ


};

