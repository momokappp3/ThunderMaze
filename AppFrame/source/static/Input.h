/*****************************************************************
 * \file   Input.h
 * \brief  �L�[�{�[�h���ȒP�ɌĂяo���@�ÓI�N���X
 * \author momoka
 * \date   2021 1/21
 * \details �S�ĐÓI�����o�ō\������
 *			�g���� = if (Input::_key[(KEY_INPUT_RETURN)] == 1) {}
 *********************************************************************/
#pragma once

class Input {
public:
	Input();
	virtual ~Input();

	static void Process();

	static int _key[256];
	static int _longKey[256];
};