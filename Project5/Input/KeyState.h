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
	void SetKeyConfig(void);			// ｶｽﾀﾑしたｺﾝﾌｨｸﾞを設定
	void (KeyState::*func)(void);

	char _buf[256];						// ｷｰｺﾝﾌｨｸﾞのﾃﾞｰﾀを保存する
	std::vector<int> _keyCon;			// ｷｰｺﾝﾌｨｸﾞのﾃﾞｰﾀ
	std::vector<int> _keyConDef;		// ﾃﾞﾌｫﾙﾄのｷｰｺﾝﾌｨｸﾞ
	int modeKeyOld;
	INPUT_ID _confID;
};

