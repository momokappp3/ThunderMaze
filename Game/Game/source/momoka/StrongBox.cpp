#include "StrongBox.h"
#include"../../../../AppFrame/source/static/MTRandom.h"

StrongBox::StrongBox() {
    _pStrongBox = nullptr;
	_pSoundManager = nullptr;

	_point = { 0,0,0 };

	_player3DPosi = { 0,0,0 };
	_endPlayerPosi = { 0,0,0 };

	_vertex1 = { 0,0,0 };
	_vertex2 = { 0,0,0 };
	_vertex3 = { 0,0,0 };
	_vertex3Anime = { 0,0,0 };

	_isPopUp = false;
	_isAnim = false;
	_isItem = true;

	_itemNum = -1;
}

StrongBox::~StrongBox() {
}

bool StrongBox::Init(std::shared_ptr<SoundManager>sound,VECTOR point) {

	_pSoundManager = sound;

	if (_pSoundManager == nullptr) {
		return false;
	}
	if (_pSoundManager != nullptr) {
		bool seTitle = _pSoundManager->LoadSEInGame();

		if (!seTitle) {
			return false;
		}
	}
	else {
		return false;
	}

    //�u���ꏊ�����炤
    _point = point;

	_pStrongBox.reset(new ModelAnimation);
	_pStrongBox->Load("model/boxAnime5.mv1",true);

	if (_pStrongBox->GetHandle() == -1) {
		return false;
	}

	_pStrongBox->AnimationPushBack(0, 0, 0.0f, 0.8f);  //��
	_pStrongBox->AnimationPushBack(0, 3, 0.0f, 0.9f);  //�J��  

	//�ݒu����ꏊ
	//(�v���C���[�̓��)  (�s���~�܂�ɐݒu����)
	_pStrongBox->GetTransform().SetPosition(_point);
	_pStrongBox->GetTransform().SetScale({ 0.18f, 0.18f, 0.18f });
	_pStrongBox->GetTransform().SetDirection({ 0.0f,0.0f,120.0f });

	_vertex1 = { _point.x - 20.0f,_point.y,_point.z };
	_vertex2 = { _point.x + 20.0f,_point.y,_point.z };
	_vertex3 = { _point.x,_point.y,_point.z - 100.0f };
	_vertex3Anime = { _point.x,_point.y,_point.z - 50.0f };

	//=============================================
	//�����_���ŃA�C�e�������ɂ��邩���߂�
	//�ێ�(4�`6)
	_itemNum = MTRandom::Get(4, 6);

    return true;
}

void StrongBox::Process() {
	
	//�󔠎O�p�`�Ɛ����̓����蔻��
	_isPopUp = HitCheck_Line_Triangle(_player3DPosi, _endPlayerPosi, _vertex1, _vertex2, _vertex3Anime).HitFlag == 1;

	//Anime�����蔻��
	if (!_isAnim && HitCheck_Line_Triangle(_player3DPosi, _endPlayerPosi, _vertex1, _vertex2, _vertex3).HitFlag) {
		_pStrongBox->PlayAnimation(0);
		_pSoundManager->PlaySEInGame(SoundManager::InGame::BoxOpen);
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