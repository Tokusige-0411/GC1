#pragma once
#include <memory>
#include "Obj.h"
#include <inputState.h>

class Player :
	public Obj
{
public:
	Player();
	Player(vector2Dbl pos, vector2Dbl size);
	void Update(sharedObj Obj) override;			// ˆ—
	~Player();
private:
	void init(void);								// ‰Šú‰»
	std::shared_ptr<InputState> _input;				// InputState‚ğÕÆ°¸Îß²İÀ‚ÅéŒ¾
};

