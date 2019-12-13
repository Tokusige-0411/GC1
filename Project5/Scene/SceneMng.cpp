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
		[](const DrawQueT& x, const DrawQueT& y) {
		// tie���g���ĕ������������Ă���
		// �����̗v�f���珇�Ԃɔ�ׂāA�����ɍ���Ȃ������玟�̗v�f���ׂĂ���
		return std::tie(std::get<static_cast<int>(DRAW_QUE::LAYER)>(x), std::get<static_cast<int>(DRAW_QUE::ZORDER)>(x))
			< std::tie(std::get<static_cast<int>(DRAW_QUE::LAYER)>(y), std::get<static_cast<int>(DRAW_QUE::ZORDER)>(y));
	});

	SetDrawScreen(DX_SCREEN_BACK);
	ClsDrawScreen();

	// ڲ԰��Ӱ�ނ̏����l��ݒ�
	LAYER drawLayer = begin(LAYER());
	int blendMode = DX_BLENDMODE_NOBLEND;
	int blendModeNum = 255;

	// �`����ݒ�
	SetDrawScreen(_layerGID);
	ClsDrawScreen();
	SetDrawBlendMode(blendMode, blendModeNum);

	// �����ɂ��܂��Ă���Que��`�悷��
	// �͈�for��
	for (auto dQue : _drawList)
	{
		double x, y, rad;
		int id;
		LAYER layer;

		// 1�O�̏���ۑ�����
		int blendModeOld = blendMode;
		int blendModeNumOld = blendModeNum;

		// tuplu�̓��e���o���V�ē������
		std::tie(id, x, y, rad, std::ignore, layer, blendMode, blendModeNum) = dQue;

		// ����ڲ԰�ɍ��킹�ĕ`����ς���
		if ((layer != drawLayer) || (blendModeOld != blendMode) || (blendModeNum != blendModeNumOld))
		{
			// layerGID�ɕ`�������e���ޯ��ޯ̧�ɕ`�悷��
			SetDrawScreen(DX_SCREEN_BACK);
			SetDrawBlendMode(blendModeOld, blendModeNumOld);
			auto layPos = ScreenCenter + (*_activeScene)._screenPos;
			DrawRotaGraph(layPos.x, layPos.y, 1.0, 0.0, _layerGID, true);

			// �`����_layerGID�ɐݒ�
			SetDrawScreen(_layerGID);
			SetDrawBlendMode(blendMode, blendModeNum);
			ClsDrawScreen();
		}

		DrawRotaGraph(static_cast<int>(x), static_cast<int>(y), 1.0, rad, id, true);
	}

	SetDrawScreen(DX_SCREEN_BACK);
	SetDrawBlendMode(blendMode, blendModeNum);

	DrawRotaGraph(ScreenCenter.x, ScreenCenter.y, 1.0, 0, _layerGID, true);


	ScreenFlip();

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
}

SceneMng::SceneMng() : 
	// const�ɂȂ钼�O�ɒl������������
	ScreenSize{ 800,600 }, 
	GameScreenSize{ 500,390 }, 
	ScreenCenter{ ScreenSize / 2 }, 
	GameScreenOffset{ (ScreenSize - GameScreenSize) / 2 }
{
}

SceneMng::~SceneMng()
{
}

void SceneMng::Run(void)
{
	SysInit();
	_activeScene = std::make_unique <TitleScene> ();
	while (!ProcessMessage() && !CheckHitKey(KEY_INPUT_ESCAPE))
	{
		_dbgStartDraw();
		_drawList.clear();
		lpSceneMng.AddDrawQue({ IMAGE_ID("�g")[0], ScreenSize.x / 2, ScreenSize.y / 2, 0.0, 0, LAYER::UI, DX_BLENDMODE_NOBLEND, 255});
		// ��ذ�𒼐ڊǗ�����ׂ��ł͂Ȃ�(get�����܂�g��Ȃ��悤��)
		// [(*_activeScene).] = [_activeScene->]
		// ���L����n��(��߰�����Ȃ�)
		_activeScene = (*_activeScene).Update(std::move(_activeScene));
		// ���ʓI��List�͍폜����Ă��邪�A�폜���K�v���ǂ������f����悤�ɂ���
		(*_activeScene).RunActQue(std::move(_actList));
		Draw();
		gameCount++;
	}
}

bool SceneMng::AddDrawQue(DrawQueT dQue)
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

bool SceneMng::AddActQue(ActQueT aQue)
{
	_actList.emplace_back(aQue);
	return true;
}

bool SceneMng::SysInit(void)
{
	// ���я���
	SetWindowText("kadai5");
	SetGraphMode(ScreenSize.x, ScreenSize.y, 16);		// 800*600�ޯāA65536�FӰ�ނɐݒ�
	ChangeWindowMode(true);								// true:window false:�ٽ�ذ�
	if (DxLib_Init() == -1)								// DXײ���؂̏���������
	{
		return false;
	}

	SetDrawScreen(DX_SCREEN_BACK);						// �`�����ޯ��ޯ̧�ɐݒ�

	// ����Ă���΍��Ȃ�
	_layerGID = MakeScreen(ScreenSize.x, ScreenSize.y, true);

	_dbgSetup(255);										// ���ޯ�ޗp��ı���
	lpImageMng.GetID("�g", "image/frame.png");			// �ڰщ摜�o�^
	lpImageMng.GetID("Black", "image/black.png");
	lpImageMng.GetID("White", "image/white.png");

	return false;
}
