#include "DxLib.h"
#include <vector>
#include "ResourceServer.h"

namespace {
    // 静的メンバ実体
    std::unordered_map<std::string, int> _mapGraph3D;  //ファイル名 識別番号
    std::unordered_map<std::string, int> _mapGraph2D;
}

void ResourceServer::Init() {
    _mapGraph3D.clear();
}

void ResourceServer::Release() {   //ここをどうしてするのか
    ClearGraph();
}

void ResourceServer::ClearGraph() {

    // すべてのデータの削除をする
    for (auto itr = _mapGraph3D.begin(); itr != _mapGraph3D.end(); itr++) {
        MV1DeleteModel(itr->second);   //ここで削除してからclear
    }
    _mapGraph3D.clear();
}

//拡張　複数のインスタンスを生成する場合そのままハンドルを返す
int ResourceServer::MV1LoadModel(const TCHAR* FileName,bool multiple) {

    if (!multiple) {
        // キーの検索
        auto itr = _mapGraph3D.find(FileName);  //引数のファイル名のキーの位置

        if (itr != _mapGraph3D.end()) {   //最終要素の次ではなかったら　　ここの説明
            // キーがあった
            return itr->second;   //second = ハンドル
        }
    }

    int cg = DxLib::MV1LoadModel(FileName);     // DXLIBのAPIを呼ぶので、::を先頭に付け、このクラスの同じ名前の関数と区別する

    if (!multiple) {
        // キーとデータをmapに登録
        _mapGraph3D[FileName] = cg;
    }

    return cg;   //識別番号を返す
}

bool ResourceServer::DeleteModel(int handle) {

    if (handle == -1) {
        return false;
    }

    for (auto itr = _mapGraph3D.begin(); itr != _mapGraph3D.end(); itr++) {
        if (itr->second == handle) {
            DxLib::MV1DeleteModel(handle);

            _mapGraph3D.erase(itr);

            return true;
        }
    }

    return false;
}

//2D
int ResourceServer::LoadGraph(const TCHAR* FileName) {

    // キーの検索
    auto itr = _mapGraph2D.find(FileName);  //引数のファイル名のキーの位置

    if (itr != _mapGraph2D.end()) {   //最終要素の次ではなかったら　　ここの説明

        // キーがあった
        return itr->second;   //second = ハンドル
    }


    int cg = DxLib::LoadGraph(FileName);     // DXLIBのAPIを呼ぶので、::を先頭に付け、このクラスの同じ名前の関数と区別する

        // キーとデータをmapに登録
    _mapGraph2D[FileName] = cg;

    return cg;   //識別番号を返す
}

bool ResourceServer::DeleteGraph(int handle) {

    if (handle == -1) {
        return false;
    }

    for (auto itr = _mapGraph2D.begin(); itr != _mapGraph2D.end(); itr++) {
        if (itr->second == handle) {
            DxLib::DeleteGraph(handle);

            _mapGraph2D.erase(itr);

            return true;
        }
    }

    return false;
}