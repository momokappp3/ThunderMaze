#include "UINumber.h"
#include "DxLib.h"

UINumber::UINumber() :UI2DBase() {

	_vNumHandle.clear();

	_point = { 0,0 };

	_num = 0;
	_digitMax = 0;

}

UINumber::~UINumber() {
}

bool UINumber::Init(int digitMax) {

	_digitMax = digitMax;

	SetNumHandle(digitMax);

	return true;
}

void UINumber::Process() {

	SetNumHandle(_num);
}

void UINumber::Draw() {

	//メンバの_pointはメニューの動きで使う
	Point point = _point;

	for (int i = 0; i < _digitMax; i++) {
		if (i != 0) {

			int x = 0, y =0;

			GetGraphSize(_vNumHandle[i - 1], &x, &y);

			point.x -= x; //前の画像の幅を足す
		}

		DrawGraph(point.x, point.y, _vNumHandle[i], TRUE);  //二回目でvnumHandleが入っていない
	}
	_vNumHandle.clear();
}

bool UINumber::SetNumHandle(int num) {

	int maxNum = 1;

	for (int i = 0; i < _digitMax;i++) {
		maxNum *= 10;
	}

	maxNum -= 1;

	if (num < 0 || num > maxNum) {
		return false;
	}

	for (int i = 0; i < _digitMax; i++) {

		int mod = num % 10; // 余りが一の位 最後の桁

		num = num / 10; // 取得済みの余りを"num"から除去

		int handle = UI2DBase::GetHandle(mod);// _vDrawInfo[mod].handle;  //今のハンドルを取り出す

		_vNumHandle.push_back(handle);  //ハンドルが入っていく  
										//[6]の位置に一の位が入っている
	}
}