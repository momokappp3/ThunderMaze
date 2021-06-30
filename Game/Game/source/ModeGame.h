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
#include "../../../AppFrame/source/momoka/SoundManager.h"
#include "UI/UIHpGauge.h"
#include "UI/UITime.h"
#include "UI/UIItem.h"
#include "momoka/Item.h"


class ModeGame : public ModeBase{
public:
	ModeGame();
	virtual ~ModeGame();
	virtual bool Initialize();
	virtual bool Process();
	virtual bool Render();
	virtual bool Terminate();
private:

	std::unique_ptr<Input> _pKeyInput;
	std::unique_ptr<MazeStage> _pMazeStage;
	std::unique_ptr<UIPopUp> _pUIPopUp;
	std::unique_ptr<UIHpGauge> _pHp;
	std::unique_ptr<UITime> _pUITime;
	std::unique_ptr<UIItem> _pUIItem;
	std::unique_ptr<Item> _pItem;

	bool _isBGM;
	bool _isAnimEnd;

	float _playTime;

	int _attachDoorIndexRight;
	int _attachDoorIndexLeft;

	int _hpNum;
}; 