#include "../../../AppFrame/source/appframe.h"
#include "ApplicationMain.h"
#include "ModeTitle.h"

// ����
ApplicationMain	g_oApplicationMain;

bool ApplicationMain::Initialize(HINSTANCE hInstance) {
	if (!base::Initialize(hInstance)) { return false; }

	// ���[�h�̓o�^
	ModeServer::GetInstance()->Add(new ModeTitle(), 1, "title");

	return true;
}

bool ApplicationMain::Terminate() {
	base::Terminate();
	return true;
}

bool ApplicationMain::Input() {
	base::Input();
	return true;
}

bool ApplicationMain::Process() {
	base::Process();
	return true;
}

bool ApplicationMain::Render() {
	base::Render();
	return true;
}