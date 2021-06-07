/*****************************************************************
 * \file   UI2DBase.h
 * \brief  画像の基本表示クラス
 * \author momoka
 * \date   2021 6/2
 * \details このクラスを継承していろいろな使い方をする
 *********************************************************************/
#pragma once
#include "../../../../AppFrame/source/momoka/Types.h"
#include <vector>
#include <memory>

class UI2DBase {
public:
	UI2DBase();
	virtual ~UI2DBase();
	
	virtual bool Init();
	virtual void Process();
	virtual void Draw();

	Point GetCenter();  ///画像の真ん中を返す

	int SetDrawInfo(DrawInfo& info) {
		_vDrawInfo.push_back(info);
		return _vDrawInfo.size() - 1;
	}

	bool GetDrawInfo(int index, DrawInfo& info);  //参照なので第二引数に情報が入る

	void SetPoint(int index, Point point) {
		_vDrawInfo[index].xy = point;
	}

	Point GetPoint() {
		return _vDrawInfo[0].xy;
	}

	void SetDraw(int index,bool draw) {
		_vDrawInfo[index].isDraw = draw;
	}

	int GetHandle(int index) {
		return _vDrawInfo[index].handle;
	}

protected:

	std::vector<DrawInfo> _vDrawInfo;   //ハンドルとxy描画するための情報を入れている
};