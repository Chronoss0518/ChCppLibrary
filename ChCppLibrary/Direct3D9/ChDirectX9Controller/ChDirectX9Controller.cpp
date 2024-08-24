
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

	// �����_�����O�E�X�e�[�g��ݒ�//
	// Z �o�b�t�@�L����->�O��֌W�̌v�Z�𐳊m�ɂ��Ă����//
	ZBufferUseFlg(true);

	// �A���t�@�u�����f�B���O�L����//
	AlphaBlendUseFlg(true);

	// �A���t�@�u�����f�B���O���@��ݒ�//
	AlphaBlendSetting();

	// �����_�����O���̃A���t�@�l�̌v�Z���@�̐ݒ�//
	RenderSetting();

	//���ʃJ�����O
	SetCullMode(CULL::CCW);

	// �t�B���^�ݒ�
	SetFilter(D3DTEXF_LINEAR, D3DTEXF_LINEAR, D3DTEXF_LINEAR);

	// ���C�g
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

	// �E�C���h�E�̍쐬�����������̂ŁADirect3D ������������
	D3DPRESENT_PARAMETERS res;
	ChStd::MZero(&res);

	if (ChPtr::NullCheck(d3d9))return res;

	// Direct3D �������p�����[�^�̐ݒ�
	if (_fullScreenFlg)
	{
		// �t���X�N���[�� : �قƂ�ǂ̃A�_�v�^�ŃT�|�[�g����Ă���t�H�[�}�b�g���g�p
		//	d3dpp.backBufferFormat = D3DFMT_R5G6B5;
		res.BackBufferFormat = D3DFMT_X8R8G8B8;
	}
	else
	{
		// �E�C���h�E : ���݂̉�ʃ��[�h���g�p
		D3DDISPLAYMODE disp;
		// ���݂̉�ʃ��[�h���擾
		d3d9->GetAdapterDisplayMode(adapter, &disp);
		res.BackBufferFormat = disp.Format;

		// �E�C���h�E���[�h
		res.Windowed = 1;
	}
	// �\���̈�T�C�Y�̐ݒ�
	res.BackBufferWidth = _scrW;
	res.BackBufferHeight = _scrH;
	res.SwapEffect = D3DSWAPEFFECT_FLIP;


	// Z �o�b�t�@�̎����쐬
	res.EnableAutoDepthStencil = 1;
	res.AutoDepthStencilFormat = D3DFMT_D16;

	//�ޯ��ޯ̧��ۯ��\�ɂ���(GetDC���\�ɂȂ�)
	res.Flags = D3DPRESENTFLAG_LOCKABLE_BACKBUFFER;

	//�t���[�����̐�������.
	res.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	//ؾ�ėp�ɏ�ԏ���ۑ�
	param = res;

	return res;
}

void DirectX3D9Base::DrawStart(const D3DCOLOR& _BackColor)
{
	CH_D3D9CONTROLLER_INIT_TEST(true);
	// �`�揀��
	device->BeginScene();
	// �o�b�N�o�b�t�@�� Z �o�b�t�@���N���A
	device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, _BackColor, 1.0f, 0);
	
	dFlg = true;

}

void DirectX3D9Base::DrawEnd(const bool& _RTFlg)
{
	CH_D3D9CONTROLLER_INIT_TEST(false);
	// �`��I��
	device->EndScene();

	dFlg = false;

	if (_RTFlg)return;

	// �o�b�N�o�b�t�@���v���C�}���o�b�t�@�ɃR�s�[
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

		msgBox.DisplayServiceNotificationA("Direct3D �̍쐬�Ɏ��s���܂����B", "ERROR");
		
		// �I������
		PostQuitMessage(0);
		return;
	}
	// �g�p����A�_�v�^�ԍ�
	adapter = 0;

	// �E�C���h�E�̍쐬�����������̂ŁADirect3D ������������
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
	// �f�o�C�X�̍쐬 - T&L HAL
	if (FAILED(d3d9->CreateDevice(adapter, D3DDEVTYPE_HAL, _hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, _d3dpp, &device)))
	{
		// ���s�����̂� HAL �Ŏ��s
		if (FAILED(d3d9->CreateDevice(adapter, D3DDEVTYPE_HAL, _hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, _d3dpp, &device)))
		{
			// ���s�����̂� REF �Ŏ��s
			if (FAILED(d3d9->CreateDevice(adapter, D3DDEVTYPE_REF, _hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, _d3dpp, &device)))
			{
				ChWin::MsgBox msgBox;
				msgBox.SetDisplayIconType(ChWin::MsgBox::DisplayIconType::Stop);
				msgBox.ClearDisplayButtonType();
				msgBox.AddDisplayButtonType(ChWin::MsgBox::DisplayButtonType::Ok);

				msgBox.DisplayServiceNotificationA("DirectX9���������ł��܂���B\n���Ή��̃p�\�R���Ǝv���܂��B", "ERROR");

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

		msgBox.DisplayServiceNotificationW(L"Direct3D �̍쐬�Ɏ��s���܂����B", L"ERROR");

		// �I������
		PostQuitMessage(0);
		return;
	}
	// �g�p����A�_�v�^�ԍ�
	adapter = 0;

	// �E�C���h�E�̍쐬�����������̂ŁADirect3D ������������
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
	// �f�o�C�X�̍쐬 - T&L HAL
	if (FAILED(d3d9->CreateDevice(adapter, D3DDEVTYPE_HAL, _hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, _d3dpp, &device)))
	{
		// ���s�����̂� HAL �Ŏ��s
		if (FAILED(d3d9->CreateDevice(adapter, D3DDEVTYPE_HAL, _hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, _d3dpp, &device)))
		{
			// ���s�����̂� REF �Ŏ��s
			if (FAILED(d3d9->CreateDevice(adapter, D3DDEVTYPE_REF, _hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, _d3dpp, &device)))
			{
				ChWin::MsgBox msgBox;
				msgBox.SetDisplayIconType(ChWin::MsgBox::DisplayIconType::Stop);
				msgBox.ClearDisplayButtonType();
				msgBox.AddDisplayButtonType(ChWin::MsgBox::DisplayButtonType::Ok);

				msgBox.DisplayServiceNotificationW(L"DirectX9���������ł��܂���B\n���Ή��̃p�\�R���Ǝv���܂��B", L"ERROR");

				return false;
			}
		}
	}

	return true;
}
