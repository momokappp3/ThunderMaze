/*****************************************************************
 * \file   StrongBox.h
 * \brief  ïÛî†ÇÃÉÇÉfÉãèÓïÒ
 * \author momoka
 * \date   2021 7/1
 *********************************************************************/
#pragma once
#include "../../../../AppFrame/source/momoka/ModelAnimation.h"

class StrongBox {
public:
    StrongBox();
    virtual ~StrongBox();

    bool Init(VECTOR point);
    void Process();
    void Draw();

    void SetPlayerPosition(VECTOR start, VECTOR end) {
        _player3DPosi = start;
        _endPlayerPosi = end;
    }

private:
    std::unique_ptr<ModelAnimation> _pStrongBox;
    VECTOR _point;

    bool _isPopUp;
    bool _isAnim;

    VECTOR _player3DPosi;
    VECTOR _endPlayerPosi;

    VECTOR _vertex1;
    VECTOR _vertex2;
    VECTOR _vertex3;
    VECTOR _vertex3Anime;
};