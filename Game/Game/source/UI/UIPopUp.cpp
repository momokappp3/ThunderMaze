#include "UIPopUp.h"
#include "Dxlib.h"
#include "../../../../AppFrame/source/static/ResourceServer.h"

UIPopUp::UIPopUp() {

    _pPopUpBase = nullptr;
    _pOkBSelectBase = nullptr;

	_ok = false;
	_nowMode = false;
	_popString = { _T("������"),{0,0},false };
	_fontHandle = -1;
}

UIPopUp::~UIPopUp() {
}

bool UIPopUp::Init() {

	_pKeyInput.reset(new Input);

	//ModeGame�̃T�E���h�}�l�W���[�������p��
	/*
	if (soundManager != nullptr) {
		bool seTitle = soundManager->LoadSECommon();

		if (!seTitle) {
			return false;
		}
	}
	else {
		return false;
	}
	*/

	//================
	//������n���h��
	_fontHandle = CreateFontToHandle("UD �f�W�^�� ���ȏ��� N-B", 40,1);

	_pPopUpBase.reset(new UI2DBase);
	_pOkBSelectBase.reset(new UI2DSelectBase);

	//=================================================================
	//popupBase
	int handle = ResourceServer::LoadGraph("png/gameUI/popUp.png");

	if (handle == -1) {
		return false;
	}

	DrawInfo info = { handle,340,290,true };
	_pPopUpBase->SetDrawInfo(info);


	//====================================================================
	//OK�{�^��
	handle = ResourceServer::LoadGraph("png/gameUI/OkB.png");
	int handle2 = ResourceServer::LoadGraph("png/gameUI/OkBSelect.png");

	if (handle == -1 && handle2 == -1) {
		return false;
	}

	info = { handle,607,490,true };
	DrawInfo info2 = { handle2,607,490,true };

	_pOkBSelectBase->SetDrawInfo(info);
	_pOkBSelectBase->SetDrawInfo(info2);

	//_pOkBSelectBase->SetRect();

	//=======================================
	//sound

	auto onSelect = [this]() {
		//�T�E���h�炷
		//_pSoundManager->PlaySECommon(SoundManager::SECommon::Select);
	};

	_pOkBSelectBase->SetOnSelect(onSelect);

	return true;
}

void UIPopUp::Process() {

	if (_nowMode) {
		_ok = true;
		if (_pKeyInput->_key[(KEY_INPUT_RETURN) == 1]) {
			
		}
	}

	int select = _ok ? 1 : 0;

	_pOkBSelectBase->SetSelect(select);

	_pKeyInput->Process();
	_pPopUpBase->Process();
	_pOkBSelectBase->Process();
	//_pSoundManager->Process();
}

void UIPopUp::Draw() {

	if (_nowMode) {
		_pPopUpBase->Draw();
		_pOkBSelectBase->Draw();

		if (_popString.isDraw) {
			/*
			DrawFormatString(_popString.xy.x, _popString.xy.y, GetColor(255, 255, 255),
							 _popString.string.c_str());
			*/
			DrawStringToHandle(_popString.xy.x, _popString.xy.y, _popString.string.c_str(),GetColor(33,30,85),_fontHandle);
		}
	}
}