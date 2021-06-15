/*****************************************************************
 * \file   ModeTitle.h
 * \brief  Titleシーンクラス
 * \author momoka
 * \date   2021 6/2
 *********************************************************************/
#pragma once
#include "../../../AppFrame/source/appframe.h"
#include <memory>
#include"../../../AppFrame/source/momoka/Input.h"
#include "UI/UI2DSelectBase.h"

class ModeTitle : public ModeBase{
public:
	enum class SelectMenu{
		Max = 0,
		NewGame,
		Exit
	};

	ModeTitle();
	virtual ~ModeTitle();

	virtual bool Initialize();
	virtual bool Process();
	virtual bool Render();
	virtual bool Terminate();

protected:
	std::unique_ptr<Input> _pKeyInput;
	std::unique_ptr<UI2DSelectBase> _pNewGameString;
	std::unique_ptr<UI2DSelectBase> _pExitString;

	SelectMenu _nowMenuSelect;

	int _cg;
	bool _isBgm;
}; 