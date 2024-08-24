
#include<Windows.h>
#include"../../BaseIncluder/ChBase.h"
#include"../../BaseIncluder/ChD3D9I.h"

#include"../../WindowsObject/MsgBox/ChMsgBox.h"


using namespace ChD3D9;

void DirectX3D9Base::Release()
{
	if (!IsInit())return;

	if (ChPtr::NotNullCheck(d3d9))d3d9->Release(); d3d9 = nullptr;
	if (ChPtr::NotNullCheck(backBuffer))backBuffer->Release(); backBuffer = nullptr;
	if (ChPtr::NotNullCheck(device))device->Release(); device = nullptr;

	SetInitFlg(false);
}

void DirectX3D9Base::Init()
{
	if (ChPtr::NullCheck(device))return;

	// レンダリング・ステートを設定//
	// Z バッファ有効化->前後関係の計算を正確にしてくれる//
	ZBufferUseFlg(true);

	// アルファブレンディング有効化//
	AlphaBlendUseFlg(true);

	// アルファブレンディング方法を設定//
	AlphaBlendSetting();

	// レンダリング時のアルファ値の計算方法の設定//
	RenderSetting();

	//裏面カリング
	SetCullMode(CULL::CCW);

	// フィルタ設定
	SetFilter(D3DTEXF_LINEAR, D3DTEXF_LINEAR, D3DTEXF_LINEAR);

	// ライト
	LightSetting(true);

	SetBackBuffer();

	SetFVF((FVF::XYZ | FVF::DIFFUSE | FVF::TEX));

	SetInitFlg(true);
}

D3DPRESENT_PARAMETERS DirectX3D9Base::CreateParameter(
	const bool _fullScreenFlg,
	const unsigned short _scrW,
	const unsigned short _scrH)
{

	// ウインドウの作成が完了したので、Direct3D を初期化する
	D3DPRESENT_PARAMETERS res;
	ChStd::MZero(&res);

	if (ChPtr::NullCheck(d3d9))return res;

	// Direct3D 初期化パラメータの設定
	if (_fullScreenFlg)
	{
		// フルスクリーン : ほとんどのアダプタでサポートされているフォーマットを使用
		//	d3dpp.backBufferFormat = D3DFMT_R5G6B5;
		res.BackBufferFormat = D3DFMT_X8R8G8B8;
	}
	else
	{
		// ウインドウ : 現在の画面モードを使用
		D3DDISPLAYMODE disp;
		// 現在の画面モードを取得
		d3d9->GetAdapterDisplayMode(adapter, &disp);
		res.BackBufferFormat = disp.Format;

		// ウインドウモード
		res.Windowed = 1;
	}
	// 表示領域サイズの設定
	res.BackBufferWidth = _scrW;
	res.BackBufferHeight = _scrH;
	res.SwapEffect = D3DSWAPEFFECT_FLIP;


	// Z バッファの自動作成
	res.EnableAutoDepthStencil = 1;
	res.AutoDepthStencilFormat = D3DFMT_D16;

	//ﾊﾞｯｸﾊﾞｯﾌｧをﾛｯｸ可能にする(GetDCも可能になる)
	res.Flags = D3DPRESENTFLAG_LOCKABLE_BACKBUFFER;

	//フレーム数の制限解除.
	res.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	//ﾘｾｯﾄ用に状態情報を保存
	param = res;

	return res;
}

void DirectX3D9Base::DrawStart(const D3DCOLOR& _BackColor)
{
	CH_D3D9CONTROLLER_INIT_TEST(true, );
	// 描画準備
	device->BeginScene();
	// バックバッファと Z バッファをクリア
	device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, _BackColor, 1.0f, 0);
	
	dFlg = true;

}

void DirectX3D9Base::DrawEnd(const bool& _RTFlg)
{
	CH_D3D9CONTROLLER_INIT_TEST(false, );
	// 描画終了
	device->EndScene();

	dFlg = false;

	if (_RTFlg)return;

	// バックバッファをプライマリバッファにコピー
	if (FAILED(device->Present(NULL, NULL, NULL, NULL)))
	{
		device->Reset(&param);
	}

}

ChVec3_9 DirectX3D9Base::GetOnViewPos(const ChMat_9& _Mat)
{
	CH_D3D9CONTROLLER_INIT_TEST(false,ChVec3_9());
	device->BeginScene();

	D3DVIEWPORT9 ViewPort;
	ChMat_9 TmpMat, TmpVMat, TmpPMat;
	ChVec3_9 TmpVec;
	TmpVec = _Mat;

	TmpMat.Identity();

	device->GetViewport(&ViewPort);

	device->GetTransform(D3DTS_VIEW, &TmpVMat);
	device->GetTransform(D3DTS_PROJECTION, &TmpPMat);

	D3DXVec3Project(&TmpVec, &TmpVec, &ViewPort, &TmpPMat, &TmpVMat, &TmpMat);

	device->EndScene();

	return TmpVec;
}

