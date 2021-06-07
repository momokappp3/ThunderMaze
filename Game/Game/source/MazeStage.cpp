/*
** �E�}�b�v��`�悷�錳
** �E�}�b�v��������������
** �E��l���ƃS�[���̐ݒ�A�ړ��A������
** �E��l������A�ړ��ł�������͈͂��`�F�b�N
** �E�S�[�������l���̈ʒu�܂ł̍ŒZ���[�g�𒲂ׂ�
*/

#include "MazeStage.h"
#include "../../../AppFrame/source/Mode/ModeBase.h"
#include "../../../AppFrame/source/static/ResourceServer.h"
#include "ApplicationMain.h"
#include "ModeGame.h"
#include "../../../AppFrame/source/static/Input.h"

// 3D�p
#define BLOCK_SIZE 80.0f			// �u���b�N�̃T�C�Y
#define CAMERA_Y (BLOCK_SIZE/2.f)	// �J�����̍���
#define	MOVE_BLOCK_SPEED 10.f		// 1�u���b�N�ړ�����t���[����

bool MazeStage::Initialize() {

	cg[ECG_CHIP_BLACK] = ResourceServer::LoadGraph("png/stage/chip_black.png");
	cg[ECG_CHIP_WHITE] = ResourceServer::LoadGraph("png/stage/chip_white.png");
	cg[ECG_CHIP_BROWN] = ResourceServer::LoadGraph("png/stage/chip_brown.png");
	cg[ECG_CHIP_RED] = ResourceServer::LoadGraph("png/stage/chip_red.png");
	cg[ECG_CHIP_BLUE] = ResourceServer::LoadGraph("png/stage//chip_blue.png");
	cg[ECG_CHIP_GREEN] = ResourceServer::LoadGraph("png/stage/chip_green.png");
	cg[ECG_STAR] = ResourceServer::LoadGraph("png/stage/star.png");
	cg[ECG_HEART] = ResourceServer::LoadGraph("png/stage/heart.png");

	StageInit();  	// �X�e�[�W������

	// �v���C���[�ʒu���A��[�i�̂ЂƂ����j����I��
	while (1) {
		plx = ((rand() % MAZE_W / 2)) * 2 + 1;
		ply = 1;
		if (maze[ply * MAZE_W + plx] == 0) {
			break;
		}
	}

	// �S�[���ʒu���A���[����I��
	glx = ((rand() % (MAZE_W - 1) / 2)) * 2 + 1;
	gly = MAZE_H - 1;
	maze[gly * MAZE_W + glx] = 0;	// �����J����

	//�S�[���Ƀh�A���f����ݒu
	_pDoor.reset(new Model);
	_pDoor->Load("model/door.mv1");

	if (_pDoor->GetHandle() == -1) {
		return false;
	}

	//�����󂯂��ꏊ�̍��W��3D���W�ɕϊ�
	_pDoor->GetTransform().SetPosition({ BLOCK_SIZE * glx, 0.0f, BLOCK_SIZE * -gly });
	_pDoor->GetTransform().SetScale({ 0.4f, 0.4f, 0.4f });

	return true;
}

