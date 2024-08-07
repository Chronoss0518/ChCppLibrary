#include<Windows.h>

#include"../../BaseIncluder/ChBase.h"

#define NULL_CHECK(val) (val == NULL || val == nullptr)
#define NOT_NULL_CHECK(val) (val != NULL && val != nullptr)

#include"../PackData/ChPoint.h"
#include"ChWindObject.h"
#include"ChWindStyle.h"

#define Wind_Object_Inheritance_Functions(_AorW,_CharaType) \
void WindObject##_AorW##::Release(){\
	if (!IsInit())return;\
	if (NOT_NULL_CHECK(windProcedures)){\
		delete windProcedures;\
		windProcedures = nullptr;\
		SetWindowLong##_AorW##(hWnd, GWLP_USERDATA, reinterpret_cast<long>(nullptr));}\
	DestroyWindow(hWnd);\
	SetInitFlg(false);}\
\
void WindObject##_AorW##::SetWindID(long _IDPtr){\
	if (!IsInit())return;\
	SetWindowLong##_AorW##(hWnd, GWLP_ID, _IDPtr);}\
\
long WindObject##_AorW##::GetWindID(){\
	if (!IsInit())return 0;\
	return GetWindowLong##_AorW##(hWnd, GWLP_ID);}\
\
const HINSTANCE WindObject##_AorW##::GetInstance()const{ return (HINSTANCE)GetWindowLong##_AorW##(hWnd, GWL_HINSTANCE); }\
\
bool WindObject##_AorW##::Update(){\
	UpdateWindow(hWnd);\
	if (!IsInit())return false;\
	if (!PeekMessage##_AorW##(&msg, nullptr, 0, 0, PM_NOREMOVE))return true;\
	if ((GetMessage##_AorW##(&msg, nullptr, 0, 0)) <= 0)return false;\
	TranslateMessage(&msg);\
	DispatchMessage##_AorW##(&msg);\
	return true;}\
\
LPARAM WindObject##_AorW##::Send(const unsigned int _msg, WPARAM _wParam, LPARAM _lParam){\
	LPARAM out = _lParam;\
	if (!*this)return out;\
	WPARAM wParam = _wParam;\
	SendMessage##_AorW##(hWnd, _msg, wParam, out);\
	return out;}\
\
bool WindCreater::Create(WindObject##_AorW##* _out, const _CharaType* _appName, const _CharaType* _windClassName, const int _nShowCmd)const{\
	if (NULL_CHECK(_out))return false;\
	_out->hWnd = CreateWindowEx##_AorW##(\
		exStyle,\
		_windClassName,\
		_appName,\
		style,\
		pos.x, pos.y,\
		size.w, size.h,\
		parent,\
		hMenu,\
		hInst,\
		param);\
	if (NULL_CHECK(_out->hWnd))return false;\
	_out->CreateEnd(_nShowCmd);\
	SetWindowLong##_AorW##(_out->hWnd, GWLP_USERDATA, reinterpret_cast<long>(_out->windProcedures));\
	_out->parent = parent;\
	return true;}


using namespace ChWin;

///////////////////////////////////////////////////////////////////////////////////
//WindowObject Method
///////////////////////////////////////////////////////////////////////////////////

LRESULT CALLBACK ChWin::BaseWndProc(
	HWND _hWnd,
	UINT _uMsg,
	WPARAM _wParam,
	LPARAM _lParam,
	LONG(WINAPI* GetWindowLongPtrFunction)(_In_ HWND, _In_ int),
	LRESULT(WINAPI* DefWindowProcFunction)(_In_ HWND, _In_ UINT, _In_ WPARAM, _In_ LPARAM))
{
	ChWin::WindProcedure* base = ((ChWin::WindProcedure*)GetWindowLongPtrFunction(_hWnd, GWLP_USERDATA));

	if (NOT_NULL_CHECK(base))
	{
		return base->UpdateProcedure(_hWnd,_uMsg,_wParam,_lParam, GetWindowLongPtrFunction);
	}

	if (NULL_CHECK(base))
	{
		switch (_uMsg)
		{
		case WM_DESTROY:

			PostQuitMessage(0);
			return 0;

		default:
			break;
		}
	}

	return DefWindowProcFunction(_hWnd, _uMsg, _wParam, _lParam);
}

void WindObjectBase::Init(HWND _hWnd, const int _nShowCmd)
{
	if (NULL_CHECK(_hWnd))return;
	Release();
	hWnd = _hWnd;
	CreateEnd(_nShowCmd);
}

void WindObjectBase::SetWindPos(const unsigned int _x, const unsigned int _y, const unsigned int _flgs)
{
	if (!IsInit())return;
	SetWindowPos(hWnd, HWND_TOP, _x, _y, 0, 0, _flgs);
}

void WindObjectBase::SetWindSize(const unsigned int _w, const unsigned int _h, const unsigned int _flgs)
{
	if (!IsInit())return;
	SetWindowPos(hWnd, HWND_TOP, 0, 0, _w, _h, _flgs);
}

void WindObjectBase::SetWindRect(const unsigned int _x, const unsigned int _y, const unsigned int _w, const unsigned int _h, const unsigned int _flgs)
{
	if (!IsInit())return;
	SetWindowPos(hWnd, HWND_TOP, _x, _y, _w, _h, _flgs);
}

const ChPOINT WindObjectBase::GetWindSize()const
{
	ChPOINT out;
	if (!*this)return out;
	RECT rect;
	GetWindowRect(hWnd, &rect);

	out.w = rect.right - rect.left;
	out.h = rect.bottom - rect.top;

	return out;
}

const ChPOINT WindObjectBase::GetWindPos()const
{
	ChPOINT out;
	if (!*this)return out;
	RECT rect;
	GetWindowRect(hWnd, &rect);

	out.x = rect.left;
	out.y = rect.top;

	return out;
}

bool WindObjectBase::IsCursorPosOnWindow()
{
	auto size = GetWindSize();

	POINT cPos;
	GetCursorPos(&cPos);
	ScreenToClient(hWnd, &cPos);

	if (0 <= cPos.x && size.w > cPos.x && 0 <= cPos.y && size.h > cPos.y) { return true; }

	return false;
}


Wind_Object_Inheritance_Functions(A, char);

Wind_Object_Inheritance_Functions(W, wchar_t);

//WindowObjectCreate Method//

void WindCreater::SetWindStyle(const WindStyle* _style)
{
	style = _style->GetStyle();
}

void WindCreater::SetInitPosition(const ChINTPOINT& _pos)
{
	SetInitPosition(_pos.x, _pos.y);
}

void WindCreater::SetInitPosition(const int _x, const int _y)
{
	pos.x = _x >= 0 ? _x : _x * -1;
	pos.y = _y >= 0 ? _y : _y * -1;
}

void WindCreater::SetInitSize(const ChINTPOINT& _size)
{
	SetInitSize(_size.w, _size.h);
}

void WindCreater::SetInitSize(const int _w, const int _h)
{

	size.w = _w >= 0 ? _w : _w * -1;
	size.y = _h >= 0 ? _h : _h * -1;
}
