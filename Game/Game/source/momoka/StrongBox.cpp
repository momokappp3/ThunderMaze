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

    //置く場所をもらう
    _point = point;

	_pStrongBox.reset(new ModelAnimation);
	_pStrongBox->Load("model/boxAnime.mv1");

	if (_pStrongBox->GetHandle() == -1) {
		return false;
	}

	_pStrongBox->AnimationPushBack(0, 1, 0.0f, 3.0f);
	_pStrongBox->AnimationPushBack(0, 2, 0.0f, 3.0f);

	//設置する場所
	//(プレイヤーの二個隣)  (行き止まりに設置する)
	_pStrongBox->GetTransform().SetPosition(_point);
	_pStrongBox->GetTransform().SetScale({ 0.1f, 0.1f, 0.1f });

	_vertex1 = { _point.x - 40.0f,_point.y,_point.z };
	_vertex2 = { _point.x + 40.0f,_point.y,_point.z };
	_vertex3 = { _point.x,_point.y,_point.z + 40.0f };
	_vertex3Anime = { _point.x,_point.y,_point.z + 60.0f };

    return true;
}

void StrongBox::Process() {
	
	//宝箱三角形と線分の当たり判定
	_isPopUp = HitCheck_Line_Triangle(_player3DPosi, _endPlayerPosi, _vertex1, _vertex2, _vertex3).HitFlag == 1;

	//Anime当たり判定
	if (!_isAnim && HitCheck_Line_Triangle(_player3DPosi, _endPlayerPosi, _vertex1, _vertex2, _vertex3Anime).HitFlag) {
		_pStrongBox->PlayAnimation(0);
		_isAnim = true;
	}

	_pStrongBox->Process();
}

void StrongBox::Draw(){

	_pStrongBox->Draw();

	//プレイヤーから伸びた線
	DrawLine3D(_player3DPosi, _endPlayerPosi, GetColor(255, 30, 0));

	//ドアエリアの当たり判定描画(三角)
	DrawTriangle3D(_vertex1, _vertex2, _vertex3, GetColor(255, 255, 0), FALSE);

	//ドアアニメの当たり判定描画(三角)
	DrawTriangle3D(_vertex1, _vertex2, _vertex3Anime, GetColor(255, 30, 0), FALSE);
}