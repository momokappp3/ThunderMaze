/*****************************************************************//**
 * \file   UI2DSelectBase.h
 * \brief  選択されて画像が変更される時に使うクラス
 * \author momoka
 * \date   June 2021
 * \details 選択されたら画像を変更 音を鳴らす
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
    int _lastSelect;  //音を鳴らすために追加
};