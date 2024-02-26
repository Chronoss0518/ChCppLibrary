#ifndef Ch_D3D11_CB_Blur_h
#define Ch_D3D11_CB_Blur_h

#include"../ChCBBase11.h"
#include"../../../ShaderHeaderFiles/HLSL/5.0/HighlightMap.hlsli"

namespace ChD3D11
{
	namespace CB
	{
		class CBHighlightMap11 final :public CBBase11
		{
		public:

			virtual ~CBHighlightMap11()
			{
				Release();
			}

		public:

			///////////////////////////////////////////////////////////////////////////////////
			//InitAndRelease//

			void Init(
				ID3D11Device* _device);

			void Release()override;

			///////////////////////////////////////////////////////////////////////////////////
			//SetFunction//

			void SetGameWindowSize(const ChVec2& _size);

			void SetBlurPower(const int& _power);

			void SetLiteBlurFlg(const bool _flg);

			void SetBlurData(const ChS_HighLight& _data);

			void SetPSSpriteData(ID3D11DeviceContext* _dc);

			void SetVSSpriteData(ID3D11DeviceContext* _dc);

			void SetShaderSpriteData(ID3D11DeviceContext* _dc);

			///////////////////////////////////////////////////////////////////////////////////
			//GetFunction//

			inline ChS_HighLight GetBlurData() { return blurData; }

			inline ChVec2 GetGameWindowSize() { return blurData.windowSize; }

			inline int GetBlurPower() { return blurData.blurPower; }

			inline bool GetLiteBlurFlg() { return blurData.liteBlurFlg == 1; }

		private:

			void UpdateSD(ID3D11DeviceContext* _dc);

			ChS_HighLight blurData;
			ConstantBuffer11<ChS_HighLight> blurBuf;
			bool updateFlg = true;

		};

	}

}


#endif
