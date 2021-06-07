#include "../appframe.h"

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow) {

	ApplicationBase *appBase = ApplicationBase::GetInstance();

	if (!appBase) {
		return 0;
	}

	if (!appBase->Initialize(hInstance)) {
		return 0;
	}

	while (ProcessMessage() == 0){
		appBase->Input();

		appBase->Process();

		ClearDrawScreen();		// ��ʂ�����������

		appBase->Render();

		ScreenFlip();			// ����ʂ̓��e��\��ʂɔ��f������
	}

	appBase->Terminate();

	return 0;
}