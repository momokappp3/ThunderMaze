/*****************************************************************//**
 * \file   Timer.h
 * \brief  秒でカウントダウンする
 * \author momoka
 * \date   2021 6/18
 *********************************************************************/
#pragma once
#include "../momoka/Types.h"

class Timer{
public:
    Timer();
    virtual ~Timer();

    void Process();

    bool GetIsEnd();

    void SetStartSeconds(int startNum);
    void SetStartMinutes(int minutes, int seconds);

    int GetNowTimeSeconds();
    Point GetNowTimeMinutes();

    void AddTime(int seconds) {
        _startNum += seconds;
    }

private:
    int _startTime;
    int _startNum;
    int _nowNum;

    bool _isStart;
    bool _isStop;
    bool _isEnd;
};