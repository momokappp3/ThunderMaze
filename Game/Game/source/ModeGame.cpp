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

	if(!_pMazeStage->Initialize(_pSoundManager) || !_pUIPopUp->Init() || !_pHp->Init() || !_pUITime->Init()||
	   !_pItem->Init(_pSoundManager)|| !_pUIItem->Init()) {
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

	if (_pKeyInput->_key[(KEY_INPUT_U)] == 1) {
		_pItem->SetItem(ITEM::TimeLong);
	}
	
	_pUIItem->SetUpperItem(_pItem->GetUpperItem());
	_pUIItem->SetMiddleItem(_pItem->GetMiddleItem());
	_pUIItem->SetDownItem(_pItem->GetDownItem());

	_pMazeStage->GetModeCount(GetModeCount());

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

	 //=======================================================
	 //宝箱のポップアップ&アイテム

	 for (int i = 0; i < _pMazeStage->GetStrongSize(); i++) {
		 if (_pMazeStage->GetBox(i)->GetIsPopUp()) {
			 _pUIPopUp->SetNowMode(true);
			 if (_pMazeStage->GetBox(i)->GetIsItem()) {

				 switch (_pMazeStage->GetBox(i)->GetItemNum()) {
				 case ITEM::Barrier:
					 _pUIPopUp->SetPopString({ "バリア" ,573,403,true });
					 break;
				 case ITEM::Portion:
					 _pUIPopUp->SetPopString({ "回復薬" ,573,403,true });
					 break;
				 case ITEM::Through:
					 _pUIPopUp->SetPopString({ "すり抜け" ,573,403,true });
					 break;
				 case ITEM::TimeLong:
					 _pUIPopUp->SetPopString({ "時間" ,573,403,true });
					 break;
				 default:
					 break;
				 }

				 if (_pKeyInput->_key[(KEY_INPUT_RETURN)] == 1) {
					 _pMazeStage->GetBox(i)->SetIsItem(false);
					 _pItem->SetItem(_pMazeStage->GetBox(i)->GetItemNum());
					 _pSoundManager->PlaySECommon(SoundManager::SECommon::OK);
				 }
			 }
			 else {
				 _pUIPopUp->SetPopString({ "何も入っていない" ,553,403,true });
			 }
		 }
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

	MouseInput::Draw();
	return true;
}

bool ModeGame::Terminate() {
	ModeBase::Terminate();
	_pMazeStage->Terminate();
	return true;
}