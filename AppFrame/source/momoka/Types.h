/*****************************************************************
 * \file   Types.h
 * \brief  �����ȃN���X�Ŏg��enumclass�\���̂��W�߂��N���X
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

//DrawInfo�̊i�[���ɕR�Â��Ă���
enum class ITEM {
	Barrier = 4,
	Portion,
	Through,
	None = 0
};