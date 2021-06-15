#include "Model.h"
#include "Dxlib.h"
#include "../static/ResourceServer.h"

Model::Model(){
	_handle = -1;
}

Model::~Model() {
}

bool Model::Load(const TCHAR* fileName,bool multiple) {

	_handle = ResourceServer::MV1LoadModel(fileName, multiple);

	return _handle != -1;
}

void Model::Process() {

	if (_handle == -1) {
		return;
	}

	_pModelTransform.Update();

	MV1SetMatrix(_handle, _pModelTransform.GetTransform());

	//for•¶‘S•”‰ñ‚·
	//MV1SetFrameUserLocalMatrix(_handle, );
}

void Model::Render() {

	if (_handle == -1) {
		return;
	}

	MV1DrawModel(_handle);
}