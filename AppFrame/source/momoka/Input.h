/*****************************************************************
 * \file   Input.h
 * \brief  �L�[�{�[�h���ȒP�ɌĂяo���@�ÓI�N���X
 * \author momoka
 * \date   2021 1/21
 * \details �g���� = if (Input::_key[(KEY_INPUT_RETURN)] == 1) {}
 *********************************************************************/
#pragma once

class Input {
public:
	Input();
	virtual ~Input();

	void Process();

	int _key[256];
};