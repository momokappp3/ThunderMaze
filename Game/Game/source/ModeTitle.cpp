#include "../../../AppFrame/source/momoka/Types.h"
#include "../../../AppFrame/source/appframe.h"
#include "ApplicationMain.h"
#include "ModeGame.h"
#include "../../../AppFrame/source/static/ResourceServer.h"
#include "../../../AppFrame/source/static/MouseInput.h"
#include "ModeTitle.h"

ModeTitle::ModeTitle() {

	_pNewGameString = nullptr;
	_pExitString = nullptr;
	_pItem = nullptr;
	_isBgm = false;

	_nowMenuSelect = SelectMenu::NewGame;
}

ModeTitle::~ModeTitle() {
}

bool ModeTitle::Initialize() {

	if (!ModeBase::Initialize()) {
		return false;
	}

	if (_pSoundManager != nullptr) {
		bool seTitle = _pSoundManager->LoadSECommon();

		if (!seTitle) {
			return false;
		}
	}
	else {
		return false;
	}

	_pKeyInput.reset(new Input);
	_pNewGameString.reset(new UI2DSelectBase);
	_pExitString.reset(new UI2DSelectBase);

	_pItem.reset(new Item);
	_pItem->Init();

	//newGameString
	int handle = ResourceServer::LoadGraph("png/title/newgame.png");
	int handle2 = ResourceServer::LoadGraph("png/title/newgame_select.png");

	if (handle == -1 && handle2 == -1) {
		return false;
	}

	DrawInfo info = { handle,412,500,true };
	DrawInfo info2 = { handle2,412,500,true };

	_pNewGameString->SetDrawInfo(info);
	_pNewGameString->SetDrawInfo(info2);
	
	//exitString
	handle = ResourceServer::LoadGraph("png/title/exit.png");
	handle2 = ResourceServer::LoadGraph("png/title/exitSelect.png");

	if (handle == -1 && handle2 == -1) {
		return false;
	}

	info = { handle,412,570,true };
	info2 = { handle2,412,570,true };

	_pExitString->SetDrawInfo(info);
	_pExitString->SetDrawInfo(info2);

	_cg = ResourceServer::LoadGraph("png/title.png");

	auto onSelect = [this]() {
		//サウンド鳴らす
		_pSoundManager->PlaySECommon(SoundManager::SECommon::Select);
	};

	_pNewGameString->SetOnSelect(onSelect);
	_pExitString->SetOnSelect(onSelect);

	//Timer::SetStartSeconds(500);

	return true;
}

bool ModeTitle::Process() {

	ModeBase::Process();
	_pItem->Process();

	if (!_isBgm) {
		if (_pSoundManager != nullptr) {  //null
			_pSoundManager->PlayBgm(SoundManager::BGM::Title);
			_isBgm = true;
		}
	}

	if (_pKeyInput->_key[(KEY_INPUT_RETURN)] == 1)	{
		if (_nowMenuSelect == SelectMenu::NewGame) {
			ModeServer::GetInstance()->Del(this);
			ModeServer::GetInstance()->Add(new ModeGame(), 1, "game");

			_pSoundManager->PlaySECommon(SoundManager::SECommon::OK);
		}
		else if (_nowMenuSelect == SelectMenu::Exit) {
			//終了処理
			_pSoundManager->PlaySECommon(SoundManager::SECommon::OK);
			
		}
	}

	if (_pKeyInput->_key[(KEY_INPUT_UP)] == 1) {

		int nowNum = static_cast<int>(_nowMenuSelect);

		if (nowNum > 1) {
			nowNum--;
		}
		_nowMenuSelect = static_cast<SelectMenu>(nowNum);
	}

	if (_pKeyInput->_key[(KEY_INPUT_DOWN)] == 1) {

		int nowNum = static_cast<int>(_nowMenuSelect);

		if (nowNum < 2) {
			nowNum++;
		}

		_nowMenuSelect = static_cast<SelectMenu>(nowNum);
	}

	_pNewGameString->SetSelect(_nowMenuSelect == SelectMenu::NewGame);
	_pExitString->SetSelect(_nowMenuSelect == SelectMenu::Exit);

	_pKeyInput->Process();
	MouseInput::Process();
	_pNewGameString->Process();
	_pExitString->Process();

	return true;
}

bool ModeTitle::Render() {

	DrawGraph(0, 0, _cg, TRUE);
	DrawFormatString(20, 50, GetColor(255, 255, 255), "Menu::%d", static_cast<int>(_nowMenuSelect));

	ModeBase::Render();
	_pNewGameString->Draw();
	_pExitString->Draw();
	MouseInput::Draw();
	_pItem->Draw();

	return true;
}

bool ModeTitle::Terminate() {
	ModeBase::Terminate();
	return true;
}