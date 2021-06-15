/*****************************************************************
 * \file   Input.h
 * \brief  キーボードを簡単に呼び出す　静的クラス
 * \author momoka
 * \date   2021 1/21
 * \details 使い方 = if (Input::_key[(KEY_INPUT_RETURN)] == 1) {}
 *********************************************************************/
#pragma once

class Input {
public:
	Input();
	virtual ~Input();

	void Process();

	int _key[256];
};