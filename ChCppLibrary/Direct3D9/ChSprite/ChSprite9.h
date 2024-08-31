
#ifndef Ch_D3D9_Sp_h
#define Ch_D3D9_Sp_h

namespace ChTex
{
	typedef class BaseTexture9 Texture9;

	//(�V���O���g���ɑ΂��ĉ��ǒ�)
	//�X�v���C�g�`����s���N���X//
	class Sprite9 :public ChCp::Initializer
	{
	public://Init And Release//

		void Init(const LPDIRECT3DDEVICE9 _d);

		virtual void Release();

	public:

		//��O������NULL����nullptr�������ꍇ,��ʃT�C�Y�Ɠ����ɂȂ�B//
		virtual void DrawSprite(
			const Texture9& _tex,
			const ChMat_9& _mat,
			const ChVec3_9& _centerPos,
			const RECT& _animationRect = { 0,0,0,0 });

	protected:


		LPD3DXSPRITE sp;
		LPDIRECT3DDEVICE9 device;
	
	protected://Constructer Destructer//

		Sprite9() {};

		virtual ~Sprite9() { Release(); };

	public:

		inline static Sprite9& GetIns()
		{
			static Sprite9 Ins;
			return Ins;
		}

	};

	inline Sprite9& DrawSp9() { return Sprite9::GetIns(); };

}

#endif
//CopyRight Chronoss0518 2018/08