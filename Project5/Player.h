#pragma once
#include <memory>
#include "Obj.h"
#include <inputState.h>

class Player :
	public Obj
{
public:
	Player();
	Player(Vector2 pos, Vector2 size);
	void Update(void) override;
	~Player();
private:
	void init(void);						// ‰Šú‰»
	std::shared_ptr<InputState> _input;		// InputState‚ğÕÆ°¸Îß²İÀ‚ÅéŒ¾
};

