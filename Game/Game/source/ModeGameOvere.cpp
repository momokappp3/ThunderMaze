#include "ModeGameOvere.h"
#include "../../../AppFrame/source/static/ResourceServer.h"
#include "../../../AppFrame/source/static/MouseInput.h"
#include "ModeTitle.h"

ModeGameOvere::ModeGameOvere() {
    _cg = -1;
}

ModeGameOvere:: ~ModeGameOvere() {
}

bool ModeGameOvere::Initialize() {

	if (!ModeBase::Initialize()) {
		return false;
	}

	_pKeyInput.reset(new Input);

	_cg = ResourceServer::LoadGraph("png/gameOver.png");

	return true;
}

bool ModeGameOvere::Process() {
	if (_pKeyInput->_key[(KEY_INPUT_RETURN)] == 1 && ModeBase::GetModeTm() >= 2000) {
		ModeServer::GetInstance()->Del(this);
		ModeServer::GetInstance()->Add(new ModeTitle(), 1, "title");
	}

	_pKeyInput->Process();
	ModeBase::Process();
	MouseInput::Process();

	return true;
}

bool ModeGameOvere::Render() {

	DrawGraph(0, 0, _cg, TRUE);
	//DrawFormatString(20, 50, GetColor(255, 255, 255), "%d", ModeBase::GetModeTm());

	ModeBase::Render();
	MouseInput::Draw();

	return true;
}

bool ModeGameOvere::Terminate(){
	ModeBase::Terminate();
	return true;
}