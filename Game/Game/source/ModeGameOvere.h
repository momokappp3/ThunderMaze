/*****************************************************************//**
 * \file   ModeGameOvere.h
 * \brief  GameOvereシーンクラス
 * \author momoka
 * \date   2021 7/12
 *********************************************************************/
#pragma once
#include "../../../AppFrame/source/appframe.h"
#include "../../../AppFrame/source/momoka/Input.h"

class ModeGameOvere:public ModeBase {
public:
	ModeGameOvere();
	virtual ~ModeGameOvere();

	virtual bool Initialize();
	virtual bool Process();
	virtual bool Render();
	virtual bool Terminate();

protected:
	std::unique_ptr<Input> _pKeyInput;
	int _cg;
};