#ifndef Ch_D3D11_SS_BaseSprite_h
#define Ch_D3D11_SS_BaseSprite_h

#include"../ChSampleShaderBase11.h"


namespace ChD3D11
{

	class Sprite11;

	namespace Shader
	{

		class BaseDrawSprite11 final :public SampleShaderBase11
		{
		public://Init And Release//

			void Init(ID3D11Device* _device);

			void Release();

		protected://Init And Release//

			void InitVertexShader()override;

			void InitPixelShader()override;

		public://Set Functions//

			inline void SetAlphaBlendFlg(const bool _flg) { alphaBlendFlg = _flg; }

		public://Get Functions//

			inline ChLMat GetSpriteMatrix() { return spriteData.GetSpriteMatrix(); }

			inline ChVec4 GetBaseColor() { return spriteData.GetBaseColor(); }

		public://Other Functions//

			//í èÌï`âÊ//
			void Draw(
				ID3D11DeviceContext* _dc
				, TextureBase11& _tex
				, Sprite11& _sprite
				, const ChMat_11& _mat = ChMat_11());

		//í èÌï`âÊ//
			void Draw(
				ID3D11DeviceContext* _dc
				, TextureBase11& _tex
				, Sprite11& _sprite
				, const ChVec4& _baseColor
				, const ChMat_11& _mat = ChMat_11());

		private://Member Value//

			CB::CBSprite11 spriteData;

			VertexBuffer11<Ch3D::Vertex> vertexBuffer;
			IndexBuffer11 indexBuffer;

			bool alphaBlendFlg = false;

		};
	}
}



#endif