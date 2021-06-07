/*****************************************************************//**
 * \file   MazeStage.h
 * \brief  ステージを生成するクラス
 * \author momoka
 * \date 2021 5/28
 * details
 *********************************************************************/
#pragma once
#include "Dxlib.h"
#include "../../../AppFrame/source/momoka/Model.h"
#include <memory>

class MazeStage{
public:
	virtual bool Initialize();
	virtual bool Terminate();
	virtual bool Process();
	virtual bool Render();

	void GetModeCount(int num) {
		_modeCount = num;
	}

protected:

	std::unique_ptr<Model> _pDoor;

	static const int CHIP_W = 16;
	static const int CHIP_H = 16;

	// 画像一覧
	enum {
		ECG_CHIP_BLACK = 0,
		ECG_CHIP_WHITE,
		ECG_CHIP_BROWN,
		ECG_CHIP_RED,
		ECG_CHIP_BLUE,
		ECG_CHIP_GREEN,

		ECG_STAR,
		ECG_HEART,

		_ECG_EOT_	// End of table.
	};

	int	cg[_ECG_EOT_];

	// 迷路の大きさとマップデータ
	// サイズは奇数のみ
	static const int MAZE_W = 79;
	static const int MAZE_H = 43;
	char maze[MAZE_H * MAZE_W];

	// 主人公位置
	int plx, ply;

	// ゴール位置
	int glx, gly;

	// 主人公の移動歩数サーチ数
	int route_search = 8;

	// 指定位置からの歩数情報格納配列
	int  mazeroute_c[MAZE_W * MAZE_H];

	// 指定位置から指定位置までの最短距離ルート格納配列
	char mazeroute_f[MAZE_W * MAZE_H];

	// デバッグ用
	int search_time_ms = 0, search_call_cnt = 0;	// サーチ経過時間,サーチ呼び出し回数
	int draw_route_c = 0;		// mazeroute_c[]を描画するか否か
	int draw_checkroute = 0;	// CheckRoute()中に描画するか否か
	int draw_route_f = 0;		// mazeroute_f[]を描画するか否か
	int draw_makeroute = 0;		// MakeRoute()中に描画するか否か

	// 3D表示用
	int play_mode = 0;		// 0:2D, 1:3D
	VECTOR vPlayer;		// プレイヤー座標
	VECTOR vDir;		// 向いている方向
	float playerSpeed;	// 1フレームの移動力


	// 関数群
	void GameDraw();
	void StageInit();
	void _CheckChipRoute(int x1, int y1, int x2, int y2, int cntmax);
	int CheckChipRoute(int x1, int y1, int x2, int y2, int cntmax);
	int MakeShortRoute(int x1, int y1, int x2, int y2, int cntmax);

	int _modeCount;
};