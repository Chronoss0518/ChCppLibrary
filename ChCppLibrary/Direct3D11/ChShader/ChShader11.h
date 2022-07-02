#ifndef Ch_D3D11_Shader_h
#define Ch_D3D11_Shader_h

#include"../ChShaderObject/ChShaderObject11.h"
#include"../ChShaderParts/ChShaderParts11.h"

namespace ChD3D11
{
	class DirectX3D11;

	class Mesh11;
	class TextureBase11;
	class Texture11;
	class RenderTarget11;
	class DepthStencilTexture11;
	class Sprite11;
	class PolygonBoard11;

	using DLight = ShaderParts::ChLightHeader::DirectionalLight;
	using PLight = ShaderParts::ChLightHeader::PointLight;

	//※LightはShader内のBaseLightとPointLightを利用してください//
	//独自で構築しているShaderクラス//
	class ShaderController11 final :public ChCp::Initializer,public ChCp::Releaser
	{
	public:

		///////////////////////////////////////////////////////////////////////////////////
		//InitAndRelease//


		void Init(
			DirectX3D11& _chDevice
			, const ChVec2& _windSize);

		void Init(
			DirectX3D11& _chDevice
			, const float& _windWitdh
			, const float& _windHeight);

		void Init(ID3D11Device* _d
			, ID3D11DeviceContext* _dc
			, IDXGISwapChain* _sc
			, const ChVec2& _windSize);

		void Init(ID3D11Device* _d
			, ID3D11DeviceContext* _dc
			, IDXGISwapChain* _sc
			, const float& _windWitdh
			, const float& _windHeight);

		void Release()override;

		///////////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		//描画させるレンダーターゲットを登録する//
		void SetRenderTarget(RenderTarget11& _tex);

		inline void SetBackColor(const ChVec4& _color)
		{
			if (!*this)return;
			if (drawFlg)return;

			backColor = _color;
		}

		//描画対象をバックバッファにする//
		inline void SetBackBuffer()
		{
			if (!*this)return;
			if (drawFlg)return;

			renderTargets.clear();
		}

		//描画をする際に利用するカリングタイプをセット//
		inline void SetCullMode(const D3D11_CULL_MODE _cull)
		{
			if (!*this)return;
			if (drawFlg)return;

			cull = _cull;

			rasteriserUpdate = true;
		}

		//描画をする際に利用するフィルタイプをセット//
		inline void SetFillMode(const D3D11_FILL_MODE _fill)
		{
			if (!*this)return;
			if (drawFlg)return;

			fill = _fill;

			rasteriserUpdate = true;
		}

		//霧効果を使用するか否かのフラグ//
		inline void SetFogFlg(ChStd::Bool _flg)
		{
			if (!*this)return;
			if (drawFlg)return;

			fogFlg = _flg;
		}

		inline void SetViewMat(const ChMat_11& _viewMat)
		{

			if (!*this)return;
			if (drawFlg)return;

			bdObject.viewMat = _viewMat;

			bdUpdateFlg = true;

		}

		inline void SetProjMat(const ChMat_11& _projMat)
		{

			if (!*this)return;
			if (drawFlg)return;

			bdObject.projMat = _projMat;

			bdUpdateFlg = true;

		}

		inline void SetWindPos(const ChVec2& _pos)
		{

			if (!*this)return;
			if (drawFlg)return;

			view.SetTopLeftPos(_pos);

		}

		inline void SetWindSize(const ChVec2& _size)
		{

			if (!*this)return;
			if (drawFlg)return;

			view.SetSize(_size);
		}

		inline void SetLightDiffuse(const ChVec3& _dif)
		{
			if (!*this)return;
			if (drawFlg)return;

			lightDatas.SetLightDiffuse(_dif);
		}

		inline void SetUseLightFlg(const ChStd::Bool& _flg)
		{
			if (!*this)return;
			if (drawFlg)return;

			lightDatas.SetUseLightFlg(_flg);
		}

		inline void SetCamPos(const ChVec3& _camPos)
		{
			if (!*this)return;
			if (drawFlg)return;

			lightDatas.SetCamPos(_camPos);
		}

		inline void SetLightData(const ShaderParts::ChLightHeader _ld)
		{
			if (!*this)return;
			if (drawFlg)return;

			lightDatas = _ld;
		}

		inline void SetImportLightPowMap(ChPtr::Shared<Texture11>& _lightPowMap)
		{
			if (!*this)return;
			if (drawFlg)return;

			lightDatas.SetImportLightPowMap(_lightPowMap);
		}

		///////////////////////////////////////////////////////////////////////////////////
		//GetFunction//

		inline D3D11_CULL_MODE GetCullMode() { return cull; }

		inline D3D11_FILL_MODE GetFillMode() { return fill; }

		inline ShaderParts::ChLightHeader GetLightDatas() { return lightDatas; }

		inline BaseDatas GetBaseData() { return bdObject; }

		inline CharaDatas GetCharaData() { return cdObject; }

		inline PolygonDatas GetPolygonData() { return pdObject; }

		inline BoneDatas GetBoneData() { return bodObject; }

		///////////////////////////////////////////////////////////////////////////////////
		//IsFunction//

		void IsLight(const ChStd::Bool _flg);

		//描画可能確認関数//
		inline ChStd::Bool IsDraw() { return drawFlg; }

		inline ChStd::Bool IsRTDraw() { return rtDrawFlg; }

		///////////////////////////////////////////////////////////////////////////////////

		//描画対象となる画像群の登録を解除する//
		inline void ClearRenderTargets()
		{
			renderTargets.clear();
		}

		///////////////////////////////////////////////////////////////////////////////////