void MazeStage::StageInit() {
	// ���H�𐶐�����
	int x, y;

	// �S����ǂŖ��߂�
	for (y = 0; y < MAZE_H; y++) {
		for (x = 0; x < MAZE_W; x++) {
			maze[y * MAZE_W + x] = 1;
		}
	}

	// startpos�����肷��B�K���O�����B
	while (1) {
		x = (rand() % (MAZE_W / 2)) * 2 + 1;
		y = (rand() % (MAZE_H / 2)) * 2 + 1;
		if (x == 1 || x == MAZE_W - 2 || y == 1 || y == MAZE_H - 2) { break; }
	}

	// ���x�X�^�[�g
	while (1) {
		int f = 1;
		int vtbl[][2] = {
			{ 0, -1 }, { 0, 1 }, { -1, 0 }, { 1, 0 },
		};
		while (1) {
			int v, nx, ny, i;
			// �����Ō��肵�������ɕ����Ă����B�ǂ̊O�ɏo��Ȃ�������肵�Ȃ���
			v = rand() % 4;
			nx = x + vtbl[v][0] * 2;
			ny = y + vtbl[v][1] * 2;
			if (nx < 0 || nx >= MAZE_W || ny < 0 || ny >= MAZE_H) {
				continue;
			}
			// ���߂��ꏊ�͂��łɌ����@���Ă��邩�H
			if (maze[ny * MAZE_W + nx] == 0) {
				// �@���Ă���̂ŏI��
				break;
			}
			// ���߂��ꏊ�ƍ��̏ꏊ�̊Ԃ𖄂߂�
			maze[y * MAZE_W + x] = 0;
			for (i = 0; i < 2; i++) {
				x += vtbl[v][0];
				y += vtbl[v][1];
				maze[y * MAZE_W + x] = 0;
			}

			// �f�o�b�O�p�`��
			// ����������ƁA�}�b�v������Ă������܂�������
		//	GameDraw();

		}
		// �S�ӏ������@�������H
		for (y = 1; y < MAZE_H; y += 2) {
			for (x = 1; x < MAZE_W; x += 2) {
				if (maze[y * MAZE_W + x] != 0) {
					f = 0;
				}
			}
		}
		if (f) {
			// �S�ӏ��@���Ă���̂ŏI��
			break;
		}
		// ���̃X�^�[�g�n�_���A�@���Ă���ꏊ����I��
		while (1) {
			x = (rand() % (MAZE_W / 2)) * 2 + 1;
			y = (rand() % (MAZE_H / 2)) * 2 + 1;
			if (maze[y * MAZE_W + x] == 0) {
				break;
			}
		}
	}
}

