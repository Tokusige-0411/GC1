#pragma once
#include <memory>
#include <tuple>
#include <vector>
#include <Vector2.h>
#include "BeseScene.h"

// �`�悷��̂ɕK�v�ȏ��<ImageID, ���WX, ���WY>
using DrawQuwT = std::tuple<int, int, int>;

// lp �ݸ��߲���
#define lpSceneMng SceneMng::GetInstance()

class SceneMng
{
public:
	// -------------�֐�
	// �ÓI�ȼݸ����
	//�@static SceneMng& GetInstance(void)
	//�@{
	//		return sInstance;
	//�@}

	// ���I�ȼݸ����
	static SceneMng& GetInstance(void)
	{
		Create();
		return *sInstance;
	}
	static void Create(void)
	{
		if (sInstance == nullptr)
		{
			sInstance = new SceneMng();
		}
	}

	// �ݸ���݂̓��I�޽�׸�
	static void Destroy()
	{
		if (sInstance != nullptr)
		{
			delete sInstance;
		}
		sInstance = nullptr;
	}

	void Run(void);						// �ް�ٰ��

	// �����̗v�f��1�ɂ܂Ƃ߂�
	// std::pair<int, double> data1
	// std::tuple<int, int, int> 

	bool AddDrawQue(DrawQuwT dQue);		// ����̒ǉ�

	// -------------�ϐ�
	const vector2Int screenSize;		// ��ذݻ���X,Y
private:
	static SceneMng* sInstance;
	unique_Base _activeScene;

	void Draw(void);					// ���ׂĂ�`�悷��

	std::vector<DrawQuwT> _drawList;	// ����̒ǉ�

	SceneMng();
	~SceneMng();
	bool SysInit(void);					// ���ьn������
};

