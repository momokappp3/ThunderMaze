/*****************************************************************
 * \file   ResourceServer.h
 * \brief  (共有リソースを制御するためのサーバ) 画像と3Dモデルの入れ物クラス
 * \author momoka Fuhita
 * \date   2021 5/28
 * @details すべて静的メンバで構成する
 *			LoadGraphをmapを使った配列に例 _mapGraph[/png/player.png]の中身識別番号
**************************************/
#pragma once
#include <unordered_map>   //決められた順序で並んでいない
#include<Tchar.h>

class ResourceServer {
public:
	static void	Init();   //staticだとインスタンスなしで呼べる
	static void	Release();
	static void	ClearGraph();

	static int MV1LoadModel(const TCHAR* FileName,bool multiple);
	static bool DeleteModel(int handle);

	//2D
	static int LoadGraph(const TCHAR* FileName);
	static int DerivationGraph(int x, int y, int width, int height, int handle, const TCHAR* FileName);
	static bool DeleteGraph(int handle);
};