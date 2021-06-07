#include "MouseInput.h"
#include "DxLib.h"

int MouseInput::_posX;
int MouseInput::_posY;

MouseInput::MouseInput() {

	SetMouseDispFlag(TRUE);

	_posX = 0;
	_posY = 0;
}

MouseInput::~MouseInput() {
}

void MouseInput::Process(){

	GetMousePoint(&_posX, &_posY);  //�}�E�X�|�C���^�̍��W���擾
}

void MouseInput::Draw() {

	DrawFormatString(20, 500, GetColor(255, 255, 255), "�}�E�X�̍��W( %d, %d )", _posX, _posY);
}