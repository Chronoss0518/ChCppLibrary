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

	//��Light��Shader����BaseLight��PointLight�𗘗p���Ă�������//
	//�Ǝ��ō\�z���Ă���Shader�N���X//
	class ShaderController11 final :public ChCp::Initializer,public ChCp::Releaser
	{
	public://Init And Release//

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

	public://SetFunction//

		//�`�悳���郌���_�[�^�[�Q�b�g��o�^����//
		void SetRenderTarget(RenderTarget11& _tex);

		inline void SetBackColor(const ChVec4& _color)
		{
			if (!*this)return;
			if (drawFlg)return;

			backColor = _color;
		}

		//�`��Ώۂ��o�b�N�o�b�t�@�ɂ���//
		inline void SetBackBuffer()
		{
			if (!*this)return;
			if (drawFlg)return;

			renderTargets.clear();
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


	public://Is Functions//

		//�`��\�m�F�֐�//
		inline ChStd::Bool IsDraw() { return drawFlg; }

		inline ChStd::Bool IsRTDraw() { return rtDrawFlg; }

	public://Othre Functions//

		//�`��ΏۂƂȂ�摜�Q�̓o�^����������//
		inline void ClearRenderTargets()
		{
			renderTargets.clear();
		}

	public://Draw Functions//

		//�`��J�n�O�ɌĂԊ֐�//
		void DrawStart();

		//3D�̕`��J�n�O�ɌĂԊ֐�//
		void DrawStart3D();

		//2D�̕`��J�n�O�ɌĂԊ֐�//
		void DrawStart2D();

		//���ׂĂ̕`��I�����ɌĂԊ֐�//
		void DrawEnd();


	protected://Set Functions//

		//�����_�[�^�[�Q�b�g�p�t���O//
		inline void SetRTDraw(const ChStd::Bool _Flg) { rtDrawFlg = _Flg; }

	protected://Member Value//

		//�|���S���Ȃǃe�N�X�`���P�̕`��p�V�F�[�_�[//
		RenderTarget11 out3D;
		RenderTarget11 out2D;

		Sprite11 outSprite;

		ChPtr::Unique<Shader::BaseDrawSprite11> spriteShader = nullptr;

		//�`��Ώۂɐݒ肷��摜�Q//
		std::vector<ID3D11RenderTargetView*>renderTargets;

		ID3D11Device* device = nullptr;
		ID3D11DeviceContext* dc = nullptr;

		//DepthStencilBuffer�p//
		DepthStencilTexture11 dsBuffer;

		ShaderParts::DrawWindow window;

		ShaderParts::ViewPort view;
		
		//�`��\�t���O//
		ChStd::Bool drawFlg = false;
		ChStd::Bool rtDrawFlg = false;

		//�w�i�F//
		ChVec4 backColor = ChVec4(1.0f, 1.0f, 1.0f, 1.0f);

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