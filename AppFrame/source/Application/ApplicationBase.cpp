#include "ApplicationBase.h"

ApplicationBase	*ApplicationBase::_lpInstance = NULL;

ApplicationBase::ApplicationBase() {
	_lpInstance = this;
}

ApplicationBase::~ApplicationBase() {
}

bool ApplicationBase::Initialize(HINSTANCE hInstance) {

	// DX���C�u�����̏�����
	if(AppWindowed()){
		ChangeWindowMode(true);							// �E�B���h�E���[�h�Ɏw�肷��
	}
	SetGraphMode(DispSizeW(), DispSizeH(), 32);

	if (DxLib_Init() == -1)
	{	// �G���[���N�����璼���ɏI��
		return false;
	}
	SetDrawScreen(DX_SCREEN_BACK);		// �`����ʂ𗠉�ʂɃZ�b�g

	// ����������
	srand((unsigned int)time(NULL));

	// ���[�h�T�[�o�̏�����
	_serverMode = new ModeServer();

	return true;
}

bool ApplicationBase::Terminate() {
	// DX���C�u�����J��
	DxLib_End();

	return true;
}

bool ApplicationBase::Input() {
	// �L�[�̓��́A�g���K���͂𓾂�
	return true;
}

bool ApplicationBase::Process() {
	_serverMode->ProcessInit();
	_serverMode->Process();
	_serverMode->ProcessFinish();
	return true;
}

bool ApplicationBase::Render() {
	_serverMode->RenderInit();
	_serverMode->Render();
	_serverMode->RenderFinish();
	return true;
}