bool MazeStage::Process() {

	int key = ApplicationMain::GetInstance()->GetKey();
	int trg = ApplicationMain::GetInstance()->GetTrg();
	int nModeCnt = _modeCount;  //�Q�[���N���X�������Ă���
	int f = 0;	// ���[�g�X�V��1�ɂ���

	if (nModeCnt == 0) {
		f = 1;

		// 3D���[�h�p�ݒ�

		// 1�t���[���̈ړ���
		playerSpeed = BLOCK_SIZE / MOVE_BLOCK_SPEED;
		// �����Ă��������2D�ŏ�i3D�ŉ��j�ŏ���������
		vDir.x = 0.f;
		vDir.y = 0.f;
		vDir.z = 1.f * playerSpeed;
	}

	if (play_mode == 0) {
		// 2D
		// R�������Ȃ���łȂ��ꍇ�A��l���̈ړ�
		if (!(Input::_key[(KEY_INPUT_R)] == 1)) {

			// ��l���̈ړ�
			if (Input::_key[(KEY_INPUT_LEFT)] == 1) { plx--; f = 1; }
			if (Input::_key[(KEY_INPUT_RIGHT)] == 1) { plx++; f = 1; }
			if (Input::_key[(KEY_INPUT_UP)] == 1) { ply--; f = 1; }
			if (Input::_key[(KEY_INPUT_DOWN)] == 1) { ply++; f = 1; }

			// ��l���̈ړ������}�b�v���ɐ���
			if (plx < 0) { plx = 0; }
			if (plx >= MAZE_W) { plx = MAZE_W - 1; }
			if (ply < 0) { ply = 0; }
			if (ply >= MAZE_H) { ply = MAZE_H - 1; }

			// �X�y�[�X����������}�b�v�̕ǂ�ON/OFF
			if (Input::_key[(KEY_INPUT_SPACE)] == 1) {
				maze[ply * MAZE_W + plx] = 1 - maze[ply * MAZE_W + plx];
				f = 1;
			}
		}

		// R�������Ȃ���㉺���E�ŃS�[���̈ړ�
		if (Input::_key[(KEY_INPUT_R)] == 1) {
			// �S�[���̈ړ�
			if (Input::_key[(KEY_INPUT_LEFT)] == 1) { glx--; f = 1; }
			if (Input::_key[(KEY_INPUT_RIGHT)] == 1) { glx++; f = 1; }
			if (Input::_key[(KEY_INPUT_UP)] == 1) { gly--; f = 1; }
			if (Input::_key[(KEY_INPUT_DOWN)] == 1) { gly++; f = 1; }

			// �S�[���̈ړ������}�b�v���ɐ���
			if (glx < 0) { glx = 0; }
			if (glx >= MAZE_W) { glx = MAZE_W - 1; }
			if (gly < 0) { gly = 0; }
			if (gly >= MAZE_H) { gly = MAZE_H - 1; }

			// �X�y�[�X����������}�b�v�̕ǂ�ON/OFF
			if (Input::_key[(KEY_INPUT_SPACE)] == 1) {
				maze[gly * MAZE_W + glx] = 1 - maze[gly * MAZE_W + glx];
				f = 1;
			}
		}

		// Z,X����������A���[�g�T�[�`�J�E���^��ύX����
		if (key & PAD_INPUT_1) { route_search--; f = 1; }
		if (key & PAD_INPUT_2) { route_search++; f = 1; }

		// A,S����������A���[�g�T�[�`�J�E���^��傫���ύX����
//		if (key & PAD_INPUT_4) { route_search -= 10; f = 1; }
//		if (key & PAD_INPUT_5) { route_search += 10; f = 1; }

		// A,S����������A�Q�[�����[�h��3D�ɕύX
		if (Input::_key[(KEY_INPUT_A)] == 1) {
			play_mode = 1;
			// ���̃v���C���[���W��3D�p���W�ɕϊ�����
			vPlayer.x = BLOCK_SIZE * plx;
			vPlayer.y = 0.f;
			vPlayer.z = BLOCK_SIZE * -ply;		// ������W���ƁA2D��Y���傫���Ȃ�قǁA3D��Z�͎�O�ɂȂ�
		}

		// ���[�g�T�[�`�J�E���^�������ɐ���
		if (route_search < 1) { route_search = 1; }
		if (route_search > 255) { route_search = 255; }

		// Q����������A���[�g�J�E���^�f�o�b�O�\��
		if (trg & PAD_INPUT_7) { draw_checkroute = 1; draw_route_c = 1; f = 1; }

		// D����������A���[�g�J�E���^�f�o�b�O�\����ύX
		if (trg & PAD_INPUT_6) { draw_route_c = 1 - draw_route_c; }

		// W����������A���[�g�����f�o�b�O�\��
		if (trg & PAD_INPUT_8) { draw_makeroute = 1; draw_route_f = 1; f = 1; }

		// C����������A���[�g�t���O�f�o�b�O�\����ύX
		if (trg & PAD_INPUT_3) { draw_route_f = 1 - draw_route_f; }
	}
	else {
		// 3D
		// A,S����������A�Q�[�����[�h��3D�ɕύX
		//if (trg & (PAD_INPUT_4 | PAD_INPUT_5)) {
		if (Input::_key[(KEY_INPUT_A)] == 1) {
			play_mode = 0;
			// ���̃v���C���[���W��2D�p���W�ɕϊ�����
			plx = vPlayer.x / BLOCK_SIZE;
			ply = vPlayer.z / -BLOCK_SIZE;
		}

		// �����Ă��������x,z���猻�݂̊p�x���v�Z
		float rad = atan2(vDir.z, vDir.x);

		// ���E�Ŋp�x�ύX
		if (Input::_key[(KEY_INPUT_LEFT)] == 1) { rad += 1.f / MOVE_BLOCK_SPEED; }
		if (Input::_key[(KEY_INPUT_RIGHT)] == 1) { rad -= 1.f / MOVE_BLOCK_SPEED; }

		// �㉺�Ō����Ă�������Ɉړ�
		float fMove = 0.f;		// 0���ƈړ����Ȃ�
		if (Input::_key[(KEY_INPUT_UP)] == 1) { fMove = 1.f; }
		if (Input::_key[(KEY_INPUT_DOWN)] == 1) { fMove = -1.f; }

		// �ړ��{���������āA�����Ă�������Ɉړ�����
		vPlayer.x += vDir.x * fMove;
		vPlayer.y += vDir.y * fMove;
		vPlayer.z += vDir.z * fMove;

		// �p�x��������Ă���������v�Z
		vDir.x = cos(rad) * playerSpeed;
		vDir.z = sin(rad) * playerSpeed;

	}

	// �ړ������Ȃ�f�[�^�X�V
	if (f) {
		// GetNowTime() �ŁA�����������Ԃ��v������
		int n = GetNowCount(0);

		search_call_cnt = 0;		// _CheckChipRoute() ���ċN�ŌĂ΂ꂽ�񐔂��J�E���g
		{
			CheckChipRoute(plx, ply, glx, gly, route_search);
			MakeShortRoute(plx, ply, glx, gly, route_search);
		}
		search_time_ms = GetNowCount(0) - n;
	}

	// �f�o�b�O�\���t���OOFF
	draw_checkroute = 0;
	draw_makeroute = 0;

	Input::Process();
	_pDoor->Process();

	return true;
}

