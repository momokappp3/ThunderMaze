#include "Input.h"
#include "DxLib.h"

Input::Input() {

    for (int i = 0; i < 256; i++) {
        _key[i] = 0;
    }
}

Input::~Input() {
}

void Input::Process(){

    char tmpKey[256];

    GetHitKeyStateAll(tmpKey); // 全てのキーの入力状態を得る

    for (int i = 0; i < 256; i++) {
        if (tmpKey[i] != 0) { // i番のキーコードに対応するキーが押されていたら
            _key[i]++;     // 加算
        }
        else {              // 押されていなければ
            _key[i] = 0;   // 0にする
        }
    }
}