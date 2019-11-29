#pragma once
#include <memory>
#include <Obj.h>

class BaseScene;

enum class ACT_QUE
{
	NON,
	SHOT,
	CHECK_HIT
};

using unique_Base = std::unique_ptr<BaseScene>;
using ActQueT = std::pair<ACT_QUE, Obj&>;

class BaseScene
{
public:
	BaseScene();
	virtual ~BaseScene();
	virtual unique_Base Update(unique_Base own) = 0;
	// RunActQue�̉��z�֐��i_actList�����̂܂ܓn���j
	// �K�������S���̼�݂ŕK�v����Ȃ�����
	virtual void RunActQue(std::vector<ActQueT> actList);		// ���������邾��
};

