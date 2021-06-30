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
	_pUITime = nullptr;
	_pUIItem = nullptr;
	_pItem = nullptr;
	_pKeyInput = nullptr;

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
	_pUITime.reset(new UITime);
	_pItem.reset(new Item);
	_pUIItem.reset(new UIItem);

	if(!_pMazeStage->Initialize() || !_pUIPopUp->Init() || !_pHp->Init() || !_pUITime->Init()||
	   !_pItem->Init()|| !_pUIItem->Init()) {
		return false;
	}

	_pHp->InitHP(2000);

	return true;
}

bool ModeGame::Process() {

	//ゲームのBGM
	if (!_isBGM) {
		if (_pSoundManager != nullptr) {
			_pSoundManager->PlayBgm(SoundManager::BGM::InGame);
			_isBGM = true;
			_pUITime->SetStart(3,20);
		}
	}

	//=======================================================
	//test

	if (_pKeyInput->_key[(KEY_INPUT_R)] == 1) {
		_pItem->SetItem(ITEM::Barrier);
	}

	if (_pKeyInput->_key[(KEY_INPUT_T)] == 1) {
		_pItem->SetItem(ITEM::Portion);
	}

	if (_pKeyInput->_key[(KEY_INPUT_Y)] == 1) {
		_pItem->SetItem(ITEM::Through);
	}


	_pUIItem->SetUpperItem(_pItem->GetUpperItem());
	_pUIItem->SetMiddleItem(_pItem->GetMiddleItem());
	_pUIItem->SetDownItem(_pItem->GetDownItem());

	_pMazeStage->GetModeCount(GetModeCount());
	/*
	//ドアのアニメーション 0が右 3が左
	if (_pMazeStage->GetIsDoorAnim()) {
		if (!_isAnimEnd) {
			_playTime += 0.1f;
			_attachDoorIndexRight = MV1AttachAnim(_pMazeStage->GetDoorHandle(), 0, -1, FALSE);
			_attachDoorIndexLeft = MV1AttachAnim(_pMazeStage->GetDoorHandle(), 3, -1, FALSE);
		}
	}
	*/

	//攻撃が当たったら
	if (_pMazeStage->GetIsHit()) {
		_pHp->SetHp(1500);
	}

	//エスケープキーでタイトルに
	 if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) {  //Titleに戻る処理
		ModeServer::GetInstance()->Del(this);
		ModeServer::GetInstance()->Add(new ModeTitle(), 1, "title");
	}

	 //=================================================
	 //DoorのPopUp表示クリアに行く処理
	 if (_pMazeStage->GetIsDoorArea()) {
		 _pUIPopUp->SetNowMode(true);
		 _pUIPopUp->SetPopString({ "ここから出る" ,573,403,true });
		 // DrawFormatString(500, 500, GetColor(0, 128, 128), "HIT");
		 if (_pUIPopUp->GetOk()) {
			 //popUpOKならクリアに行く
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

	 _pUITime->Process();
	 _pUIPopUp->Process();
	 _pHp->Process();
	 MouseInput::Process();
	 _pKeyInput->Process();
	 ModeBase::Process();
	 _pMazeStage->Process();
	 _pItem->Process();

	return true;
}

bool ModeGame::Render() {
	ModeBase::Render();
	_pMazeStage->Render();
	_pUIPopUp->Draw();
	_pUITime->Draw();
	_pItem->Draw();
;
	if (_pMazeStage->GetIs3D()) {
		_pHp->Draw();
		_pUIItem->Draw();
	}

	if (_pMazeStage->GetIsDoorAnim()) {
		//MV1SetAttachAnimTime(_pMazeStage->GetDoorHandle(), _attachDoorIndexRight, _playTime);
		//MV1SetAttachAnimTime(_pMazeStage->GetDoorHandle(), _attachDoorIndexLeft, _playTime);
	}

	MouseInput::Draw();
	return true;
}

bool ModeGame::Terminate() {
	ModeBase::Terminate();
	_pMazeStage->Terminate();
	return true;
}