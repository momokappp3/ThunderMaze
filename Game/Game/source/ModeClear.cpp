#include "../../../AppFrame/source/momoka/Types.h"
#include "../../../AppFrame/source/appframe.h"
#include "../source/ApplicationMain.h"
#include "../source/ModeGame.h"
#include "../../../AppFrame/source/static/ResourceServer.h"
#include "../../../AppFrame/source/static/MouseInput.h"
#include "ModeClear.h"
#include "ModeTitle.h"

ModeClear::ModeClear() {
	_cg = -1;
}

ModeClear::~ModeClear() {
}

bool ModeClear::Initialize() {

	if (!ModeBase::Initialize()) {
		return false;
	}

	_pKeyInput.reset(new Input);

	_cg = ResourceServer::LoadGraph("png/clear.png");

	return true;
}

bool ModeClear::Process() {

	if (_pKeyInput->_key[(KEY_INPUT_RETURN)] == 1 && ModeBase::GetModeTm() >= 2000) {
		ModeServer::GetInstance()->Del(this);
		ModeServer::GetInstance()->Add(new ModeTitle(), 1, "title");
	}

	_pKeyInput->Process();
	ModeBase::Process();
	MouseInput::Process();

	return true;
}

bool ModeClear::Render() {

	DrawGraph(0, 0, _cg, TRUE);
	//DrawFormatString(20, 50, GetColor(255, 255, 255), "%d", ModeBase::GetModeTm());

	ModeBase::Render();
	MouseInput::Draw();

	return true;
}

bool ModeClear::Terminate() {
	ModeBase::Terminate();
	return true;
}
