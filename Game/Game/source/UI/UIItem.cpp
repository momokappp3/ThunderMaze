#include "UIItem.h"
#include "../../../../AppFrame/source/static/ResourceServer.h"
#include "Dxlib.h"

UIItem::UIItem() {
	_upperItem = 0;
	_middleItem = 0;
	_downItem = 0;
}

UIItem::~UIItem() {
}

bool UIItem::Init() {

	//Base
	int handle = ResourceServer::LoadGraph("png/gameUI/itemBase.png");

	if (handle == -1) {
		return false;
	}

	DrawInfo info = { handle,10,400,true };  //���Base
	SetDrawInfo(info);

	info = { handle,100,500,true };  //�^�񒆂�Bace
	SetDrawInfo(info);

	info = { handle,142,614,true };  //����Base
	SetDrawInfo(info);

	//�g
	handle = ResourceServer::LoadGraph("png/gameUI/itemWaku3.png");

	if (handle == -1) {
		return false;
	}

	info = { handle,100,500,true };
	SetDrawInfo(info);

	//============================================================
	//item�̉摜 4����
	handle = ResourceServer::LoadGraph("png/gameUI/baria.png");

	if (handle == -1) {
		return false;
	}

	info = { handle,0,0,false };
	SetDrawInfo(info);

	handle = ResourceServer::LoadGraph("png/gameUI/portion.png");

	if (handle == -1) {
		return false;
	}

	info = { handle,0,0,false };
	SetDrawInfo(info);

	handle = ResourceServer::LoadGraph("png/gameUI/surinuke.png");

	if (handle == -1) {
		return false;
	}

	info = { handle,0,0,false };
	SetDrawInfo(info);

	handle = ResourceServer::LoadGraph("png/gameUI/timeLong.png");

	if (handle == -1) {
		return false;
	}

	info = { handle,0,0,false };
	SetDrawInfo(info);


    return true;
}

void UIItem::Process(){

	
}

void UIItem::Draw(){

	for (int i = 0; i < 3; i++) {
		DrawGraph(_vDrawInfo[i].xy.x, _vDrawInfo[i].xy.y, _vDrawInfo[i].handle, TRUE);
	}
	
	//item�̕`��
	if (_upperItem != 0) {
		DrawGraph(_vDrawInfo[0].xy.x, _vDrawInfo[0].xy.y, _vDrawInfo[_upperItem].handle, TRUE);
	}
	if (_middleItem != 1) {
		DrawGraph(_vDrawInfo[1].xy.x, _vDrawInfo[1].xy.y, _vDrawInfo[_middleItem].handle, TRUE);
	}
	if (_downItem != 2) {
		DrawGraph(_vDrawInfo[2].xy.x, _vDrawInfo[2].xy.y, _vDrawInfo[_downItem].handle, TRUE);
	}

	//�g
	DrawGraph(_vDrawInfo[3].xy.x, _vDrawInfo[3].xy.y, _vDrawInfo[3].handle, TRUE);
}