/*****************************************************************
 * \file   ModeClear.h
 * \brief  Clear
 * \author momoka
 * \date   2021 6/2
 *********************************************************************/
#pragma once
#include "../../../AppFrame/source/appframe.h"
#include <memory>
#include "../../../AppFrame/source/momoka/Input.h"

class ModeClear : public ModeBase {
public:

	ModeClear();
	virtual ~ModeClear();

	virtual bool Initialize();
	virtual bool Process();
	virtual bool Render();
	virtual bool Terminate();

protected:
	std::unique_ptr<Input> _pKeyInput;
	int _cg;
};