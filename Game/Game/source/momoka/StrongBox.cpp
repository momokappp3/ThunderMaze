#include "StrongBox.h"

StrongBox::StrongBox() {
    _pStrongBox = nullptr;

	_point = { 0,0,0 };

	_player3DPosi = { 0,0,0 };
	_endPlayerPosi = { 0,0,0 };

	_vertex1 = { 0,0,0 };
	_vertex2 = { 0,0,0 };
	_vertex3 = { 0,0,0 };
	_vertex3Anime = { 0,0,0 };

	_isPopUp = false;
	_isAnim = false;
}

StrongBox::~StrongBox() {
}

bool StrongBox::Init(VECTOR point) {

    //�u���ꏊ�����炤
    _point = point;

	_pStrongBox.reset(new ModelAnimation);
	_pStrongBox->Load("model/boxAnime.mv1");

	if (_pStrongBox->GetHandle() == -1) {
		return false;
	}

	_pStrongBox->AnimationPushBack(0, 1, 0.0f, 3.0f);
	_pStrongBox->AnimationPushBack(0, 2, 0.0f, 3.0f);

	//�ݒu����ꏊ
	//(�v���C���[�̓��)  (�s���~�܂�ɐݒu����)
	_pStrongBox->GetTransform().SetPosition(_point);
	_pStrongBox->GetTransform().SetScale({ 0.1f, 0.1f, 0.1f });

	_vertex1 = { _point.x - 40.0f,_point.y,_point.z };
	_vertex2 = { _point.x + 40.0f,_point.y,_point.z };
	_vertex3 = { _point.x,_point.y,_point.z + 40.0f };
	_vertex3Anime = { _point.x,_point.y,_point.z + 60.0f };

    return true;
}

void StrongBox::Process() {
	
	//�󔠎O�p�`�Ɛ����̓����蔻��
	_isPopUp = HitCheck_Line_Triangle(_player3DPosi, _endPlayerPosi, _vertex1, _vertex2, _vertex3).HitFlag == 1;

	//Anime�����蔻��
	if (!_isAnim && HitCheck_Line_Triangle(_player3DPosi, _endPlayerPosi, _vertex1, _vertex2, _vertex3Anime).HitFlag) {
		_pStrongBox->PlayAnimation(0);
		_isAnim = true;
	}

	_pStrongBox->Process();
}

void StrongBox::Draw(){

	_pStrongBox->Draw();

	//�v���C���[����L�т���
	DrawLine3D(_player3DPosi, _endPlayerPosi, GetColor(255, 30, 0));

	//�h�A�G���A�̓����蔻��`��(�O�p)
	DrawTriangle3D(_vertex1, _vertex2, _vertex3, GetColor(255, 255, 0), FALSE);

	//�h�A�A�j���̓����蔻��`��(�O�p)
	DrawTriangle3D(_vertex1, _vertex2, _vertex3Anime, GetColor(255, 30, 0), FALSE);
}