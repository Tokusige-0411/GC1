#include <cmath>
#include <_DebugConout.h>
#include <_DebugDispOut.h>
#include "EnemyMove.h"
#include <Vector2.h>
#include "Scene\SceneMng.h"

#define SPAI_RAD 540.0		// ��]���������p�x
#define pi 3.14159			// �~����
#define MAX_COUNT 50
	
int EnemyMove::_pitInCnt = 0;
int EnemyMove::_maxCount = MAX_COUNT;

EnemyMove::EnemyMove(vector2Dbl& pos, double & rad, bool & exFlag) : _pos(pos), _rad(rad), _exFlag(exFlag)
{
	_move = nullptr;
	_aimCnt = -1;
	_sigCount = -5.0;
	_spaiAngl = 90.0;
	_rateCnt = 0;
}

EnemyMove::~EnemyMove()
{
}

void EnemyMove::Update(sharedObj Obj)
{
	_plPos = (*Obj).pos();			// ��ڲ԰�̍��W���m��
	// �D��x�̖��
	if (_move != nullptr)
	{
		(this->*_move)();
	}

	_dbgDrawPixel(static_cast<int>(_pos.x + lpSceneMng.GameScreenOffset.x), static_cast<int>(_pos.y + lpSceneMng.GameScreenOffset.y), 0xffffff);
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
		for (_aimCnt = 0; _aimCnt < static_cast<int>(_aimState.size()); _aimCnt++)
		{
			if (_aimState[_aimCnt].first == MOVE_TYPE::EXRATE)
			{
				break;
			}
		}
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
		if (_endPos.y > _startPos.y)
		{
			_spaiAngl = -90.0;
		}
		count = 0;
		break;
	case MOVE_TYPE::PITIN:
		_move = &EnemyMove::PitIn;
		if (_pos.y > lpSceneMng.GameScreenSize.y)
		{
			_pos.y = -100.0;
			_startPos = _pos;								// ���݂̍��W������
			_exLad = _center - _endPos;
			_endPos = _center - _exLad *
						(static_cast<double>((100 + ((lpSceneMng.gameCount - _rateCnt + 90) % 60) -
						(((lpSceneMng.gameCount - _rateCnt + 90) % 30 * 2) *
						(((lpSceneMng.gameCount - _rateCnt + 90) / 30) % 2)))) / 100.0);

		}
		else
		{
			_endPos.x += (((lpSceneMng.gameCount + 90) % 180 - 45) - (((lpSceneMng.gameCount + 90) % 90 * 2) * ((lpSceneMng.gameCount + 90) / 90 % 2)));
		}
		_lenght = _endPos - _startPos;						// �ړ�����������
		count = 0;
		break;
	case MOVE_TYPE::LR:
		_move = &EnemyMove::MoveLR;
		count = 0;
		_pitInCnt++;
		break;
	case MOVE_TYPE::EXRATE:
		_move = &EnemyMove::ExRate;
		if (_rateCnt == 0)
		{
			_center = _endPos;
			_exLad = _center - _startPos;
			_rateCnt = lpSceneMng.gameCount;
		}
		break;
	case MOVE_TYPE::ATTACK:
		_move = &EnemyMove::Attack;
		count = 0;
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
	_rad = (atan2(_pos.y - oldPos.y, _pos.x - oldPos.x) + pi / 2);

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
	vector2Dbl oldPos = _pos;

	tmpPos.x = _spaiRad * cos(_spaiAngl * (pi / 180.0));
	tmpPos.y = _spaiRad * sin(_spaiAngl * (pi / 180.0));

	_pos.x = _endPos.x + tmpPos.x;
	_pos.y = _endPos.y + tmpPos.y;

	// �`�����������
	_rad = (atan2(_pos.y - oldPos.y, _pos.x - oldPos.x) + pi / 2);;

	if (_startPos.x < lpSceneMng.GameScreenSize.x/2)
	{
		if (_endPos.y < _startPos.y)
		{
			_spaiAngl += 3;
		}
		else
		{
			_spaiAngl -= 3;
		}
	}
	else
	{
		if (_endPos.y < _startPos.y)
		{
			_spaiAngl -= 3;
		}
		else
		{
			_spaiAngl += 3;
		}
	}
	count += 3;

	// ���a�����������Ă���
	_spaiRad -= 0.2;

	if (count >= SPAI_RAD)
	{
		SetMovePrg();
	}
}

void EnemyMove::PitIn(void)
{
	// _stratPos��_endPos���g���Ĉړ�������
	vector2Dbl lenght;

	// ���ނ̈ʒu�ɗ�����LR�Ɉڂ�悤�ɂ���
	if (count < 90)
	{
		// �ړ�
		_pos += _lenght / 90.0;

		// �p�x�̏���
		lenght = _endPos - _pos;
		_rad = (atan2(lenght.y, lenght.x) + pi / 2);
	}
	else
	{
		_pos = _endPos;
		_rad = 0.0;
		SetMovePrg();
	}
	count++;
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
	_pos.x = _endPos.x + ((lpSceneMng.gameCount % 180 - 45) - ((lpSceneMng.gameCount % 90 * 2) * (lpSceneMng.gameCount / 90 % 2)));
	// �S����pitin�I���Ȃ�������̈ʒu�ɓ��B������
	if ((_pos == _endPos) && _pitInCnt >= _maxCount)
	{
		_pos = _endPos;
		SetMovePrg();
	}
}

void EnemyMove::ExRate(void)
{
	// _rotaCnt���g����
	_pos = _endPos - 
		(_exLad * 
		(static_cast<double>(((100 + ((lpSceneMng.gameCount - _rateCnt) % 60) - 
			(((lpSceneMng.gameCount - _rateCnt) % 30 * 2) * 
			(((lpSceneMng.gameCount - _rateCnt) / 30) % 2))))) / 100.0));
	if (_exFlag)
	{
		SetMovePrg();
		_exFlag = false;
	}
}

void EnemyMove::Attack(void)
{
	if (count < _endPos.x)
	{
		_rad++;
	}
	else
	{
		_move = &EnemyMove::PitIn;
		_endPos.x = _plPos.x;
		_endPos.y = _plPos.y + 100.0;
		_lenght = _endPos - _pos;
		count = 0;
	}
	count++;
}

void EnemyMove::SetMaxCount(void)
{
	if (static_cast<MOVE_TYPE>(_aimCnt) == MOVE_TYPE::PITIN)
	{
		_maxCount--;
	}
	else
	{
		_maxCount--;
		_pitInCnt--;
	}
}

std::pair<MOVE_TYPE, vector2Dbl> EnemyMove::GetMoveState(void)
{
	return _aimState[_aimCnt];
}
