#include "ModelAnimation.h"

ModelAnimation::ModelAnimation() {

    //_vAnimation.size();  //縦の要素層
    //_vAnimation.at(0).size(); //横の要素数

    _vAnimation.clear();

    for (int i = 0; i < AnimSetMax; i++) {

        std::vector<ANIM_INFO> list = {};

        _vAnimation.emplace_back(std::move(list));  //ローカル変数だったから
        
        _vIsAnim[i] = false;
    }
}

ModelAnimation:: ~ModelAnimation() {
}

void ModelAnimation::Process() {

    Model::Process();
}

void ModelAnimation::Draw(){

    for (int y = 0; y < _vAnimation.size(); y++) {
        if (_vIsAnim[y]) {  //y方向がtrueだったら
            for (int x = 0; x < _vAnimation.at(y).size(); x++) {
                auto info = _vAnimation[y][x];

                if (/*info.playTime <= 60.0f*/true) {
                    info.playTime += info.animSpead;
                    MV1SetAttachAnimTime(_handle, info.animHandle, info.playTime);
                    _vAnimation[y][x] = info;
                }
            }
        }
    }

    Model::Render();
}