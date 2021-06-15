/*****************************************************************
 * \file   ModeGame.h
 * \brief  ゲームのメインのクラス描画クラスやモデルクラスを読み込む
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