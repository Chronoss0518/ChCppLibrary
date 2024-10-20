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
	template<typename CharaType>
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

		//レンダーターゲット用のテクスチャを設定//
		//第二引数で画面をクリアする色指定//
		//ChD3D9::Shader::DrawStartと併用できません//
		void SetRT(
			const std::basic_string<CharaType>& _dataName,
			const D3DCOLOR _backCol = D3DCOLOR_ARGB(0, 0, 0, 0));

	public://Get Functions//

		//作成したテクスチャを取得//
		inline ChPtr::Shared<Texture9> GetRTTexture(const std::basic_string<CharaType>& _dataName)
		{
			if (rtList.find(_dataName) == rtList.end())return nullptr;
			return rtList[_dataName];
		}

	public:

		//登録されてるテクスチャを選択して消去//
		void DeleteRTTexture(const std::basic_string<CharaType>& _dataName)
		{
			if (rtList.empty())return;
			if (rtList.find(_dataName) == rtList.end())return;

			rtList.erase(_dataName);
		}

		//レンダーターゲットとなるテクスチャを作成:登録//
		void CreateRT(
			const std::basic_string<CharaType>& _dataName,
			const UINT _rtWidth = 1280,
			const UINT _rtHeight = 720,
			const _D3DFORMAT _format = D3DFMT_A8R8G8B8);


		//登録してあるすべてのレンダーターゲットテクスチャを解放//
		void ClearRT();

		//レンダーターゲットをバックバッファに戻す//
		void ReturnRT();

	private:

		LPDIRECT3DDEVICE9 device;

		ChD3D9::ShaderController* uShader = nullptr;

		std::map<std::basic_string<CharaType>, ChPtr::Shared<BaseTexture9>>rtList;
		ChPtr::Shared<BaseTexture9>dbData;

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

	template<typename CharaType>
	inline RenderTargetManager9<CharaType>& RTManager9() { return  RenderTargetManager9<CharaType>::GetInc(); }

	inline RenderTargetManager9<char>& RTManagerA9() { return  RenderTargetManager9<char>::GetInc(); }
	inline RenderTargetManager9<wchar_t>& RTManagerW9() { return  RenderTargetManager9<wchar_t>::GetInc(); }


	inline
#ifdef UNICODE
		RenderTargetManager9<wchar_t>&
#else
		RenderTargetManager9<char>&
#endif
		RTManager9()
	{
#ifdef UNICODE
		RTManagerW9();
#else
		RTManagerA9();
#endif
	}


}

#endif