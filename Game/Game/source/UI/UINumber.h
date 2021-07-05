/*****************************************************************//**
 * \file   UINumber.h
 * \brief  指定された数字を表示
 * \author momoka
 * \date   2021 6/17
 * \details 初期化で必ず桁数の指定をする
 *********************************************************************/
#pragma once
#include "UI2DBase.h"

class UINumber : public UI2DBase {
public:
    UINumber();
    virtual ~UINumber();

    bool Init(int digitMax);
    void Process()override;
    void Draw() override;

    //一桁目の座標が基準で二桁目から一桁目の画像サイズを足していく
    bool SetNumHandle(int num);

    //基底クラスにあるが紛らわしいのでオーバーロード
    void SetPoint(Point point) {
        _point = point;
    }

    void SetNum(int num){
        _num = num;
    }

private:
    //Drawでクリアしてるのでプロセスで絶対値を入れないといけない

    std::vector<int> _vNumHandle;  //Setした数字のハンドルが入ったベクター

    Point _point;  //一桁目の座標

    int _num;
    int _digitMax;
};