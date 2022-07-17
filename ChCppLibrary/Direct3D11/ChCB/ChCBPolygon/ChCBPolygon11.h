#ifndef Ch_D3D11_CB_Polygon_h
#define Ch_D3D11_CB_Polygon_h

#include"../ChCBBase11.h"
#include"../../../ShaderHeaderFiles/HLSL/5.0/DrawPolygon.hlsli"

namespace ChD3D11
{
	namespace CB
	{
		class CBPolygon11 final :public CBBase11
		{
		public:

			///////////////////////////////////////////////////////////////////////////////////
			//InitAndRelease//

			void Init(ID3D11Device* _device);

			void Release()override;

			///////////////////////////////////////////////////////////////////////////////////
			//SetFunction//

			void SetFrameMatrix(const ChLMat& _mat);

			void SetWorldMatrix(const ChLMat& _mat);

			void SetViewMatrix(const ChLMat& _mat);

			void SetProjectionMatrix(const ChLMat& _mat);

			void SetWindSize(const ChVec2& _size);

			void SetMateDiffuse(const ChVec4& _diffuseCol);

			void SetMateSpecularColor(const ChVec3& _specularCol);

			void SetMateSpecularPower(const float _specularPow);

			void SetMateAmbientColor(const ChVec3& _ambientCol);

			void SetDrawData(const ChP_DrawData& _data);

			void SetCharaData(const ChP_CharaData& _data);

			void SetMaterialData(const ChP_Material& _data);

			void SetPSDrawData(ID3D11DeviceContext* _dc);

			void SetVSDrawData(ID3D11DeviceContext* _dc);

			void SetShaderDrawData(ID3D11DeviceContext* _dc);

			void SetPSCharaData(ID3D11DeviceContext* _dc);

			void SetVSCharaData(ID3D11DeviceContext* _dc);

			void SetShaderCharaData(ID3D11DeviceContext* _dc);

			void SetPSMaterialData(ID3D11DeviceContext* _dc);

			void SetVSMaterialData(ID3D11DeviceContext* _dc);

			void SetShaderMaterialData(ID3D11DeviceContext* _dc);

			void SetShaderTexture(ID3D11DeviceContext* _dc);

			///////////////////////////////////////////////////////////////////////////////////
			//GetFunction//

			inline ChP_DrawData GetDrawData() { return drawData; }

			inline ChP_CharaData GetCharaData() { return charaData; }

			inline ChP_Material GetMateData() { return mateData; }

		private:

			void UpdateDD(ID3D11DeviceContext* _dc);

			void UpdateCD(ID3D11DeviceContext* _dc);

			void UpdateMD(ID3D11DeviceContext* _dc);

			ChP_DrawData drawData;
			ConstantBuffer11<ChP_DrawData> drawBuf;
			ChStd::Bool dUpdateFlg = true;
			ChP_CharaData charaData;
			ConstantBuffer11<ChP_CharaData> charaBuf;
			ChStd::Bool cUpdateFlg = true;
			ChP_Material mateData;
			ConstantBuffer11<ChP_Material> mateBuf;
			ChStd::Bool mUpdateFlg = true;

			ChPtr::Weak<TextureBase11>baseTex;
			ChPtr::Weak<TextureBase11>normalTex;

		};

	}

}


#endif