bool MazeStage::Render() {

	GameDraw();

	return true;
}

bool MazeStage::Terminate() {
	return true;
}

void MazeStage::_CheckChipRoute(int x1, int y1, int x2, int y2, int cntmax) {

	// �g�O�Ȃ�߂�
	if (x1 < 0 || x1 >= MAZE_W || y1 < 0 || y1 >= MAZE_H) { return; }

	// �f�o�b�O�p�B�ċN�ŉ���Ă΂ꂽ���J�E���g
	search_call_cnt++;

	// ���̈ʒu�͈ړ��\���H
	int mvFlg = maze[(y1)*MAZE_W + (x1)];
	if (mvFlg) {
		// �ړ��s��
		return;
	}
	// �ړ��\�B�������������ނ��A���łɏ�������ł��邩�H
	if (mazeroute_c[(y1)*MAZE_W + (x1)] != 0 && mazeroute_c[(y1)*MAZE_W + (x1)] >= cntmax) {
		// ���łɏ������܂�ĂāA���������c�肪�傫���̂ŁA�`�F�b�N����Ӗ�������
		return;
	}
	mazeroute_c[(y1)*MAZE_W + (x1)] = cntmax;
	cntmax--;

	// �f�o�b�O�p�r���\��
	if (draw_checkroute) { GameDraw(); }

	// �������c���Ă��邩�H
	if (cntmax <= 0) {
		// �c���Ă��Ȃ��̂ł����܂�
		return;
	}
	// �ړI�l�ɓ������H
	if (x1 == x2 && y1 == y2) {
		// ���������̂ł����܂�
		return;
	}
	// �㉺���E�Ɉړ�
	_CheckChipRoute(x1, y1 - 1, x2, y2, cntmax);		// ��
	_CheckChipRoute(x1 + 1, y1, x2, y2, cntmax);		// �E
	_CheckChipRoute(x1, y1 + 1, x2, y2, cntmax);		// ��
	_CheckChipRoute(x1 - 1, y1, x2, y2, cntmax);		// ��

	return;
}

// (x1,y1):���ݒn, (x2,y2):�ړI�n
int MazeStage::CheckChipRoute(int x1, int y1, int x2, int y2, int cntmax) {
	// ���[�g�}�b�v������
	memset(mazeroute_c, 0, sizeof(mazeroute_c));
	// ���[�g�}�b�v�쐬
	_CheckChipRoute(x1, y1, x2, y2, cntmax);
	// ���ǂ蒅�������H
	if (mazeroute_c[(y2)*MAZE_W + (x2)] == 0) {
		// ���ǂ���Ȃ�����
		return 0;
	}
	// ���ǂ�����B������Ԃ�
	return (cntmax - mazeroute_c[(y2)*MAZE_W + (x2)]) + 1;
}

// mazeroute_c[]���������A�ړI�n�ւ̍ŒZ���[�g�𓾂�
// (x1,y1):���ݒn, (x2,y2):�ړI�n
// �ړI�n����t�Z���Ă���
int MazeStage::MakeShortRoute(int x1, int y1, int x2, int y2, int cntmax) {
	// ���[�g�t���O������
	memset(mazeroute_f, 0, sizeof(mazeroute_f));
	// �{���ɂ�����́H
	int x, y;
	x = x2; y = y2;
	int n = mazeroute_c[(y)*MAZE_W + (x)];
	if (n == 0) {
		// �s���Ȃ�
		return 0;
	}
	// ���̕����l���烋�[�g�쐬
	while (x1 != x || y1 != y) {
		// ��E�����̏�
		mazeroute_f[(y)*MAZE_W + (x)] = 1;
		if (n + 1 == mazeroute_c[(y - 1) * MAZE_W + (x)]) { x += 0; y += -1; n++; }
		else if (n + 1 == mazeroute_c[(y)*MAZE_W + (x + 1)]) { x += 1; y += 0; n++; }
		else if (n + 1 == mazeroute_c[(y + 1) * MAZE_W + (x)]) { x += 0; y += 1; n++; }
		else if (n + 1 == mazeroute_c[(y)*MAZE_W + (x - 1)]) { x += -1; y += 0; n++; }

		// �f�o�b�O�p�r���\��
		if (draw_makeroute) { GameDraw(); }

	}
	mazeroute_f[(y)*MAZE_W + (x)] = 1;
	return (cntmax - mazeroute_c[(y2)*MAZE_W + (x2)]) + 1;
}

