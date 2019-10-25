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
	void init(void);						// 初期化
	std::shared_ptr<InputState> _input;		// InputStateをﾕﾆｰｸﾎﾟｲﾝﾀで宣言
};

