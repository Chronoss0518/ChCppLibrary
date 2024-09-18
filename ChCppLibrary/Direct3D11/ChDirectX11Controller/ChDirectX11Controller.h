
#ifndef Ch_D3D11_DXCo_h
#define Ch_D3D11_DXCo_h

namespace ChD3D11
{

	//Direct3D11�𗘗p���邽�߂ɍ��ꂽ�N���X//
	class DirectX3D11:public ChCp::Initializer
	{
	public:

		virtual ~DirectX3D11() { Release(); }

	public://Init and Release//

		void Init(
			HWND _hWnd, 
			const bool _fullScreenFlg, 
			const unsigned long _scrW,
			const unsigned long _scrH);

		/*
		void Init(
			ChWin::WindObject& _windObject,
			const bool _fullScreenFlg);

		*/

		virtual void Release();

	public://Get Functions//

		//Direct3D11�������ǂ�f�o�C�X�̎擾//
		inline ID3D11Device* const GetDevice() { return device; }

		//�`��������ǂ�f�o�C�X�̎擾//
		inline ID3D11DeviceContext* const GetDC() { return dContext; }

		inline IDXGISwapChain* const GetSC() { return window; }

		inline IDXGISurface* const GetSurface() { return surface; }

		inline unsigned long GetCreateDeviceWitdh() { return createDeviceWitdh; }

		inline unsigned long GetCreateDeviceHeight() { return createDeviceHeight; }

		inline ChMath::Vector2Base<unsigned long>GetCreateDeviceSizeToChVector2()
		{
			ChMath::Vector2Base<unsigned long> res;
			res.w = createDeviceWitdh;
			res.h = createDeviceHeight;
			return res;
		}

	public://Is Functions//

		//�f�o�C�X�����݂��邩���Ȃ����̊m�F//
		inline bool IsInstanse()
		{
			if (ChPtr::NullCheck(device))return false;
			if (ChPtr::NullCheck(dContext))return false;
			if (ChPtr::NullCheck(window))return false;
			return true;
		}

	protected://Create Fucntions// 

		void CreateDevice(
			HWND _hWnd,
			const unsigned long _scrW,
			const unsigned long _scrH);

	protected://Member Value//

		//��{�I�u�W�F�N�g�������ǂ�f�o�C�X//
		ID3D11Device* device = nullptr;

		//�`��p�f�o�C�X//
		ID3D11DeviceContext* dContext = nullptr;

		//�ێ�����Window�f�[�^//
		IDXGISwapChain* window = nullptr;

		//Direct2D�Ƃ̌݊������������邽�߂̃f�[�^//
		IDXGISurface* surface = nullptr;

		//���ۂɕ`�悷�邽�߂̃_�u���o�b�t�@//
		ID3D11RenderTargetView* renderTarget = nullptr;

		unsigned long createDeviceWitdh = 0;
		unsigned long createDeviceHeight = 0;
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