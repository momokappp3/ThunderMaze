#include "UI2DSelectBase.h"
#include "Dxlib.h"

UI2DSelectBase::UI2DSelectBase() :UI2DBase() {

	_select = 0;
	_lastSelect = -1;
	_onSelect = nullptr;
}

UI2DSelectBase::~UI2DSelectBase() {
}

void UI2DSelectBase::Process() {

	if (_lastSelect == 0 && _select == 1) {
		if (_onSelect != nullptr) {
			_onSelect();
		}
	}

	_lastSelect = _select;
}

void UI2DSelectBase::Draw() {

	if (_vDrawInfo.size() == 0 || _select < 0 || _select >= _vDrawInfo.size()) {
		return;
	}

	for (const DrawInfo& info : _vDrawInfo) {    //ベクターの中身が情報が入って最後まで処理
		if (!info.isDraw) {
			return;
		}
	}

	DrawInfo info = _vDrawInfo[_select];

	DrawGraph(info.xy.x, info.xy.y, info.handle, TRUE);
}