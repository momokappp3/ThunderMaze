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

class ModelAnimation : public Model{
public:
    ModelAnimation();
    virtual ~ModelAnimation();

    struct ANIM_INFO {

        int animHandle;
        int playTime;
        float animSpead;
    };

    void Process();
    void Draw();

    bool AnimationPushBack(int num, int anim,int playTime,int animSpead) {

        int handle = MV1AttachAnim(_handle, anim, -1, FALSE);

        if (handle == -1) {
            return false;
        }

        ANIM_INFO info = { handle,playTime,animSpead };

        _vAnimation[num].push_back(info);

        return true;
    }

    void PlayAnimation(int num, int element) {

        for (int i = 0; i < _vAnimation.at(element).size(); i++) {
            MV1SetAttachAnimTime(_handle, i, _vAnimation[num][element].playTime);
        }
    }

private:
        
    std::vector<std::vector<ANIM_INFO>> _vAnimation;  //1��ōĐ�����A�j���[�V�������

};