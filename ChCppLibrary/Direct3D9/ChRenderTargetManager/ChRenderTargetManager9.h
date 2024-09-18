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

#ifdef CRT
		//�����_�[�^�[�Q�b�g�p�̃e�N�X�`����ݒ�//
		//�������ŉ�ʂ��N���A����F�w��//
		//ChD3D9::Shader::DrawStart�ƕ��p�ł��܂���//
		void SetRT(
			const std::string& _dataName,
			const D3DCOLOR _backCol = D3DCOLOR_ARGB(0, 0, 0, 0))
		{
			if (rtList.find(_dataName) == rtList.end())return;
			if (dbData == nullptr)return;

			if (ChPtr::NotNullCheck(uShader))
			{
				if (uShader->IsDraw())return;
			}

			device->SetRenderTarget(0, rtList[_dataName]->GetSur());
			device->SetDepthStencilSurface(rtList[_dataName]->GetZBu());


			if (ChPtr::NotNullCheck(uShader))
			{
				uShader->SetRTDraw(true);
				uShader->SetDrawDatas(_backCol);
			}

		}
#endif

	public://Get Functions//

#ifdef CRT
		//�쐬�����e�N�X�`�����擾//
		inline ChPtr::Shared<Texture9> GetRTTexture(const std::string& _dataName)
		{
			if (rtList.find(_dataName) == rtList.end())return nullptr;
			return rtList[_dataName];
		}
#endif

	private:

		BaseTexture9* GetDBData();

	public:

#ifdef CRT
		
		
		//�o�^����Ă�e�N�X�`����I�����ď���//
		void DeleteRTTexture(const std::string& _dataName)
		{
			if (rtList.empty())return;
			if (rtList.find(_dataName) == rtList.end())return;

			rtList.erase(_dataName);
		}

		//�����_�[�^�[�Q�b�g�ƂȂ�e�N�X�`�����쐬:�o�^//
		void CreateRT(
			const std::string& _dataName,
			const UINT _rtWidth = 1280,
			const UINT _rtHeight = 720,
			const _D3DFORMAT _format = D3DFMT_A8R8G8B8)
		{
			if (_rtWidth <= 0 || _rtHeight <= 0)return;
			if (rtList.find(_dataName) != rtList.end())return;

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

			rtList[_dataName] = tmpRT;
	}

#endif

		//�o�^���Ă��邷�ׂẴ����_�[�^�[�Q�b�g�e�N�X�`�������//
		void ClearRT();

		//�����_�[�^�[�Q�b�g���o�b�N�o�b�t�@�ɖ߂�//
		void ReturnRT();

	private:

		LPDIRECT3DDEVICE9 device;

		ChD3D9::ShaderController* uShader = nullptr;


#ifdef CRT

		std::map<std::string, ChPtr::Shared<BaseTexture9>>rtList;

		ChPtr::Shared<BaseTexture9>dbData;

#endif

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

	inline RenderTargetManager9& RTManager9() { return  RenderTargetManager9::GetInc(); }

}

#ifdef CRT

void ChTex::RenderTargetManager9::CreateDBData()
{
	dbData = ChPtr::Make_S<Texture9>();
}

//�o�^���Ă��邷�ׂẴ����_�[�^�[�Q�b�g�e�N�X�`�������//
void ChTex::RenderTargetManager9::ClearRT()
{
	if (rtList.empty())return;
	rtList.clear();
}

#endif

#endif