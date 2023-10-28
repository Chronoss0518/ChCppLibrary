#include<Windows.h>
#include"../../../BaseIncluder/ChBase.h"
#include"../../../BaseIncluder/ChD3D11I.h"

#include"ChCBBasicShapes11.h"

using namespace ChD3D11;
using namespace CB;

void CBBasicShapes11::Init(
	ID3D11Device* _device)
{
	if (IsInit())return;
	if (!_defaultBase->IsTex())return;

	CBBase11::Init(_device);

	bsBuf.CreateBuffer(GetDevice(), BASIC_SHAPES_DATA_REGISTERNO);

	SetInitFlg(true);
}

void CBBasicShapes11::Release()
{
	if (!IsInit())return;

	bsBuf.Release();

	SetInitFlg(false);

	bsUpdateFlg = true;
}

void CBBasicShapes11::SetSpriteMatrix(const ChLMat& _mat)
{
	bsData.spriteMat = _mat;

	bsUpdateFlg = true;
}

void CBBasicShapes11::SetColor(const ChVec4& _color)
{
	bsData.color = _color;

	bsUpdateFlg = true;
}

void CBBasicShapes11::SetBasicShapesData(const BasicShapesData& _data)
{
	bsData = _data;

	bsUpdateFlg = true;
}

void CBBasicShapes11::SetPSBasicShapesData(ID3D11DeviceContext* _dc)
{
	if (!*this)return;

	UpdateSD(_dc);

	bsBuf.SetToPixelShader(_dc);
}

void CBBasicShapes11::SetVSBasicShapesData(ID3D11DeviceContext* _dc)
{
	if (!*this)return;

	UpdateSD(_dc);

	bsBuf.SetToVertexShader(_dc);
}

void CBBasicShapes11::SetShaderBasicShapesData(ID3D11DeviceContext* _dc)
{
	if (!*this)return;

	SetPSBasicShapesData(_dc);
	SetVSBasicShapesData(_dc);
}

void CBBasicShapes11::UpdateSD(ID3D11DeviceContext* _dc)
{
	if (!IsInit())return;
	if (!bsUpdateFlg)return;
	bsBuf.UpdateResouce(_dc, &bsData);
	bsUpdateFlg = false;
}

void CBBasicShapesPosition11::Init(
	ID3D11Device* _device)
{
	if (IsInit())return;
	if (!_defaultBase->IsTex())return;

	CBBase11::Init(_device);

	positionBuf.CreateBuffer(GetDevice(), BASIC_SHAPES_POSITION_DATA_REGISTERNO);

	SetInitFlg(true);
}

void CBBasicShapesPosition11::Release()
{
	if (!IsInit())return;

	positionBuf.Release();

	SetInitFlg(false);

	updateFlg = true;
}

void CBBasicShapesPosition11::SetPositions(const ChBasicShapesPositions& _positions)
{
	positionData.positions = _positions;

	updateFlg = true;
}

void CBBasicShapesPosition11::SetPosition(const ChVec2& _position, int _no)
{
	if (_no >= MAX_POSITION_DATA)return;

	positionData.positions.positions[_no] = _position;

	updateFlg = true;
}

void CBBasicShapesPosition11::SetUsePositionCount(int _positionCount)
{
	positionData.usePositionCount = _positionCount;

	updateFlg = true;
}

void CBBasicShapesPosition11::SetPSBasicShapesPositionData(ID3D11DeviceContext* _dc)
{
	if (!*this)return;

	UpdateSD(_dc);

	positionBuf.SetToPixelShader(_dc);
}

void CBBasicShapesPosition11::SetVSBasicShapesPositionData(ID3D11DeviceContext* _dc)
{
	if (!*this)return;

	UpdateSD(_dc);

	positionBuf.SetToVertexShader(_dc);
}

void CBBasicShapesPosition11::SetShaderBasicShapesPositionData(ID3D11DeviceContext* _dc)
{
	if (!*this)return;

	SetPSBasicShapesPositionData(_dc);
	SetVSBasicShapesPositionData(_dc);
}

void CBBasicShapesPosition11::UpdateSD(ID3D11DeviceContext* _dc)
{
	if (!IsInit())return;
	if (!updateFlg)return;
	positionBuf.UpdateResouce(_dc, &positionData);
	updateFlg = false;
}

void CBBasicShapesCircle11::Init(
	ID3D11Device* _device)
{
	if (IsInit())return;
	if (ChPtr::NullCheck(_defaultBase))return;
	if (!_defaultBase->IsTex())return;

	CBBase11::Init(_device);

	circleBuf.CreateBuffer(GetDevice(), BASIC_SHAPES_CIRCLE_DATA_REGISTERNO);

	SetInitFlg(true);
}

void CBBasicShapesCircle11::Release()
{
	if (!IsInit())return;

	circleBuf.Release();

	SetInitFlg(false);

	updateFlg = true;
}

void CBBasicShapesCircle11::SetCenterPosition(const ChVec2& _centerPos)
{
	circleData.circleData.centerPosition = _centerPos;

	updateFlg = true;
}

void CBBasicShapesCircle11::SetSize(float _size)
{
	circleData.circleData.size = _size;

	updateFlg = true;
}

void CBBasicShapesCircle11::SetPSBasicShapesCircleData(ID3D11DeviceContext* _dc)
{
	if (!*this)return;

	UpdateSD(_dc);

	circleBuf.SetToPixelShader(_dc);
}

void CBBasicShapesCircle11::SetVSBasicShapesCircleData(ID3D11DeviceContext* _dc)
{
	if (!*this)return;

	UpdateSD(_dc);

	circleBuf.SetToVertexShader(_dc);
}

void CBBasicShapesCircle11::SetShaderBasicShapesCircleData(ID3D11DeviceContext* _dc)
{
	if (!*this)return;

	SetPSBasicShapesCircleData(_dc);
	SetVSBasicShapesCircleData(_dc);
}

void CBBasicShapesCircle11::UpdateSD(ID3D11DeviceContext* _dc)
{
	if (!IsInit())return;
	if (!updateFlg)return;
	circleBuf.UpdateResouce(_dc, &circleData);
	updateFlg = false;
}
