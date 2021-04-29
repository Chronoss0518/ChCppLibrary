#ifndef Ch_D3D11_Shader_h
#define Ch_D3D11_Shader_h

#include"../ChShaderObject/ChShaderObject11.h"
#include"../ChShaderParts/ChShaderParts11.h"

namespace ChD3D11
{
	class DirectX3D11;

	class Mesh11;
	class Texture11;
	class Sprite11;
	class PolygonBoard11;

	using DLight = ShaderParts::ChLightHeader::DirectionalLight;
	using PLight = ShaderParts::ChLightHeader::PointLight;

	//※LightはShader内のBaseLightとPointLightを利用してください//
	//独自で構築しているShaderクラス//
	class ShaderController11 final :public ChCpp::ChCp::Initializer,public ChCpp::ChCp::Releaser
	{
	public:

		///////////////////////////////////////////////////////////////////////////////////
		//InitAndRelease//


		void Init(
			DirectX3D11& _ChDevice
			, const ChVec2& _WindSize);

		void Init(
			DirectX3D11& _ChDevice
			, const float& _WindWitdh
			, const float& _WindHeight);

		void Init(ID3D11Device* _d
			, ID3D11DeviceContext* _DC
			, IDXGISwapChain* _SC
			, const ChVec2& _WindSize);

		void Init(ID3D11Device* _d
			, ID3D11DeviceContext* _DC
			, IDXGISwapChain* _SC
			, const float& _WindWitdh
			, const float& _WindHeight);

	protected:

		void InitShader();

	public:

		void Release()override;

		///////////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		//描画させるレンダーターゲットを登録する//
		void SetRenderTarget(Texture11& _Tex);

		inline void SetBackColor(const ChVec4& _Color)
		{
			if (!*this)return;
			if (DrawFlg)return;

			BackColor = _Color;
		}

		//描画対象をバックバッファにする//
		inline void SetBackBuffer()
		{
			if (!*this)return;
			if (DrawFlg)return;

			RenderTargets.clear();
		}

		//描画をする際に利用するカリングタイプをセット//
		inline void SetCullMode(const D3D11_CULL_MODE _CULL)
		{
			if (!*this)return;
			if (DrawFlg)return;

			Cull = _CULL;

			RasteriserUpdate = true;
		}

		//描画をする際に利用するフィルタイプをセット//
		inline void SetFilMode(const D3D11_FILL_MODE _Fill)
		{
			if (!*this)return;
			if (DrawFlg)return;

			Fill = _Fill;

			RasteriserUpdate = true;
		}

		//霧効果を使用するか否かのフラグ//
		inline void SetFogFlg(ChStd::Bool _Flg)
		{
			if (!*this)return;
			if (DrawFlg)return;

			FogFlg = _Flg;
		}

		inline void SetViewMat(const ChMat_11& _ViewMat)
		{

			if (!*this)return;
			if (DrawFlg)return;

			BDObject.ViewMat = _ViewMat;

			BDUpdateFlg = true;

		}

		inline void SetProjMat(const ChMat_11& _ProjMat)
		{

			if (!*this)return;
			if (DrawFlg)return;

			BDObject.ProjMat = _ProjMat;

			BDUpdateFlg = true;

		}

		inline void SetWindPos(const ChVec2& _Pos)
		{

			if (!*this)return;
			if (DrawFlg)return;

			View.SetWindPos(_Pos);

		}

		inline void SetWindSize(const ChVec2& _Size)
		{

			if (!*this)return;
			if (DrawFlg)return;

			View.SetWindSize(_Size);
		}

		inline void SetLightDiffuse(const ChVec3& _Dif)
		{
			if (!*this)return;
			if (DrawFlg)return;

			LightDatas.SetLightDiffuse(_Dif);
		}

		inline void SetUseLightFlg(const ChStd::Bool& _Flg)
		{
			if (!*this)return;
			if (DrawFlg)return;

			LightDatas.SetUseLightFlg(_Flg);
		}

		inline void SetLightDir(const ChVec3& _Dir)
		{
			if (!*this)return;
			if (DrawFlg)return;

			LightDatas.SetLightDir(_Dir);
		}

