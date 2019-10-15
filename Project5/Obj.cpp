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
}

Obj::~Obj()
{
}

bool Obj::state(const STATE key)
{
	// ｷｰがあるかどうか
	if (_animMap.find(key) == _animMap.end())
	{
		return false;
	}
	// ｷｰが変わっていればｱﾆﾒｰｼｮﾝを初期化する
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
	// c++17以降
	return (_animMap.try_emplace(key, std::move(data))).second;
	// ﾏｯﾌﾟはｱｸｾｽしたらﾃﾞｰﾀを作ってしまう
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
	// 該当するｷｰがあるかどうか
	if (_animMap.find(_state) == _animMap.end())
	{
		return true;
	}
	// _animFrameが範囲内かどうか
	if (_animFrame >= _animMap[_state].size() ||
		_animFrame < 0)
	{
		return true;
	}
	// ｱﾆﾒｰｼｮﾝが終わっているかどうか
	if (_animMap[_state][_animFrame].first == -1)
	{
		return true;
	}
	else
	{
		return false;
	}
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
	// C++でif文を深くしないように
	// 該当するｷｰがあるかどうか
	if (_animMap.find(_state) == _animMap.end())
	{
		return;
	}
	// _animFrameが範囲内かどうか
	if (_animFrame >= _animMap[_state].size() ||
		_animFrame < 0)
	{
		return;
	}
	// ｱﾆﾒｰｼｮﾝさせる
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
	// ｷｭｰの追加
	lpSceneMng.AddDrawQue({ _animMap[_state][_animFrame].first, _pos.x, _pos.y });
}

void Obj::Draw(int id)
{
	lpSceneMng.AddDrawQue({ id, _pos.x, _pos.y });
}
