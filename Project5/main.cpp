#include <DxLib.h>			// DxLibײ���؂��g�p����
#include <Scene\SceneMng.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPlevInstance, LPSTR lpCmbLine, int nCmdShow)
{
	//SceneMng sceneMng;
	//sceneMng.Run();

	SceneMng::Create();
	SceneMng::GetInstance().Run();
	SceneMng::Destroy();

	return 0;
}