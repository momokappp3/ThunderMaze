/*****************************************************************//**
 * \file   UI2DSelectBase.h
 * \brief  �I������ĉ摜���ύX����鎞�Ɏg���N���X
 * \author momoka
 * \date   June 2021
 * \details �I�����ꂽ��摜��ύX ����炷
 *********************************************************************/
#pragma once
#include "UI2DBase.h"
#include <functional>
#include "../../../../AppFrame/source/momoka/Types.h"

class UI2DSelectBase : public UI2DBase{
public:
    UI2DSelectBase();
    virtual ~UI2DSelectBase();

    void Process()override;
    void Draw() override;

    void SetOnSelect(std::function<void(void)> onSelect) {
        _onSelect = onSelect;
    }
    

    void SetSelect(int select) {
        _select = select;
    }

    int GetSelect() {
        return _select;
    }

private:
    std::function<void(void)> _onSelect;

    int _select;
    int _lastSelect;  //����炷���߂ɒǉ�
};