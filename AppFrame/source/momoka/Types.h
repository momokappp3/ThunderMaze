/*****************************************************************
 * \file   Types.h
 * \brief  いろんなクラスで使うenumclass構造体を集めたクラス
 * \author momoka
 * \date   2021 6/2
 *********************************************************************/
#pragma once

struct Point {
	int x;
	int y;
};

struct DrawInfo {
	int handle;
	Point xy;
	bool isDraw;
};