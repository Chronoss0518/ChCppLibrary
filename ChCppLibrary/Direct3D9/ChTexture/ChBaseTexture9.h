#ifndef Ch_D3D9_BTex_h
#define Ch_D3D9_BTex_h

#include<string>

#include"../../BasePack/ChPtr.h"
#include"../../BasePack/ChMath3D.h"


namespace ChTex
{
	class PngTex9;
	class JpegTex9;
	class BmpTex9;


	typedef class BaseTexture9
	{
	public:

		virtual ~BaseTexture9()
		{
			Release();
		}

	public://Init And Release//

		virtual void Release();

	public://Set Functions//

		void SetBaseColor(const ChVec4& _col){ col = _col; }

		void SetBaseColor(const D3DCOLOR& _col) { col = D3DColorToColor255(_col); }

		void SetSclXSize(const float _scl) { scal.x = _scl; }

		void SetSclYSize(const float _scl) { scal.y = _scl; }

		void SetOriginalWidth(const unsigned int _width) { original.x = _width; }

		void SetOriginalHeight(const unsigned int _height) { original.y = _height; }

	public://Get Functions//

		//�I�������ӏ��̐F�擾//
		template<class T>
		T GetColor(
			const unsigned int _width,
			const unsigned int _height);

		inline const LPDIRECT3DTEXTURE9 GetTex()const { return tex; }

		inline const LPDIRECT3DSURFACE9 GetSur()const { return sur; }

		inline const LPDIRECT3DSURFACE9 GetZBu()const { return zBu; }

		float GetSclXSize()const { return scal.x; }

		float GetSclYSize()const { return scal.y; }

		unsigned int GetOriginalWidth()const { return original.w; }

		unsigned int GetOriginalHeight()const { return original.h; }

		ChVec4 GetBaseColor()const { return col; }

		D3DCOLOR GetBaseColD3D()const 
		{
			return D3DCOLOR_ARGB(
				static_cast<unsigned char>(col.a * 255),
				static_cast<unsigned char>(col.r * 255),
				static_cast<unsigned char>(col.g * 255),
				static_cast<unsigned char>(col.b * 255));
		}

		inline LPDIRECT3DTEXTURE9& GetTex() { return tex; }

		inline LPDIRECT3DSURFACE9& GetSur() { return sur; }

		inline LPDIRECT3DSURFACE9& GetZBu() { return zBu; }

	public://To Functions//

		//��p�g���q�ł̃C���|�[�g//
		static ChVec4 D3DColorToColor255(const D3DCOLOR& _col);

	public://Create Fucntion//

		//�O���t�@�C�����摜�쐬//
		void CreateTexture(
			const std::string& _fileName,
			const LPDIRECT3DDEVICE9& _dev,
			const D3DCOLOR& _colKey = D3DCOLOR_ARGB(0, 0, 0, 0))
		{
			CreateTextureBase(_fileName.c_str(), _dev, _colKey);
		}

		//�O���t�@�C�����摜�쐬//
		void CreateTexture(
			const std::wstring& _fileName,
			const LPDIRECT3DDEVICE9& _dev,
			const D3DCOLOR& _colKey = D3DCOLOR_ARGB(0, 0, 0, 0))
		{
			CreateTextureBase(_fileName.c_str(), _dev, _colKey);
		}


		//�F�t���摜�쐬//
		void CreateColTexture(
			const LPDIRECT3DDEVICE9& _dev,
			const D3DCOLOR& _col = D3DCOLOR_ARGB(255, 255, 255, 255),
			const unsigned long _w = 1,
			const unsigned long _h = 1);

		//�F�t���ڍ׉摜�쐬//
		template<typename T>
		void CreateMinuColTexture(
			const LPDIRECT3DDEVICE9& _dev,
			const T& _col,
			const unsigned long _w = 1,
			const unsigned long _h = 1,
			const _D3DFORMAT _format = D3DFMT_A8R8G8B8,
			const unsigned long _usage = 0,
			const _D3DPOOL _pool = D3DPOOL_MANAGED);

		//�T�[�t�F�C�X�쐬//
		//���摜�쐬��Ɏg�p//
		inline void CreateSurface(const unsigned int _level)
		{
			if (ChPtr::NullCheck(tex))return;

			tex->GetSurfaceLevel(0, &sur);
		}

		//�[�x�o�b�t�@�̍쐬//
		//���摜�쐬��Ɏg�p//
		void CreateZBuffer(
			const LPDIRECT3DDEVICE9& _dev,
			const _D3DFORMAT _format = D3DFMT_D16,
			const _D3DMULTISAMPLE_TYPE _mSample = D3DMULTISAMPLE_NONE,
			const unsigned long _mQuality = 0);

	protected:

		//�O���t�@�C�����摜�쐬//
		void CreateTextureBase(
			const char* _fileName,
			const LPDIRECT3DDEVICE9& _dev,
			const D3DCOLOR& _colKey = D3DCOLOR_ARGB(0, 0, 0, 0));

		//�O���t�@�C�����摜�쐬//
		void CreateTextureBase(
			const wchar_t* _fileName,
			const LPDIRECT3DDEVICE9& _dev,
			const D3DCOLOR& _colKey = D3DCOLOR_ARGB(0, 0, 0, 0));

	public://Static Functions//

		static ChPtr::Shared<BaseTexture9> TextureType(const std::string& _fileName);

		static ChPtr::Shared<BaseTexture9> TextureType(const std::wstring& _fileName);

	protected://Member Value//

		LPDIRECT3DTEXTURE9 tex = nullptr;	//�e�N�X�`���}�b�v���[�p//
		LPDIRECT3DSURFACE9 sur = nullptr;
		LPDIRECT3DSURFACE9 zBu = nullptr;

		ChMath::Vector2Base<float>scal;//�g�k�̃T�C�Y//

		ChMath::Vector2Base<unsigned int>original;//�I���W�i���̃T�C�Y//

		ChVec4 col{ 1.0f,1.0f,1.0f,1.0f };	//�F�ʊ�{�F//

	protected://Other Functions//

		template<typename T>
		inline void SetTexColor(const T& _color);

		virtual void OpenFile(const char* _fileName) {};

		virtual void OpenFile(const wchar_t* _fileName) {};

	}Texture9;
}

#endif