/*****************************************************************
 * \file   Types.h
 * \brief  いろんなクラスで使うenumclass構造体を集めたクラス
 * \author momoka
 * \date   2021 6/2
 *********************************************************************/
#include<String>
#include<tchar.h>
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

struct PopString {
	std::string string;
	Point xy;
	bool isDraw;
};

//DrawInfoの格納順に紐づけている
enum class ITEM {
	Barrier = 4,
	Portion,
	Through,
	None = 0
};