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
	void SetKeyConfig(void);			// 
	void (KeyState::*func)(void);

	char _buf[256];
	std::vector<int> _keyCon;
	std::vector<int> _keyConDef;		// ÃŞÌ«ÙÄ‚Ì·°ºİÌ¨¸Ş


};

