#pragma once
#include <vector>
#include <Vector2.h>

enum class MOVE_TYPE
{
	WAIT,
	SIGMOID,
	SPIRAL,
	PITIN,
	LR
};

using MoveState = std::vector<std::pair<MOVE_TYPE, vector2Dbl>>;

class EnemyMove
{
public:
	EnemyMove(vector2Dbl& pos);
	~EnemyMove();
	void Update(void);
	bool SetMoveState(MoveState& state, bool newFlag);
private:
	void SetMovePrg(void);
	void (EnemyMove::*_move)(void);
	void MoveSigmoid(void);
	void MoveSpairal(void);
	void PitIn(void);
	void Wait(void);
	void MoveLR(void);

	MoveState _aimState;
	int _aimCnt;

	vector2Dbl _startPos;		// �e�ړ��֐��̽��Ĉʒu
	vector2Dbl _endPos;			// �e�ړ��֐��̴��ވʒu
	vector2Dbl & _pos;
};

