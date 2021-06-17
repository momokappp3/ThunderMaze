/*********************************************************************
 * \file   UIItem.h
 * \brief  アイテムを扱うクラス
 * \author momoka
 * \date   2021 6/17
 *********************************************************************/
#pragma once
#include "UI2DBase.h"

class UIItem : public UI2DBase{
public:
    UIItem();
    virtual ~UIItem();

    bool Init();
    void Process();
    void Draw();

private:

    //ハンドルに紐づけられる
    enum class ITEM{
        Barrier = 4,
        Portion,
        Through
    };



};