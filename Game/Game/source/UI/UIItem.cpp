#include "UIItem.h"
#include "../../../../AppFrame/source/static/ResourceServer.h"
#include "Dxlib.h"

UIItem::UIItem() {

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


    return true;
}

void UIItem::Process(){

	
}

void UIItem::Draw(){

	for (int i = 0; i < 3; i++) {
		DrawGraph(_vDrawInfo[i].xy.x, _vDrawInfo[i].xy.y, _vDrawInfo[i].handle, TRUE);
	}
	
	//item�̕`��




	//�g
	DrawGraph(_vDrawInfo[3].xy.x, _vDrawInfo[3].xy.y, _vDrawInfo[3].handle, TRUE);
}