#include "UITime.h"
#include "../../../../AppFrame/source/static/ResourceServer.h"
#include <array>
#include "DxLib.h"

UITime::UITime() {

	_isStop = false;
	_isEnd = false;
	_isTimeEnd = false;

	_pTimer = nullptr;
	_pUIMinutes = nullptr;
	_pCenter = nullptr;
    _pUISeconds = nullptr;

    _maxNum = 0;
}

UITime:: ~UITime() {
}

bool UITime::Init() {

	_pTimer.reset(new Timer);
	_pUIMinutes.reset(new UINumber);
	_pCenter.reset(new UI2DBase);
    _pUISeconds.reset(new UINumber);

	int handle = ResourceServer::LoadGraph("png/gameUI/number/time_center.png");
	
	if (handle == -1) {
		return false;
	}

	DrawInfo info = { handle,1080,20,true};  //:

	_pCenter->SetDrawInfo(info);

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

	for (int i = 0; i < 10; i++) {
		info = { trustHandle[i] ,0,0,true};

		_pUISeconds->SetDrawInfo(info);
		_pUIMinutes->SetDrawInfo(info);
	}
	
	_pUIMinutes->SetPoint({1000,20});  //•ª
	_pUISeconds->SetPoint({ 1180,20 });  //•b

	_pUIMinutes->Init(1);
	_pUISeconds->Init(2);

	return true;
}

void UITime::Process() {

	Point time = _pTimer->GetNowTimeMinutes();  //•Ô‚è’l‚ª‚¨‚©‚µ‚¢

	_pUIMinutes->SetNum(time.x);
	_pUISeconds->SetNum(time.y);
	
	if (time.x == 0 && time.y ==0 ) {
		_isTimeEnd = true;
	}

	_pUIMinutes->Process();
	_pCenter->Process();
	_pUISeconds->Process();
	_pTimer->Process();
}

void UITime::Draw() {
	_pUIMinutes->Draw();
	_pCenter->Draw();
    _pUISeconds->Draw();
}

void UITime::SetStart(int minutes, int seconds) {

	_isEnd = false;
	_isStop = false;

	_pTimer->SetStartMinutes(minutes,seconds);

	_pUIMinutes->SetNum(minutes);
	_pUISeconds->SetNum(seconds);
}