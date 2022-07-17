#ifndef Ch_D3D11_CB_Sprite_h
#define Ch_D3D11_CB_Sprite_h


#include"../../../ShaderHeaderFiles/HLSL/5.0/DrawSprite.hlsli"

namespace ChD3D11
{
	namespace CB
	{
		class CBSprite11 final :public ChCp::Initializer, public ChCp::Releaser
		{
		public:

			///////////////////////////////////////////////////////////////////////////////////
			//InitAndRelease//

			void Init(ID3D11Device* _device);

			void Release()override;

			///////////////////////////////////////////////////////////////////////////////////
			//SetFunction//

			void SetSpriteMatrix(const ChLMat& _mat);

			void SetWindSize(const ChVec2& _size);

			void SetBaseColor(const ChVec4& _color);

			void SetDrawData(const ChS_DrawData& _data);

			void SetSpriteData(const ChS_SpriteData& _data);

			void SetPSDrawData(ID3D11DeviceContext* _dc);

			void SetVSDrawData(ID3D11DeviceContext* _dc);

			void SetShaderDrawData(ID3D11DeviceContext* _dc);

			void SetPSSpriteData(ID3D11DeviceContext* _dc);

			void SetVSSpriteData(ID3D11DeviceContext* _dc);

			void SetShaderSpriteData(ID3D11DeviceContext* _dc);

			void SetShaderTexture(ID3D11DeviceContext* _dc);

			///////////////////////////////////////////////////////////////////////////////////
			//GetFunction//

			inline ChS_DrawData GetDrawData() { return drawData; }

			inline ChS_SpriteData GetCharaData() { return spData; }

		private:

			void UpdateDD(ID3D11DeviceContext* _dc);

			void UpdateSD(ID3D11DeviceContext* _dc);

			void SetShaderTexture(ID3D11DeviceContext* _dc, ChPtr::Weak<TextureBase11> _tex, TextureBase11& _defaultTex, const unsigned long _registerNo);

			ChS_DrawData drawData;
			ConstantBuffer11<ChS_DrawData> drawBuf;
			ChStd::Bool dUpdateFlg = true;
			ChS_SpriteData spData;
			ConstantBuffer11<ChS_SpriteData> spBuf;
			ChStd::Bool sUpdateFlg = true;

			ID3D11Device* device = nullptr;

			ChPtr::Weak<TextureBase11>baseTex;
		};

	}

}


#endif
