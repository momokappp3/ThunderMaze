/*****************************************************************//**
 * \file   MazeStage.h
 * \brief  �X�e�[�W�𐶐�����N���X
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

	// �摜�ꗗ
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

	// ���H�̑傫���ƃ}�b�v�f�[�^
	// �T�C�Y�͊�̂�
	static const int MAZE_W = 79;
	static const int MAZE_H = 43;
	char maze[MAZE_H * MAZE_W];

	// ��l���ʒu
	int plx, ply;

	// �S�[���ʒu
	int glx, gly;

	// ��l���̈ړ������T�[�`��
	int route_search = 8;

	// �w��ʒu����̕������i�[�z��
	int  mazeroute_c[MAZE_W * MAZE_H];

	// �w��ʒu����w��ʒu�܂ł̍ŒZ�������[�g�i�[�z��
	char mazeroute_f[MAZE_W * MAZE_H];

	// �f�o�b�O�p
	int search_time_ms = 0, search_call_cnt = 0;	// �T�[�`�o�ߎ���,�T�[�`�Ăяo����
	int draw_route_c = 0;		// mazeroute_c[]��`�悷�邩�ۂ�
	int draw_checkroute = 0;	// CheckRoute()���ɕ`�悷�邩�ۂ�
	int draw_route_f = 0;		// mazeroute_f[]��`�悷�邩�ۂ�
	int draw_makeroute = 0;		// MakeRoute()���ɕ`�悷�邩�ۂ�

	// 3D�\���p
	int play_mode = 0;		// 0:2D, 1:3D
	VECTOR vPlayer;		// �v���C���[���W
	VECTOR vDir;		// �����Ă������
	float playerSpeed;	// 1�t���[���̈ړ���


	// �֐��Q
	void GameDraw();
	void StageInit();
	void _CheckChipRoute(int x1, int y1, int x2, int y2, int cntmax);
	int CheckChipRoute(int x1, int y1, int x2, int y2, int cntmax);
	int MakeShortRoute(int x1, int y1, int x2, int y2, int cntmax);

	int _modeCount;
};