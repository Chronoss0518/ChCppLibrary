#ifndef Ch_D3D11_CB_Sprite_h
#define Ch_D3D11_CB_Sprite_h

#include"../ChCBBase11.h"
#include"../../../ShaderHeaderFiles/HLSL/5.0/DrawSprite.hlsli"

namespace ChD3D11
{
	namespace CB
	{
		class CBSprite11 final :public CBBase11
		{
		public:

			///////////////////////////////////////////////////////////////////////////////////
			//InitAndRelease//

			void Init(ID3D11Device* _device);

			void Release()override;

			///////////////////////////////////////////////////////////////////////////////////
			//SetFunction//

			void SetSpriteMatrix(const ChLMat& _mat);

			void SetBaseColor(const ChVec4& _color);

			inline void SetBaseTexture(ChPtr::Weak<TextureBase11> _tex)
			{
				baseTex = _tex;
			}

			void SetSpriteData(const ChS_SpriteData& _data);

			void SetPSSpriteData(ID3D11DeviceContext* _dc);

			void SetVSSpriteData(ID3D11DeviceContext* _dc);

			void SetShaderSpriteData(ID3D11DeviceContext* _dc);

			void SetShaderTexture(ID3D11DeviceContext* _dc);

			///////////////////////////////////////////////////////////////////////////////////
			//GetFunction//

			inline ChS_SpriteData GetSpriteData() { return spData; }

			inline ChLMat GetSpriteMatrix() { return spData.spriteMat; }

			inline ChVec4 GetBaseColor() { return spData.baseColor; }

		private:

			void UpdateSD(ID3D11DeviceContext* _dc);

			void SetShaderTexture(ID3D11DeviceContext* _dc, ChPtr::Weak<TextureBase11> _tex, TextureBase11& _defaultTex, const unsigned long _registerNo);

			ChS_SpriteData spData;
			ConstantBuffer11<ChS_SpriteData> spBuf;
			ChStd::Bool sUpdateFlg = true;

			ChPtr::Weak<TextureBase11>baseTex;
		};

	}

}


#endif
