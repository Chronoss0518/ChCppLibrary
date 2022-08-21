#ifndef Ch_D3D11_SS_BaseSprite_h
#define Ch_D3D11_SS_BaseSprite_h

#include"../ChSampleShaderBase11.h"


namespace ChD3D11
{

	class Sprite11;

	namespace Shader
	{

		class BaseDrawSprite final :public SampleShaderBase11
		{
		public://Init And Release//

			void Init(ID3D11Device* _device);

			void Release();

		protected://Init And Release//

			void InitVertexShader()override;

			void InitPixelShader()override;

		public://Set Functions//

			void SetSpriteMatrix(const ChLMat& _mat);

		public://Get Functions//

			inline ChLMat GetSpriteMatrix() { return spriteData.GetSpriteMatrix(); }

			inline D3D11_FILL_MODE GetFillMode() { return fill; }

			inline D3D11_CULL_MODE GetCullMode() { return cull; }

		public://Other Functions//

		//í èÌï`âÊ//
			void Draw(
				ID3D11DeviceContext* _dc
				, TextureBase11& _tex
				, Sprite11& _sprite
				, const ChMat_11& _mat = ChMat_11());

		private:

			void Update();

		private://Member Value//

			CB::CBSprite11 spriteData;

			D3D11_FILL_MODE fill = D3D11_FILL_MODE::D3D11_FILL_SOLID;
			D3D11_CULL_MODE cull = D3D11_CULL_MODE::D3D11_CULL_NONE;
			ChStd::Bool updateFlg = true;

			VertexBuffer11<Ch3D::Vertex> vertexBuffer;
			IndexBuffer11 indexBuffer;

		};
	}
}



#endif