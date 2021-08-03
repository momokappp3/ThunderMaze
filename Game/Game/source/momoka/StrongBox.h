/*****************************************************************
 * \file   StrongBox.h
 * \brief  �󔠂̃��f�����
 * \author momoka
 * \date   2021 7/1
 *********************************************************************/
#pragma once
#include "../../../../AppFrame/source/momoka/ModelAnimation.h"
#include"Item.h"

class StrongBox {
public:
    StrongBox();
    virtual ~StrongBox();

    bool Init(std::shared_ptr<SoundManager> sound,VECTOR point, NoPassageType type);
    void Process();
    void Draw();

    void SetPlayerPosition(VECTOR start, VECTOR end) {
        _player3DPosi = start;
        _endPlayerPosi = end;
    }

    bool GetIsPopUp() {
        return _isPopUp;
    }

    bool GetIsItem() {
        return _isItem;
    }

    void SetIsItem(bool item) {
        _isItem = item;
    }

    ITEM GetItemNum() {
        return static_cast<ITEM>(_itemNum);
    }

    void SetSetDirection(int num) {
       
    }

private:
    std::unique_ptr<ModelAnimation> _pStrongBox;
    std::shared_ptr<SoundManager> _pSoundManager;
    VECTOR _point;

    VECTOR _player3DPosi;
    VECTOR _endPlayerPosi;

    VECTOR _vertex1;
    VECTOR _vertex2;
    VECTOR _vertex3;
    VECTOR _vertex3Anime;

    bool _isPopUp;  //popUp�G���A�ɓ����Ă��邩���Ȃ���
    bool _isAnim;  //�A�j���[�V����������
    bool _isItem;  //�A�C�e�����������Ă��邩���Ă��Ȃ���

    int _itemNum;  //�A�C�e��Type
};