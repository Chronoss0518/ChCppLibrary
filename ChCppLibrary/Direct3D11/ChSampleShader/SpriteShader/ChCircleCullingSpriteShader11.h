#ifndef Ch_D3D11_SS_CircleCullingSprite_h
#define Ch_D3D11_SS_CircleCullingSprite_h

#include"../ChSampleShaderBase11.h"


namespace ChD3D11
{

	class Sprite11;

	namespace Shader
	{

		class CircleCullingSprite11 final :public SampleShaderBase11
		{
		public:

			virtual ~CircleCullingSprite11()
			{
				Release();
			}

		public://Init And Release//

			void Init(ID3D11Device* _device)override;

			void Release()override;

		protected://Init And Release//

			void InitVertexShader()override;

			void InitPixelShader()override;

		public://Set Functions//

			inline void SetAlphaBlendFlg(const bool _flg) { alphaBlendFlg = _flg; }

			void SetStartDrawDir(const ChVec2& _dir);

			void SetCenterPos(const ChVec2& _pos);
			
			void SetDrawValue(const float& _dir);

		public://Get Functions//

			inline float GetDrawValue() { return circleCullingData.GetDrawValue(); }

			inline ChLMat GetSpriteMatrix() { return spriteData.GetSpriteMatrix(); }

			inline ChVec4 GetBaseColor() { return spriteData.GetBaseColor(); }

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

			CB::CBSprite11 spriteData;
			CB::CBCircleCulling11 circleCullingData;

			VertexBuffer11<Ch3D::Vertex> vertexBuffer;
			IndexBuffer11 indexBuffer;

			bool alphaBlendFlg = false;

		};
	}
}



#endif