#ifndef Ch_D3D9_RTList_h
#define Ch_D3D9_RTList_h

namespace ChD3D9
{
	class ShaderController;
}

namespace ChTex
{

	typedef class BaseTexture9 Texture9;

	//レンダーターゲットを設定するクラス//
	typedef class RenderTargetList9 :public ChCp::Initializer
	{
	public://Constructer Destructer//

		RenderTargetList9() {};

		virtual ~RenderTargetList9()
		{
			Release();
		}

	public://Init And Release//

		void Init(
			const LPDIRECT3DDEVICE9& _dv,
			const unsigned short _windWidth,
			const unsigned short _windHeight,
			const ChD3D9::ShaderController* _shader = nullptr);

		virtual void Release();

	private:

		void CreateDBData();

		BaseTexture9* GetDBData();

		void ReleaseDBData();

	public://Set Functions//

		//レンダーターゲット用のテクスチャを設定//
		//第二引数で画面をクリアする色指定//
		//ChD3D9::Shader::DrawStartと併用できません//
		void SetRT(
			const unsigned short _dataNum,
			const D3DCOLOR _backCol = D3DCOLOR_ARGB(0,0,0,0));

	public://RTTexture Control Functions//

		//作成したテクスチャを取得//
		Texture9* GetRTTexture(const unsigned short _dataNum);

		//登録されてるテクスチャを選択して消去//
		void DeleteRTTexture(const unsigned short _dataNum);

		//登録してあるすべてのレンダーターゲットテクスチャを解放//
		void ClearRT();

#ifdef CRT
		//レンダーターゲットとなるテクスチャを作成:登録//
		void CreateRT(
			const unsigned short _dataNum,
			const UINT _rtWidth = 1280,
			const UINT _rtHeight = 720,
			const _D3DFORMAT _format = D3DFMT_A8R8G8B8)

		{
			if (_rtWidth <= 0 || _rtHeight <= 0)return;

			auto&& rt = GetRTTexture(_dataNum);
			if (ChPtr::NullCheck(rt))return;

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
			rtList[_dataNum] = tmpRT;
		}
#endif

		//レンダーターゲットをバックバッファに戻す//
		void ReturnRT();

	private://Member Value//

		LPDIRECT3DDEVICE9 device;

		ChD3D9::ShaderController* uShader = nullptr;
#ifdef CRT

		std::map<unsigned short, ChPtr::Shared<BaseTexture9>>rtList;

		ChPtr::Shared<BaseTexture9>dbData = nullptr;

#endif

	}ChRTList9;

}

#ifdef CRT


void ChTex::RenderTargetList9::CreateDBData()
{
	dbData = ChPtr::Make_S<Texture9>();
}

ChTex::BaseTexture9* ChTex::RenderTargetList9::GetDBData()
{
	return dbData.get();
}

void ChTex::RenderTargetList9::ReleaseDBData()
{
	dbData = nullptr;
}

//作成したテクスチャを取得//
ChTex::BaseTexture9* ChTex::RenderTargetList9::GetRTTexture(const unsigned short _dataNum)
{
	auto&& rt = rtList.find(_dataNum);
	if (rt == rtList.end())return nullptr;
	return rt->second.get();
}

//登録されてるテクスチャを選択して消去//
void ChTex::RenderTargetList9::DeleteRTTexture(const unsigned short _dataNum)
{
	if (rtList.empty())return;
	auto&& rt = rtList.find(_dataNum);
	if (rt == rtList.end())return;

	rtList.erase(rt);
}

//登録してあるすべてのレンダーターゲットテクスチャを解放//
void ChTex::RenderTargetList9::ClearRT()
{
	if (rtList.empty())return;
	rtList.clear();
}

#endif

#endif