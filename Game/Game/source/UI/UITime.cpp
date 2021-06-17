#include "UITime.h"
#include "../../../../AppFrame/source/static/ResourceServer.h"
#include <array>
#include "DxLib.h"

UITime::UITime() {

	_startTime = 0;
	_startNum = 0;
	_nowNum = 0;

	_isStart = false;
	_isStop = false;
	_isEnd = false;
	_isEndNow = false;

	//_pTimeBase = nullptr;
    _pUINumber = nullptr;

    _maxNum = 0;
}

UITime:: ~UITime() {
}

bool UITime::Init(int maxNum ,int digit) {

    _maxNum = maxNum;

    _pUINumber.reset(new UINumber);
	//_pTimeBase.reset(new UI2DBase);

	//int handle = ResourceServer::LoadGraph("png/galUI/numBase.png");
	/*
	if (handle == -1) {
		return false;
	}*/

	//DrawInfo info = { handle,180,195,true};

	//_pTimeBase->SetDrawInfo(info);

	std::array<int, 10> trustHandle{
	ResourceServer::LoadGraph("png/gameUI/number/trust0.png"),
	ResourceServer::LoadGraph("png/gameUI/number/trust1.png"),
	ResourceServer::LoadGraph("png/gameUI/number/trust2.png"),
	ResourceServer::LoadGraph("png/gameUI/number/trust3.png"),
	ResourceServer::LoadGraph("png/gameUI/number/trust4.png"),
	ResourceServer::LoadGraph("png/gameUI/number/trust5.png"),
	ResourceServer::LoadGraph("png/gameUI/number/trust6.png"),
	ResourceServer::LoadGraph("png/gameUI/number/trust7.png"),
	ResourceServer::LoadGraph("png/gameUI/number/trust8.png"),
	ResourceServer::LoadGraph("png/gameUI/number/trust9.png"),
	};
	
	DrawInfo info;

	for (int i = 0; i < 10; i++) {
		info = { trustHandle[i] ,300,270,true};

		_pUINumber->SetDrawInfo(info);
	}
	
	_pUINumber->SetPoint({ 1122,30 });

	_pUINumber->Init(digit);

	DrawInfo infoInit;
	//_pTimeBase->GetDrawInfo(0, infoInit);
	_pUINumber->GetDrawInfo(0, infoInit);

	return true;
}

void UITime::Process() {

	//_pTimeBase->Process();
	_pUINumber->Process();

	if (!_isStart || _isEnd || _isStop) {
		return;
	}

	int nowTime = GetNowCount() - _startTime;
	int nowSecond = nowTime / 1000;
	int nowNum = _startNum - nowSecond;

	if (_nowNum != nowNum) {
		_nowNum = nowNum;

		if (_nowNum < 0) {
			_nowNum = 0;
		}

		if (_nowNum == 0) {
			_isEnd = true;
			_isEndNow = true;
		}

		_pUINumber->SetNum(_nowNum);
	}
	/*
	if (_isEnd) {
		_isEndNow = true;
	}
	*/
}

void UITime::Draw() {
	//_pTimeBase->Draw();
    _pUINumber->Draw();
	_isEndNow = false;
}

void UITime::SetStart(int startNum) {

	_isStart = true;
	_isEnd = false;
	_isStop = false;

	_startNum = startNum;
	_nowNum = startNum;

	_startTime = GetNowCount();  //‹N“®‚µ‚Ä‚©‚ç‚Ç‚ê‚­‚ç‚¢‚½‚Á‚½‚©

	_pUINumber->SetNum(startNum);

}