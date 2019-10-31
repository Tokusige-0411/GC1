#include <DxLib.h>
#include "SceneMng.h"
#include "GameScene.h"
#include "TitleScene.h"


SceneMng* SceneMng::sInstance = nullptr;

enum class DRAW_QUE
{
	IMAGE,
	X,
	Y,
	RAD
};

void SceneMng::Draw(void)
{
	SetDrawScreen(DX_SCREEN_BACK);
	ClsDrawScreen();

	// �����ɂ��܂��Ă���Que��`�悷��
	// �͈�for��
	for (auto dQue : _drawList)
	{
		DrawRotaGraph(
			static_cast<int>(std::get<static_cast<int>(DRAW_QUE::X)>(dQue)),
			static_cast<int>(std::get<static_cast<int>(DRAW_QUE::Y)>(dQue)),
			1.0,
			std::get<static_cast<int>(DRAW_QUE::RAD)>(dQue),
			std::get<static_cast<int>(DRAW_QUE::IMAGE)>(dQue),
			true);
	}

	// ��ڰ�����g����for��
	// auto = std::vector<DrawQuwT>::iterator
	//for (auto dQue = _drawList.begin(); dQue != _drawList.end(); dQue++)
	//{
	//	DrawGraph(
	//		std::get<static_cast<int>(DRAW_QUE::X)>(*dQue),
	//		std::get<static_cast<int>(DRAW_QUE::Y)>(*dQue),
	//		std::get<static_cast<int>(DRAW_QUE::IMAGE)>(*dQue),
	//		true);
	//}

	//for (int i = 0; i < _drawList.size(); i++)
	//{
	//	DrawGraph(
	//		std::get<static_cast<int>(DRAW_QUE::X)>(_drawList[i]),
	//		std::get<static_cast<int>(DRAW_QUE::Y)>(_drawList[i]),
	//		std::get<static_cast<int>(DRAW_QUE::IMAGE)>(_drawList[i]),
	//		true);
	//}

	ScreenFlip();
}

SceneMng::SceneMng() : screenSize{800,600}		// const�ɂȂ钼�O�ɒl������������
{
}

SceneMng::~SceneMng()
{
}

void SceneMng::Run(void)
{
	SysInit();
	_activeScene = std::make_unique<GameScene>();
	while (!ProcessMessage() && !CheckHitKey(KEY_INPUT_ESCAPE))
	{
		_drawList.clear();
		// ��ذ�𒼐ڊǗ�����ׂ��ł͂Ȃ�(get�����܂�g��Ȃ��悤��)
		// [(*_activeScene).] = [_activeScene->]
		// ���L����n��(��߰�����Ȃ�)
		_activeScene = (*_activeScene).Update(std::move(_activeScene));
		Draw();
	}
}

bool SceneMng::AddDrawQue(DrawQuwT dQue)
{
	// static_cast<���Ă������^>(���Ă������Ώە�)
	if (std::get<static_cast<int>(DRAW_QUE::IMAGE)>(dQue) <= 0)
	{
		// �摜ID���s���Ȃ̂ŁA�ǉ����Ȃ�
		return false;
	}
	// Que��ǉ�
	//_drawList.push_back();
	_drawList.emplace_back(dQue);
	return true;
}

bool SceneMng::SysInit(void)
{
	// ���я���
	SetWindowText("kadai5");
	SetGraphMode(screenSize.x, screenSize.y, 16);		// 320*600�ޯāA65536�FӰ�ނɐݒ�
	ChangeWindowMode(true);								// true:window false:�ٽ�ذ�
	if (DxLib_Init() == -1)								// DXײ���؂̏���������
	{
		return false;
	}

	SetDrawScreen(DX_SCREEN_BACK);						// �`�����ޯ��ޯ̧�ɐݒ�

	return false;
}
