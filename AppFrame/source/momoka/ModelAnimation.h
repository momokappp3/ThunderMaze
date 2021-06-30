/*****************************************************************
 * \file   ModelAnimation.h
 * \brief  ���f���N���X�ɃA�j���[�V�����@�\��ǉ���������
 * \author momoka
 * \date   2021 6/21
  * \details ���N���X��Load��Y��Ȃ��悤��
  * �@�@�@�@ Init��pushBack�֐��œo�^ �v�f�� = �A�j���[�V������Z�b�g
 *********************************************************************/
#pragma once
#include "Model.h"
#include <vector>
#include <array>

class ModelAnimation : public Model{
public:
    static constexpr int AnimSetMax = 3;
    ModelAnimation();
    virtual ~ModelAnimation();

    struct ANIM_INFO {

        int animHandle;
        float playTime;
        float animSpead;
    };

    void Process();
    void Draw();

    //Init
    bool AnimationPushBack(int num, int anim,float playTime,float animSpead) {

        if (num >= AnimSetMax) {
            return false;
        }

        int handle = MV1AttachAnim(_handle, anim, -1, FALSE);

        if (handle == -1) {
            return false;
        }

        ANIM_INFO info = { handle,playTime,animSpead };
        _vAnimation[num].emplace_back(info);

        return true;
    }

    //�A�j���[�V�������������Ƃ�
    void PlayAnimation(int num) {

        _vIsAnim[num] = true;
    }

private:
        
    std::vector<std::vector<ANIM_INFO>> _vAnimation;  //1��ōĐ�����A�j���[�V�������
    std::array<bool, AnimSetMax> _vIsAnim;
};