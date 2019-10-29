#include "EnemyMove.h"



EnemyMove::EnemyMove(vector2Dbl& pos) : _pos(pos)
{
	
}


EnemyMove::~EnemyMove()
{
}

void EnemyMove::Update(void)
{
	_pos.x++;
}