void MazeStage::GameDraw() {
	int x, y;

	// ��ʃN���A
	ClearDrawScreen();

	// �`�摬�x�v���p
	unsigned int tStart = GetNowCount();

	if (play_mode == 0) {
		// 2D

		// ���H
		for (y = 0; y < MAZE_H; y++) {
			for (x = 0; x < MAZE_W; x++) {
				if (maze[y * MAZE_W + x] != 0) {
					DrawGraph(x * CHIP_W, y * CHIP_H, cg[ECG_CHIP_BROWN], FALSE);
				}
				else {
					DrawGraph(x * CHIP_W, y * CHIP_H, cg[ECG_CHIP_BLACK], FALSE);
				}
			}
		}

		// �J�E���g
		SetFontSize(16);
		for (y = 0; y < MAZE_H; y++) {
			for (x = 0; x < MAZE_W; x++) {
				if (draw_route_f) {
					if (mazeroute_f[y * MAZE_W + x] != 0) {
						DrawGraph(x * CHIP_W, y * CHIP_H, cg[ECG_CHIP_BLUE], FALSE);
					}
				}
				if (draw_route_c) {
					DrawFormatString(x * CHIP_W, y * CHIP_H, GetColor(128, 128, 128), "%2x", mazeroute_c[y * MAZE_W + x]);
				}
			}
		}

		// �S�[��
		DrawGraph(glx * CHIP_W, gly * CHIP_H, cg[ECG_HEART], TRUE);

		// �v���C���[
		DrawGraph(plx * CHIP_W, ply * CHIP_H, cg[ECG_STAR], TRUE);

		// ���\��
		DrawFormatString(0, 720 - 16, GetColor(255, 255, 255), "search_time: %d, search_call: %d", search_time_ms, search_call_cnt);
	}
	else {
		// 3D
		SetUseZBuffer3D(TRUE);
		SetWriteZBuffer3D(TRUE);
		SetUseBackCulling(TRUE);
		SetCameraNearFar(0.1f, 5000.0f);

		VECTOR CamPos;		// �J�����̍��W
		VECTOR CamTarg;		// �J�����̒����_

		// �J�����̍��W���Z�b�g
		CamPos = vPlayer;
		CamPos.y = CAMERA_Y;	// �J�����̍����ɕύX����

		// �J�����̒����_���Z�b�g
		CamTarg = vDir;
		CamTarg = VAdd(CamPos, CamTarg);

		// �J�����̈ʒu�ƌ������Z�b�g����
		SetCameraPositionAndTarget_UpVecY(CamPos, CamTarg);

		// ���H
		// ��ɍő�l���̍��W�o�b�t�@���C���f�b�N�X�o�b�t�@��p�ӂ���
		VERTEX3D* vBuf = new VERTEX3D[MAZE_W * MAZE_H * 8];		// �������AindexBuf��unsigned short�Ȃ̂ŁA65535�𒴂��Ȃ��悤��
		int cntBuf = 0;
		unsigned short* indexBuf = new unsigned short[MAZE_W * MAZE_H * (6 * 4)];
		int cntIndexBuf = 0;

		// �o�b�t�@�𐶐�����
		for (y = 0; y < MAZE_H; y++) {
			for (x = 0; x < MAZE_W; x++) {
				if (maze[y * MAZE_W + x] != 0) {
					// �ǂ̏ꏊ�ɔ��|���S����\������
					VERTEX3D v[8];	// ���_�f�[�^(����\������ɂ�8���_�K�v)
					for (int i = 0; i < 8; i++) {
						float posTbl[][3] = {
							// (0,0,0)�𔠂̒��S�Ƃ��čl���āA�e���_���ǂ��ɂ��邩
							{-0.5f,  0.0f, -0.5f},	// 0:�����O
							{ 0.5f,  0.0f, -0.5f},	// 1:�E���O
							{-0.5f,  0.0f,  0.5f},	// 2:������
							{ 0.5f,  0.0f,  0.5f},	// 3:�E����
							{-0.5f,  1.0f, -0.5f},	// 4:����O
							{ 0.5f,  1.0f, -0.5f},	// 5:�E��O
							{-0.5f,  1.0f,  0.5f},	// 6:���㉜
							{ 0.5f,  1.0f,  0.5f},	// 7:�E�㉜
						};
						v[i].pos = VGet(posTbl[i][0] * BLOCK_SIZE, posTbl[i][1] * BLOCK_SIZE, posTbl[i][2] * BLOCK_SIZE);
						VECTOR	vPos = { x * BLOCK_SIZE, 0, -y * BLOCK_SIZE };
						v[i].pos = VAdd(v[i].pos, vPos);
						v[i].norm = VGet(0.0f, 0.0f, -1.0f);
						v[i].dif = GetColorU8(255, 127 + (x % 2) * 127, 128 + (y % 2) * 127, 255);
						v[i].spc = GetColorU8(0, 0, 0, 0);
						v[i].u = 0.0f;
						v[i].v = 0.0f;
						v[i].su = 0.0f;
						v[i].sv = 0.0f;
					}
					unsigned short index[] = {	// 8�̒��_���g���āA�ǂ�3�p�`�|���S����`�悷�邩�B6�ʕ��p�ӂ���
						// �o�b�N�J�����O�����Ă��邽�߁A�E����\�ʂƂ���
						0,4,1,1,4,5,	// �O(0,1,4,5)
						0,2,4,4,2,6,	// ��(0,2,4,6)
						1,5,3,3,5,7,	// �E(1,3,5,7)
					//	0,2,1,1,2,3,	// ��(0,1,2,3)	// ��Ɖ��͖��H�Q�[���ɂ͕K�v����
					//	4,6,5,5,6,7,	// ��(4,5,6,7)	//
						2,3,6,6,3,7,	// ��(2,3,6,7)
					};
					int vNum = sizeof(v) / sizeof(v[0]);
					int pNum = sizeof(index) / sizeof(index[0]) / 3;
					//DrawPolygonIndexed3D(v, vNum, index, pNum, DX_NONE_GRAPH, FALSE);

					// �o�b�t�@�ɏ�������
					for (int i = 0; i < pNum * 3; i++) {
						indexBuf[cntIndexBuf] = index[i] + cntBuf;		// ���_�ԍ���vBuf[]�ɂ��킹�Ă��炷
						cntIndexBuf++;
					}
					for (int i = 0; i < vNum; i++) {
						vBuf[cntBuf] = v[i];
						cntBuf++;
					}

					/*
					// ���C���t���[���̕`��
					for (int i = 0; i < pNum; i++) {
						DrawLine3D(v[index[i * 3 + 0]].pos, v[index[i * 3 + 1]].pos, GetColor(255, 255, 255));
						DrawLine3D(v[index[i * 3 + 1]].pos, v[index[i * 3 + 2]].pos, GetColor(255, 255, 255));
						DrawLine3D(v[index[i * 3 + 2]].pos, v[index[i * 3 + 0]].pos, GetColor(255, 255, 255));
					}
					*/
				}
			}
		}

		// �o�b�t�@�̃f�[�^���܂Ƃ߂ĕ`�悷��
		DrawPolygonIndexed3D(vBuf, cntBuf, indexBuf, cntIndexBuf / 3, DX_NONE_GRAPH, FALSE);

		// �o�b�t�@�̉��
		delete[] vBuf;
		delete[] indexBuf;

		_pDoor->Render();
	}
	
	// �`�摬�x�\��
	DrawFormatString(0, 0, GetColor(255, 255, 255), "%d", GetNowCount() - tStart);

	// �y�[�W�؂�ւ�
	ScreenFlip();
}