#pragma once
#include <memory>
#include <tuple>
#include <vector>
#include <map>
#include <Vector2.h>
#include "BeseScene.h"
#include "LAYER_ID.h"

enum class DRAW_QUE
{
	IMAGE,
	X,
	Y,
	RAD,
	ZORDER,		// ڲ԰���̕`�揇(���l���Ⴂ�ق�����)
	LAYER		// ID�̏��������̂����ɕ`��
};

// �`�悷��̂ɕK�v�ȏ��<ImageID, ���WX, ���WY, �摜�̉�]�p>
using DrawQueT = std::tuple<int, double, double, double, int, LAYER>;

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

	bool AddDrawQue(DrawQueT dQue);		// ����̒ǉ�
	bool AddActQue(ActQueT aQue);

	// -------------�ϐ�
	const vector2Int ScreenSize;		// ��ذݻ���X,Y
	const vector2Int ScreenCenter;
	const vector2Int GameScreenSize;
	const vector2Int GameScreenOffset;

	int gameCount;						// �ްёS�̶̂��Đ�

private:
	static SceneMng* sInstance;
	unique_Base _activeScene;

	void Draw(void);					// ���ׂĂ�`�悷��

	std::map<LAYER, int > _screenID;	// �`�悷���ʂ��w�肷��

	std::vector<DrawQueT> _drawList;	// ����̒ǉ�
	std::vector<ActQueT> _actList;

	SceneMng();
	~SceneMng();
	bool SysInit(void);					// ���ьn������
};

