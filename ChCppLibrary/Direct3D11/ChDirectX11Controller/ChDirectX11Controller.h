
#ifndef Ch_D3D11_DXCo_h
#define Ch_D3D11_DXCo_h

namespace ChWin
{
	class WindObject;
};

namespace ChD3D11
{

	//Direct3D11を利用するために作られたクラス//
	class DirectX3D11:public ChCp::Initializer,public ChCp::Releaser
	{
	public://Init and Release//

		void Init(
			HWND _hWnd, 
			const ChStd::Bool _fullScreenFlg, 
			const unsigned long _scrW,
			const unsigned long _scrH);

		void Init(
			ChWin::WindObject& _windObject,
			const ChStd::Bool _fullScreenFlg);

		void Release()override;

	public://Get Functions//

		//Direct3D11をつかさどるデバイスの取得//
		inline ID3D11Device* const GetDevice()
		{
			return device;
		}

		//描画をつかさどるデバイスの取得//
		inline ID3D11DeviceContext* const GetDC()
		{
			return dContext;
		}

		inline IDXGISwapChain* const GetSC()
		{
			return window;
		}

	public://Is Functions//

		//デバイスが存在するかしないかの確認//
		inline ChStd::Bool IsInstanse()
		{
			if (ChPtr::NullCheck(device))return false;
			if (ChPtr::NullCheck(dContext))return false;
			if (ChPtr::NullCheck(window))return false;
			return true;
		}

	protected://Create Fucntions// 

		void CreateDevice(
			HWND _hWnd
			, const unsigned short _scrW
			, const unsigned short _scrH);

	protected://Member Value//

		//基本オブジェクトをつかさどるデバイス//
		ID3D11Device* device = nullptr;

		//描画用デバイス//
		ID3D11DeviceContext* dContext = nullptr;

		//保持するWindowデータ//
		IDXGISwapChain* window = nullptr;

	};

	inline DirectX3D11& D3D11API()
	{
		static DirectX3D11 ins;
		return ins;
	}

	inline ID3D11Device* D3D11Device()
	{
		return D3D11API().GetDevice();
	};


	inline ID3D11DeviceContext* D3D11DC()
	{
		return D3D11API().GetDC();
	};
}

#endif