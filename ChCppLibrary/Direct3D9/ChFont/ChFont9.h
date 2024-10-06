#ifndef Ch_D3D9_Fo_h
#define Ch_D3D9_Fo_h

namespace ChD3D9
{

	//標準機能で描画されるフォントクラス//
	class DrawFontBase:public ChCp::Initializer
	{
	public://Init And Release//

		virtual void Release();

	public://Set Functions//

		//描画する際のフォントサイズ//
		inline void SetFontSize(const unsigned long _w, const unsigned long _h)
		{		
			fontSize.w = _w;
			fontSize.h = _h;
			Create();
		}

		inline void SetFontWeight(const unsigned long _weight)
		{
			fontWeight = _weight;
			Create();
		}

	protected:

		virtual void Create() = 0;

	protected://Constructer Destructer//

		virtual ~DrawFontBase()
		{
			Release();
		}


	protected://Member Value//

		LPD3DXFONT lpFont;
		LPDIRECT3DDEVICE9 device;

		ChMath::Vector2Base<long>fontSize = ChMath::Vector2Base<long>(16,32);
		unsigned long fontWeight = FW_REGULAR;
	};

	//標準機能で描画されるフォントクラス//
	class DrawFontA :public DrawFontBase
	{
	public:

		inline void Init(const LPDIRECT3DDEVICE9 _dv, const std::string& _fontType = "MS ゴシック")
		{
			fontType = _fontType;
			Init(_dv, fontType.c_str());
		}

	protected://Init And Release//

		void Init(const LPDIRECT3DDEVICE9 _dv, const char* _fontTypeText);

	protected://Create Functions//

		inline void Create()override
		{
			Init(device, GetFontType());
		}

	public://Set Functions//

		inline void SetFontType(const std::string& _fontType = "MS ゴシック")
		{
			fontType = _fontType;
			Create();
		}

	protected://Get Functions//

		const char* GetFontType();


	public://Draw Functions//

		//フォントの描画//
		inline void Draw(
			const std::string& _drawStr,
			const long _x,
			const long _y,
			ChVec4 _col = ChVec4(1.0f, 1.0f, 1.0f, 1.0f))
		{
			Draw(_drawStr.c_str(), _drawStr.length(), _x, _y, _col);
		}

	protected://Draw Functions//

		//フォントの描画//
		void Draw(
			const char* _drawStr,
			const unsigned long _drawStrLen,
			const long _x,
			const long _y,
			ChVec4 _col = ChVec4(1.0f, 1.0f, 1.0f, 1.0f));

	protected://Constructer Destructer//

		virtual ~DrawFontA()
		{
			Release();
		}

	private://Member Value//

		std::string fontType = "";

	public:

		static DrawFontA& GetIns()
		{
			static DrawFontA ins;
			return ins;
		}
	};

	//標準機能で描画されるフォントクラス//
	class DrawFontW :public DrawFontBase
	{
	public:

		inline void Init(const LPDIRECT3DDEVICE9 _dv, const std::wstring& _fontType = L"MS ゴシック")
		{
			fontType = _fontType;
			Init(_dv, fontType.c_str());
		}

	protected://Init And Release//

		void Init(const LPDIRECT3DDEVICE9 _dv, const wchar_t* _fontTypeText);

	protected://Create Functions//

		inline void Create()override
		{
			Init(device, GetFontType());
		}

	public://Set Functions//

		inline void SetFontType(const std::wstring& _fontType = L"MS ゴシック")
		{
			fontType = _fontType;
			Create();
		}

	protected://Get Functions//

		const wchar_t* GetFontType();

	public://Draw Functions//

		//フォントの描画//
		inline void Draw(
			const std::wstring& _drawStr,
			const long _x,
			const long _y,
			ChVec4 _col = ChVec4(1.0f, 1.0f, 1.0f, 1.0f))
		{
			Draw(_drawStr.c_str(), _drawStr.length(), _x, _y, _col);
		}

	protected://Draw Functions//

		//フォントの描画//
		void Draw(
			const wchar_t* _drawStr,
			const unsigned long _drawStrLen,
			const long _x,
			const long _y,
			ChVec4 _col = ChVec4(1.0f, 1.0f, 1.0f, 1.0f));

	protected://Constructer Destructer//

		virtual ~DrawFontW()
		{
			Release();
		}

	private://Member Value//

		std::wstring fontType = L"";

	public:

		static DrawFontW& GetIns()
		{
			static DrawFontW ins;
			return ins;
		}
	};

	inline DrawFontA& FontA() { return DrawFontA::GetIns(); }

	inline DrawFontW& FontW() { return DrawFontW::GetIns(); }

}

#endif