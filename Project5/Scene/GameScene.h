#pragma once
#include <functional>
#include <map>
#include "BeseScene.h"
#include "Obj.h"

// ���g������ꍇ��ͯ�ް��ݸٰ�ނ��Ȃ��Ƃ����Ȃ����A��������Ȃ��ꍇ�͉��錾�ł���
struct FuncCheckHit;
struct FuncBullet;
struct FuncShake;

using funcAct = std::function<bool(ActQueT&, void*)>;

class GameScene :
	public BaseScene
{
public:
	GameScene();
	~GameScene();
	unique_Base Update(unique_Base own) override;		// �`����̱����ް�
private:
	// ����ޓo�^
	friend FuncCheckHit;
	friend FuncBullet;
	friend FuncShake;

	void initFunc(void);
	std::vector<sharedObj> _objList;					// ��޼ު�Ă̔z��
	// RunActQue�ŕ`��Ɠ����悤�Ȃ��Ƃ�
	void RunActQue(std::vector<ActQueT> actList);		// ���ˁA�����蔻�������
	std::map<ACT_QUE, funcAct> funcQue;					// Act���Ǘ�����
	int _shakeCount;									// 
};

