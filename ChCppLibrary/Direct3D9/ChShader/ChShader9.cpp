
#include<Windows.h>
#include"../../BaseIncluder/ChBase.h"
#include"../../BaseIncluder/ChD3D9I.h"

#include"../ChTexture/ChBaseTexture9.h"
#include"../ChMesh/ChBaseMesh9.h"
#include"../ChLight/ChLight9.h"
#include"ChShader9.h"



using namespace ChD3D9;

ChVec2 ShaderController::windSize = ChVec2(1280.0f, 720.0f);

///////////////////////////////////////////////////////////////////////////////////////
//ChShaderControllerメソッド
///////////////////////////////////////////////////////////////////////////////////////

void ShaderController::Init(
	const LPDIRECT3DDEVICE9 _d,
	const D3DPRESENT_PARAMETERS& _param,
	const float& _windWidth,
	const float& _windHeight) {
	
	if (ChPtr::NullCheck(_d))return;

	device = _d;
	param = _param;

	InitShader();

	device->GetVertexDeclaration(&baseDec);

	{

		D3DVERTEXELEMENT9 decl[] = {
			{0,  0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION,     0},
			{0, sizeof(D3DXVECTOR3), D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR,  0},
			{0, sizeof(D3DXVECTOR3) + sizeof(D3DCOLORVALUE), D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0},
			D3DDECL_END()
		};


		device->CreateVertexDeclaration(decl, &tVerDec);

	}

	{

		D3DVERTEXELEMENT9 decl[] = {
			{0,  0, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION,     0},
			{0, sizeof(D3DXVECTOR4), D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL,  0},
			{0, sizeof(D3DXVECTOR4) + sizeof(D3DXVECTOR3), D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0},
			D3DDECL_END()
		};


		device->CreateVertexDeclaration(decl, &mVerDec);

	}

	MakeWhiteTexture();

	MakeNormalMapTexture();

	MakeLightingPowTexture();

	CreateBeforeTex();

	SetInitFlg(true);
}

void ShaderController::InitShader()
{

	{
#include"MVShader.inc"


		device->CreateVertexShader((DWORD*)main, &bVModel);
	}

	{
#include"MPShader.inc"


		device->CreatePixelShader((DWORD*)main, &bPModel);
	}

	{
#include"MVOLShader.inc"


		device->CreateVertexShader((DWORD*)main, &cVModel);
	}

	{
#include"MPColShader.inc"


		device->CreatePixelShader((DWORD*)main, &cPModel);
	}

	{
#include"STVShader.inc"


		device->CreateVertexShader((DWORD*)main, &spVTex);
	}

	{
#include"PTVShader.inc"

		device->CreateVertexShader((DWORD*)main, &poVTex);
	}

	{
#include"TPShader.inc"

		device->CreatePixelShader((DWORD*)main, &bPTex);
	}

}
///////////////////////////////////////////////////////////////////////////////////

void ShaderController::Release()
{
	if (ChPtr::NotNullCheck(bVModel))
	{
		bVModel->Release();
		bVModel = nullptr;
	}
	if (ChPtr::NotNullCheck(bPModel))
	{
		bPModel->Release();
		bPModel = nullptr;
	}

	if (ChPtr::NotNullCheck(cVModel))
	{
		cVModel->Release();
		cVModel = nullptr;
	}
	if (ChPtr::NotNullCheck(cPModel))
	{
		cPModel->Release();
		cPModel = nullptr;
	}

	if (ChPtr::NotNullCheck(spVTex))
	{
		spVTex->Release();
		spVTex = nullptr;
	}
	if (ChPtr::NotNullCheck(poVTex))
	{
		poVTex->Release();
		poVTex = nullptr;
	}
	if (ChPtr::NotNullCheck(bPTex))
	{
		bPTex->Release();
		bPTex = nullptr;
	}

	if (ChPtr::NotNullCheck(baseDec))
	{
		baseDec->Release();
		baseDec = nullptr;
	}
	if (ChPtr::NotNullCheck(tVerDec))
	{
		tVerDec->Release();
		tVerDec = nullptr;
	}
	if (ChPtr::NotNullCheck(mVerDec))
	{
		mVerDec->Release();
		mVerDec = nullptr;
	}

	ReleaseTextures();
	
	SetInitFlg(false);
}

