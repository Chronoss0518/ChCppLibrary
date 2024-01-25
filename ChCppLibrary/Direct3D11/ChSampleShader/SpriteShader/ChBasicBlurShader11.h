#ifndef Ch_D3D11_SS_BasicBlur_h
#define Ch_D3D11_SS_BasicBlur_h

#include"ChSampleSpriteShaderBase11.h"


namespace ChD3D11
{

	class Sprite11;

	namespace Shader
	{

		class BasicBlurShader11 final :public SampleSpriteShaderBase11
		{
		public:

			virtual ~BasicBlurShader11()
			{
				Release();
			}

		public://Init And Release//

			void Init(ID3D11Device* _device)override;

			void Release()override;

		protected://Init And Release//

			void InitPixelShader()override;

		public://Set Functions//

			inline void SetBlurPower(const int& _blurPower) { blurData.SetBlurPower(_blurPower); }

			void SetGameWindowSize(const ChVec2& _size) { blurData.SetGameWindowSize(_size); }

		public://Get Functions//

			inline int GetBlurPower() { return blurData.GetBlurPower(); }

			inline ChVec2 GetGameWindowSize() { return blurData.GetGameWindowSize(); }

		public://Other Functions//

			//�ʏ�`��//
			void Draw(
				TextureBase11& _tex
				, Sprite11& _sprite
				, const ChMat_11& _mat = ChMat_11());

			//�ʏ�`��//
			void Draw(
				TextureBase11& _tex
				, Sprite11& _sprite
				, const ChVec4& _baseColor
				, const ChMat_11& _mat = ChMat_11());

		private://Member Value//

			CB::CBBlur11 blurData;

		};
	}
}



#endif