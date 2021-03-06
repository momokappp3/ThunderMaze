#include "Transform.h"

float Transform::ToRadian(float angle) {
	return angle * DX_PI_F / 180.f;
}
float Transform::ToAngle(float radian) {
	return radian * 180.0f / DX_PI_F;
}

Transform::Transform() {

	_vScale = { 1.0f, 1.0f, 1.0f };

	_vBaseDirection = { 0.0f, 0.0f, 1.0f };
	_vDirection = _vBaseDirection;

	_vPosition = { 0.0f, 0.0f, 0.0f };

	_mTransform = MGetIdent();
}

Transform::~Transform() {
}

void Transform::Forward(float speed) {

	VECTOR forward = VScale(_vDirection, speed);

	_vPosition = VAdd(_vPosition, forward);
}

void Transform::SetRotateY(float angle) {
	_vDirection = VTransformSR(_vBaseDirection, MGetRotY(ToRadian(angle)));
}

void Transform::AddRotateY(float angle) {
	_vDirection = VTransformSR(_vDirection, MGetRotY(ToRadian(angle)));
}

void Transform::Update() {

	MATRIX scale = MGetScale(_vScale);
	MATRIX posture = MGetRotVec2(_vBaseDirection, _vDirection);  //In1 の向きから In2 の向きへ変換する回転行列
	MATRIX translate = MGetTranslate(_vPosition);  //平行移動行列を取得する

	//MMult = 行列の掛け算
	_mTransform = MMult(MMult(scale, posture), translate);

}