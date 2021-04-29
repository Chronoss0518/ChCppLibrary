#ifndef Ch_D3D9_Shader_h
#define Ch_D3D9_Shader_h

#include"../ChVertexData9.h"

namespace ChMesh
{
	typedef class BaseMesh9 Mesh9;
}

namespace ChTex
{
	typedef class BaseTexture9 Texture9;

	class RenderTargetList9;
	class RenderTargetManager9;
}

namespace ChD3D9
{



	//※LightはShader内のBaseLightとPointLightを利用してください//
	//独自で構築しているShaderクラス//
	class ShaderController:public ChCpp::ChCp::InitPack
	{

	protected:

		struct LambertLight
		{
			ChStd::COLOR1f Dif = ChStd::COLOR1f(1.0f, 1.0f, 1.0f, 1.0f);
			ChVec3_9 Dir = ChVec3_9(0.0f, -1.0f, 0.0f);
			float AmbPow = 0.3f;
		};

		struct PointLight
		{
			PointLight() {}

			ChVec3 Dif = ChVec3(1.0f);
			float Len = 1.0f;
			ChVec3_9 Pos = ChVec3_9();
			bool Flg;
		};

		struct Material
		{

			ChStd::COLOR1f Dif;
			ChVec3 SpeCol;
			float SpePow;
		};

	public:

		///////////////////////////////////////////////////////////////////////////////////
		//InitAndRelease//

		//第一引数にChLibraryの入っているDirectoryPathを選択//
		void Init(const LPDIRECT3DDEVICE9 _d
			, const D3DPRESENT_PARAMETERS Param
			, const float& _WindWidth = 1280.0f
			, const float& _WindHeight = 720.0f);

		void Release();

		///////////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		//描画をする際に利用するカリングタイプをセット//
		inline void SetCullMode(const CULL _CULL)
		{
			Device->SetRenderState(D3DRS_CULLMODE, ChStd::EnumCast(_CULL));
		}

		//霧効果を使用するか否かのフラグ//
		inline void SetFogFlg(ChStd::Bool _Flg) { FogFlg = _Flg; }

		//Windサイズの設定//
		inline void SetWindSize(const float _w, const float _h)
		{
			WindSize.w = _w;
			WindSize.h = _h;
		}

		inline void SetWindSize(const ChStd::FPOINT& _Size)
		{
			WindSize = _Size;
		}

		//自身の用意したライトの強さを表すテクスチャを利用するためのフラグ//
		inline void SetLightPowTexFlg(const ChStd::Bool _Flg)
		{
			if (MyLightTex == nullptr)return;
			UseMyLightTex = _Flg;
		}

		inline void SetCamPos(const ChVec3_9& _Pos) { CamPos = _Pos; }

		///////////////////////////////////////////////////////////////////////////////////
		//GetFunction//

		inline LambertLight& GetLightInstanse() { return Light; }

		struct PointLights
		{
			PointLight Light[7];

			PointLight& operator[](int _Num)
			{
				return Light[_Num];
			}
		};

		inline PointLights& GetPointLightInstanse() { return PosLight; }

		inline ChStd::FPOINT GetWindSize()
		{
			return WindSize;
		}

		///////////////////////////////////////////////////////////////////////////////////
		//IsFunction//

		void IsLight(const ChStd::Bool _Flg);

		//描画可能確認関数//
		inline ChStd::Bool IsDraw()
		{
			return DrawFlg;
		}

		inline ChStd::Bool IsRTDraw() { return RTDrawFlg; }

		///////////////////////////////////////////////////////////////////////////////////

		//描画開始前に呼ぶ関数//
		//ChTex::RenderTargetManager9::SetRT//
		//ChTex::RenderTargetList9::SetRTとは併用できません//
		void DrawStart(const D3DCOLOR& _BackColor = D3DCOLOR_ARGB(255, 255, 255, 255));

		///////////////////////////////////////////////////////////////////////////////////

		//描画終了時に呼ぶ関数//
		//レンダーターゲット利用した際にFlgをTrueにする//
		void DrawEnd(const ChStd::Bool& _RTFlg = false);

		///////////////////////////////////////////////////////////////////////////////////

		//Mesh描画用関数//
		void DrawMesh(
			const ChPtr::Shared<ChMesh::Mesh9> _Mesh
			, const ChMat_9& _Mat = ChMat_9());

		///////////////////////////////////////////////////////////////////////////////////

		//板ポリゴン描画//
		void DrawPolygonBoard(
			const ChPtr::Shared<ChTex::Texture9>& _Tex
			, const VertexData& _Vertex
			, const ChMat_9& _Mat = ChMat_9()
			, const unsigned int _TriangleCount = 2);

		///////////////////////////////////////////////////////////////////////////////////

