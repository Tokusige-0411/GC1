#include <cmath>
#include <_DebugConout.h>
#include "EnemyMove.h"
#include <Vector2.h>

#define MOVE_CNT 60.0

EnemyMove::EnemyMove(vector2Dbl& pos, double & rad) : _pos(pos), _rad(rad)
{
	_move = nullptr;
	_aimCnt = -1;
	_sigCount = -5.0;
	_spaiAngl = 90.0;
}

EnemyMove::~EnemyMove()
{
}

void EnemyMove::Update(void)
{
	// �D��x�̖��
	if (_move != nullptr)
	{
		(this->*_move)();
	}
}

bool EnemyMove::SetMoveState(MoveState & state, bool newFlag)
{
	// �V�����ݒ肳�ꂽ�璆�g����ɂ���
	if (newFlag)
	{
		_aimState.clear();
	}

	// ���L����n��
	_aimState = std::move(state);
	
	// �V�����ݒ肳�ꂽ��֐���ݒ肷��
	if (newFlag)
	{
		SetMovePrg();
	}

	return true;
}

void EnemyMove::SetMovePrg(void)
{
	_aimCnt++;

	// ���Ă�����Ă��牽�������I���
	if (_aimCnt >= static_cast<int>(_aimState.size()))
	{
		return;
	}

	_startPos = _pos;								// ���݂̍��W������
	_endPos = _aimState[_aimCnt].second;			// �֐��I���ʒu������

	// ���̶݂��Ăɉ����ď��������߂�
	switch (_aimState[_aimCnt].first)
	{
	case MOVE_TYPE::WAIT:
		_move = &EnemyMove::Wait;
		count = 0;
		break;
	case MOVE_TYPE::SIGMOID:
		_move = &EnemyMove::MoveSigmoid;
		count = 0;
		break;
	case MOVE_TYPE::SPIRAL:
		_move = &EnemyMove::MoveSpairal;
		_spaiRad = abs(_endPos.y - _startPos.y);			// _endPos����ɔ��a������
		break;
	case MOVE_TYPE::PITIN:
		_move = &EnemyMove::PitIn;
		_oneMoveVec = ((_endPos - _startPos) / 120.0);			// �ړ����Ԃ�120�ڰтɂȂ�悤��
		break;
	case MOVE_TYPE::LR:
		_move = &EnemyMove::MoveLR;
		break;
	default:
		AST();
		_move = &EnemyMove::Wait;
		break;
	}
}

void EnemyMove::MoveSigmoid(void)
{
	// ���Ӳ�ދȐ���`��
	vector2Dbl tmpPos = _pos;			// ���W�����߂�p
	vector2Dbl oldPos = _pos;			// �p�x�����߂�p
	
	tmpPos.x = ((_endPos.x - _startPos.x) / 150.0);
	tmpPos.y = ((1.0 / (1.0 + exp(-_sigCount))) * (_endPos.y - _startPos.y));
	_sigCount += 0.1;

	// ���߂��ړ��ʂ����W�ɔ��f
	_pos.x += tmpPos.x;
	_pos.y = _startPos.y + tmpPos.y;

	// �`�����������
	_rad = (atan2(_pos.y - oldPos.y, _pos.x - oldPos.x) + 3.14159 / 2);

	// �b���܂ōs������MoveSpairal�ɕϊ�
	if (count >= 150)
	{
		SetMovePrg();
	}
	count++;
}

void EnemyMove::MoveSpairal(void)
{
	vector2Dbl tmpPos;

	tmpPos.x = _spaiRad * cos(_spaiAngl * (3.14159 / 180.0));
	tmpPos.y = _spaiRad * sin(_spaiAngl * (3.14159 / 180.0));

	_pos.x = _endPos.x + tmpPos.x;
	_pos.y = _endPos.y + tmpPos.y;

	if (_startPos.x < 400.0)
	{
		_spaiAngl++;
	}
	else
	{
		_spaiAngl--;
	}
	_spaiRad -= 0.5;
}

void EnemyMove::PitIn(void)
{
	// _stratPos��_endPos���g���Ĉړ�������
	vector2Dbl _lenght;

	// ���ނ̈ʒu�ɗ�����LR�Ɉڂ�悤�ɂ���
	if (abs(_endPos.x - _pos.x) >= abs(_oneMoveVec.x))
	{
		// �ړ�
		_pos += _oneMoveVec;

		// �p�x�̏���
		_lenght = _endPos - _pos;
		_rad = (atan2(_lenght.y, _lenght.x) + 3.14159 / 2);
	}
	else
	{
		_pos = _endPos;
		_rad = 0.0;
		SetMovePrg();
	}
}

void EnemyMove::Wait(void)
{
	if (count > _aimState[_aimCnt].second.x)
	{
		SetMovePrg();
	}
	count++;
}

void EnemyMove::MoveLR(void)
{

}