		inline void SetLightAmbientPow(const float _Amb)
		{
			if (!*this)return;
			if (DrawFlg)return;

			LightDatas.SetLightAmbientPow(_Amb);
		}

		inline void SetPLightPos(const ChVec3& _Pos, const unsigned long _No = 0)
		{
			if (!*this)return;
			if (DrawFlg)return;

			LightDatas.SetPLightPos(_Pos, _No);
		}

		inline void SetPLightLen(const float _Len, const unsigned long _No = 0)
		{
			if (!*this)return;
			if (DrawFlg)return;

			LightDatas.SetPLightLen(_Len, _No);
		}

		inline void SetPLightDiffuse(const ChVec3& _Dif, const unsigned long _No = 0)
		{
			if (!*this)return;
			if (DrawFlg)return;

			LightDatas.SetPLightDiffuse(_Dif, _No);
		}

		inline void SetPLightUseFlg(const ChStd::Bool& _Flg, const unsigned long _No = 0)
		{
			if (!*this)return;
			if (DrawFlg)return;

			LightDatas.SetPLightUseFlg(_Flg, _No);
		}

		inline void SetCamPos(const ChVec3& _CamPos)
		{
			if (!*this)return;
			if (DrawFlg)return;

			LightDatas.SetCamPos(_CamPos);
		}

		inline void SetLightData(const ShaderParts::ChLightHeader::LightData& _LD)
		{
			if (!*this)return;
			if (DrawFlg)return;

			LightDatas.SetLightData(_LD);
		}

		inline void SetImportLightPowMap(ChPtr::Shared<Texture11>& _LightPowMap)
		{
			if (!*this)return;
			if (DrawFlg)return;

			LightDatas.SetImportLightPowMap(_LightPowMap);
		}

		///////////////////////////////////////////////////////////////////////////////////
		//GetFunction//

		inline D3D11_CULL_MODE GetCullMode() { return Cull; }

		inline D3D11_FILL_MODE GetFillMode() { return Fill; }

		///////////////////////////////////////////////////////////////////////////////////
		//IsFunction//

		void IsLight(const ChStd::Bool _Flg);

		//描画可能確認関数//
		inline ChStd::Bool IsDraw() { return DrawFlg; }

		inline ChStd::Bool IsRTDraw() { return RTDrawFlg; }

		///////////////////////////////////////////////////////////////////////////////////

		//描画対象となる画像群の登録を解除する//
		inline void ClearRenderTargets()
		{
			RenderTargets.clear();
		}

		///////////////////////////////////////////////////////////////////////////////////

		//描画開始前に呼ぶ関数//
		void DrawStart();

		///////////////////////////////////////////////////////////////////////////////////

		//描画終了時に呼ぶ関数//
		void DrawEnd();

		///////////////////////////////////////////////////////////////////////////////////
		//Mesh描画群//

		void Draw(
			Mesh11& _Mesh
			, const ChMat_11& _Mat = ChMat_11());

		//OutLine描画//
		void DrawOutLine(
			Mesh11& _Mesh
			, const ChVec4& _Color
			, const ChMat_11& _Mat = ChMat_11()
			, const float _Size = 1.0f);

		///////////////////////////////////////////////////////////////////////////////////
		//板ポリゴン描画群//

		void Draw(
			Texture11& _Tex
			, PolygonBoard11& _Polygon
			, const ChMat_11& _Mat = ChMat_11());

		//円形で指定範囲を描画//
		void DrawToCircleParsec(
			Texture11& _Tex
			, PolygonBoard11& _Polygon
			, const ChVec2& _StartLine
			, const float _DrawDot
			, const ChMat_11& _Mat = ChMat_11());

		//四角形で指定範囲を描画//
		void DrawSquareParsec(
			Texture11& _Tex
			, PolygonBoard11& _Polygon
			, const ChVec2& _StartLine
			, const float _DrawDot
			, const ChMat_11& _Mat = ChMat_11());

		///////////////////////////////////////////////////////////////////////////////////
		//Sprite描画群//

		//通常描画//
		void Draw(
			Texture11& _Tex
			, Sprite11& _Sprite
			, const ChMat_11& _Mat = ChMat_11());

