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

		ClearDrawScreen();		// ‰æ–Ê‚ğ‰Šú‰»‚·‚é

		appBase->Render();

		ScreenFlip();			// — ‰æ–Ê‚Ì“à—e‚ğ•\‰æ–Ê‚É”½‰f‚³‚¹‚é
	}

	appBase->Terminate();

	return 0;
}