void ShaderController::SetDrawDatas(const D3DCOLOR&
	_backColor)
{

	// バックバッファと Z バッファをクリア
	device->Clear(0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, _backColor, 1.0f, 0);

	if (ChPtr::NullCheck(device))return;

	struct MatData
	{
		ChMat_9 viewMat;
		ChMat_9 proMat;
	};

	MatData tmp;



	device->GetTransform(D3DTS_VIEW, &tmp.viewMat);
	device->GetTransform(D3DTS_PROJECTION, &tmp.proMat);

	//ビュー・射影行列セット//
	device->SetVertexShader(poVTex);

	device->SetVertexShaderConstantF(0, (const float*)&tmp, 8);

	device->SetVertexShader(cVModel);

	device->SetVertexShaderConstantF(0, (const float*)&tmp, 8);

	device->SetVertexShader(bVModel);

	device->SetVertexShaderConstantF(0, (const float*)&tmp, 8);

	ChVec4 tmpPos;

	tmpPos.x = camPos.x;
	tmpPos.y = camPos.y;
	tmpPos.z = camPos.z;

	tmpPos.w = 0.0f;

	device->SetPixelShader(bPModel);

	device->SetPixelShaderConstantF(0, (const float*)&tmpPos, 1);
}

void ShaderController::IsLight(const bool _flg)
{
	lightUseFlg = _flg;
}

void ShaderController::DrawStart(const D3DCOLOR& _backColor)
{
	if (!*this)return;
	if (rtDrawFlg)return;
	if (drawFlg)return;

	SetDrawDatas(_backColor);

	device->BeginScene();

	drawFlg = true;
}

void ShaderController::DrawEnd()
{
	if (!*this)return;
	if (rtDrawFlg)return;
	if (!drawFlg)return;

	if (ChPtr::NullCheck(device))return;

	device->EndScene();

	drawFlg = false;

	// バックバッファをプライマリバッファにコピー
	if (FAILED(device->Present(NULL, NULL, NULL, NULL)))
	{
		device->Reset(&param);
	}

}

void ShaderController::DrawMesh(const ChMesh::Mesh9& _mesh, const ChMat_9& _mat)
{
	if (!*this)return;
	if (!drawFlg && !rtDrawFlg)return;
	if (ChPtr::NullCheck(_mesh.GetMesh()))return;

	device->SetVertexShader(bVModel);
	device->SetPixelShader(bPModel);

	SetLightFunction();

	ChMat_9 tmpMat;

	device->SetVertexDeclaration(mVerDec);

	for (unsigned long i = 0; i < _mesh.GetMaterialCount(); i++) {

		tmpMat = _mesh.GetMaterial(i).mat * _mat;

		device->SetVertexShaderConstantF(8, (const float*)&_mat, 4);

		auto tmpMate = SetMateData(_mesh.GetMaterial(i));

		device->SetPixelShaderConstantF(1, (const float*)&tmpMate, 2);

		{
			auto tmpTex = _mesh.GetTexture(i)->GetTex();

			if (ChPtr::NullCheck(tmpTex))tmpTex = GetWhiteTex()->GetTex();

			device->SetTexture(0, tmpTex);

		}

		if (_mesh.GetNormalTextureCount() > 0)
		{
			auto pNormal = _mesh.GetNormalTexture(i)->GetTex();

			if (ChPtr::NullCheck(pNormal))pNormal = GetNormalTex()->GetTex();

			device->SetTexture(2, pNormal);

		}
		else
		{
			device->SetTexture(2, GetNormalTex()->GetTex());
		}

		_mesh.GetMesh()->DrawSubset(i);
	}

	device->SetVertexDeclaration(baseDec);

}

//Mesh描画用関数//
void ShaderController::DrawMeshContour(
	const ChMesh::Mesh9& _mesh,
	const ChVec4& _color,
	const ChMat_9& _mat,
	const float _Size)
{
	if (!*this)return;
	if (_Size < 0.0f)return;
	if (!drawFlg && !rtDrawFlg)return;
	if (ChPtr::NullCheck(_mesh.GetMesh()))return;

	CULL tmpCull = GetCullMode();
	SetCullMode(ChD3D9::CULL::CW);

	device->SetVertexShader(cVModel);
	device->SetPixelShader(cPModel);

	ChMat_9 tmpMat;

	device->SetVertexDeclaration(mVerDec);

	for (unsigned long i = 0; i < _mesh.GetMaterialCount(); i++) {

		tmpMat = _mesh.GetMaterial(i).mat * _mat;

		device->SetVertexShaderConstantF(8, (const float*)&_mat, 4);

		ChVec4 tmpVec = ChVec4(_Size, 0.0f, 0.0f, 0.0f);

		device->SetVertexShaderConstantF(12, (const float*)&_Size, 1);

		device->SetPixelShaderConstantF(0, (const float*)&_color, 1);

		_mesh.GetMesh()->DrawSubset(i);
	}

	device->SetVertexDeclaration(baseDec);

	SetCullMode(tmpCull);
}

