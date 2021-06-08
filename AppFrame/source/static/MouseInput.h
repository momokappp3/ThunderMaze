/*****************************************************************
 * \file   MouseInput.h
 * \brief  マウス入力クラス(座標見る用)
 * \author momoka
 * \date   2021 6/2
 * \details 静的メンバで構成する
 *			Processを一番先に呼ばないとバグる
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