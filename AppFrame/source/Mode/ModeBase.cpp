#include "ModeBase.h"

ModeBase::ModeBase() {
	_szName = "";
	_uid = 1;
	_layer = 0;

	_cntMode = 0;
	_tmMode = 0;
	_tmStep = 0;
	_tmModeBase = 0;
	_tmPauseBase = 0;
	_tmPauseStep = 0;
	_tmOldFrame = 0;

	SetCallPerFrame(1);
	SetCallOfCount(1);

	_pSoundManager = nullptr;
}

ModeBase::~ModeBase() {
}

bool ModeBase::Initialize() {

	_pSoundManager.reset(new SoundManager);
	_pSoundManager->Init();

	return true;
}

bool ModeBase::Process(){

	_pSoundManager->Process();

	return	true;
}

bool ModeBase::Render(){
	return	true;
}

bool ModeBase::Terminate() {

	return true;
}

// 時間経過をさせる
void ModeBase::StepTime(unsigned long tmNow) {
	// 時間経過処理
	if (_cntMode == 0) {
		_tmMode = 0;
		_tmStep = 0;
		_tmModeBase = tmNow;
		_tmPauseBase = 0;
		_tmPauseStep = 0;
	}
	else {
		_tmMode = tmNow - _tmModeBase + _tmPauseStep;
		_tmStep = tmNow - _tmOldFrame;
	}
	_tmOldFrame = tmNow;
}

// カウントを進める
void ModeBase::StepCount() {
	_cntMode++;
}