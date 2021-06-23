/*********************************************************************
 * \file   UIItem.h
 * \brief  アイテムを扱うクラス
 * \author momoka
 * \date   2021 6/17
 * \details
 *********************************************************************/
#pragma once
#include "UI2DBase.h"
#include "../momoka/Item.h"

class UIItem : public UI2DBase{
public:
    UIItem();
    virtual ~UIItem();

    bool Init();
    void Process();
    void Draw();

    void SetUpperItem(ITEM item) {
        _upperItem = static_cast<int>(item);
    }

    void SetMiddleItem(ITEM item) {
        _middleItem = static_cast<int>(item);
    }

    void SetDownItem(ITEM item) {
        _downItem = static_cast<int>(item);
    }

private:

    int _upperItem;
    int _middleItem;
    int _downItem;
};