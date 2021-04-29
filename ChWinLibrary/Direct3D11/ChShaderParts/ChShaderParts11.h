#ifndef Ch_D3D11_SParts_h
#define Ch_D3D11_SParts_h

namespace ChD3D11
{
	namespace ShaderParts
	{
		class ViewPort final
		{

		public:

			///////////////////////////////////////////////////////////////////////////////////
			//SetFunction//

			inline void SetWindPos(const ChVec2& _Pos) { View.TopLeftX = _Pos.x; View.TopLeftY = _Pos.y; }

			inline void SetWindSize(const ChVec2& _Size) { View.Width = _Size.x; View.Height = _Size.y; }

			inline void SetDrawDepth(const float _Min,const float _Max) { View.MinDepth = _Min; View.MaxDepth = _Max; }

			void SetDrawData(ID3D11DeviceContext* _DC);

			///////////////////////////////////////////////////////////////////////////////////

		private:

			D3D11_VIEWPORT View;

		};

		class DrawWindow final:public ChCpp::ChCp::Initializer
		{

		public:

			///////////////////////////////////////////////////////////////////////////////////
			//InitAndRelease//

			void Init(
				ID3D11Device* _Device
				,IDXGISwapChain* _SC);

			void Release();

			///////////////////////////////////////////////////////////////////////////////////
			//SetFunction//

			void SetSwapEffect(const DXGI_SWAP_EFFECT& _Effect) { SEffect = _Effect; }

			void SetDrawData(ID3D11DeviceContext* _DC, ID3D11DepthStencilView* _DSView = nullptr);

			///////////////////////////////////////////////////////////////////////////////////

			void ClearView(ID3D11DeviceContext* _DC,const ChVec4& _Color);

			///////////////////////////////////////////////////////////////////////////////////

			void Draw();

			///////////////////////////////////////////////////////////////////////////////////


		private:

			IDXGISwapChain* Window = nullptr;

			//描画後にバックバッファを消去する等のフラグメント//
			DXGI_SWAP_EFFECT SEffect = DXGI_SWAP_EFFECT_DISCARD;

			//描画用//
			ID3D11RenderTargetView* BBTargetView = nullptr;
		};

		class ChLightHeader final :public ChCpp::ChCp::Initializer,public ChCpp::ChCp::Releaser
		{
		public:

			///////////////////////////////////////////////////////////////////////////////////
			//Structures//
			struct DirectionalLight
			{
				ChVec3 Dif;
				bool UseLightFlg = false;
				ChVec3 Dir;
				float AmbPow = 0.0f;
			};

			struct PointLight
			{
				ChVec3 Pos;
				float Len = 10.0f;
				ChVec3 Dif;
				bool UseFlg = false;
			};

			struct LightData
			{
				ChVec3 CamPos;
				DirectionalLight Light;
				PointLight PLight[10];
			};

			///////////////////////////////////////////////////////////////////////////////////
			//InitAndRelease//

			void Init(ID3D11Device* _Device);

			void Release()override;

			///////////////////////////////////////////////////////////////////////////////////
			//SetFunction//

			void SetLightDiffuse(const ChVec3& _Dif);

			void SetUseLightFlg(const ChStd::Bool& _Flg);

			void SetLightDir(const ChVec3& _Dir);

			void SetLightAmbientPow(const float _Amb);

			void SetPLightPos(const ChVec3& _Pos,const unsigned long _No = 0);

			void SetPLightLen(const float _Len, const unsigned long _No = 0);

			void SetPLightDiffuse(const ChVec3& _Dif, const unsigned long _No = 0);

			void SetPLightUseFlg(const ChStd::Bool& _Flg, const unsigned long _No = 0);

			void SetCamPos(const ChVec3& _CamPos);

			void SetLightData(const LightData& _LD);

			void SetPSDrawData(ID3D11DeviceContext* _DC);

			void SetVSDrawData(ID3D11DeviceContext* _DC);

			void SetDrawData(ID3D11DeviceContext* _DC);

			void SetImportLightPowMap(ChPtr::Shared<Texture11>& _LightPowMap);

			///////////////////////////////////////////////////////////////////////////////////
			//GetFunction//

			LightData GetLightData();

			///////////////////////////////////////////////////////////////////////////////////

			void ClearImportLightPowMap();

		private:

			void SetTexture(ID3D11DeviceContext* _DC);

			void Update(ID3D11DeviceContext* _DC);

			struct UseLightData
			{
				ChVec3 CamPos;
				int PLightCount = 10;
				DirectionalLight Light;
				PointLight PLight[10];
			};

			UseLightData LightDatas;
			ID3D11Device* Device = nullptr;
			ConstantBuffer Buf = nullptr;
			ChStd::Bool UpdateFlg = true;

			Texture11 LightPow;
			ChPtr::Shared<Texture11>ImportLightPowMap;
		};

	}

}


#endif
