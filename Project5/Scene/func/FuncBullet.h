#pragma once
#include <map>
#include <BeseScene.h>

// �֐���޼ު�Ă͊�{����د��ł���
struct FuncBullet
{
	bool operator()(ActQueT actData, void* scene);		// �e��ł�
private:
	static std::map<UNIT_ID, int> _maxCount;	// �e�̕\���ő吔
};

