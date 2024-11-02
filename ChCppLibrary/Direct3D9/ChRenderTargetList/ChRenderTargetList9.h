#ifndef Ch_D3D9_RTList_h
#define Ch_D3D9_RTList_h

namespace ChD3D9
{
	class ShaderController;
}

namespace ChTex
{

	typedef class BaseTexture9 Texture9;

	//�����_�[�^�[�Q�b�g��ݒ肷��N���X//
	typedef class RenderTargetList9 :public ChCp::Initializer
	{
	public://Constructer Destructer//

		RenderTargetList9() {};

		virtual ~RenderTargetList9()
		{
			Release();
		}

	public://Init And Release//

		void Init(
			const LPDIRECT3DDEVICE9& _dv,
			const unsigned short _windWidth,
			const unsigned short _windHeight,
			const ChD3D9::ShaderController* _shader = nullptr);

		virtual void Release();

	private:

		void CreateDBData();

		BaseTexture9* GetDBData();

		void ReleaseDBData();

	public://Set Functions//

		//�����_�[�^�[�Q�b�g�p�̃e�N�X�`����ݒ�//
		//�������ŉ�ʂ��N���A����F�w��//
		//ChD3D9::Shader::DrawStart�ƕ��p�ł��܂���//
		void SetRT(
			const unsigned short _dataNum,
			const D3DCOLOR _backCol = D3DCOLOR_ARGB(0,0,0,0));

	public://RTTexture Control Functions//

		//�쐬�����e�N�X�`�����擾//
		Texture9* GetRTTexture(const unsigned short _dataNum);

		//�o�^����Ă�e�N�X�`����I�����ď���//
		void DeleteRTTexture(const unsigned short _dataNum);

		//�o�^���Ă��邷�ׂẴ����_�[�^�[�Q�b�g�e�N�X�`�������//
		void ClearRT();

		//�����_�[�^�[�Q�b�g�ƂȂ�e�N�X�`�����쐬:�o�^//
		void CreateRT(
			const unsigned short _dataNum,
			const UINT _rtWidth = 1280,
			const UINT _rtHeight = 720,
			const _D3DFORMAT _format = D3DFMT_A8R8G8B8)

		{
			if (_rtWidth <= 0 || _rtHeight <= 0)return;

			auto&& rt = GetRTTexture(_dataNum);
			if (ChPtr::NullCheck(rt))return;

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
			rtList[_dataNum] = tmpRT;
		}

		//�����_�[�^�[�Q�b�g���o�b�N�o�b�t�@�ɖ߂�//
		void ReturnRT();

	private://Member Value//

		LPDIRECT3DDEVICE9 device;

		ChD3D9::ShaderController* uShader = nullptr;

		std::map<unsigned short, ChPtr::Shared<BaseTexture9>>rtList;

		ChPtr::Shared<BaseTexture9>dbData = nullptr;


	}ChRTList9;

}

#endif