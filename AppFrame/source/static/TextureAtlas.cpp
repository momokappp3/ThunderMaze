#include "TextureAtlas.h"
#include "ResourceServer.h"
#include "DxLib.h"

LIBTEXPACK_DATA* TextureAtlas::_texPack;

TextureAtlas::TextureAtlas() {
}

TextureAtlas::~TextureAtlas() {

	LibTextPackReleaseBin(_texPack);
	LibTexPackRelease();
}

bool TextureAtlas::Init(){

	LibTexPackInit();  // ������

	FILE* fp;  // bin�t�@�C���̓ǂݍ���

	if (fopen_s(&fp, "pngkari/tr1.bin", "rb")) {
		return false; //�t�@�C���J���Ȃ�����
	}

	fseek(fp, 0, SEEK_END);
	int fsize = ftell(fp); 
	fseek(fp, 0, SEEK_SET);
	void* p = malloc(fsize);
	fread(p, 1, fsize, fp);
	fclose(fp);

	// �o�^
	_texPack = LibTexPackSetBin(p, fsize);
	free(p);
}

int TextureAtlas::GetHandle(std::string string) {

	// �摜�p�[�c���擾
	TEXTUREPACK_TEXTUREDATA	tex;
	int sx, sy, sw, sh;
	int ox, oy, ow, oh;

	const char* szId = string.c_str();

	if (LibTexPackGetData(_texPack, szId, &tex, &sx, &sy, &sw, &sh, &ox, &oy, &ow, &oh) == 0) {
		return -1;  //���s���Ă���
	}

	int handle = -1;

	//���e�N�X�`�������邩�Ԃ�

	int num = LibTexPackGetIndex(_texPack, szId);
	 num = LibTexPackGetIndex(_texPack, szId);

	switch (num) {
	case 1:
		handle = ResourceServer::LoadGraph("pngkari/tr1_000.png");
		break;
	case 2:
		handle = ResourceServer::LoadGraph("pngkari/tr1_001.png");
		break;
	case 3:
		handle = ResourceServer::LoadGraph("pngkari/tr1_002.png");
		break;
	case 4:
		handle = ResourceServer::LoadGraph("pngkari/tr1_003.png");
		break;
	case 5:
		handle = ResourceServer::LoadGraph("pngkari/tr1_004.png");
		break;
	case 6:
		handle = ResourceServer::LoadGraph("pngkari/tr1_005.png");
		break;
	case 7:
		handle = ResourceServer::LoadGraph("pngkari/tr1_006.png");
		break;
	case 8:
		handle = ResourceServer::LoadGraph("pngkari/tr1_007.png");
		break;
	case 9:
		handle = ResourceServer::LoadGraph("pngkari/tr1_008.png");
		break;
	case 10:
		handle = ResourceServer::LoadGraph("pngkari/tr1_009.png");
		break;
	default:
		break;
	}

	return ResourceServer::DerivationGraph(sx, sy, sw, sh, handle, szId);
}