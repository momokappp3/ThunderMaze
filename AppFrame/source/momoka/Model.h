/*****************************************************************
 * \file   Model.h
 * \brief  3Dの読み込み3Dモデルの基底クラス
 * \author momoka
 * \date   2021 6/7
 * \details メンバ関数で*thisを返すことでメソッドチェインでを使う トランスフォームクラス
 *********************************************************************/
#pragma once
#include "Transform.h"
#include <memory>

class Model {
public:
	Model();
	virtual ~Model();

	//multiple = true : 重複する
	virtual bool Load(const TCHAR* fileName, bool multiple = false);

	void Process();
	void Render();

	Transform& GetTransform() {
		return _pTransform;
	}

	int GetHandle() {
		return _handle;
	}

protected:
	Transform _pTransform;

	int _handle;
};