		//円形で指定範囲を描画//
		void DrawToCircleParsec(
			Texture11& _Tex
			, Sprite11& _Sprite
			, const ChVec2& _StartLine
			, const float _DrawDot
			, const ChMat_11& _Mat = ChMat_11());

		//四角形で指定範囲を描画//
		void DrawSquareParsec(
			Texture11& _Tex
			, Sprite11& _Sprite
			, const ChVec2& _StartLine
			, const float _DrawDot
			, const ChMat_11& _Mat = ChMat_11());

		///////////////////////////////////////////////////////////////////////////////////

	protected:

		//レンダーターゲット用フラグ//
		inline void SetRTDraw(const ChStd::Bool _Flg) { RTDrawFlg = _Flg; }

		///////////////////////////////////////////////////////////////////////////////////

		//描画データの初期化//
		void SetDrawDatas();

		///////////////////////////////////////////////////////////////////////////////////

		void BaseDataUpdate();

		///////////////////////////////////////////////////////////////////////////////////

		//3Dモデル描画用シェーダー//
		VertexShader11 BVModel;
		PixelShader11 BPModel;
		VertexShader11 PoVTex;


		//板ポリゴンなどテクスチャ単体描画用シェーダー//
		VertexShader11 SpVTex;
		PixelShader11 BPTex;

		//ShadowMap生成用//
		Texture11 DepthShadowTex;

		//モデルの画像がない場合にセットする//
		Texture11 WhiteTex;

		//モデルの法線マップがない場合に使用する画像//
		Texture11 NormalTex;

		//描画対象に設定する画像群//
		std::vector<ID3D11RenderTargetView*>RenderTargets;
		ID3D11RenderTargetView** TmpView = nullptr;

		ID3D11Device* Device = nullptr;
		ID3D11DeviceContext* DC = nullptr;

		//DepthStencilBuffer用//
		Texture11 DSBuffer;

		ShaderParts::DrawWindow Window;

		ShaderParts::ViewPort View;
		
		ShaderParts::ChLightHeader LightDatas;

		//描画可能フラグ//
		ChStd::Bool DrawFlg = false;
		ChStd::Bool RTDrawFlg = false;

		//フォグ描画フラグ//
		ChStd::Bool FogFlg = false;

		//カリングタイプ//
		D3D11_CULL_MODE Cull = D3D11_CULL_MODE::D3D11_CULL_NONE;

		//面描画タイプ//
		D3D11_FILL_MODE Fill = D3D11_FILL_MODE::D3D11_FILL_SOLID;

		ID3D11RasterizerState* Rasteriser = nullptr;

		ChStd::Bool RasteriserUpdate = false;

		//背景色//
		ChVec4 BackColor = ChVec4(1.0f, 1.0f, 1.0f, 1.0f);

		struct BaseDatas
		{
			//ビュー変換行列//
			ChMat_11 ViewMat;
			//射影変換行列//
			ChMat_11 ProjMat;
			//画面サイズ//
			ChVec4 WindSize;
		};

		struct CharaDatas
		{
			//モデル行列//
			ChMat_11 ModelMat;

		};

		struct PolygonDatas
		{
			//モデル行列//
			ChMat_11 ModelMat;
			//スプライトベース色//
			ChVec4 BaseColor = ChVec4(1.0f, 1.0f, 1.0f, 1.0f);
		};

		struct BoneDatas
		{
			//スキンメッシュ用行列//
			ChMat_11 SkinWeightMat[1000];
		};

		ChStd::Bool BDUpdateFlg = true;

		BaseDatas BDObject;
		ConstantBuffer BaseData = nullptr;

		CharaDatas CDObject;
		ConstantBuffer CharaData = nullptr;

		PolygonDatas PDObject;
		ConstantBuffer PolygonData = nullptr;

		BoneDatas BoDObject;
		ConstantBuffer BoneData = nullptr;

		///////////////////////////////////////////////////////////////////////////////////

		Texture11 Out3D;
		Texture11 Out2D;

		Sprite11 OutSprite;

	public:

		static inline ShaderController11& GetIns()
		{
			static ShaderController11 Ins;
			return Ins;
		}

	private:

		ShaderController11() {}

	};

	static const std::function<ShaderController11& ()>Shader11 = ShaderController11::GetIns;

}

#endif
//CopyRight Chronoss0518 2018/08