void DirectX3D9A::Init(
	const HWND _hWnd,
	const bool _fullScreenFlg,
	const unsigned short _scrW,
	const unsigned short _scrH)
{
	Release();

	if (!_fullScreenFlg)
	{
		RECT rc = { 0,0,_scrW,_scrH };
		AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
		SetWindowPos(_hWnd, NULL, 10, 10, rc.right - rc.left, rc.bottom - rc.top, SWP_SHOWWINDOW | SWP_NOZORDER);
	}

	d3d9 = Direct3DCreate9(D3D_SDK_VERSION);

	if (!d3d9)
	{

		ChWin::MsgBox msgBox;
		msgBox.SetDisplayIconType(ChWin::MsgBox::DisplayIconType::Stop);
		msgBox.ClearDisplayButtonType();
		msgBox.AddDisplayButtonType(ChWin::MsgBox::DisplayButtonType::Ok);

		msgBox.DisplayServiceNotificationA("Direct3D の作成に失敗しました。", "ERROR");
		
		// 終了する
		PostQuitMessage(0);
		return;
	}
	// 使用するアダプタ番号
	adapter = 0;

	// ウインドウの作成が完了したので、Direct3D を初期化する
	D3DPRESENT_PARAMETERS d3dpp = CreateParameter(_fullScreenFlg, _scrW, _scrH);

	if (!CreateD3DXDevice(_hWnd, &d3dpp))
	{
		d3d9->Release();
		PostQuitMessage(0);
		return;
	}

	DirectX3D9Base::Init();
}

bool DirectX3D9A::CreateD3DXDevice(const HWND _hWnd, D3DPRESENT_PARAMETERS* _d3dpp)
{
	// デバイスの作成 - T&L HAL
	if (FAILED(d3d9->CreateDevice(adapter, D3DDEVTYPE_HAL, _hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, _d3dpp, &device)))
	{
		// 失敗したので HAL で試行
		if (FAILED(d3d9->CreateDevice(adapter, D3DDEVTYPE_HAL, _hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, _d3dpp, &device)))
		{
			// 失敗したので REF で試行
			if (FAILED(d3d9->CreateDevice(adapter, D3DDEVTYPE_REF, _hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, _d3dpp, &device)))
			{
				ChWin::MsgBox msgBox;
				msgBox.SetDisplayIconType(ChWin::MsgBox::DisplayIconType::Stop);
				msgBox.ClearDisplayButtonType();
				msgBox.AddDisplayButtonType(ChWin::MsgBox::DisplayButtonType::Ok);

				msgBox.DisplayServiceNotificationA("DirectX9が初期化できません。\n未対応のパソコンと思われます。", "ERROR");

				return false;
			}
		}
	}

	return true;
}

void DirectX3D9W::Init(
	const HWND _hWnd,
	const bool _fullScreenFlg,
	const unsigned short _scrW,
	const unsigned short _scrH)
{
	Release();

#if 0
	if (!_fullScreenFlg)
	{
		RECT rc = { 0,0,_scrW,_scrH };
		AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
		SetWindowPos(_hWnd, NULL, 10, 10, rc.right - rc.left, rc.bottom - rc.top, SWP_SHOWWINDOW | SWP_NOZORDER);
	}
#endif

	d3d9 = Direct3DCreate9(D3D_SDK_VERSION);

	if (!d3d9)
	{
		ChWin::MsgBox msgBox;
		msgBox.SetDisplayIconType(ChWin::MsgBox::DisplayIconType::Stop);
		msgBox.ClearDisplayButtonType();
		msgBox.AddDisplayButtonType(ChWin::MsgBox::DisplayButtonType::Ok);

		msgBox.DisplayServiceNotificationW(L"Direct3D の作成に失敗しました。", L"ERROR");

		// 終了する
		PostQuitMessage(0);
		return;
	}
	// 使用するアダプタ番号
	adapter = 0;

	// ウインドウの作成が完了したので、Direct3D を初期化する
	D3DPRESENT_PARAMETERS d3dpp = CreateParameter(_fullScreenFlg, _scrW, _scrH);

	if (!CreateD3DXDevice(_hWnd, &d3dpp))
	{
		d3d9->Release();
		PostQuitMessage(0);
		return;
	}

	DirectX3D9Base::Init();
}

bool DirectX3D9W::CreateD3DXDevice(const HWND _hWnd
	, D3DPRESENT_PARAMETERS* _d3dpp)
{
	// デバイスの作成 - T&L HAL
	if (FAILED(d3d9->CreateDevice(adapter, D3DDEVTYPE_HAL, _hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, _d3dpp, &device)))
	{
		// 失敗したので HAL で試行
		if (FAILED(d3d9->CreateDevice(adapter, D3DDEVTYPE_HAL, _hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, _d3dpp, &device)))
		{
			// 失敗したので REF で試行
			if (FAILED(d3d9->CreateDevice(adapter, D3DDEVTYPE_REF, _hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, _d3dpp, &device)))
			{
				ChWin::MsgBox msgBox;
				msgBox.SetDisplayIconType(ChWin::MsgBox::DisplayIconType::Stop);
				msgBox.ClearDisplayButtonType();
				msgBox.AddDisplayButtonType(ChWin::MsgBox::DisplayButtonType::Ok);

				msgBox.DisplayServiceNotificationW(L"DirectX9が初期化できません。\n未対応のパソコンと思われます。", L"ERROR");

				return false;
			}
		}
	}

	return true;
}
