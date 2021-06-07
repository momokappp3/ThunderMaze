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

	_pTransform.Update();

	MV1SetMatrix(_handle, _pTransform.GetTransform());
}

void Model::Render() {

	if (_handle == -1) {
		return;
	}

	MV1DrawModel(_handle);
}