#ifndef Ch_D3D11_Light_h
#define Ch_D3D11_Light_h


namespace ChD3D11
{


	namespace ShaderParts
	{
		class Light11 final :public ChCp::Initializer, public ChCp::Releaser
		{
		public:

			///////////////////////////////////////////////////////////////////////////////////
			//Structures//
			struct DirectionalLight
			{
				ChVec3 dif;
				bool useLightFlg = false;
				ChVec3 dir;
				float ambPow = 0.0f;
			};

			struct PointLight
			{
				ChVec3 pos;
				float len = 10.0f;
				ChVec3 dif;
				bool useFlg = false;
			};

			struct LightData
			{
				ChVec3 camPos;
				DirectionalLight light;
				PointLight* pLight = nullptr;
			};

			///////////////////////////////////////////////////////////////////////////////////
			//InitAndRelease//

			void Init(ID3D11Device* _device, const unsigned long _bufferRegisterNo, const unsigned long _textureRegisterNo,const unsigned long _pointLightCount = 10);

			void Release()override;

			///////////////////////////////////////////////////////////////////////////////////
			//SetFunction//

			void SetLightDiffuse(const ChVec3& _dif);

			void SetUseLightFlg(const ChStd::Bool& _flg);

			void SetLightDir(const ChVec3& _dir);

			void SetLightAmbientPow(const float _amb);

			void SetDirectionLightData(const bool _useFlg, const ChVec3& _dif, const ChVec3& _dir, const float _ambPow);

			void SetPLightPos(const ChVec3& _pos, const unsigned long _no = 0);

			void SetPLightLen(const float _len, const unsigned long _no = 0);

			void SetPLightDiffuse(const ChVec3& _dif, const unsigned long _no = 0);

			void SetPLightUseFlg(const bool& _flg, const unsigned long _no = 0);

			void SetPointLightData(const bool _useFlg, const ChVec3& _dif, const ChVec3& _pos, const float _len, const unsigned long _no = 0);

			void SetCamPos(const ChVec3& _camPos);

			void SetLightData(const LightData& _ld);

			void SetPSDrawData(ID3D11DeviceContext* _dc);

			void SetVSDrawData(ID3D11DeviceContext* _dc);

			void SetDrawData(ID3D11DeviceContext* _dc);

			void SetImportLightPowMap(ChPtr::Shared<Texture11>& _lightPowMap);

			void SetRegisterNo(const unsigned long _registerNo);

			void SetTextureRegisterNo(const unsigned long _registerNo);

			void SetTexture(ID3D11DeviceContext* _dc);

			///////////////////////////////////////////////////////////////////////////////////
			//GetFunction//

			LightData GetLightData();

			///////////////////////////////////////////////////////////////////////////////////

			void ClearImportLightPowMap();

		private:

			void Update(ID3D11DeviceContext* _dc);


			struct UseLightData
			{
				ChVec3 camPos;
				int pLightCount = 10;
				DirectionalLight light;
				PointLight pLight[10];
			};

			UseLightData lightDatas;
			ID3D11Device* device = nullptr;
			ConstantBuffer11<UseLightData> buf;
			ChStd::Bool updateFlg = true;

			Texture11 lightPow;
			ChPtr::Shared<Texture11>importLightPowMap;
			unsigned long textureRegisterNo = 0;

			unsigned long pointlightCount = 0;
		};

	}

}


#endif
