#ifndef Ch_D3D9_ReTa_h
#define Ch_D3D9_ReTa_h

namespace ChD3D9
{
	class ShaderController;
}

namespace ChTex
{

	typedef class BaseTexture9 Texture9;

	//�����_�[�^�[�Q�b�g��ݒ肷��N���X//
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

		//�����_�[�^�[�Q�b�g�p�̃e�N�X�`����ݒ�//
		//�������ŉ�ʂ��N���A����F�w��//
		//ChD3D9::Shader::DrawStart�ƕ��p�ł��܂���//
		void SetRT(
			const std::basic_string<CharaType>& _dataName,
			const D3DCOLOR _backCol = D3DCOLOR_ARGB(0, 0, 0, 0));

	public://Get Functions//

		//�쐬�����e�N�X�`�����擾//
		inline ChPtr::Shared<Texture9> GetRTTexture(const std::basic_string<CharaType>& _dataName)
		{
			if (rtList.find(_dataName) == rtList.end())return nullptr;
			return rtList[_dataName];
		}

	public:

		//�o�^����Ă�e�N�X�`����I�����ď���//
		void DeleteRTTexture(const std::basic_string<CharaType>& _dataName)
		{
			if (rtList.empty())return;
			if (rtList.find(_dataName) == rtList.end())return;

			rtList.erase(_dataName);
		}

		//�����_�[�^�[�Q�b�g�ƂȂ�e�N�X�`�����쐬:�o�^//
		void CreateRT(
			const std::basic_string<CharaType>& _dataName,
			const UINT _rtWidth = 1280,
			const UINT _rtHeight = 720,
			const _D3DFORMAT _format = D3DFMT_A8R8G8B8);


		//�o�^���Ă��邷�ׂẴ����_�[�^�[�Q�b�g�e�N�X�`�������//
		void ClearRT();

		//�����_�[�^�[�Q�b�g���o�b�N�o�b�t�@�ɖ߂�//
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