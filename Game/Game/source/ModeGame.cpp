#include "../../../AppFrame/source/appframe.h"
#include "ApplicationMain.h"
#include "ModeGame.h"
#include "../../../AppFrame/source/static/Input.h"
#include "ModeTitle.h"

ModeGame::ModeGame() {

	_pMazeStage = nullptr;
}

ModeGame::~ModeGame() {
}

bool ModeGame::Initialize() {

	if (!ModeBase::Initialize()) { 
		return false;
	}

	_pMazeStage.reset(new MazeStage);

	if(!_pMazeStage->Initialize()) {
		return false;
	}

	return true;
}

bool ModeGame::Process() {

	_pMazeStage->GetModeCount(GetModeCount());


	if (Input::_key[(KEY_INPUT_ESCAPE)] == 1) {
		//Title‚É–ß‚éˆ—
		ModeServer::GetInstance()->Del(this);
		ModeServer::GetInstance()->Add(new ModeTitle(), 1, "title");
	}
	
	Input::Process();
	ModeBase::Process();
	_pMazeStage->Process();
	return true;
}

bool ModeGame::Render() {
	ModeBase::Render();
	_pMazeStage->Render();

	return true;
}

bool ModeGame::Terminate() {
	ModeBase::Terminate();
	_pMazeStage->Terminate();
	return true;
}