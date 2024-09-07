#ifndef Ch_D3D9_ReTa_h
#define Ch_D3D9_ReTa_h

namespace ChD3D9
{
	class ShaderController;
}

namespace ChTex
{

	typedef class BaseTexture9 Texture9;

	//レンダーターゲットを設定するクラス//
	class RenderTargetManager9:public ChCp::Initializer
	{
	public://Init And Release//

		void Init(
			const LPDIRECT3DDEVICE9& _dv,
			const unsigned short _windWidth,
			const unsigned short _windHeight,
			const ChD3D9::ShaderController* _shader = nullptr);

		virtual void Release();

	private:

		void CreateDBData();

	public://Set Functions//

#ifdef CRT
		//レンダーターゲット用のテクスチャを設定//
		//第二引数で画面をクリアする色指定//
		//ChD3D9::Shader::DrawStartと併用できません//
		void SetRT(
			const std::string& _dataName,
			const D3DCOLOR _backCol = D3DCOLOR_ARGB(0, 0, 0, 0))
		{
			if (rtList.find(_dataName) == rtList.end())return;
			if (dbData == nullptr)return;

			if (ChPtr::NotNullCheck(uShader))
			{
				if (uShader->IsDraw())return;
			}

			device->SetRenderTarget(0, rtList[_dataName]->GetSur());
			device->SetDepthStencilSurface(rtList[_dataName]->GetZBu());


			if (ChPtr::NotNullCheck(uShader))
			{
				uShader->SetRTDraw(true);
				uShader->SetDrawDatas(_backCol);
			}

		}
#endif

	public://Get Functions//

#ifdef CRT
		//作成したテクスチャを取得//
		inline ChPtr::Shared<Texture9> GetRTTexture(const std::string& _dataName)
		{
			if (rtList.find(_dataName) == rtList.end())return nullptr;
			return rtList[_dataName];
		}
#endif

	private:

		BaseTexture9* GetDBData();

	public:

#ifdef CRT
		
		
		//登録されてるテクスチャを選択して消去//
		void DeleteRTTexture(const std::string& _dataName)
		{
			if (rtList.empty())return;
			if (rtList.find(_dataName) == rtList.end())return;

			rtList.erase(_dataName);
		}

		//レンダーターゲットとなるテクスチャを作成:登録//
		void CreateRT(
			const std::string& _dataName,
			const UINT _rtWidth = 1280,
			const UINT _rtHeight = 720,
			const _D3DFORMAT _format = D3DFMT_A8R8G8B8)
		{
			if (_rtWidth <= 0 || _rtHeight <= 0)return;
			if (rtList.find(_dataName) != rtList.end())return;

			auto tmpRT = ChPtr::Make_S<Texture9>();

			tmpRT->CreateMinuColTexture<D3DCOLOR>(
				device,
				D3DCOLOR_ARGB(0, 0, 0, 0),
				_rtWidth,
				_rtHeight,
				_format,
				D3DUSAGE_RENDERTARGET,
				D3DPOOL_DEFAULT);

			if (ChPtr::NullCheck(tmpRT->GetTex()))return;

			tmpRT->CreateSurface(0);

			if (ChPtr::NullCheck(tmpRT->GetSur()))return;

			tmpRT->CreateZBuffer(device);

			if (ChPtr::NullCheck(tmpRT->GetZBu()))return;

			rtList[_dataName] = tmpRT;
	}

#endif

		//登録してあるすべてのレンダーターゲットテクスチャを解放//
		void ClearRT();

		//レンダーターゲットをバックバッファに戻す//
		void ReturnRT();

	private:

		LPDIRECT3DDEVICE9 device;

		ChD3D9::ShaderController* uShader = nullptr;


#ifdef CRT

		std::map<std::string, ChPtr::Shared<BaseTexture9>>rtList;

		ChPtr::Shared<BaseTexture9>dbData;

#endif

	private://ConstructerDestructer//

		RenderTargetManager9() {};

		virtual ~RenderTargetManager9() { Release(); };


	public:

		static RenderTargetManager9& GetInc()
		{
			static RenderTargetManager9 ins;
			return ins;
		}

	};

	inline RenderTargetManager9& RTManager9() { return  RenderTargetManager9::GetInc(); }

}

#ifdef CRT

void ChTex::RenderTargetManager9::CreateDBData()
{
	dbData = ChPtr::Make_S<Texture9>();
}

//登録してあるすべてのレンダーターゲットテクスチャを解放//
void ChTex::RenderTargetManager9::ClearRT()
{
	if (rtList.empty())return;
	rtList.clear();
}

#endif

#endif