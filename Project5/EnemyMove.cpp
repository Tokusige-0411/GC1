#include <cmath>
#include <_DebugConout.h>
#include <_DebugDispOut.h>
#include "EnemyMove.h"
#include <Vector2.h>
#include "Scene\SceneMng.h"
	
int EnemyMove::_pitInCnt = 0;

#define SPAI_RAD 540.0		// ‰ñ“]‚³‚¹‚½‚¢Šp“x
#define pi 3.14159			// ‰~Žü—¦
#define MAX_COUNT 50

EnemyMove::EnemyMove(vector2Dbl& pos, double & rad) : _pos(pos), _rad(rad)
{
	_move = nullptr;
	_aimCnt = -1;
	_sigCount = -5.0;
	_spaiAngl = 90.0;
	_LRSpeed = 2.0;
}

EnemyMove::~EnemyMove()
{
}

void EnemyMove::Update(void)
{
	// —Dæ“x‚Ì–â‘è
	if (_move != nullptr)
	{
		(this->*_move)();
	}
	_dbgDrawPixel(static_cast<int>(_pos.x + lpSceneMng.GameScreenOffset.x), static_cast<int>(_pos.y + lpSceneMng.GameScreenOffset.y), 0xffffff);
}

bool EnemyMove::SetMoveState(MoveState & state, bool newFlag)
{
	// V‚µ‚­Ý’è‚³‚ê‚½‚ç’†g‚ð‹ó‚É‚·‚é
	if (newFlag)
	{
		_aimState.clear();
	}

	// Š—LŒ ‚ð“n‚·
	_aimState = std::move(state);
	
	// V‚µ‚­Ý’è‚³‚ê‚½‚çŠÖ”‚ðÝ’è‚·‚é
	if (newFlag)
	{
		SetMovePrg();
	}

	return true;
}

void EnemyMove::SetMovePrg(void)
{
	_aimCnt++;

	// ¶³ÝÄ‚ª‰ñ‚Á‚Ä‚½‚ç‰½‚à‚¹‚¸I‚í‚é
	if (_aimCnt >= static_cast<int>(_aimState.size()))
	{
		return;
	}

	_startPos = _pos;								// Œ»Ý‚ÌÀ•W‚ð“ü‚ê‚é
	_endPos = _aimState[_aimCnt].second;			// ŠÖ”I—¹ˆÊ’u‚ð“ü‚ê‚é

	// Œ»Ý‚Ì¶³ÝÄ‚É‰ž‚¶‚Äˆ—‚ðŒˆ‚ß‚é
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
		_spaiRad = abs(_endPos.y - _startPos.y);			// _endPos‚ðŠî€‚É”¼Œa‚ðŒˆ’è
		if (_endPos.y > _startPos.y)
		{
			_spaiAngl = -90.0;
		}
		count = 0;
		break;
	case MOVE_TYPE::PITIN:
		_move = &EnemyMove::PitIn;
		_endPos.x += (((lpSceneMng.gameCount + 90) % 180 - 45) - (((lpSceneMng.gameCount + 90) % 90 * 2) * ((lpSceneMng.gameCount + 90) / 90 % 2)));
		_oneMoveVec = (_endPos - _startPos) / 90.0;;			// ˆÚ“®ŽžŠÔ‚ª120ÌÚ°Ñ‚É‚È‚é‚æ‚¤‚É
		break;
	case MOVE_TYPE::LR:
		_move = &EnemyMove::MoveLR;
		count = 0;
		_pitInCnt++;
		break;
	case MOVE_TYPE::EXRATE:
		_move = &EnemyMove::ExRate;
		_lenght = _endPos - _pos;
		break;
	default:
		AST();
		_move = &EnemyMove::Wait;
		break;
	}
}

void EnemyMove::MoveSigmoid(void)
{
	// ¼¸ÞÓ²ÄÞ‹Èü‚ð•`‚­
	vector2Dbl tmpPos = _pos;			// À•W‚ð‹‚ß‚é—p
	vector2Dbl oldPos = _pos;			// Šp“x‚ð‹‚ß‚é—p
	
	tmpPos.x = ((_endPos.x - _startPos.x) / 150.0);
	tmpPos.y = ((1.0 / (1.0 + exp(-_sigCount))) * (_endPos.y - _startPos.y));
	_sigCount += 0.1;

	// ‹‚ß‚½ˆÚ“®—Ê‚ðÀ•W‚É”½‰f
	_pos.x += tmpPos.x;
	_pos.y = _startPos.y + tmpPos.y;

	// •`‰æ•ûŒü‚ðŒˆ’è
	_rad = (atan2(_pos.y - oldPos.y, _pos.x - oldPos.x) + pi / 2);

	// •b”‚Ü‚Ås‚Á‚½‚çMoveSpairal‚É•ÏŠ·
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

	// •`‰æ•ûŒü‚ðŒˆ’è
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

	// ”¼Œa‚ð¬‚³‚­‚µ‚Ä‚¢‚­
	_spaiRad -= 0.2;

	if (count >= SPAI_RAD)
	{
		SetMovePrg();
	}
}

void EnemyMove::PitIn(void)
{
	// _stratPos‚Æ_endPos‚ðŽg‚Á‚ÄˆÚ“®‚³‚¹‚é
	vector2Dbl lenght;

	// ´ÝÄÞ‚ÌˆÊ’u‚É—ˆ‚½‚çLR‚ÉˆÚ‚é‚æ‚¤‚É‚·‚é
	if (abs(_endPos.x - _pos.x) >= abs(_oneMoveVec.x))
	{
		// ˆÚ“®
		_pos += _oneMoveVec;

		// Šp“x‚Ìˆ—
		lenght = _endPos - _pos;
		_rad = (atan2(lenght.y, lenght.x) + pi / 2);
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
	_pos.x = _endPos.x + ((lpSceneMng.gameCount % 180 - 45) - ((lpSceneMng.gameCount % 90 * 2) * (lpSceneMng.gameCount / 90 % 2)));
	// ‘Sˆõ‚ªpitinI—¹‚È‚¨‚©‚ÂŠù’è‚ÌˆÊ’u‚É“ž’B‚µ‚½‚ç
	if ((_pos == _endPos) && _pitInCnt >= MAX_COUNT)
	{
		_pos = _endPos;
		SetMovePrg();
	}
}

void EnemyMove::ExRate(void)
{
	_pos = _endPos + (_lenght * (static_cast<double>(((100 + (count % 60 - ((count % 30 * 2) * (count / 30 % 2))))) / 100.0)));
	count++;
}
