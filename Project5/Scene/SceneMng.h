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
	LAYER,		// ID�̏��������̂����ɕ`��
	DRAW_MODE,
	DRAW_NUM,
};

// �`�悷��̂ɕK�v�ȏ��<ImageID, ���WX, ���WY, �摜�̉�]�p, zOrder, Layer, �`��Ӱ��, �`��œn���l>
using DrawQueT = std::tuple<int, double, double, double, int, LAYER, int, int>;

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

	bool AddDrawQue(DrawQueT dQue);		// �`�淭��̒ǉ�
	bool AddActQue(ActQueT aQue);		// ����ݷ���̒ǉ�

	// -------------�ϐ�
	const vector2Int ScreenSize;		// ��ذݻ���X,Y
	const vector2Int ScreenCenter;		// ��ʂ̒���
	const vector2Int GameScreenSize;	// �ްѽ�ذݻ���X,Y
	const vector2Int GameScreenOffset;	// �ްѽ�ذ̵݂̾��

	int gameCount;						// �ްёS�̶̂��Đ�

private:
	static SceneMng* sInstance;
	unique_Base _activeScene;			// �ǂ̼�݂𑖂点�邩

	void Draw(void);					// ���ׂĂ�`�悷��

	int _layerGID;

	std::vector<DrawQueT> _drawList;	// �`�淭����Ǘ�����z��
	std::vector<ActQueT> _actList;		// ����ݷ�����Ǘ�����z��

	SceneMng();
	~SceneMng();
	bool SysInit(void);					// ���ьn������
};

