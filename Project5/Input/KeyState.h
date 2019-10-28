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
	void RefKeyData(void);				// Ì§²Ù‚©‚çºİÌ¨¸ŞÃŞ°À‚ğ“Ç‚İ‚Ş
	void SetKeyConfig(void);			// ¶½ÀÑ‚µ‚½ºİÌ¨¸Ş‚ğİ’è
	void (KeyState::*func)(void);

	char _buf[256];						// ·°ºİÌ¨¸Ş‚ÌÃŞ°À‚ğ•Û‘¶‚·‚é
	std::vector<int> _keyCon;			// ·°ºİÌ¨¸Ş‚ÌÃŞ°À
	std::vector<int> _keyConDef;		// ÃŞÌ«ÙÄ‚Ì·°ºİÌ¨¸Ş
	int modeKeyOld;
	INPUT_ID _confID;
	FILE* filePt;
};

