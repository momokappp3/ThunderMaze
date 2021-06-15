/*****************************************************************
 * \file   Transform.h
 * \brief  3Dモデル変形操作
 * \author momoka
 * \date   2021　6/7
 *********************************************************************/
#pragma once
#include "DxLib.h"
#include <unordered_map>

class Transform {
public:
	static float ToRadian(float angle);  //度からラジアンに
	static float ToAngle(float radian);  //ラジアンから度に

	Transform();
	virtual ~Transform();

	void SetBaseDirection(float x, float y, float z) {
		_vBaseDirection = VNorm(VGet(x, y, z));
	}

	void Forward(float speed);
	void SetRotateY(float angle);
	void AddRotateY(float angle);
	void ADDRotateYFrame(int frame, float angle);
	void Update();

	void SetScale(VECTOR scale) {
		_vScale = VGet(scale.x, scale.y, scale.z);
	}

	void AddScale(float x, float y, float z) {
		_vScale = VGet(_vScale.x + x, _vScale.y + y, _vScale.z + z);
	}

	void SetDirection(VECTOR direction) {
		_vDirection = VNorm(VGet(direction.x, direction.y, direction.z));
		//_vDirection = VGet(direction.x, direction.y, direction.z);
	}

	void AddDirection(float x, float y, float z) {
		_vDirection = VNorm(VGet(_vDirection.x + x, _vDirection.y + y, _vDirection.z + z));
	}

	void SetPosition(VECTOR position) {
		_vPosition = VGet(position.x, position.y, position.z);
	}

	void AddPosition(float x, float y, float z) {
		_vPosition = VGet(_vPosition.x + x, _vPosition.y + y, _vPosition.z + z);
	}

	VECTOR GetScale() const {
		return _vScale;
	}

	VECTOR GetDirection() const {
		return _vDirection;
	}

	VECTOR GetPosition() const {
		return _vPosition;
	}

	MATRIX GetTransform() const {
		return _mTransform;
	}

private:
	VECTOR _vScale;  // 拡大縮小

	VECTOR _vBaseDirection;  //最初の向き(モデルの作りによって違う)
	VECTOR _vDirection;  //向き

	VECTOR _vPosition;  //場所

	MATRIX _mTransform;  //モデル変換行列
};