#ifndef Ch_D3D9_Shader_h
#define Ch_D3D9_Shader_h

#include"../ChVertexData9.h"

namespace ChMesh
{
	class BaseMesh9;
}

namespace ChTex
{
	typedef class BaseTexture9 Texture9;

	class RenderTargetList9;
	template<typename CharaType>
	class RenderTargetManager9;
}

namespace ChD3D9
{



	//※LightはShader内のBaseLightとPointLightを利用してください//
	//独自で構築しているShaderクラス//
	class ShaderController:public ChCp::Initializer
	{
	protected:

		struct LambertLight
		{
			ChVec4 dif = ChVec4(1.0f, 1.0f, 1.0f, 1.0f);
			ChVec3_9 dir = ChVec3_9(0.0f, -1.0f, 0.0f);
			float ambPow = 0.3f;
		};

		struct PointLight
		{
			PointLight() {}

			ChVec3 dif = ChVec3(1.0f);
			float len = 1.0f;
			ChVec3_9 pos = ChVec3_9();
			bool flg;
		};

		struct Material
		{
			ChVec4 dif;
			ChVec3 speCol;
			float spePow;
		};

		struct TmpPLight
		{

			ChVec3 dif = ChVec3(1.0f);
			ChVec3_9 pos = ChVec3_9();
			float len = 1.0f;
		};

	public:

		struct PointLights
		{
			PointLight light[7];

			PointLight& operator[](int _Num)
			{
				return light[_Num];
			}
		};

	public:

		friend ChTex::RenderTargetList9;
		friend ChTex::RenderTargetManager9<char>;
		friend ChTex::RenderTargetManager9<wchar_t>;
		friend ChTex::RenderTargetManager9<char16_t>;
		friend ChTex::RenderTargetManager9<char32_t>;
#ifdef CPP17
		friend ChTex::RenderTargetManager9<char8_t>;
#endif
	public://InitAndRelease//

		//第一引数にChLibraryの入っているDirectoryPathを選択//
		void Init(const LPDIRECT3DDEVICE9 _d,
			const D3DPRESENT_PARAMETERS& param,
			const float& _windWidth = 1280.0f,
			const float& _windHeight = 720.0f);

		virtual void Release();

	protected://InitAndRelease//

		void InitShader();

		void ReleaseTextures();

	public://Set Functions//

		//描画をする際に利用するカリングタイプをセット//
		inline void SetCullMode(const CULL _cull)
		{
			cull = _cull;
			device->SetRenderState(D3DRS_CULLMODE, static_cast<unsigned char>(_cull));
		}

		//霧効果を使用するか否かのフラグ//
		inline void SetFogFlg(bool _flg) { fogFlg = _flg; }

		//Windサイズの設定//
		inline void SetWindSize(const float _w, const float _h)
		{
			windSize.w = _w;
			windSize.h = _h;
		}

		inline void SetWindSize(const ChVec4& _Size)
		{
			windSize = _Size;
		}

		//自身の用意したライトの強さを表すテクスチャを利用するためのフラグ//
		inline void SetLightPowTexFlg(const bool _Flg)
		{
			if (GetMyLightTex() == nullptr)return;
			useMyLightTex = _Flg;
		}

		inline void SetCamPos(const ChVec3_9& _pos) { camPos = _pos; }

		inline void SetUseLightFlg(const bool _flg) { lightUseFlg = _flg; }

	protected://Set Functions//

		//レンダーターゲット用フラグ//
		inline void SetRTDraw(const bool _flg) { rtDrawFlg = _flg; }

		//描画データの初期化//
		void SetDrawDatas(const D3DCOLOR&_backColor);

		//標準マテリアルから自身の使うマテリアル型への変更//
		Material SetMateData(const D3DMATERIAL9& _mate);

		void SetLightFunction();

	public://Get Functions//

		inline LambertLight& GetLightInstanse() { return light; }

		inline PointLights& GetPointLightInstanse() { return posLight; }

		inline CULL GetCullMode() { return cull; }

		inline ChVec2 GetWindSize() { return windSize; }

	protected://Get Functions//

		ChTex::BaseTexture9* GetWhiteTex();
		
		ChTex::BaseTexture9* GetNormalTex();
		
		ChTex::BaseTexture9* GetLightEffectTex();
		
		ChTex::BaseTexture9* GetBeforeTex();

		ChTex::BaseTexture9* GetMyLightTex();

	public://Is Functions//

		//描画可能確認関数//
		inline bool IsDraw()
		{
			return drawFlg;
		}

		inline bool IsRTDraw() { return rtDrawFlg; }

	public://Create Functions//

		void CreateLightPowTex(const std::string& _lightPowTexName);

