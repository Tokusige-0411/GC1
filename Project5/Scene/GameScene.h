#pragma once
#include "BeseScene.h"
#include "Obj.h"

class GameScene :
	public BaseScene
{
public:
	GameScene();
	~GameScene();
	unique_Base Update(unique_Base own) override;		// �`����̱����ް�
	// RunActQue�ŕ`��Ɠ����悤�Ȃ��Ƃ�
	void RunActQue(std::vector<ActQueT> actList);
private:
	std::vector<sharedObj> _objList;					// ��޼ު�Ă̔z��
};

