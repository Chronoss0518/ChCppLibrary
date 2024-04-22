#include<Windows.h>
#include"../../BaseIncluder/ChBase.h"

#include"../../BaseIncluder/ChD3D11I.h"

#include"../../WindowsObject/WindObject/ChWindObject.h"
#include"ChDirectX11Controller.h"

using namespace ChD3D11;

#if 0
void DirectX3D11::Init(
	ChWin::WindObject& _windObject,
	const bool _fullScreenFlg)
{
	if (!_windObject.IsInit())return;

	auto windSize = _windObject.GetWindSize();

	Init(_windObject.GethWnd(),
		_fullScreenFlg,
		static_cast<unsigned long>(windSize.w),
		static_cast<unsigned long>(windSize.h));

}
#endif

void DirectX3D11::Init(
	HWND _hWnd
	, const bool _fullScreenFlg
	, const unsigned long _scrW
	, const unsigned long _scrH)
{
	if (ChPtr::NullCheck(_hWnd))return;

	
	CreateDevice(_hWnd, _scrW, _scrH);

	if (!IsInstanse())
	{
		PostQuitMessage(0);
		return;
	}

	window->SetFullscreenState(_fullScreenFlg, nullptr);

	SetInitFlg(true);

}

///////////////////////////////////////////////////////////////////////////////////

void DirectX3D11::Release()
{

	if (ChPtr::NotNullCheck(device)) { device->Release(); device = nullptr; }

	if (ChPtr::NotNullCheck(dContext))
	{
		dContext->ClearState();  dContext->Release(); dContext = nullptr;
	}

	if (ChPtr::NotNullCheck(window)) { window->Release(); window = nullptr; }

	if (ChPtr::NotNullCheck(surface)) { surface->Release(); surface = nullptr; }

	if (ChPtr::NotNullCheck(renderTarget)) { renderTarget->Release(); renderTarget = nullptr; }

	SetInitFlg(false);
}

///////////////////////////////////////////////////////////////////////////////////

void DirectX3D11::CreateDevice(
	HWND _hWnd
	, const unsigned long _scrW
	, const unsigned long _scrH)
{

	DXGI_SWAP_CHAIN_DESC scd;

	ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));

	scd.BufferCount = 1;
	scd.BufferDesc.Width = static_cast<unsigned int>(createDeviceWitdh = _scrW);
	scd.BufferDesc.Height = static_cast<unsigned int>(createDeviceHeight = _scrH);
	scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

	//�h��ւ��鎞��//
	//scd.BufferDesc.RefreshRate.Numerator = 0;
	//scd.BufferDesc.RefreshRate.Denominator = 0;

	//��ʏo��//
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;

	//�n���h���R�Â�//
	scd.OutputWindow = _hWnd;

	//1�s�N�Z���Ɏg�����ԕ⊮�F�̐�//
	scd.SampleDesc.Count = 1;

	//�掿���x��//
	scd.SampleDesc.Quality = 0;

	scd.Windowed = true;

	//DirectX�̋@�\�ݒ�//
	D3D_FEATURE_LEVEL lv[] = { D3D_FEATURE_LEVEL_11_0 };
	D3D_FEATURE_LEVEL rLv;

	if (FAILED(D3D11CreateDeviceAndSwapChain
	(
		NULL
		, D3D_DRIVER_TYPE_HARDWARE
		, NULL
		, D3D11_CREATE_DEVICE_FLAG::D3D11_CREATE_DEVICE_BGRA_SUPPORT
		//,0
		, lv
		, 1
		, D3D11_SDK_VERSION
		, &scd
		, &window
		, &device
		, &rLv
		, &dContext
	)))
	{
		Release();
		return;
	};

	if (FAILED(window->GetBuffer(0, IID_PPV_ARGS(&surface))))
	{
		Release();
		return;
	}

	ID3D11Texture2D* pBackBuffer = nullptr;

	window->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);

	device->CreateRenderTargetView(pBackBuffer, nullptr, &renderTarget);

	pBackBuffer->Release();


}