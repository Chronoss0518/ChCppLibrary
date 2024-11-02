#ifndef Ch_D3D9_StCo_h
#define Ch_D3D9_StCo_h

#include"../ChSprite/ChSprite9.h"

//(改良中)(使用不可)//
//その場で文字列用テクスチャを生成、ベースとなるテクスチャを用意する必要がある//
//あるフォルダに置かれた一文字づつの画像を操作するコントローラー。//
//始めにその画像群の置かれたディレクトリパスを入力する。//
//画像サイズは統一する。//

namespace ChTex
{

	typedef class BaseTexture9 Texture9;

	typedef class StringController9:public ChCp::Initializer
	{
	public://Constructer Dextructer//

		StringController9(
			const LPDIRECT3DDEVICE9 _dv,
			const std::string& _path,
			const std::string& _type,
			const unsigned short _originalWedth,
			const unsigned short _originalHeight)
		{
			size.w = _originalWedth;
			size.h = _originalHeight;
			if (size.w == 0 || size.h == 0)return;
			device = _dv;
			strPath = _path;
			typeName = _type;

			SetInitFlg(true);
		}


		~StringController9() { SetInitFlg(false); };

	public://SetFunction//

		void SetStringColor(const ChVec4& _color);

		void SetStringAlpha(const unsigned char _a);

	private://Set Functions//

		void SetStrTexture(const std::string& _str)
		{
			strTex.CreateTexture(strPath + _str + strPath, device);
		}

	public://Draw Functions//

		void DrawSprightString(
			const std::string& _str,
			const ChMat_9& _mat,
			Sprite9& _sp)
		{
			if (device == nullptr)return;
			if (_str.length() <= 0)return;

			std::string tmpStr;
			tmpStr = _str + strPath;

			for (unsigned short i = 0; i < _str.length(); i++)
			{
				//char tmpChar[3];
				SetStrTexture(_str);

				_sp.DrawSprite(
					strTex,
					_mat,
					ChVec3_9(0.0f, 0.0f, 0.0f));
			}

		}

	private://Mmember Values//
		
		ChMath::Vector2Base<unsigned short>size;

		LPDIRECT3DDEVICE9 device = nullptr;

		Texture9 strTex;

		std::string strPath;
		std::string typeName;

	}StrCon;
}


#endif