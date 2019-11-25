#include <DxLib.h>
#include <imageMng.h>
#include <Scene\SceneMng.h>
#include "Obj.h"

Obj::Obj()
{
	_alive = true;
	_dead = false;
	_animFrame = 0;
	_animCount = 0;
	_rad = 0;
	_zOrder = 100;
	_unitID = UNIT_ID::NON;
}

Obj::~Obj()
{
}

bool Obj::state(const STATE key)
{
	// �������邩�ǂ���
	if (_animMap.find(key) == _animMap.end())
	{
		return false;
	}
	// �����ς���Ă���α�Ұ��݂�����������
	if (_state != key)
	{
		_animFrame = 0;
		_animCount = 0;
	}

	_state = key;
	return true;
}

const STATE Obj::state(void) const
{
	return _state;
}

bool Obj::SetAnim(const STATE key, AnimVector& data)
{
	// c++17�ȍ~
	return (_animMap.try_emplace(key, std::move(data))).second;
	// ϯ�߂ͱ����������ް�������Ă��܂�
	//if (_animMap.find(key) == _animMap.end())
	//{
	//	_animMap[key] = data;
	//	return true;
	//}
	//return false;
}

bool Obj::SetAlive(bool alive)
{
	_alive = alive;
	if (!_alive)
	{
		state(STATE::DETH);
	}

	return true;
}

bool Obj::isAnimEnd(void)
{
	// �Y�����鷰�����邩�ǂ���
	if (_animMap.find(_state) == _animMap.end())
	{
		return true;
	}
	// _animFrame���͈͓����ǂ���
	if (_animFrame >= _animMap[_state].size() ||
		_animFrame < 0)
	{
		return true;
	}
	// ��Ұ��݂��I����Ă��邩�ǂ���
	if (_animMap[_state][_animFrame].first == -1)
	{
		return true;
	}
	else
	{
		return false;
	}
}

const vector2Dbl & Obj::pos(void) const
{
	return _pos;
}

const vector2Dbl & Obj::size(void) const
{
	return _size;
}

const UNIT_ID & Obj::unitID(void) const
{
	return _unitID;
}

bool Obj::DestroyPrpc(void)
{	
	if (_alive)
	{
		return false;
	}
	if (isAnimEnd())
	{
		_dead = true;
	}
	return true;
}

void Obj::Update(void)
{

}

void Obj::Draw(void)
{
	// C++��if����[�����Ȃ��悤��
	// �Y�����鷰�����邩�ǂ���
	if (_animMap.find(_state) == _animMap.end())
	{
		return;
	}
	// _animFrame���͈͓����ǂ���
	if (_animFrame >= _animMap[_state].size() ||
		_animFrame < 0)
	{
		return;
	}
	// ��Ұ��݂�����
	if (_animCount >= _animMap[_state][_animFrame].second)
	{
		if (_animMap[_state][_animFrame].first >= 0)
		{
			_animFrame++;
		}
		else
		{
			return;
		}
	}
	_animCount++;
	if (_animFrame >= _animMap[_state].size())
	{
		_animFrame = 0;
		_animCount = 0;
	}
	// ����̒ǉ�
	lpSceneMng.AddDrawQue({ _animMap[_state][_animFrame].first, _pos.x + lpSceneMng.GameScreenOffset.x, _pos.y + lpSceneMng.GameScreenOffset.y, _rad, _zOrder, LAYER::CHAR});
}

void Obj::Draw(int id)
{
	lpSceneMng.AddDrawQue({ id, _pos.x, _pos.y , _rad, _zOrder, LAYER::CHAR });
}
