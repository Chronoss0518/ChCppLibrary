
#ifdef _WINDOWS_

#ifndef Ch_D3D9_DXCo_h
#define Ch_D3D9_DXCo_h

#include"../../ClassParts/ChCPInitializer.h"


#ifndef	CH_D3D9CONTROLLER_INIT_TEST
#define	CH_D3D9CONTROLLER_INIT_TEST(_drawFlg, _defaultResult)\
if(!IsInit())return _defaultResult##;\
if(_drawFlg == dFlg)return _defaultResult##;
#endif

namespace ChD3D9
{

	//�K�v�Ɗ�����l�����ׂĂ킩��₷����������
	namespace FVF
	{
		const unsigned long XYZ = D3DFVF_XYZ;
		const unsigned long DIFFUSE = D3DFVF_DIFFUSE;
		const unsigned long TEX = D3DFVF_TEX1;
		const unsigned long NORMAL = D3DFVF_NORMAL;
	}

	enum class CULL { NONE = 1, CW, CCW };

	//Direct3D9�𗘗p���邽�߂ɍ��ꂽ�N���X//
	//D3DX����������Ă���//
	class DirectX3D9Base:public ChCp::Initializer
	{
	public://Init And Releas//

		void Release();

	protected:

		void Init();

	public://Draw Functions//

		//�`��J�n���ɌĂԊ֐�//
		void DrawStart(const D3DCOLOR& _backColor = D3DCOLOR_ARGB(255, 255, 255, 255));

		//�`��I�����ɌĂԊ֐�//
		//�����_�[�^�[�Q�b�g���p�����ۂ�Flg��True�ɂ���//
		void DrawEnd(const bool& _rtFlg = false);

	public://Set Functions//

		//�Œ�@�\�`�������ۂɗ��p���郉�C�g�f�[�^���Z�b�g//
		inline void SetLight(const unsigned short _setNo, const D3DLIGHT9 *_light)
		{
			CH_D3D9CONTROLLER_INIT_TEST(false,);
			device->SetLight(static_cast<DWORD>(_setNo), _light);
		}

		//�Œ�@�\�`�������ۂɗ��p����J�����O�f�[�^���Z�b�g//
		inline void SetCullMode(const CULL _cull)
		{
			CH_D3D9CONTROLLER_INIT_TEST(false, );
			device->SetRenderState(D3DRS_CULLMODE, static_cast<DWORD>(_cull));
		}

		//�Œ�@�\�`�������ۂɗ��p����e�N�X�`���`����@���Z�b�g//
		inline void SetFilter(
			_D3DTEXTUREFILTERTYPE _mip,
			_D3DTEXTUREFILTERTYPE _min,
			_D3DTEXTUREFILTERTYPE _mag)
		{
			CH_D3D9CONTROLLER_INIT_TEST(false, );

			device->SetSamplerState(0, D3DSAMP_MIPFILTER, _mip);
			device->SetSamplerState(0, D3DSAMP_MINFILTER, _min);
			device->SetSamplerState(0, D3DSAMP_MAGFILTER, _mag);
		}

		//�`����s�����߂̃o�b�N�o�b�t�@�Z�b�g//
		inline void SetBackBuffer()
		{
			CH_D3D9CONTROLLER_INIT_TEST(false, );
			device->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &backBuffer);
		}

		//���_�𗘗p�����|���S���̕`��Ɋւ���f�[�^�̃Z�b�g//
		inline void SetFVF(unsigned long _FVF)
		{
			CH_D3D9CONTROLLER_INIT_TEST(false, );
			device->SetFVF(_FVF);
		}
	
	public://Get Functions//

		//Direct3D9�������ǂ�f�o�C�X�̎擾//
		inline LPDIRECT3DDEVICE9 GetDevice()
		{
			return device;
		}

		//�Ώۂ̃}�g���b�N�X�ɑ΂��ĉ�ʏ�ł̈ʒu���擾//
		ChVec3_9 GetOnViewPos(const ChMat_9& _mat);

		//�����p�����[�^�̎擾//
		inline D3DPRESENT_PARAMETERS GetInitParam()
		{
			return param;
		}

		//�ˉe�s��̎擾//
		inline const ChMat_9 GetCamPMat()
		{
			CH_D3D9CONTROLLER_INIT_TEST(false, ChMat_9());
			ChMat_9 proj;
			device->GetTransform(D3DTS_PROJECTION, &proj);
			return proj;
		}

		//�r���[�s��̎擾//
		inline const ChMat_9 GetCamVMat()
		{
			CH_D3D9CONTROLLER_INIT_TEST(false, ChMat_9());
			ChMat_9 view;
			device->GetTransform(D3DTS_VIEW, &view);
			return view;

		}

	public://Is Functions//

		//�Œ�@�\�`��\�m�F//
		inline bool IsDraw()
		{
			return dFlg;
		}
	
	public://Flg Function//

