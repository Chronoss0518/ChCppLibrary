//imgui Library License//
/*

The MIT License (MIT)

Copyright (c) 2014-2021 Omar Cornut

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef Ch_ImGui_BaWind_h
#define Ch_ImGui_BaWind_h

#ifndef IMGUI_VERSION

#include"../../External/imgui/imgui.h"
#include"../../External/imgui/imconfig.h"

#endif

#ifdef _WINDOWS_

LRESULT ImGui_ImplWin32_WndProcHandler(
	HWND hWnd
	, UINT msg
	, WPARAM wParam
	, LPARAM lParam);

#else

struct HWND;

struct IDirect3DDevice9;
struct ID3D11Device;
struct ID3D11DeviceContext;

#endif

bool ImGui_ImplWin32_Init(void*);
void ImGui_ImplWin32_Shutdown();
void ImGui_ImplWin32_NewFrame();
bool ImGui_ImplDX9_Init(IDirect3DDevice9*);
void ImGui_ImplDX9_Shutdown();
void ImGui_ImplDX9_NewFrame();
void ImGui_ImplDX9_RenderDrawData(ImDrawData*);
bool ImGui_ImplDX11_Init(ID3D11Device*, ID3D11DeviceContext*);
void ImGui_ImplDX11_Shutdown();
void ImGui_ImplDX11_NewFrame();
void ImGui_ImplDX11_RenderDrawData(ImDrawData*);

namespace ChImGui
{

	class BaseWind : public ChCp::Initializer
	{
	public:

		///////////////////////////////////////////////////////////////////////////////////
		//ConstructerDestructer//

		virtual ~BaseWind() { Release(); }

		///////////////////////////////////////////////////////////////////////////////////
		//InitAndRelease//

		//日本語化未実装//
		//基本的にWinInit等環境に合ったものを利用する//

#ifdef _WINDOWS_
		inline void Init(
			const HWND _hWnd
			, const bool _LJapaneseFlg = false)
		{
			if (IsBaseInit())return;

			Init(_LJapaneseFlg);

			ImGui_ImplWin32_Init(_hWnd);
			GetFlgManager().WinRelease = []()
			{
				ImGui_ImplWin32_Shutdown();
			};

			GetFlgManager().WinDrawSetting = []()
			{
				ImGui_ImplWin32_NewFrame();
			};

#ifdef Ch_Game_Windows_h

			ChSystem::Windows::ImGuiProc = ImGuiProc;

#endif

		}

#ifdef _D3D9_H_
		inline void Init(const HWND _hWnd
			, const LPDIRECT3DDEVICE9 _lpDevice
			, const bool _LJapaneseFlg = false)
		{
			if (IsBaseInit())return;

			Init(_hWnd, _LJapaneseFlg);

			ImGui_ImplDX9_Init(_lpDevice);

			GetFlgManager().D3D9Release = []()
			{
				ImGui_ImplDX9_Shutdown();
			};

			GetFlgManager().D3D9DrawSetting = []()
			{
				ImGui_ImplDX9_NewFrame();
			};

			GetFlgManager().D3D9Draw = []()
			{
				ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
			};


		}
#endif //D3D9//

#ifdef __d3d11_h__
		inline void Init(const HWND _hWnd
			, const ID3D11Device* _lpDevice
			, const ID3D11DeviceContext* _lpContext
			, const bool _LJapaneseFlg = false)
		{

			if (IsBaseInit())return;
			Init(_hWnd, _LJapaneseFlg);

			ID3D11Device* Device
				= const_cast<ID3D11Device*>(_lpDevice);

			ID3D11DeviceContext* Context
				= const_cast<ID3D11DeviceContext*>(_lpContext);

			ImGui_ImplDX11_Init(Device, Context);

			GetFlgManager().D3D11Release = []()
			{
				ImGui_ImplDX11_Shutdown();
			};
			GetFlgManager().D3D11DrawSetting = []()
			{
				ImGui_ImplDX11_NewFrame();
			};

			GetFlgManager().D3D11Draw = []()
			{
				ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
			};
		}


#endif //D3D9//

#endif


		void Release()
		{
			if (!IsBaseInit())return;

		}


	public:

		///////////////////////////////////////////////////////////////////////////////////
		//Operator//

		BaseWind& operator = (const BaseWind& _Wind)
		{
			WPos = _Wind.WPos;
			WSize = _Wind.WSize;
			WFlg = _Wind.WFlg;
			return *this;
		}

		///////////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		void SetWindSize(
			const ImVec2& _Vec
			, const bool _NotReSize = false);

		void SetWindSize(
			const ChVec2& _Vec
			, const bool _NotReSize = false);

		void SetWindSize(
			const float _w
			, const float _h
			, const bool _NotMove = false);

		void SetWindPos(
			const ImVec2& _Vec
			, const bool _NotMove = false);

		void SetWindPos(
			const ChVec2& _Vec
			, const bool _NotMove = false);

		void SetWindPos(
			const float _w
			, const float _h
			, const bool _NotReSize = false);

		inline void SetWindTrueFlg(const ImGuiWindowFlags _Flg)
		{

		}

		inline void SetWindFalseFlg(const ImGuiWindowFlags _Flg)
		{

		}

		inline void SetIOpenFlg(const bool _Flg) { IOpenFlg = _Flg; }

		inline void SetCutLine()
		{
			if (!IsBaseInit())return;

			ImGui::Separator();
		}

		static inline void SetNotIniFile()
		{

			if (!IsBaseInit())return;
			ImGui::GetIO().IniFilename = nullptr;
		}


		///////////////////////////////////////////////////////////////////////////////////
		//IsFunction//

		//このボタンが押された際にtrueになる//
		//SameLine = 同じ行という意味//
		bool IsOpenButton(
			const std::string& _ButtonName
			, const bool _SameLineFlg = false
			, const std::string& _SubName = "");

		static bool IsBaseInit();

		inline bool IsIOpen() { return IOpenFlg; }

		///////////////////////////////////////////////////////////////////////////////////
		//EditFunction//


		//InputText//

		void InputText(
			std::string& _Text
			, const std::string& _Label
			, const unsigned long _MaxTextNum = 100);

		//TextDraw//
		void Text(const std::string& _Text)
		{

			if (!IsBaseInit())return;
			if (!GetFlgManager().IsWindOpen())return;

			ImGui::Text(_Text.c_str());

		}

		template<typename ...T>
		void Text(const std::string& _Text
			, T... Args)
		{

			if (!IsBaseInit())return;
			if (!GetFlgManager().IsWindOpen())return;

			ImGui::Text(_Text.c_str(), Args);

		}

		//LabelTextDraw//
		void LabelText(const std::string& _Text)
		{

			if (!IsBaseInit())return;
			if (!GetFlgManager().IsWindOpen())return;

			ImGui::LabelText(_Text.c_str(), nullptr);
		}

		template<typename ...T>
		void LabelText(const std::string& _Text
			, const std::string& _SubText
			, T... Args)
		{
			if (!IsBaseInit())return;
			if (!GetFlgManager().IsWindOpen())return;

			ImGui::LabelText(_Text.c_str(), _SubText.c_str(), Args);
		}

		template<typename ...T>
		void LabelText(const std::string& _Text
			, T... Args)
		{

			if (!IsBaseInit())return;
			if (!GetFlgManager().IsWindOpen())return;

			ImGui::LabelText(_Text, Args);
		}

		//FloatEdit//
		void DragFloat(
			float& _Val
			, const std::string& _Label
			, const float _Min = 0.0f
			, const float _Max = 0.0f
			, const float _Speed = 1.0f);

		void SliderFloat(
			float& _Val
			, const std::string& _Label
			, const float _Min = 0.0f
			, const float _Max = 0.0f);

		//Vector2Edit//
		void DragVector2(
			float& _x
			, float& _y
			, const std::string& _Label
			, const float _Min = 0.0f
			, const float _Max = 0.0f
			, const float _Speed = 1.0f);

		inline void DragVector2(
			ChVec2& _Vec
			, const std::string& _Label
			, const float _Min = 0.0f
			, const float _Max = 0.0f
			, const float _Speed = 1.0f)
		{
			if (!IsBaseInit())return;
			if (!GetFlgManager().IsWindOpen())return;

			float tmp[2];
			tmp[0] = _Vec.val[0];
			tmp[1] = _Vec.val[1];

			ImGui::DragFloat2(
				_Label.c_str()
				, tmp
				, _Speed
				, _Min
				, _Max);

			_Vec.val.Set(tmp);

		}

		//Vector2Edit(Slider)//
		void SliderVector2(
			float& _x
			, float& _y
			, const std::string& _Label
			, const float _Min = 0.0f
			, const float _Max = 0.0f);

		inline void SliderVector2(
			ChVec2& _Vec
			, const std::string& _Label
			, const float _Min = 0.0f
			, const float _Max = 0.0f)
		{
			if (!IsBaseInit())return;
			if (!GetFlgManager().IsWindOpen())return;

			float tmp[2];
			tmp[0] = _Vec.val[0];
			tmp[1] = _Vec.val[1];

			ImGui::SliderFloat2(
				_Label.c_str()
				, tmp
				, _Min
				, _Max);

			_Vec.val.Set(tmp);
		}


		//Vector3Edit//
		void DragVector3(
			float& _x
			, float& _y
			, float& _z
			, const std::string& _Label
			, const float _Min = 0.0f
			, const float _Max = 0.0f
			, const float _Speed = 1.0f);

		inline void DragVector3(
			ChVec3& _Vec
			, const std::string& _Label
			, const float _Min = 0.0f
			, const float _Max = 0.0f
			, const float _Speed = 1.0f)
		{
			if (!IsBaseInit())return;
			if (!GetFlgManager().IsWindOpen())return;

			float tmp[3];
			tmp[0] = _Vec.val[0];
			tmp[1] = _Vec.val[1];
			tmp[2] = _Vec.val[2];


			ImGui::DragFloat3(
				_Label.c_str()
				, tmp
				, _Speed
				, _Min
				, _Max);

			_Vec.val.Set(tmp);
		}

		//Vector3Edit(Slider)//
		void SliderVector3(
			float& _x
			, float& _y
			, float& _z
			, const std::string& _Label
			, const float _Min = 0.0f
			, const float _Max = 0.0f);

		inline void SliderVector3(
			ChVec3& _Vec
			, const std::string& _Label
			, const float _Min = 0.0f
			, const float _Max = 0.0f)
		{

			if (!IsBaseInit())return;
			if (!GetFlgManager().IsWindOpen())return;

			float tmp[3];
			tmp[0] = _Vec.val[0];
			tmp[1] = _Vec.val[1];
			tmp[2] = _Vec.val[2];

			ImGui::SliderFloat3(
				_Label.c_str()
				, tmp
				, _Min
				, _Max);

			_Vec.val.Set(tmp);
		}

		//Vector4Edit//
		void DragVector4(
			float& _x
			, float& _y
			, float& _z
			, float& _w
			, const std::string& _Label
			, const float _Min = 0.0f
			, const float _Max = 0.0f
			, const float _Speed = 1.0f);

		inline void DragVector4(
			ChVec4& _Vec
			, const std::string& _Label
			, const float _Min = 0.0f
			, const float _Max = 0.0f
			, const float _Speed = 1.0f)
		{
			if (!IsBaseInit())return;
			if (!GetFlgManager().IsWindOpen())return;

			float tmp[4];
			tmp[0] = _Vec.val[0];
			tmp[1] = _Vec.val[1];
			tmp[2] = _Vec.val[2];
			tmp[3] = _Vec.val[3];

			ImGui::DragFloat4(
				_Label.c_str()
				, tmp
				, _Speed
				, _Min
				, _Max);

			_Vec.val.Set(tmp);
		}

		//Vector4Edit(Slider)//
		void SliderVector4(
			float& _x
			, float& _y
			, float& _z
			, float& _w
			, const std::string& _Label
			, const float _Min = 0.0f
			, const float _Max = 0.0f);

		inline void SliderVector4(
			ChVec4& _Vec
			, const std::string& _Label
			, const float _Min = 0.0f
			, const float _Max = 0.0f)
		{

			if (!IsBaseInit())return;
			if (!GetFlgManager().IsWindOpen())return;

			float tmp[4];
			tmp[0] = _Vec.val[0];
			tmp[1] = _Vec.val[1];
			tmp[2] = _Vec.val[2];
			tmp[3] = _Vec.val[3];

			ImGui::SliderFloat4(
				_Label.c_str()
				, tmp
				, _Min
				, _Max);

			_Vec.val.Set(tmp);
		}

		//ColorEdit//
		void EditColor(
			float& _a
			, float& _r
			, float& _g
			, float& _b
			, const std::string& _Label);

		inline void EditColor(
			ChMath::Vector4Base<float> _Vec
			, const std::string& _Label
			, const float _Min = 0.0f
			, const float _Max = 0.0f)
		{

			if (!IsBaseInit())return;
			if (!GetFlgManager().IsWindOpen())return;

			EditColor(
				_Vec.a
				, _Vec.r
				, _Vec.g
				, _Vec.b
				, _Label
			);
		}

		inline void EditColor(
			ChMath::Vector4Base<float>& _Col
			, const std::string& _Label)
		{
			if (!IsBaseInit())return;
			if (!GetFlgManager().IsWindOpen())return;


			EditColor(
				_Col.a
				, _Col.r
				, _Col.g
				, _Col.b
				, _Label
			);
		}

		inline void EditColor(
			ChMath::Vector4Base<char>& _Col
			, const std::string& _Label)
		{
			if (!IsBaseInit())return;
			if (!GetFlgManager().IsWindOpen())return;

			ChMath::Vector4Base<float> TmpCol;
			_Col.val.Mul(255);

			TmpCol.val.Set(_Col.val);

			EditColor(
				TmpCol.a
				, TmpCol.r
				, TmpCol.g
				, TmpCol.b
				, _Label

			);

			_Col.val.Set(TmpCol.val);
			_Col.val.Div(255);

		}

		///////////////////////////////////////////////////////////////////////////////////

		void WindBegin(const std::string& _WindName);

		///////////////////////////////////////////////////////////////////////////////////

		void WindEnd();

		///////////////////////////////////////////////////////////////////////////////////

		static void Draw();

		///////////////////////////////////////////////////////////////////////////////////

#ifdef _WINDOWS_

		inline static bool ImGuiProc(
			HWND _hWnd
			, UINT _uMsg
			, WPARAM _wParam
			, LPARAM _lParam)
		{

			if (!IsBaseInit())return false;

			return
				ImGui_ImplWin32_WndProcHandler(
					_hWnd, _uMsg, _wParam, _lParam) ? true : false;

		};

#endif

	protected:

		inline void Init(const bool _LJapaneseFlg = false)
		{
			if (GetFlgManager())return;

			GetFlgManager().Init();
			CreateJapaneseLangage();
		}

		void CreateJapaneseLangage();

		///////////////////////////////////////////////////////////////////////////////////
		//全体フラグ管理クラス//
		class ImGuiFlagBase :public ChCp::Initializer
		{
		public:

			///////////////////////////////////////////////////////////////////////////////////
			//InitAndRelease//

			void Init();

			void Release();

			///////////////////////////////////////////////////////////////////////////////////
			//SetFunction//

			void SetWindOpen(const bool _Flg) { WindOpenFlg = _Flg; }

			///////////////////////////////////////////////////////////////////////////////////
			//IsFunction//

			bool IsWindOpen() { return WindOpenFlg; }

			///////////////////////////////////////////////////////////////////////////////////

			void DrawSetting();

			///////////////////////////////////////////////////////////////////////////////////

			void Draw();

			///////////////////////////////////////////////////////////////////////////////////

			friend BaseWind;

		protected:

			std::function<void()> WinRelease = nullptr;
			std::function<void()> D3D9Release = nullptr;
			std::function<void()> D3D11Release = nullptr;

			std::function<void()> WinDrawSetting = nullptr;
			std::function<void()> D3D9DrawSetting = nullptr;
			std::function<void()> D3D11DrawSetting = nullptr;

			std::function<void()> D3D9Draw = nullptr;
			std::function<void()> D3D11Draw = nullptr;


		private:

			///////////////////////////////////////////////////////////////////////////////////
			//ConstructerDestructer//

			virtual ~ImGuiFlagBase() { Release(); }

			///////////////////////////////////////////////////////////////////////////////////

			bool DrawSettingFlg = false;
			bool WindOpenFlg = false;

		};


		static ImGuiFlagBase& GetFlgManager()
		{
			static ImGuiFlagBase ins;
			return ins;
		}

		bool OnceFlg = false;

		ImGuiWindowFlags WFlg = 0;

		ImVec2 WSize = ImVec2(-1.0f, -1.0f);
		bool RSizeFlg = false;

		ImVec2 WPos = ImVec2(-1.0f, -1.0f);
		bool RMoveFlg = false;

	private:

		static bool BaseInitFlgment;

		bool IOpenFlg = false;

	};

	class  ImGuiWindObject :public BaseWind
	{

	public:

		///////////////////////////////////////////////////////////////////////////////////
		//ConstructerDestructer//

		ImGuiWindObject(const std::string& _WindName);

		ImGuiWindObject(
			const std::string& _WindName
			, const BaseWind& _Wind);

		virtual ~ImGuiWindObject() final { WindEnd(); };

	private:



	};



}

#endif