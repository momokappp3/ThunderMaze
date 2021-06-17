/*****************************************************************//**
 * \file   UITime.h
 * \brief  �b�P�ʂŃJ�E���g�_�E������(����)
 * \author momoka
 * \date   2021 6/16
 * \details SetStart���Ăяo��
 *********************************************************************/
#pragma once
#include "UINumber.h"
#include <memory>
#include "UI2DBase.h"

class UITime {
public:
    UITime();
    virtual ~UITime();

    bool Init(int maxNum ,int digit);
    void Process();
    void Draw();
    void SetStart(int startNum);

    void SetStop(bool stop) {
        _isStop = stop;
    }

    int GetNowTime() {
        return _nowNum;
    }

    bool GetEndNow() {
        return _isEndNow;
    }

private:
    std::unique_ptr<UINumber> _pUINumber;
 
    int _maxNum;

    int _startTime;
    int _startNum;
    int _nowNum;

    bool _isStart;
    bool _isStop;
    bool _isEnd;

    bool _isEndNow;  //�S�t���[�����X�^�[�g�ō��G���h�̎�true;
};