		//Z�o�b�t�@(�[�x��ǂݍ��ރo�b�t�@)�𗘗p���邩�ۂ��̃t���O//
		inline void ZBufferUseFlg(const bool _flg)
		{
			CH_D3D9CONTROLLER_INIT_TEST(false, );

			_flg ? device->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE)
				: device->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);

			device->SetRenderState(D3DRS_ZWRITEENABLE, _flg);
		}

		//�Œ�@�\�ŃA���t�@�u�����h(���ߍ���)�𗘗p���邩�ۂ��̃t���O//
		inline void AlphaBlendUseFlg(const bool _flg)
		{
			CH_D3D9CONTROLLER_INIT_TEST(false, );

			device->SetRenderState(D3DRS_ALPHABLENDENABLE, _flg);
			device->SetRenderState(D3DRS_SEPARATEALPHABLENDENABLE, _flg);
		}

		//�Œ�@�\�ł��ꂼ���Light�𗘗p���邩�ۂ��̃t���O
		inline void LightUseFlg(const unsigned short _setNo, const bool _flg)
		{
			CH_D3D9CONTROLLER_INIT_TEST(false, );

			device->LightEnable((DWORD)_setNo, _flg);
		}
		
	public://Setting Functions//

		//�Œ�@�\�ŕ`�掞�Ƀ��C�g�v�Z���s�����ۂ��̃t���O//
		inline void LightSetting(const bool _flg)
		{
			CH_D3D9CONTROLLER_INIT_TEST(false, );

			device->SetRenderState(D3DRS_LIGHTING, _flg);
		}

		//�Œ�@�\�ŃA���t�@�u�����h(����Z����)�̐ݒ�//
		inline void AlphaBlendSetting()
		{
			CH_D3D9CONTROLLER_INIT_TEST(false, );

			device->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
			device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		}

		//�Œ�@�\�ŃA���t�@�u�����h(���Z����)�̐ݒ�//
		inline void AddBlendSetting()
		{
			CH_D3D9CONTROLLER_INIT_TEST(false, );

			device->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
		}

		//�Œ�@�\�őS�̂̕`��ݒ�//
		inline void RenderSetting()
		{
			CH_D3D9CONTROLLER_INIT_TEST(false, );

			// �����_�����O���̃A���t�@�l�̌v�Z���@�̐ݒ�//
			device->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
			// �e�N�X�`���̐F���g�p//
			device->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
			// ���_�̐F���g�p//
			device->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
			// �����_�����O���̐F�̌v�Z���@�̐ݒ�//
			device->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
		}

		//�`��J�n���ɌĂԊ֐�//
		void DrawStart(const D3DCOLOR& _backColor = D3DCOLOR_ARGB(255, 255, 255, 255));

		//�`��I�����ɌĂԊ֐�//
		//�����_�[�^�[�Q�b�g���p�����ۂ�Flg��True�ɂ���//
		void DrawEnd(const bool& _rtFlg = false);
		
	protected:

		D3DPRESENT_PARAMETERS CreateParameter(
			const bool _fullScreenFlg,
			const unsigned short _scrW,
			const unsigned short _scrH);

	protected://Member Value

		LPDIRECT3D9 d3d9 = nullptr;
		LPDIRECT3DDEVICE9 device = nullptr;
		LPDIRECT3DSURFACE9 backBuffer = nullptr;

		bool dFlg = false;

		int adapter = 0;
		D3DPRESENT_PARAMETERS param;

	protected://ConstructerDestructer//

		inline virtual ~DirectX3D9Base()
		{
			Release();
		}

	};

	//Direct3D9�𗘗p���邽�߂ɍ��ꂽ�N���X//
	//D3DX����������Ă���//
	class DirectX3D9A :public DirectX3D9Base
	{
	public://Init And Releas//

		void Init(
			const HWND _hWnd,
			const bool _fullScreenFlg,
			const unsigned short _scrW,
			const unsigned short _scrH);

	protected://Create Functions//

		//Device�������@//
		bool CreateD3DXDevice(const HWND _hWnd, D3DPRESENT_PARAMETERS* _d3dpp);

	protected://ConstructerDestructer//

		DirectX3D9A(){}

	public:

		inline static DirectX3D9A& GetIns() 
		{
			static DirectX3D9A ins;
			return ins;
		}
	};

	//Direct3D9�𗘗p���邽�߂ɍ��ꂽ�N���X//
	//D3DX����������Ă���//
	class DirectX3D9W :public DirectX3D9Base
	{
	public://Init And Releas//

		void Init(
			const HWND _hWnd,
			const bool _fullScreenFlg,
			const unsigned short _scrW,
			const unsigned short _scrH);

	protected://Create Functions//

		//Device�������@//
		bool CreateD3DXDevice(const HWND _hWnd, D3DPRESENT_PARAMETERS* _d3dpp);

	protected://ConstructerDestructer//

		DirectX3D9W() {}

	public:

		inline static DirectX3D9W& GetIns()
		{
			static DirectX3D9W ins;
			return ins;
		}
	};


	inline DirectX3D9A& D3D9AAPI() { return DirectX3D9A::GetIns(); }

	inline LPDIRECT3DDEVICE9 D3D9ADevice() { return DirectX3D9A::GetIns().GetDevice(); }


	inline DirectX3D9W& D3D9WAPI() { return DirectX3D9W::GetIns(); }

	inline LPDIRECT3DDEVICE9 D3D9WDevice() { return DirectX3D9W::GetIns().GetDevice(); }


	using DirectX3D9 =
#ifdef UNICODE
			DirectX3D9W;
#else
			DirectX3D9A;
#endif

	inline DirectX3D9& D3D9API() { return DirectX3D9::GetIns(); }

	inline LPDIRECT3DDEVICE9 D3D9Device() { return DirectX3D9::GetIns().GetDevice(); }
}

#endif

#endif