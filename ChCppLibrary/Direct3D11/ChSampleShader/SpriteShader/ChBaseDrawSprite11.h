#ifndef Ch_D3D11_SS_BaseSprite_h
#define Ch_D3D11_SS_BaseSprite_h

#include"ChSampleSpriteShaderBase11.h"


namespace ChD3D11
{

	class Sprite11;

	namespace Shader
	{

		class BaseDrawSprite11 final :public SampleSpriteShaderBase11
		{
		public:

			virtual ~BaseDrawSprite11()
			{
				Release();
			}

		public://Init And Release//

			void Init(ID3D11Device* _device)override;

			void Release()override;

		protected://Init And Release//

			void InitPixelShader()override;

		public://Other Functions//

			//í èÌï`âÊ//
			void Draw(
				TextureBase11& _tex
				, Sprite11& _sprite
				, const ChMat_11& _mat = ChMat_11());

		//í èÌï`âÊ//
			void Draw(
				TextureBase11& _tex
				, Sprite11& _sprite
				, const ChVec4& _baseColor
				, const ChMat_11& _mat = ChMat_11());

		private://Member Value//


		};
	}
}



#endif