void ShaderController::DrawPolygonBoard(
	const ChTex::Texture9& _tex,
	const VertexData& _vertex,
	const ChMat_9& _mat,
	const unsigned int _triangleCount)
{
	if (!*this)return;
	if (!drawFlg && !rtDrawFlg)return;
	if (_tex.GetBaseColor().a <= 0.1f)return;

	device->SetVertexShader(poVTex);
	device->SetPixelShader(bPTex);

	//キャラクター移動行列セット//
	device->SetVertexShaderConstantF(8, (const float*)&_mat, 4);

	{
		D3DXVECTOR4 tmpVec;
		tmpVec.x = (_tex.GetBaseColor().r / 255.0f);
		tmpVec.y = (_tex.GetBaseColor().g / 255.0f);
		tmpVec.z = (_tex.GetBaseColor().b / 255.0f);
		tmpVec.w = (_tex.GetBaseColor().a / 255.0f);
		device->SetPixelShaderConstantF(0, (const float*)&tmpVec, 1);
	}

	//画像セット//
	auto tex = _tex.GetTex();

	if (ChPtr::NullCheck(tex)) tex = GetWhiteTex()->GetTex();

	device->SetTexture(0, tex);

	device->SetVertexDeclaration(tVerDec);

	device->DrawPrimitiveUP(
		D3DPT_TRIANGLEFAN,
		_triangleCount,
		_vertex.ver,
		sizeof(VertexData::Vertex));

	device->SetVertexDeclaration(baseDec);
}

void ShaderController::DrawSprite(
	const ChTex::Texture9& _tex,
	const ChMat_9& _mat,
	const SpriteData& _spData)
{
	if (!*this)return;
	if (!drawFlg && !rtDrawFlg)return;
	if (_tex.GetBaseColor().a <= 0.1f)return;

	device->SetVertexShader(spVTex);
	device->SetPixelShader(bPTex);

	//キャラクター移動行列セット//
	device->SetVertexShaderConstantF(0, (const float*)&_mat, 4);

	{
		D3DXVECTOR4 tmpVec = D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f);

		tmpVec.x = windSize.w;
		tmpVec.y = windSize.h;

		//WindSizeSet//
		device->SetVertexShaderConstantF(4, (const float*)&tmpVec, 1);
	}

	{
		ChVec4 tmpVec;
		tmpVec = _tex.GetBaseColor();
		device->SetPixelShaderConstantF(0, (const float*)&tmpVec, 1);
	}

	{
		//画像セット//
		auto tex = _tex.GetTex();

		if (ChPtr::NullCheck(tex)) tex = GetWhiteTex()->GetTex();

		device->SetTexture(0, tex);
	}

	SpriteData tmpSprite = _spData;
	
	for (unsigned char i = 0; i < 4; i++)
	{
		tmpSprite.spData[i].pos.z = 0.0f;
	}

	device->SetVertexDeclaration(tVerDec);

	device->DrawPrimitiveUP(
		D3DPT_TRIANGLEFAN, 2
		, tmpSprite.spData.ver, sizeof(VertexData::Vertex));

	device->SetVertexDeclaration(baseDec);
}

ShaderController::Material ShaderController::SetMateData(const D3DMATERIAL9& _mate)
{
	Material tmp;
	tmp.dif.a = _mate.Diffuse.a;
	tmp.dif.r = _mate.Diffuse.r;
	tmp.dif.g = _mate.Diffuse.g;
	tmp.dif.b = _mate.Diffuse.b;

	tmp.speCol.r = _mate.Specular.r;
	tmp.speCol.g = _mate.Specular.g;
	tmp.speCol.b = _mate.Specular.b;

	tmp.spePow = _mate.Power;

	return tmp;
}

void ShaderController::SetLightFunction()
{


	device->SetVertexShader(bVModel);
	device->SetPixelShader(bPModel);

	{
		auto lightTex = GetLightEffectTex()->GetTex();

		if (useMyLightTex)lightTex = GetMyLightTex()->GetTex();

		if (ChPtr::NullCheck(lightTex))lightTex = GetWhiteTex()->GetTex();

		device->SetTexture(1, lightTex);
	}

	{
		light.dir.Normalize();

		TmpPLight pLight[7];
		float pLFlg[8];
		for (unsigned char i = 0; i < 7; i++)
		{
			pLFlg[i] = posLight[i].flg;
			if (!posLight[i].flg)continue;
			if (posLight[i].len <= 0.0f)posLight[i].flg = false;

			pLFlg[i] = posLight[i].flg ? 1.0f : -1.0f;
			pLight[i].dif = posLight[i].dif;
			pLight[i].len = posLight[i].len;
			pLight[i].pos = posLight[i].pos;
		}
		pLFlg[7] = lightUseFlg ? 1.0f : -1.0f;

		device->SetPixelShaderConstantF(3, (const float*)&light, 2);

		float tmpFlg[8] = 
		{
			pLFlg[0],pLFlg[1],pLFlg[2],pLFlg[3],
			pLFlg[4],pLFlg[5],pLFlg[6],pLFlg[7]
		};

		device->SetPixelShaderConstantF(5, tmpFlg, 2);
		device->SetPixelShaderConstantF(7, (const float*)&pLFlg, 14);
	}

}