		//描画開始前に呼ぶ関数//
		void DrawStart();

		//描画終了時に呼ぶ関数//
		void DrawEnd();

		///////////////////////////////////////////////////////////////////////////////////
		//Mesh描画群//

		void Draw(
			Mesh11& _mesh
			, const ChMat_11& _mat = ChMat_11());

		void Draw(
			Mesh11& _mesh,
			VertexShader11& _userVS,
			PixelShader11& _userPS,
			const ChMat_11& _mat = ChMat_11());

		//OutLine描画//
		void DrawOutLine(
			Mesh11& _mesh
			, const ChVec4& _color
			, const ChMat_11& _mat = ChMat_11()
			, const float _size = 1.0f);

		///////////////////////////////////////////////////////////////////////////////////
		//板ポリゴン描画群//

		void Draw(
			TextureBase11& _tex
			, PolygonBoard11& _polygon
			, const ChMat_11& _mat = ChMat_11());

		void Draw(
			TextureBase11& _tex,
			PolygonBoard11& _polygon,
			VertexShader11& _userVS,
			PixelShader11& _userPS,
			const ChMat_11& _mat = ChMat_11());

		//円形で指定範囲を描画//
		void DrawToCircleParsec(
			TextureBase11& _tex
			, PolygonBoard11& _polygon
			, const ChVec2& _startLine
			, const float _drawRad
			, const ChMat_11& _mat = ChMat_11());

		//四角形で指定範囲を描画//
		void DrawSquareParsec(
			TextureBase11& _tex
			, PolygonBoard11& _polygon
			, const ChVec2& _startLine
			, const float _drawRad
			, const ChMat_11& _mat = ChMat_11());

		///////////////////////////////////////////////////////////////////////////////////
		//Sprite描画群//

		//通常描画//
		void Draw(
			TextureBase11& _tex
			, Sprite11& _sprite
			, const ChMat_11& _mat = ChMat_11());

		void Draw(
			TextureBase11& _tex,
			Sprite11& _sprite,
			VertexShader11& _userVS,
			PixelShader11& _userPS,
			const ChMat_11& _mat = ChMat_11());

		//円形で指定範囲を描画//
		void DrawToCircleParsec(
			TextureBase11& _tex
			, Sprite11& _sprite
			, const ChVec2& _startLine
			, const float _drawRad
			, const ChMat_11& _mat = ChMat_11());

		//四角形で指定範囲を描画//
		void DrawSquareParsec(
			TextureBase11& _tex
			, Sprite11& _sprite
			, const ChVec2& _startLine
			, const float _drawRad
			, const ChMat_11& _mat = ChMat_11());

		///////////////////////////////////////////////////////////////////////////////////

	protected:

		//レンダーターゲット用フラグ//
		inline void SetRTDraw(const ChStd::Bool _Flg) { rtDrawFlg = _Flg; }

		///////////////////////////////////////////////////////////////////////////////////

		//描画データの初期化//
		void SetDrawDatas();

		///////////////////////////////////////////////////////////////////////////////////

		//3Dモデル描画用シェーダー//
		VertexShader11 bvModel;
		PixelShader11 bpModel;
		VertexShader11 pvTex;

		//板ポリゴンなどテクスチャ単体描画用シェーダー//
		VertexShader11 spvTex;
		PixelShader11 bpTex;

		//ShadowMap生成用//
		RenderTarget11 depthShadowTex;

		//モデルの画像がない場合にセットする//
		Texture11 whiteTex;

		//モデルの法線マップがない場合に使用する画像//
		Texture11 normalTex;

		//描画対象に設定する画像群//
		std::vector<ID3D11RenderTargetView*>renderTargets;
		ID3D11RenderTargetView** tmpView = nullptr;

		ID3D11Device* device = nullptr;
		ID3D11DeviceContext* dc = nullptr;

		//DepthStencilBuffer用//
		DepthStencilTexture11 dsBuffer;

		ShaderParts::DrawWindow window;

		ShaderParts::ViewPort view;
		
		ShaderParts::ChLightHeader lightDatas;

		//描画可能フラグ//
		ChStd::Bool drawFlg = false;
		ChStd::Bool rtDrawFlg = false;

		//フォグ描画フラグ//
		ChStd::Bool fogFlg = false;

		//カリングタイプ//
		D3D11_CULL_MODE cull = D3D11_CULL_MODE::D3D11_CULL_NONE;

		//面描画タイプ//
		D3D11_FILL_MODE fill = D3D11_FILL_MODE::D3D11_FILL_SOLID;

		ID3D11RasterizerState* rasteriser = nullptr;

		ChStd::Bool rasteriserUpdate = true;

		//背景色//
		ChVec4 backColor = ChVec4(1.0f, 1.0f, 1.0f, 1.0f);

		ChStd::Bool bdUpdateFlg = true;

		BaseDatas bdObject;
		ConstantBuffer11<BaseDatas> baseData;

		CharaDatas cdObject;
		ConstantBuffer11<CharaDatas> charaData;

		PolygonDatas pdObject;
		ConstantBuffer11<PolygonDatas> polygonData;

		BoneDatas bodObject;
		ConstantBuffer11<BoneDatas> boneData;

		///////////////////////////////////////////////////////////////////////////////////

		RenderTarget11 out3D;
		RenderTarget11 out2D;

		Sprite11 outSprite;

	public:

		static inline ShaderController11& GetIns()
		{
			static ShaderController11 ins;
			return ins;
		}

	private:

		ShaderController11() {}

	};

	static const std::function<ShaderController11& ()>Shader11 = ShaderController11::GetIns;

}

#endif
//CopyRight Chronoss0518 2018/08