		//スプライト描画//
		void DrawSprite(
			const ChPtr::Shared<ChTex::Texture9>& _Tex
			, const ChMat_9& _Mat = ChMat_9()
			, const SpriteData&_SpData = SpriteData(ChStd::FPOINT(0.0f, 0.0f), WindSize));

		///////////////////////////////////////////////////////////////////////////////////

		void CreateLightPowTex(const std::string& _LightPowTexName);

		///////////////////////////////////////////////////////////////////////////////////

		friend ChTex::RenderTargetList9;
		friend ChTex::RenderTargetManager9;

	protected:

		//レンダーターゲット用フラグ//
		inline void SetRTDraw(const ChStd::Bool _Flg) { RTDrawFlg = _Flg; }

		///////////////////////////////////////////////////////////////////////////////////

		//レンダーターゲットを利用する際に使用する描画データの初期化//
		void SetDrawDatas(const D3DCOLOR&
			_BackColor);

		///////////////////////////////////////////////////////////////////////////////////

		struct TmpPLight
		{
			
			ChVec3 Dif = ChVec3(1.0f);
			ChVec3_9 Pos = ChVec3_9();
			float Len = 1.0f;
		};

		void MakeBlurFuncNum();

		///////////////////////////////////////////////////////////////////////////////////

		//白色の画像生成関数//
		void MakeWhiteTexture();

		///////////////////////////////////////////////////////////////////////////////////

		//ライトの強さを表すテクスチャの生成//
		void MakeLightingPowTexture();

		///////////////////////////////////////////////////////////////////////////////////

		//法線マップ生成用関数//
		void MakeNormalMapTexture();

		///////////////////////////////////////////////////////////////////////////////////

		//標準マテリアルから自身の使うマテリアル型への変更//
		Material SetMateData(D3DMATERIAL9& _Mate);

		///////////////////////////////////////////////////////////////////////////////////

		void SetLightFunction();

		///////////////////////////////////////////////////////////////////////////////////

		//3Dモデル描画用シェーダー//
		LPDIRECT3DVERTEXSHADER9 BVModel = nullptr;
		LPDIRECT3DPIXELSHADER9 BPModel = nullptr;

		//板ポリゴンなどテクスチャ単体描画用シェーダー//
		LPDIRECT3DVERTEXSHADER9 SpVTex = nullptr;
		LPDIRECT3DVERTEXSHADER9 PoVTex = nullptr;
		LPDIRECT3DPIXELSHADER9 BPTex = nullptr;

		LPD3DXCONSTANTTABLE PixelCnstant;
		LPD3DXCONSTANTTABLE VertexCnstant;

		ChStd::Bool AllCreateFlg = false;

		//ベースとなる頂点情報//
		LPDIRECT3DVERTEXDECLARATION9 BaseDec = nullptr;

		//頂点情報変更用//
		LPDIRECT3DVERTEXDECLARATION9 TVerDec = nullptr;
		LPDIRECT3DVERTEXDECLARATION9 MVerDec = nullptr;

		//モデルの画像がない場合にセットする//
		ChPtr::Shared<ChTex::BaseTexture9>WhiteTex = nullptr;

		//モデルの法線マップがない場合に使用する画像//
		ChPtr::Shared<ChTex::BaseTexture9>NormalTex = nullptr;

		//ライトの強さを表す画像情報//
		ChPtr::Shared<ChTex::BaseTexture9>LightEffectTex = nullptr;

		//ひとつ前の描画保存用//
		ChPtr::Shared<ChTex::Texture9>BeforeTex = nullptr;

		ChStd::Bool LightUseFlg = false;

		ChStd::Bool SetLightFlg = false;

		//専用ライト//
		LambertLight Light;

		//専用ポイントライト//
		PointLights PosLight;

		ChVec3_9 CamPos;

		LPDIRECT3DDEVICE9 Device;

		//Device初期化用パラメータ//
		D3DPRESENT_PARAMETERS Param;

		LPDIRECT3DCUBETEXTURE9 AmbTex;

		//ライトの強さを設定する画像//
		ChPtr::Shared<ChTex::Texture9>MyLightTex = nullptr;

		ChStd::Bool UseMyLightTex = false;

		//描画可能フラグ//
		ChStd::Bool DrawFlg = false;
		ChStd::Bool RTDrawFlg = false;

		//フォグ描画フラグ//
		ChStd::Bool FogFlg = false;

		//ウィンドサイズ//
		static ChStd::FPOINT WindSize;

		///////////////////////////////////////////////////////////////////////////////////
	public:

		static inline ShaderController& GetIns()
		{
			static ShaderController Ins;
			return Ins;
		}

	protected:

		ShaderController() {}

		~ShaderController() {}

	};

	static const std::function<ShaderController&()>Shader = ShaderController::GetIns;

}

#endif
//CopyRight Chronoss0518 2018/08