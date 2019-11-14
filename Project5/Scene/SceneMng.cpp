#include <DxLib.h>
#include <algorithm>
#include <_DebugDispOut.h>
#include <imageMng.h>
#include "SceneMng.h"
#include "GameScene.h"
#include "TitleScene.h"

SceneMng* SceneMng::sInstance = nullptr;

void SceneMng::Draw(void)
{
	_dbgAddDraw();

	// _drawList��LAYER��������
	std::sort(_drawList.begin(), _drawList.end(),
		[](const DrawQuwT& x, const DrawQuwT& y) 
	{return ((std::get<static_cast<int>(DRAW_QUE::LAYER)>(x)) < (std::get<static_cast<int>(DRAW_QUE::LAYER)>(y))); });

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

SceneMng::SceneMng() : ScreenSize{800,600}		// const�ɂȂ钼�O�ɒl������������
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
		_dbgStartDraw();
		_drawList.clear();
		lpSceneMng.AddDrawQue({ IMAGE_ID("�g")[0], ScreenSize.x / 2, ScreenSize.y / 2, 0.0, 0, LAYER::UI });
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
	SetGraphMode(ScreenSize.x, ScreenSize.y, 16);		// 320*600�ޯāA65536�FӰ�ނɐݒ�
	ChangeWindowMode(true);								// true:window false:�ٽ�ذ�
	if (DxLib_Init() == -1)								// DXײ���؂̏���������
	{
		return false;
	}

	SetDrawScreen(DX_SCREEN_BACK);						// �`�����ޯ��ޯ̧�ɐݒ�
	_dbgSetup(255);
	lpImageMng.GetID("�g", "image/frame.png");

	return false;
}