		void CreateLightPowTex(const std::wstring& _lightPowTexName);

		void CreateBeforeTex();

	public://Draw Functions//

		//描画開始前に呼ぶ関数//
		//ChTex::RenderTargetManager9::SetRT//
		//ChTex::RenderTargetList9::SetRTとは併用できません//
		void DrawStart(const D3DCOLOR& _backColor = D3DCOLOR_ARGB(255, 255, 255, 255));

		//描画終了時に呼ぶ関数//
		//ChTex::RenderTargetManager9::ReturnRT//
		//ChTex::RenderTargetList9::ReturnRTとは併用できません//
		void DrawEnd();

		//Mesh描画用関数//
		void DrawMesh(
			const ChMesh::BaseMesh9& _mesh,
			const ChMat_9& _mat = ChMat_9());

		//Mesh描画用関数//
		void DrawMeshContour(
			const ChMesh::BaseMesh9& _mesh,
			const ChVec4& _color,
			const ChMat_9& _mat = ChMat_9(),
			const float _size = 1.0f);

		//板ポリゴン描画//
		void DrawPolygonBoard(
			const ChTex::Texture9& _tex,
			const VertexData& _vertex,
			const ChMat_9& _mat = ChMat_9(),
			const unsigned int _triangleCount = 2);

		//スプライト描画//
		void DrawSprite(
			const ChTex::Texture9& _tex,
			const ChMat_9& _mat = ChMat_9(),
			const SpriteData& _spData = SpriteData(ChVec2(0.0f, 0.0f), windSize));

	protected://Make Functions//

		void MakeWhiteTexture();

		void MakeLightingPowTexture();

		void MakeNormalMapTexture();

protected://Member Values//

		//3Dモデル描画用シェーダー//
		LPDIRECT3DVERTEXSHADER9 bVModel = nullptr;
		LPDIRECT3DPIXELSHADER9 bPModel = nullptr;
		LPDIRECT3DVERTEXSHADER9 cVModel = nullptr;
		LPDIRECT3DPIXELSHADER9 cPModel = nullptr;

		//板ポリゴンなどテクスチャ単体描画用シェーダー//
		LPDIRECT3DVERTEXSHADER9 spVTex = nullptr;
		LPDIRECT3DVERTEXSHADER9 poVTex = nullptr;
		LPDIRECT3DPIXELSHADER9 bPTex = nullptr;

		LPD3DXCONSTANTTABLE pixelCnstant = nullptr;
		LPD3DXCONSTANTTABLE vertexCnstant = nullptr;

		bool allCreateFlg = false;

		//ベースとなる頂点情報//
		LPDIRECT3DVERTEXDECLARATION9 baseDec = nullptr;

		//頂点情報変更用//
		LPDIRECT3DVERTEXDECLARATION9 tVerDec = nullptr;
		LPDIRECT3DVERTEXDECLARATION9 mVerDec = nullptr;

		bool lightUseFlg = false;

		//専用ライト//
		LambertLight light = LambertLight();

		//専用ポイントライト//
		PointLights posLight = PointLights();

		ChVec3_9 camPos = ChVec3_9();

		LPDIRECT3DDEVICE9 device = nullptr;

		//Device初期化用パラメータ//
		D3DPRESENT_PARAMETERS param{ 0 };

		LPDIRECT3DCUBETEXTURE9 ambTex = nullptr;

		bool useMyLightTex = false;

		//描画可能フラグ//
		bool drawFlg = false;
		bool rtDrawFlg = false;

		//フォグ描画フラグ//
		bool fogFlg = false;

		//ウィンドサイズ//
		static ChVec2 windSize;

		//カリングタイプ//
		CULL cull = CULL::NONE;

		//モデルの画像がない場合にセットする//
		ChPtr::Shared<ChTex::BaseTexture9>whiteTex = nullptr;

		//モデルの法線マップがない場合に使用する画像//
		ChPtr::Shared<ChTex::BaseTexture9>normalTex = nullptr;

		//ライトの強さを表す画像情報//
		ChPtr::Shared<ChTex::BaseTexture9>lightEffectTex = nullptr;

		//ひとつ前の描画保存用//
		ChPtr::Shared<ChTex::Texture9>beforeTex = nullptr;

		//ライトの強さを設定する画像//
		ChPtr::Shared<ChTex::Texture9>myLightTex = nullptr;



	public:

		static inline ShaderController& GetIns()
		{
			static ShaderController ins;
			return ins;
		}

	protected:

		ShaderController() {}

		virtual ~ShaderController()
		{
			Release();
		}

	};

	inline ShaderController& Shader() { return ShaderController::GetIns(); }
}

#endif
//CopyRight Chronoss0518 2018/08