#include "../../../AppFrame/source/appframe.h"
#include "ApplicationMain.h"
#include "ModeGame.h"
#include "ModeTitle.h"
#include "../../../AppFrame/source/static/MouseInput.h"
#include "ModeClear.h"

ModeGame::ModeGame() {

	_pMazeStage = nullptr;
	_pUIPopUp = nullptr;
}

ModeGame::~ModeGame() {
}

bool ModeGame::Initialize() {

	if (!ModeBase::Initialize()) { 
		return false;
	}

	_pKeyInput.reset(new Input);
	_pMazeStage.reset(new MazeStage);
	_pUIPopUp.reset(new UIPopUp);

	if(!_pMazeStage->Initialize() || !_pUIPopUp->Init()) {
		return false;
	}

	return true;
}

bool ModeGame::Process() {
	_pUIPopUp->Process();

	_pMazeStage->GetModeCount(GetModeCount());

	 if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) {  //Titleに戻る処理
		 //popUp表示
		 //popUpOKならタイトルへ行く
		ModeServer::GetInstance()->Del(this);
		ModeServer::GetInstance()->Add(new ModeTitle(), 1, "title");
	}
	
	 if (_pMazeStage->GetIsDoorArea()) {
		 _pUIPopUp->SetNowMode(true);
		 _pUIPopUp->SetPopString({ "ここから出る" ,573,403,true });
		 // DrawFormatString(500, 500, GetColor(0, 128, 128), "HIT");
		 if (_pUIPopUp->GetOk()) {
			 //popUpOKならクリアに行く
			 if (_pKeyInput->_key[(KEY_INPUT_RETURN)] == 1) {
				ModeServer::GetInstance()->Del(this);
				ModeServer::GetInstance()->Add(new ModeClear(), 1, "clear");
			 }
		 }
	 }
	 else {
		 _pUIPopUp->SetNowMode(false);
	 }
	 
	 MouseInput::Process();
	 _pKeyInput->Process();
	ModeBase::Process();
	_pMazeStage->Process();
	return true;
}

bool ModeGame::Render() {
	ModeBase::Render();
	_pMazeStage->Render();
	_pUIPopUp->Draw();

	if (_pMazeStage->GetIsDoorArea()) {
		//debug
		DrawFormatString(500, 500, GetColor(0, 128, 128), "HIT");
	}
	MouseInput::Draw();
	return true;
}

bool ModeGame::Terminate() {
	ModeBase::Terminate();
	_pMazeStage->Terminate();
	return true;
}