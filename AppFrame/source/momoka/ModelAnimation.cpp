#include "ModelAnimation.h"

ModelAnimation::ModelAnimation() {

    //_vAnimation.size();  //�c�̗v�f�w
    //_vAnimation.at(0).size(); //���̗v�f��

    _vAnimation.clear();
}

ModelAnimation:: ~ModelAnimation() {
}

void ModelAnimation::Process() {





    Model::Process();
}

void ModelAnimation::Draw(){



    Model::Render();
}