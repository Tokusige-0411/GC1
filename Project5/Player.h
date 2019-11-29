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
	void Update(sharedObj Obj) override;			// ����
	~Player();
private:
	void init(void);								// ������
	std::shared_ptr<InputState> _input;				// InputState���ư��߲���Ő錾
};

