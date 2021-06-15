/*****************************************************************
 * \file   Model.h
 * \brief  3D�̓ǂݍ���3D���f���̊��N���X
 * \author momoka
 * \date   2021 6/7
 * \details �����o�֐���*this��Ԃ����ƂŃ��\�b�h�`�F�C���ł��g�� �g�����X�t�H�[���N���X
 *********************************************************************/
#pragma once
#include "Transform.h"
#include <memory>
#include <unordered_map>

class Model {
public:
	Model();
	virtual ~Model();

	//multiple = true : �d������
	virtual bool Load(const TCHAR* fileName, bool multiple = false);

	void Process();
	void Render();

	Transform& GetTransform() {
		return _pModelTransform;
	}

	int GetHandle() {
		return _handle;
	}

protected:
	Transform _pModelTransform;
	//std::unordered_map<int,Transform> _pFrameTransform;

	int _handle;
};