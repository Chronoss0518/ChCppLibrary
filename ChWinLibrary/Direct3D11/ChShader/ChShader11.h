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

	//��Light��Shader����BaseLight��PointLight�𗘗p���Ă�������//
	//�Ǝ��ō\�z���Ă���Shader�N���X//
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

		//�`�悳���郌���_�[�^�[�Q�b�g��o�^����//
		void SetRenderTarget(Texture11& _Tex);

		inline void SetBackColor(const ChVec4& _Color)
		{
			if (!*this)return;
			if (DrawFlg)return;

			BackColor = _Color;
		}

		//�`��Ώۂ��o�b�N�o�b�t�@�ɂ���//
		inline void SetBackBuffer()
		{
			if (!*this)return;
			if (DrawFlg)return;

			RenderTargets.clear();
		}

		//�`�������ۂɗ��p����J�����O�^�C�v���Z�b�g//
		inline void SetCullMode(const D3D11_CULL_MODE _CULL)
		{
			if (!*this)return;
			if (DrawFlg)return;

			Cull = _CULL;

			RasteriserUpdate = true;
		}

		//�`�������ۂɗ��p����t�B���^�C�v���Z�b�g//
		inline void SetFilMode(const D3D11_FILL_MODE _Fill)
		{
			if (!*this)return;
			if (DrawFlg)return;

			Fill = _Fill;

			RasteriserUpdate = true;
		}

		//�����ʂ��g�p���邩�ۂ��̃t���O//
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

		//�`��\�m�F�֐�//
		inline ChStd::Bool IsDraw() { return DrawFlg; }

		inline ChStd::Bool IsRTDraw() { return RTDrawFlg; }

		///////////////////////////////////////////////////////////////////////////////////

		//�`��ΏۂƂȂ�摜�Q�̓o�^����������//
		inline void ClearRenderTargets()
		{
			RenderTargets.clear();
		}

		///////////////////////////////////////////////////////////////////////////////////

		//�`��J�n�O�ɌĂԊ֐�//
		void DrawStart();

		///////////////////////////////////////////////////////////////////////////////////

		//�`��I�����ɌĂԊ֐�//
		void DrawEnd();

		///////////////////////////////////////////////////////////////////////////////////
		//Mesh�`��Q//

		void Draw(
			Mesh11& _Mesh
			, const ChMat_11& _Mat = ChMat_11());

		//OutLine�`��//
		void DrawOutLine(
			Mesh11& _Mesh
			, const ChVec4& _Color
			, const ChMat_11& _Mat = ChMat_11()
			, const float _Size = 1.0f);

		///////////////////////////////////////////////////////////////////////////////////
		//�|���S���`��Q//

		void Draw(
			Texture11& _Tex
			, PolygonBoard11& _Polygon
			, const ChMat_11& _Mat = ChMat_11());

		//�~�`�Ŏw��͈͂�`��//
		void DrawToCircleParsec(
			Texture11& _Tex
			, PolygonBoard11& _Polygon
			, const ChVec2& _StartLine
			, const float _DrawDot
			, const ChMat_11& _Mat = ChMat_11());

		//�l�p�`�Ŏw��͈͂�`��//
		void DrawSquareParsec(
			Texture11& _Tex
			, PolygonBoard11& _Polygon
			, const ChVec2& _StartLine
			, const float _DrawDot
			, const ChMat_11& _Mat = ChMat_11());

		///////////////////////////////////////////////////////////////////////////////////
		//Sprite�`��Q//

		//�ʏ�`��//
		void Draw(
			Texture11& _Tex
			, Sprite11& _Sprite
			, const ChMat_11& _Mat = ChMat_11());

		//�~�`�Ŏw��͈͂�`��//
		void DrawToCircleParsec(
			Texture11& _Tex
			, Sprite11& _Sprite
			, const ChVec2& _StartLine
			, const float _DrawDot
			, const ChMat_11& _Mat = ChMat_11());

		//�l�p�`�Ŏw��͈͂�`��//
		void DrawSquareParsec(
			Texture11& _Tex
			, Sprite11& _Sprite
			, const ChVec2& _StartLine
			, const float _DrawDot
			, const ChMat_11& _Mat = ChMat_11());

		///////////////////////////////////////////////////////////////////////////////////

	protected:

		//�����_�[�^�[�Q�b�g�p�t���O//
		inline void SetRTDraw(const ChStd::Bool _Flg) { RTDrawFlg = _Flg; }

		///////////////////////////////////////////////////////////////////////////////////

		//�`��f�[�^�̏�����//
		void SetDrawDatas();

		///////////////////////////////////////////////////////////////////////////////////

		void BaseDataUpdate();

		///////////////////////////////////////////////////////////////////////////////////

		//3D���f���`��p�V�F�[�_�[//
		VertexShader11 BVModel;
		PixelShader11 BPModel;
		VertexShader11 PoVTex;


		//�|���S���Ȃǃe�N�X�`���P�̕`��p�V�F�[�_�[//
		VertexShader11 SpVTex;
		PixelShader11 BPTex;

		//ShadowMap�����p//
		Texture11 DepthShadowTex;

		//���f���̉摜���Ȃ��ꍇ�ɃZ�b�g����//
		Texture11 WhiteTex;

		//���f���̖@���}�b�v���Ȃ��ꍇ�Ɏg�p����摜//
		Texture11 NormalTex;

		//�`��Ώۂɐݒ肷��摜�Q//
		std::vector<ID3D11RenderTargetView*>RenderTargets;
		ID3D11RenderTargetView** TmpView = nullptr;

		ID3D11Device* Device = nullptr;
		ID3D11DeviceContext* DC = nullptr;

		//DepthStencilBuffer�p//
		Texture11 DSBuffer;

		ShaderParts::DrawWindow Window;

		ShaderParts::ViewPort View;
		
		ShaderParts::ChLightHeader LightDatas;

		//�`��\�t���O//
		ChStd::Bool DrawFlg = false;
		ChStd::Bool RTDrawFlg = false;

		//�t�H�O�`��t���O//
		ChStd::Bool FogFlg = false;

		//�J�����O�^�C�v//
		D3D11_CULL_MODE Cull = D3D11_CULL_MODE::D3D11_CULL_NONE;

		//�ʕ`��^�C�v//
		D3D11_FILL_MODE Fill = D3D11_FILL_MODE::D3D11_FILL_SOLID;

		ID3D11RasterizerState* Rasteriser = nullptr;

		ChStd::Bool RasteriserUpdate = false;

		//�w�i�F//
		ChVec4 BackColor = ChVec4(1.0f, 1.0f, 1.0f, 1.0f);

		struct BaseDatas
		{
			//�r���[�ϊ��s��//
			ChMat_11 ViewMat;
			//�ˉe�ϊ��s��//
			ChMat_11 ProjMat;
			//��ʃT�C�Y//
			ChVec4 WindSize;
		};

		struct CharaDatas
		{
			//���f���s��//
			ChMat_11 ModelMat;

		};

		struct PolygonDatas
		{
			//���f���s��//
			ChMat_11 ModelMat;
			//�X�v���C�g�x�[�X�F//
			ChVec4 BaseColor = ChVec4(1.0f, 1.0f, 1.0f, 1.0f);
		};

		struct BoneDatas
		{
			//�X�L�����b�V���p�s��//
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