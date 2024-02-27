#ifndef Ch_D3D11_SS_BasicHghlight_h
#define Ch_D3D11_SS_BasicHghlight_h

#include"ChSampleSpriteShaderBase11.h"


namespace ChD3D11
{

	class Sprite11;

	namespace Shader
	{

		class BasicHighlightShader11 final :public SampleSpriteShaderBase11
		{
		public:

			virtual ~BasicHighlightShader11()
			{
				Release();
			}

		public://Init And Release//

			void Init(ID3D11Device* _device)override;

			void Release()override;

		protected://Init And Release//

			void InitPixelShader()override;

		public://Set Functions//

			inline void SetBlurPower(const int& _blurPower) { highlightMapData.SetBlurPower(_blurPower); }

			inline void SetGameWindowSize(const ChVec2& _size) { highlightMapData.SetGameWindowSize(_size); }

			inline void SetLiteBlurFlg(const bool _flg) { highlightMapData.SetLiteBlurFlg(_flg); }

		public://Get Functions//

			inline int GetBlurPower() { return highlightMapData.GetBlurPower(); }

			inline ChVec2 GetGameWindowSize() { return highlightMapData.GetGameWindowSize(); }

			inline bool GetLiteBlurFlg() { return highlightMapData.GetLiteBlurFlg(); }

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

			CB::CBHighlight11 highlightMapData;

		};
	}
}



#endif