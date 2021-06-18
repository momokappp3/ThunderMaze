/*****************************************************************//**
 * \file   UITime.h
 * \brief  カウントダウンする(数字描画)
 * \author momoka
 * \date   2021 6/16
 * \details SetStartを呼び出す
 *********************************************************************/
#pragma once
#include "UINumber.h"
#include <memory>
#include "UI2DBase.h"
#include "../../../../AppFrame/source/static/Timer.h"

class UITime {
public:
    UITime();
    virtual ~UITime();

    bool Init();
    void Process();
    void Draw();
    void SetStart(int minutes, int seconds);

    void SetStop(bool stop) {
        _isStop = stop;
    }

    bool GetEndNow() {
        return _isTimeEnd;
    }

private:
    std::unique_ptr<Timer> _pTimer;
    std::unique_ptr<UINumber> _pUIMinutes;
    std::unique_ptr<UI2DBase> _pCenter;
    std::unique_ptr<UINumber> _pUISeconds;

    int _maxNum;

    bool _isStop;
    bool _isEnd;

    bool _isTimeEnd;  //全フレームがスタートで今エンドの時true;
};