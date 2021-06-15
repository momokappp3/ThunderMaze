/*****************************************************************
 * \file   ModeGame.h
 * \brief  �Q�[���̃��C���̃N���X�`��N���X�⃂�f���N���X��ǂݍ���
 * \author momoka
 * \date   2021 5/28
 *********************************************************************/
#pragma once
#include "../../../AppFrame/source/appframe.h"
#include <memory>
#include "MazeStage.h"
#include"UI/UIPopUp.h"
#include "../../../AppFrame/source/momoka/Input.h"

class ModeGame : public ModeBase{
public:
	ModeGame();
	virtual ~ModeGame();
	virtual bool Initialize();
	virtual bool Process();
	virtual bool Render();
	virtual bool Terminate();
protected:

	std::unique_ptr<Input> _pKeyInput;
	std::unique_ptr<MazeStage> _pMazeStage;
	std::unique_ptr<UIPopUp> _pUIPopUp;
}; 