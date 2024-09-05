#ifndef Ch_D3D9_PB_h
#define Ch_D3D9_PB_h



#include"../ChTexture/ChBaseTexture9.h"
#include"../ChTexture/TexIncluder9.h"

namespace ChTex
{
	typedef class BaseTexture9 Texture9;

	//板ポリゴン管理用クラス//
	class PolygonBoard9:public ChCp::Initializer
	{
	public:

		//板ポリゴンで利用する頂点情報//
		struct ChVertex9
		{
			ChVec3_9 pos;
			D3DCOLOR col;
			D3DXVECTOR2 tex;
		};

	public:

		ChVertex9& operator[](int _size)
		{
			return this->ver[_size];
		}

		ChVertex9 operator[](const int _size)const
		{
			return this->ver[_size];
		}

	public://Init And Release//

		void Init(const LPDIRECT3DDEVICE9& _dv);

	public://Set Functions//

		//透過させるかさせないかのフラグ//
		void SetAlphaFlg(bool _flg) { alphaFlg = _flg; }

		//スペキュラ情報などを含むか含まないか//
		//void SetUpDateFlg(const bool _Flg) { UpDateFlg = _Flg; }

		//左上のD3DXVECTOR3を取得し、そこからの幅高さを計算し出力してくれる。//
		//XY方向の板ポリゴンのポジション指定//
		void SetXYPosition(const ChVec3_9& _leftTopPos, const float _w, const float _h);

		//YZ方向の板ポリゴンのポジション指定//
		void SetYZPosition(const ChVec3_9& _leftTopPos, const float _w, const float _h);

		//ZX方向の板ポリゴンのポジション指定//
		void SetZXPosition(const ChVec3_9& _leftTopPos, const float _w, const float _h);

		//対象のVertexをオリジナルの位置へ持っていくことができる。//
		void SetPositionVector(const D3DXVECTOR3& _pos, const char _posNo);

		//対象のVertexの色情報をセットできる//
		void SetColor(const D3DCOLOR& _col, const unsigned char _posNo);

		//対象のVertexのTexture描画地点(スクリーン座標系)の設定を行うことができる。//
		void SetTex(const D3DXVECTOR2& _tex, const unsigned char _posNo);

#ifdef CRT

		//第二引数には、オリジナルサイズから見たピクセルサイズ。//
		//第三引数には、画像の左上画像位置。//
		void SetRectTex(
			const ChPtr::Shared<BaseTexture9> _tex,
			const RECT& _rect,
			const unsigned char _sPosNo);

#endif

		//対象のVerTexの法線をセットできる。//
		//void SetNormal(const D3DXVECTOR3 _Normal, const char _PosNo);

	public://Get Functions//

		const inline ChVertex9* GetPosVertex(unsigned char _vertexCnt)
		{
			if (vertexMaxCnt < _vertexCnt)return nullptr;
			return &ver[_vertexCnt];
		}

	public://Other Functions//

#ifdef CRT

		void Draw(
			const ChPtr::Shared<BaseTexture9>& _Tex,
			const D3DXMATRIX& _Mat);

#endif

	protected:

		bool alphaFlg;

		static constexpr unsigned char vertexMaxCnt = 4;

		LPDIRECT3DDEVICE9 device;

		union
		{
			struct
			{
				ChVertex9 _1,_2,_3,_4;
			};

			ChVertex9 ver[vertexMaxCnt];
		};

	protected://Constructer Destructer//

		//※設定を行わない場合、Defolt値の左上を(1.0f,1.0f,0.0f)//
		//を初期値とした2づつずれた向きがXY壁をセットする。//
		PolygonBoard9() {};


	public:

		inline static PolygonBoard9& GetIns()
		{
			static PolygonBoard9 ins;
			return ins;
		}

	};

	inline PolygonBoard9& PoBo9() { return PolygonBoard9::GetIns(); }

}

#ifdef CRT

void ChTex::PolygonBoard9::SetRectTex(
	const ChPtr::Shared<BaseTexture9> _tex,
	const RECT& _rect,
	const unsigned char _SPosNo)
{
	if (_tex == nullptr)return;
	if (_SPosNo > vertexMaxCnt)return;
	D3DXVECTOR2 tmpVec;
	tmpVec = D3DXVECTOR2((float)(_rect.right / _tex->GetOriginalWidth()), (float)(_rect.top / _tex->GetOriginalHeight()));
	ver[(_SPosNo + 0) % vertexMaxCnt].tex = tmpVec;
	tmpVec = D3DXVECTOR2((float)((_rect.right + _rect.left) / _tex->GetOriginalWidth())
		, (float)(_rect.top / _tex->GetOriginalHeight()));
	ver[(_SPosNo + 1) % vertexMaxCnt].tex = tmpVec;
	tmpVec = D3DXVECTOR2((float)((_rect.right + _rect.left) / _tex->GetOriginalWidth())
		, (float)((_rect.top + _rect.bottom) / _tex->GetOriginalHeight()));
	ver[(_SPosNo + 2) % vertexMaxCnt].tex = tmpVec;
	tmpVec = D3DXVECTOR2((float)(_rect.right / _tex->GetOriginalWidth())
		, (float)((_rect.top + _rect.bottom) / _tex->GetOriginalHeight()));
	ver[(_SPosNo + 3) % vertexMaxCnt].tex = tmpVec;
}

void ChTex::PolygonBoard9::Draw(
	const ChPtr::Shared<BaseTexture9>& _tex,
	const D3DXMATRIX& _mat)
{
	if (!*this)return;
	if (_tex == nullptr)return;

	DWORD tmpData;
	device->GetRenderState(D3DRS_CULLMODE, &tmpData);
	device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);


	if (alphaFlg)device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	device->SetTexture(0, _tex->GetTex());

	device->SetTransform(D3DTS_WORLD, &_mat);

	device->SetFVF((D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1));

	device->SetRenderState(D3DRS_LIGHTING, FALSE);
	device->SetRenderState(D3DRS_NORMALIZENORMALS, FALSE);

	device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, ver, sizeof(ChVertex9));

	device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ZERO);

	device->SetRenderState(D3DRS_NORMALIZENORMALS, true);
	device->SetRenderState(D3DRS_CULLMODE, tmpData);
}


#endif

#endif
//CopyRight Chronoss0518 2018/08