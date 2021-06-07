/*****************************************************************//**
 * \file   MouseInput.h
 * \brief  �}�E�X���̓N���X(���W����p)
 * \author momoka
 * \date   2021 6/2
 * \details Process()Draw()�ÓI�����o�ō\������
 *			Process���ɌĂ��GetLeft()�Ȃǂ̊֐����Ă�
 *			Draw���Ă΂Ȃ��ƃo�O��
 *********************************************************************/
#pragma once
#include "Dxlib.h"

class MouseInput {
public:
	MouseInput();
	virtual ~MouseInput();

	static void Process();
	static void Draw();

	int GetXNum() {
		return _posX;
	}

	int GetYNum() {
		return _posY;
	}

private:

	static int _posX;
	static int _posY;
};