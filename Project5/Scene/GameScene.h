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
private:
	std::vector<sharedObj> _objList;					// ��޼ު�Ă̔z��
};

