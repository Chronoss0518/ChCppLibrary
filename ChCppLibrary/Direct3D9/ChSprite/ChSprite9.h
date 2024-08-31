
#ifndef Ch_D3D9_Sp_h
#define Ch_D3D9_Sp_h

namespace ChTex
{
	typedef class BaseTexture9 Texture9;

	//(シングルトンに対して改良中)
	//スプライト描画を行うクラス//
	class Sprite9 :public ChCp::Initializer
	{
	public://Init And Release//

		void Init(const LPDIRECT3DDEVICE9 _d);

		virtual void Release();

	public:

		//第三引数がNULL又はnullptrだった場合,画面サイズと同じになる。//
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