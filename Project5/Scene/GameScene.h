#pragma once
#include <functional>
#include <map>
#include "BeseScene.h"
#include "Obj.h"

using funcAct = std::function<bool(ActQueT&, std::vector<sharedObj>&)>;

class GameScene :
	public BaseScene
{
public:
	GameScene();
	~GameScene();
	unique_Base Update(unique_Base own) override;		// �`����̱����ް�
private:
	std::vector<sharedObj> _objList;					// ��޼ު�Ă̔z��
	// RunActQue�ŕ`��Ɠ����悤�Ȃ��Ƃ�
	void RunActQue(std::vector<ActQueT> actList);
	std::map<ACT_QUE, funcAct> funcQue;
};

