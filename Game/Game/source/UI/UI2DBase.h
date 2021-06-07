/*****************************************************************
 * \file   UI2DBase.h
 * \brief  �摜�̊�{�\���N���X
 * \author momoka
 * \date   2021 6/2
 * \details ���̃N���X���p�����Ă��낢��Ȏg����������
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

	Point GetCenter();  ///�摜�̐^�񒆂�Ԃ�

	int SetDrawInfo(DrawInfo& info) {
		_vDrawInfo.push_back(info);
		return _vDrawInfo.size() - 1;
	}

	bool GetDrawInfo(int index, DrawInfo& info);  //�Q�ƂȂ̂ő������ɏ�񂪓���

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

	std::vector<DrawInfo> _vDrawInfo;   //�n���h����xy�`�悷�邽�߂̏������Ă���
};