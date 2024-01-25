#ifndef Ch_D3D11_CB_Blur_h
#define Ch_D3D11_CB_Blur_h

#include"../ChCBBase11.h"
#include"../../../ShaderHeaderFiles/HLSL/5.0/Blur.hlsli"

namespace ChD3D11
{
	namespace CB
	{
		class CBBlur11 final :public CBBase11
		{
		public:

			virtual ~CBBlur11()
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

			void SetBlurData(const ChS_Blur& _data);

			void SetPSSpriteData(ID3D11DeviceContext* _dc);

			void SetVSSpriteData(ID3D11DeviceContext* _dc);

			void SetShaderSpriteData(ID3D11DeviceContext* _dc);

			void SetShaderTexture(ID3D11DeviceContext* _dc);

			///////////////////////////////////////////////////////////////////////////////////
			//GetFunction//

			inline ChS_Blur GetBlurData() { return blurData; }

			inline ChVec2 GetGameWindowSize() { return blurData.windowSize; }

			inline int GetBlurPower() { return blurData.blurPower; }

		private:

			void UpdateSD(ID3D11DeviceContext* _dc);

			ChS_Blur blurData;
			ConstantBuffer11<ChS_Blur> blurBuf;
			bool updateFlg = true;

		};

	}

}


#endif
