#pragma once
#include <map>
#include <BeseScene.h>

// �֐���޼ު�Ă͊�{����د��ł���
struct FuncBullet
{
	bool operator()(ActQueT actData, std::vector<sharedObj>& _objList);
private:
	static std::map<UNIT_ID, int> _maxCount;
};

