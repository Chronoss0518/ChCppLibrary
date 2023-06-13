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
	class ShaderController11 final :public ChCp::Initializer
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

		virtual void Release();

	public://SetFunction//

		//�`�悳���郌���_�[�^�[�Q�b�g��o�^����//
		void SetRenderTarget(RenderTarget11& _tex);

		inline void SetBackColor(const ChVec4& _color)
		{
			if (!*this)return;

			backColor = _color;
		}

		inline void SetWindPos(const ChVec2& _pos)
		{
			if (!*this)return;

			view.SetTopLeftPos(_pos);
		}

		inline void SetWindSize(const ChVec2& _size)
		{
			if (!*this)return;

			view.SetSize(_size);
		}

	public://Draw Functions//

		//�`��J�n�O�ɌĂԊ֐�//
		void DrawStart();

		//���ׂĂ̕`��I�����ɌĂԊ֐�//
		void DrawEnd();

		//���ׂĂ̕`��I�����ɌĂԊ֐�//
		void DrawEnd(ChD3D11::TextureBase11& _tex);

	protected://Member Value//

		Sprite11 outSprite;

		ChPtr::Unique<Shader::BaseDrawSprite11> spriteShader = nullptr;

		ID3D11Device* device = nullptr;
		ID3D11DeviceContext* dc = nullptr;

		//DepthStencilBuffer�p//
		DepthStencilTexture11 dsBuffer;

		ShaderParts::ViewPort view;
		
		//�w�i�F//
		ChVec4 backColor = ChVec4(1.0f, 1.0f, 1.0f, 1.0f);
		ShaderParts::DrawWindow window;

	public:

		static inline ShaderController11& GetIns()
		{
			static ShaderController11 ins;
			return ins;
		}

	private:

		ShaderController11() {}

		virtual ~ShaderController11() { Release(); }

	};

	static const std::function<ShaderController11& ()>Shader11 = ShaderController11::GetIns;

}

#endif
//CopyRight Chronoss0518 2018/08