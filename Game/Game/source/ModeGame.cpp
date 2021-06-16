#include "../../../AppFrame/source/appframe.h"
#include "ApplicationMain.h"
#include "ModeGame.h"
#include "ModeTitle.h"
#include "../../../AppFrame/source/static/MouseInput.h"
#include "ModeClear.h"

ModeGame::ModeGame() {

	_pMazeStage = nullptr;
	_pHp = nullptr;
	_pUIPopUp = nullptr;

	_isBGM = false;
	_isAnimEnd = false;

	_playTime = 0.0f;

	_attachDoorIndexRight = -1;
	_attachDoorIndexLeft = -1;
}

ModeGame::~ModeGame() {
}

bool ModeGame::Initialize() {

	if (!ModeBase::Initialize()) { 
		return false;
	}

	if (_pSoundManager != nullptr) {
		bool seGame = _pSoundManager->LoadSECommon();

		if (!seGame) {
			return false;
		}
	}
	else {
		return false;
	}

	_pKeyInput.reset(new Input);
	_pMazeStage.reset(new MazeStage);
	_pUIPopUp.reset(new UIPopUp);
	_pHp.reset(new UIHpGauge);

	if(!_pMazeStage->Initialize() || !_pUIPopUp->Init() || !_pHp->Init()) {
		return false;
	}

	return true;
}

bool ModeGame::Process() {

	//�Q�[����BGM
	if (!_isBGM) {
		if (_pSoundManager != nullptr) {
			_pSoundManager->PlayBgm(SoundManager::BGM::InGame);
			_isBGM = true;
		}
	}

	_pMazeStage->GetModeCount(GetModeCount());

	//0���E3����
	if (_pMazeStage->GetIsDoorAnim()) {

		if (!_isAnimEnd) {
			_playTime += 0.1f;

			_attachDoorIndexRight = MV1AttachAnim(_pMazeStage->GetDoorHandle(), 0, -1, FALSE);
			_attachDoorIndexLeft = MV1AttachAnim(_pMazeStage->GetDoorHandle(), 3, -1, FALSE);
		}
	}

	 if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) {  //Title�ɖ߂鏈��
		 //popUp�\��
		 //popUpOK�Ȃ�^�C�g���֍s��
		ModeServer::GetInstance()->Del(this);
		ModeServer::GetInstance()->Add(new ModeTitle(), 1, "title");
	}
	
	 if (_pMazeStage->GetIsDoorArea()) {
		 _pUIPopUp->SetNowMode(true);
		 _pUIPopUp->SetPopString({ "��������o��" ,573,403,true });
		 // DrawFormatString(500, 500, GetColor(0, 128, 128), "HIT");
		 if (_pUIPopUp->GetOk()) {
			 //popUpOK�Ȃ�N���A�ɍs��
			 if (_pKeyInput->_key[(KEY_INPUT_RETURN)] == 1) {
				ModeServer::GetInstance()->Del(this);
				ModeServer::GetInstance()->Add(new ModeClear(), 1, "clear");
				_pSoundManager->PlaySECommon(SoundManager::SECommon::OK);
			 }
		 }
	 }
	 else {
		 _pUIPopUp->SetNowMode(false);
	 }

	 _pUIPopUp->Process();
	 _pHp->Process();
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

	if (_pMazeStage->GetIs3D()) {
		_pHp->Draw();
	}

	if (_pMazeStage->GetIsDoorArea()) {
		//debug
		//DrawFormatString(500, 500, GetColor(0, 128, 128), "HIT");
	}

	if (_pMazeStage->GetIsDoorAnim()) {
		DrawFormatString(500, 500, GetColor(0, 128, 128), "HITAnim");
		MV1SetAttachAnimTime(_pMazeStage->GetDoorHandle(), _attachDoorIndexRight, _playTime);
		MV1SetAttachAnimTime(_pMazeStage->GetDoorHandle(), _attachDoorIndexLeft, _playTime);
	}

	MouseInput::Draw();
	return true;
}

bool ModeGame::Terminate() {
	ModeBase::Terminate();
	_pMazeStage->Terminate();
	return true;
}