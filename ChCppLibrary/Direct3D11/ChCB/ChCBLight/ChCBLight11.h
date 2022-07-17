#ifndef Ch_D3D11_Light_h
#define Ch_D3D11_Light_h


#include"../../../ShaderHeaderFiles/HLSL/5.0/Light.hlsli"

namespace ChD3D11
{
	namespace CB
	{

		class Light11 final :public ChCp::Initializer, public ChCp::Releaser
		{
		public:

			///////////////////////////////////////////////////////////////////////////////////
			//InitAndRelease//

			void Init(ID3D11Device* _device, const unsigned long _bufferRegisterNo, const unsigned long _textureRegisterNo);

			void Release()override;

			///////////////////////////////////////////////////////////////////////////////////
			//SetFunction//

			void SetLightDiffuse(const ChVec3& _dif);

			void SetUseLightFlg(const bool& _flg);

			void SetLightDir(const ChVec3& _dir);

			void SetLightAmbientPow(const float _amb);

			void SetDirectionLightData(const bool _useFlg, const ChVec3& _dif, const ChVec3& _dir, const float _ambPow);

			void SetPLightPos(const ChVec3& _pos, const unsigned long _no = 0);

			void SetPLightLen(const float _len, const unsigned long _no = 0);

			void SetPLightDiffuse(const ChVec3& _dif, const unsigned long _no = 0);

			void SetPLightUseFlg(const bool& _flg, const unsigned long _no = 0);

			void SetPointLightData(const bool _useFlg, const ChVec3& _dif, const ChVec3& _pos, const float _len, const unsigned long _no = 0);

			void SetCamPos(const ChVec3& _camPos);

			void SetLightData(const ChLightData& _ld);

			void SetPSDrawData(ID3D11DeviceContext* _dc);

			void SetVSDrawData(ID3D11DeviceContext* _dc);

			void SetDrawData(ID3D11DeviceContext* _dc);

			void SetImportLightPowMap(ChPtr::Shared<TextureBase11>& _lightPowMap);

			void SetRegisterNo(const unsigned long _registerNo);

			void SetTextureRegisterNo(const unsigned long _registerNo);

			void SetTexture(ID3D11DeviceContext* _dc);

			///////////////////////////////////////////////////////////////////////////////////
			//GetFunction//

			ChLightData GetLightData();

			///////////////////////////////////////////////////////////////////////////////////

			void ClearImportLightPowMap();

		private:

			void Update(ID3D11DeviceContext* _dc);

			ChLightData lightDatas;
			ID3D11Device* device = nullptr;
			ConstantBuffer11<ChLightData> buf;
			ChStd::Bool updateFlg = true;

			Texture11 lightPow;
			ChPtr::Shared<TextureBase11>importLightPowMap;
			unsigned long textureRegisterNo = 0;

		};

	}

}


#endif
