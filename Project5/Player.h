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
	void Update(void) override;
	~Player();
private:
	void init(void);						// 初期化
	std::shared_ptr<InputState> _input;		// InputStateをﾕﾆｰｸﾎﾟｲﾝﾀで宣言
};

