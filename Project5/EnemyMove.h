#pragma once
#include <Vector2.h>

class EnemyMove
{
public:
	EnemyMove(vector2Dbl& pos);
	~EnemyMove();
	void Update(void);
private:
	vector2Dbl & _pos;
};

