#define CRT

#include"ChSmartPtrPack.h"

template<class T>
ChCRT::SharedPtrPack<T>& ChCRT::SharedPtrPack<T>::operator =(const NullPtr& _val) { value->pack = nullptr; return *this; }

template<class T>
bool ChCRT::SharedPtrPack<T>::operator ==(const ChCRT::SharedPtrPack<T>& _val)const { return reinterpret_cast<size_t>(value->pack.get()) == reinterpret_cast<size_t>(_val.value->pack.get()); }

template<class T>
bool ChCRT::SharedPtrPack<T>::operator !=(const ChCRT::SharedPtrPack<T>& _val)const { return reinterpret_cast<size_t>(value->pack.get()) != reinterpret_cast<size_t>(_val.value->pack.get()); }

template<class T>
ChCRT::SharedPtrPack<T>& ChCRT::SharedPtrPack<T>::operator =(const ChCRT::SharedPtrPack<T>& _val) { if (this != &_val)value->pack = _val.value->pack; return *this; }

template<class T>
bool ChCRT::SharedPtrPack<T>::operator ==(const ChCRT::NullPtr& _val)const { return value->pack == nullptr; }

template<class T>
bool ChCRT::SharedPtrPack<T>::operator !=(const ChCRT::NullPtr& _val)const { return value->pack != nullptr; }

template<class T>
T* ChCRT::SharedPtrPack<T>::operator ->()const { return value->pack.get(); }

template<class T>
T& ChCRT::SharedPtrPack<T>::operator * ()const { return *value->pack.get(); }

template<class T>
ChCRT::SharedPtrPack<T>::SharedPtrPack(){ CRTInit(); }

template<class T>
ChCRT::SharedPtrPack<T>::SharedPtrPack(const ChCRT::SharedPtrPack<T>& _val) { CRTInit(); value->pack = _val.value->pack; }

template<class T>
ChCRT::SharedPtrPack<T>::SharedPtrPack(ChCRT::SharedPtrPack<T>&& _val){ CRTInit(); value->pack = _val.value->pack; }

template<class T>
ChCRT::SharedPtrPack<T>::SharedPtrPack(const ChCRT::NullPtr& _val){ CRTInit(); value->pack = nullptr; }

template<class T>
ChCRT::SharedPtrPack<T>::SharedPtrPack(T* _val) { CRTInit(); value->pack.reset(_val); }

template<class T>
ChCRT::SharedPtrPack<T>::~SharedPtrPack() { delete value; }

template<class T>
void ChCRT::SharedPtrPack<T>::CRTInit() { value = new SharedPtrPackCRT(); }

template<class T>
void ChCRT::SharedPtrPack<T>::Set(T* _val) { value->pack = nullptr; value->pack.reset(_val); }

template<class T>
T* ChCRT::SharedPtrPack<T>::Get() const { return value->pack.get(); }

template<class T>
long ChCRT::SharedPtrPack<T>::GetUseCount()const { return value->pack.use_count(); }

template<class T, class Y>
ChCRT::SharedPtrPack<Y> ChCRT::UpCast(const ChCRT::SharedPtrPack<T>& _castBase)
{
	ChCRT::SharedPtrPack<Y> res;
	ChCRT::UpCast<T, Y>(res, _castBase);
	return res;
}

template<class T, class Y>
void ChCRT::UpCast(ChCRT::SharedPtrPack<Y>& _out, const ChCRT::SharedPtrPack<T>& _castBase) { _out.SetPack(_castBase.GetPack()); }

template<class T, class Y>
ChCRT::WeakPtrPack<Y> ChCRT::CreateWeak(const ChCRT::SharedPtrPack<T>& _castBase)
{
	ChCRT::WeakPtrPack<Y> res;
	ChCRT::CreateWeak<T, Y>(res, _castBase);
	return res;
}

template<class T, class Y>
void ChCRT::CreateWeak(ChCRT::WeakPtrPack<Y>& _out, const ChCRT::SharedPtrPack<T>& _castBase) { _out.SetPack(_castBase.GetPack()); }

template<class T,class Y>
ChCRT::SharedPtrPack<Y> ChCRT::Cast(const ChCRT::SharedPtrPack<T>& _castBase) { return std::dynamic_pointer_cast<Y, T>(_castBase.GetPack()); }

template<class T>
ChCRT::SharedPtrPack<T> ChCRT::Make() { return  std::make_shared<T>(); }

template<class T>
ChCRT::WeakPtrPack<T>& ChCRT::WeakPtrPack<T>::operator =(const ChCRT::WeakPtrPack<T>& _val) { if (this != &_val)value->pack = _val.value->pack; return *this; }

template<class T>
ChCRT::WeakPtrPack<T>& ChCRT::WeakPtrPack<T>::operator =(const ChCRT::SharedPtrPack<T>& _val) { value->pack = _val.GetPack(); return *this; }

template<class T>
ChCRT::WeakPtrPack<T>::WeakPtrPack(const ChCRT::SharedPtrPack<T>& _pack) { CRTInit(); value->pack = _pack.GetPack(); }

template<class T>
ChCRT::WeakPtrPack<T>::WeakPtrPack() { CRTInit(); }

template<class T>
ChCRT::WeakPtrPack<T>::~WeakPtrPack() { delete value; }

template<class T>
void ChCRT::WeakPtrPack<T>::CRTInit(){ value = new WeakPtrPackCRT(); }

template<class T>
void ChCRT::WeakPtrPack<T>::Set(const ChCRT::SharedPtrPack<T>& _val) { value->pack = _val.GetPack(); }

template<class T>
bool ChCRT::WeakPtrPack<T>::IsExpired()const { return value->pack.expired(); }

template<class T>
ChCRT::SharedPtrPack<T> ChCRT::WeakPtrPack<T>::LockChPtr()const { return ChCRT::SharedPtrPack<T>(value->pack.lock()); }

//templateÇÃñæé¶ìIêÈåæ//

#define MAKE_FUNCTION_EXPLICIT_DECLARATION(_MakeType) template<> ChCRT::SharedPtrPack<##_MakeType##> ChCRT::Make<##_MakeType##>()

#define MAKE_CAST_FUNCTION_EXPLICIT_DECLARATION(_BaseType,_MakeType)\
MAKE_FUNCTION_EXPLICIT_DECLARATION(##_MakeType##);\
template<> ChCRT::SharedPtrPack<##_MakeType##> ChCRT::Cast<##_BaseType##,##_MakeType##>(const ChCRT::SharedPtrPack<##_BaseType##>& _castBase);\
template<> ChCRT::SharedPtrPack<##_BaseType##> ChCRT::UpCast<##_BaseType##,##_MakeType##>(const ChCRT::SharedPtrPack<##_MakeType##>& _castBase);\
template<> void ChCRT::UpCast<##_BaseType##,##_MakeType##>(ChCRT::SharedPtrPack<##_BaseType##>& _out,const ChCRT::SharedPtrPack<##_MakeType##>& _castBase);\
template<> ChCRT::WeakPtrPack<##_BaseType##> ChCRT::CreateWeak<##_BaseType##,##_MakeType##>(const ChCRT::SharedPtrPack<##_MakeType##>& _castBase);\
template<> void ChCRT::CreateWeak<##_BaseType##,##_MakeType##>(ChCRT::WeakPtrPack<##_BaseType##>& _out,const ChCRT::SharedPtrPack<##_MakeType##>& _castBase)

#define USE_STRING_MAKE_FUNCTION_EXPLICIT_DECLARATION(_BaseType,_MakeType)\
MAKE_FUNCTION_EXPLICIT_DECLARATION(_BaseType##<char>,_MakeType##<char>);\
MAKE_FUNCTION_EXPLICIT_DECLARATION(_BaseType##<wchar_t>,_MakeType##<wchar_t>);\
MAKE_FUNCTION_EXPLICIT_DECLARATION(_BaseType##<char8_t>,_MakeType##<char8_t>);\
MAKE_FUNCTION_EXPLICIT_DECLARATION(_BaseType##<char16_t>,_MakeType##<char16_t>);\
MAKE_FUNCTION_EXPLICIT_DECLARATION(_BaseType##<char32_t>,_MakeType##<char32_t>)

#define JSON_MAKE_FUNCTIONS_EXPLICIT_DECLARATION(_BaseType,_MakeType)\
template<> class ChCRT::SharedPtrPack<##_MakeType##<char>>;\
template<> class ChCRT::SharedPtrPack<##_MakeType##<wchar_t>>;\
template<> class ChCRT::SharedPtrPack<##_MakeType##<char8_t>>;\
template<> class ChCRT::SharedPtrPack<##_MakeType##<char16_t>>;\
template<> class ChCRT::SharedPtrPack<##_MakeType##<char32_t>>;\
template<> class ChCRT::WeakPtrPack<##_MakeType##<char>>;\
template<> class ChCRT::WeakPtrPack<##_MakeType##<wchar_t>>;\
template<> class ChCRT::WeakPtrPack<##_MakeType##<char8_t>>;\
template<> class ChCRT::WeakPtrPack<##_MakeType##<char16_t>>;\
template<> class ChCRT::WeakPtrPack<##_MakeType##<char32_t>>;\
MAKE_CAST_FUNCTION_EXPLICIT_DECLARATION(##_BaseType##<char>, _MakeType##<char>);\
MAKE_CAST_FUNCTION_EXPLICIT_DECLARATION(##_BaseType##<wchar_t>, _MakeType##<wchar_t>);\
MAKE_CAST_FUNCTION_EXPLICIT_DECLARATION(##_BaseType##<char8_t>, _MakeType##<char8_t>);\
MAKE_CAST_FUNCTION_EXPLICIT_DECLARATION(##_BaseType##<char16_t>, _MakeType##<char16_t>);\
MAKE_CAST_FUNCTION_EXPLICIT_DECLARATION(##_BaseType##<char32_t>, _MakeType##<char32_t>)

#include"../../BasePack/ChMath3D.h"
#include"../../BasePack/Ch3D.h"
#include"../../CPP/ChBaseFrame/ChBaseFrame.h"
#include"../../CPP/ChBaseObject/ChBaseComponent.h"
#include"../../CPP/ChBaseObject/ChBaseObject.h"
#include"../../BaseSystem/ChBaseSystem/ChBaseSystem.h"
#include"../../CPP/ChJsonObject/ChJsonBaseType.h"
#include"../../CPP/ChJsonObject/ChJsonArray.h"
#include"../../CPP/ChJsonObject/ChJsonBoolean.h"
#include"../../CPP/ChJsonObject/ChJsonNumber.h"
#include"../../CPP/ChJsonObject/ChJsonObject.h"
#include"../../CPP/ChJsonObject/ChJsonString.h"

template<> class ChCRT::SharedPtrPack<ChVector4>;
MAKE_FUNCTION_EXPLICIT_DECLARATION(ChVector4, ChVector4);

template<> class ChCRT::SharedPtrPack<ChSystem::BaseSystem>;
template<> class ChCRT::SharedPtrPack<Ch3D::SavePolyData>;
template<> class ChCRT::SharedPtrPack<ChCpp::FrameList::FrameCreateMethodBase>;
template<> class ChCRT::SharedPtrPack<ChCpp::SaveDataClass>;
template<> class ChCRT::SharedPtrPack<ChCpp::SendDataClass>;
template<> class ChCRT::SharedPtrPack<ChCpp::BaseComponent>;
template<> class ChCRT::SharedPtrPack<ChCpp::BasicObject>;

template<> class ChCRT::SharedPtrPack<ChCpp::JsonBaseType<char>>;
template<> class ChCRT::SharedPtrPack<ChCpp::JsonBaseType<wchar_t>>;
template<> class ChCRT::SharedPtrPack<ChCpp::JsonBaseType<char8_t>>;
template<> class ChCRT::SharedPtrPack<ChCpp::JsonBaseType<char16_t>>;
template<> class ChCRT::SharedPtrPack<ChCpp::JsonBaseType<char32_t>>;

template<> class ChCRT::WeakPtrPack<ChCpp::JsonBaseType<char>>;
template<> class ChCRT::WeakPtrPack<ChCpp::JsonBaseType<wchar_t>>;
template<> class ChCRT::WeakPtrPack<ChCpp::JsonBaseType<char8_t>>;
template<> class ChCRT::WeakPtrPack<ChCpp::JsonBaseType<char16_t>>;
template<> class ChCRT::WeakPtrPack<ChCpp::JsonBaseType<char32_t>>;

template<> class ChCRT::SharedPtrPack<ChCpp::JsonArray<char>>; template<> class ChCRT::SharedPtrPack<ChCpp::JsonArray<wchar_t>>; template<> class ChCRT::SharedPtrPack<ChCpp::JsonArray<char8_t>>; template<> class ChCRT::SharedPtrPack<ChCpp::JsonArray<char16_t>>; template<> class ChCRT::SharedPtrPack<ChCpp::JsonArray<char32_t>>; template<> class ChCRT::WeakPtrPack<ChCpp::JsonArray<char>>; template<> class ChCRT::WeakPtrPack<ChCpp::JsonArray<wchar_t>>; template<> class ChCRT::WeakPtrPack<ChCpp::JsonArray<char8_t>>; template<> class ChCRT::WeakPtrPack<ChCpp::JsonArray<char16_t>>; template<> class ChCRT::WeakPtrPack<ChCpp::JsonArray<char32_t>>; template<> ChCRT::SharedPtrPack<ChCpp::JsonArray<char>> ChCRT::Make<ChCpp::JsonArray<char>>(); template<> ChCRT::SharedPtrPack<ChCpp::JsonArray<char>> ChCRT::Cast<ChCpp::JsonBaseType<char>, ChCpp::JsonArray<char>>(const ChCRT::SharedPtrPack<ChCpp::JsonBaseType<char>>& _castBase); template<> ChCRT::SharedPtrPack<ChCpp::JsonBaseType<char>> ChCRT::UpCast<ChCpp::JsonBaseType<char>, ChCpp::JsonArray<char>>(const ChCRT::SharedPtrPack<ChCpp::JsonArray<char>>& _castBase); template<> void ChCRT::UpCast<ChCpp::JsonBaseType<char>, ChCpp::JsonArray<char>>(ChCRT::SharedPtrPack<ChCpp::JsonBaseType<char>>& _out, const ChCRT::SharedPtrPack<ChCpp::JsonArray<char>>& _castBase); template<> ChCRT::WeakPtrPack<ChCpp::JsonBaseType<char>> ChCRT::CreateWeak<ChCpp::JsonBaseType<char>, ChCpp::JsonArray<char>>(const ChCRT::SharedPtrPack<ChCpp::JsonArray<char>>& _castBase); template<> void ChCRT::CreateWeak<ChCpp::JsonBaseType<char>, ChCpp::JsonArray<char>>(ChCRT::WeakPtrPack<ChCpp::JsonBaseType<char>>& _out, const ChCRT::SharedPtrPack<ChCpp::JsonArray<char>>& _castBase); template<> ChCRT::SharedPtrPack<ChCpp::JsonArray<wchar_t>> ChCRT::Make<ChCpp::JsonArray<wchar_t>>(); template<> ChCRT::SharedPtrPack<ChCpp::JsonArray<wchar_t>> ChCRT::Cast<ChCpp::JsonBaseType<wchar_t>, ChCpp::JsonArray<wchar_t>>(const ChCRT::SharedPtrPack<ChCpp::JsonBaseType<wchar_t>>& _castBase); template<> ChCRT::SharedPtrPack<ChCpp::JsonBaseType<wchar_t>> ChCRT::UpCast<ChCpp::JsonBaseType<wchar_t>, ChCpp::JsonArray<wchar_t>>(const ChCRT::SharedPtrPack<ChCpp::JsonArray<wchar_t>>& _castBase); template<> void ChCRT::UpCast<ChCpp::JsonBaseType<wchar_t>, ChCpp::JsonArray<wchar_t>>(ChCRT::SharedPtrPack<ChCpp::JsonBaseType<wchar_t>>& _out, const ChCRT::SharedPtrPack<ChCpp::JsonArray<wchar_t>>& _castBase); template<> ChCRT::WeakPtrPack<ChCpp::JsonBaseType<wchar_t>> ChCRT::CreateWeak<ChCpp::JsonBaseType<wchar_t>, ChCpp::JsonArray<wchar_t>>(const ChCRT::SharedPtrPack<ChCpp::JsonArray<wchar_t>>& _castBase); template<> void ChCRT::CreateWeak<ChCpp::JsonBaseType<wchar_t>, ChCpp::JsonArray<wchar_t>>(ChCRT::WeakPtrPack<ChCpp::JsonBaseType<wchar_t>>& _out, const ChCRT::SharedPtrPack<ChCpp::JsonArray<wchar_t>>& _castBase); template<> ChCRT::SharedPtrPack<ChCpp::JsonArray<char8_t>> ChCRT::Make<ChCpp::JsonArray<char8_t>>(); template<> ChCRT::SharedPtrPack<ChCpp::JsonArray<char8_t>> ChCRT::Cast<ChCpp::JsonBaseType<char8_t>, ChCpp::JsonArray<char8_t>>(const ChCRT::SharedPtrPack<ChCpp::JsonBaseType<char8_t>>& _castBase); template<> ChCRT::SharedPtrPack<ChCpp::JsonBaseType<char8_t>> ChCRT::UpCast<ChCpp::JsonBaseType<char8_t>, ChCpp::JsonArray<char8_t>>(const ChCRT::SharedPtrPack<ChCpp::JsonArray<char8_t>>& _castBase); template<> void ChCRT::UpCast<ChCpp::JsonBaseType<char8_t>, ChCpp::JsonArray<char8_t>>(ChCRT::SharedPtrPack<ChCpp::JsonBaseType<char8_t>>& _out, const ChCRT::SharedPtrPack<ChCpp::JsonArray<char8_t>>& _castBase); template<> ChCRT::WeakPtrPack<ChCpp::JsonBaseType<char8_t>> ChCRT::CreateWeak<ChCpp::JsonBaseType<char8_t>, ChCpp::JsonArray<char8_t>>(const ChCRT::SharedPtrPack<ChCpp::JsonArray<char8_t>>& _castBase); template<> void ChCRT::CreateWeak<ChCpp::JsonBaseType<char8_t>, ChCpp::JsonArray<char8_t>>(ChCRT::WeakPtrPack<ChCpp::JsonBaseType<char8_t>>& _out, const ChCRT::SharedPtrPack<ChCpp::JsonArray<char8_t>>& _castBase); template<> ChCRT::SharedPtrPack<ChCpp::JsonArray<char16_t>> ChCRT::Make<ChCpp::JsonArray<char16_t>>(); template<> ChCRT::SharedPtrPack<ChCpp::JsonArray<char16_t>> ChCRT::Cast<ChCpp::JsonBaseType<char16_t>, ChCpp::JsonArray<char16_t>>(const ChCRT::SharedPtrPack<ChCpp::JsonBaseType<char16_t>>& _castBase); template<> ChCRT::SharedPtrPack<ChCpp::JsonBaseType<char16_t>> ChCRT::UpCast<ChCpp::JsonBaseType<char16_t>, ChCpp::JsonArray<char16_t>>(const ChCRT::SharedPtrPack<ChCpp::JsonArray<char16_t>>& _castBase); template<> void ChCRT::UpCast<ChCpp::JsonBaseType<char16_t>, ChCpp::JsonArray<char16_t>>(ChCRT::SharedPtrPack<ChCpp::JsonBaseType<char16_t>>& _out, const ChCRT::SharedPtrPack<ChCpp::JsonArray<char16_t>>& _castBase); template<> ChCRT::WeakPtrPack<ChCpp::JsonBaseType<char16_t>> ChCRT::CreateWeak<ChCpp::JsonBaseType<char16_t>, ChCpp::JsonArray<char16_t>>(const ChCRT::SharedPtrPack<ChCpp::JsonArray<char16_t>>& _castBase); template<> void ChCRT::CreateWeak<ChCpp::JsonBaseType<char16_t>, ChCpp::JsonArray<char16_t>>(ChCRT::WeakPtrPack<ChCpp::JsonBaseType<char16_t>>& _out, const ChCRT::SharedPtrPack<ChCpp::JsonArray<char16_t>>& _castBase); template<> ChCRT::SharedPtrPack<ChCpp::JsonArray<char32_t>> ChCRT::Make<ChCpp::JsonArray<char32_t>>(); template<> ChCRT::SharedPtrPack<ChCpp::JsonArray<char32_t>> ChCRT::Cast<ChCpp::JsonBaseType<char32_t>, ChCpp::JsonArray<char32_t>>(const ChCRT::SharedPtrPack<ChCpp::JsonBaseType<char32_t>>& _castBase); template<> ChCRT::SharedPtrPack<ChCpp::JsonBaseType<char32_t>> ChCRT::UpCast<ChCpp::JsonBaseType<char32_t>, ChCpp::JsonArray<char32_t>>(const ChCRT::SharedPtrPack<ChCpp::JsonArray<char32_t>>& _castBase); template<> void ChCRT::UpCast<ChCpp::JsonBaseType<char32_t>, ChCpp::JsonArray<char32_t>>(ChCRT::SharedPtrPack<ChCpp::JsonBaseType<char32_t>>& _out, const ChCRT::SharedPtrPack<ChCpp::JsonArray<char32_t>>& _castBase); template<> ChCRT::WeakPtrPack<ChCpp::JsonBaseType<char32_t>> ChCRT::CreateWeak<ChCpp::JsonBaseType<char32_t>, ChCpp::JsonArray<char32_t>>(const ChCRT::SharedPtrPack<ChCpp::JsonArray<char32_t>>& _castBase); template<> void ChCRT::CreateWeak<ChCpp::JsonBaseType<char32_t>, ChCpp::JsonArray<char32_t>>(ChCRT::WeakPtrPack<ChCpp::JsonBaseType<char32_t>>& _out, const ChCRT::SharedPtrPack<ChCpp::JsonArray<char32_t>>& _castBase);
JSON_MAKE_FUNCTIONS_EXPLICIT_DECLARATION(ChCpp::JsonBaseType, ChCpp::JsonBoolean);
JSON_MAKE_FUNCTIONS_EXPLICIT_DECLARATION(ChCpp::JsonBaseType, ChCpp::JsonNull);
JSON_MAKE_FUNCTIONS_EXPLICIT_DECLARATION(ChCpp::JsonBaseType, ChCpp::JsonNumber);
JSON_MAKE_FUNCTIONS_EXPLICIT_DECLARATION(ChCpp::JsonBaseType, ChCpp::JsonObject);
JSON_MAKE_FUNCTIONS_EXPLICIT_DECLARATION(ChCpp::JsonBaseType, ChCpp::JsonString);

USE_STRING_MAKE_FUNCTION_EXPLICIT_DECLARATION(ChCpp::JsonArray, ChCpp::JsonArray);
USE_STRING_MAKE_FUNCTION_EXPLICIT_DECLARATION(ChCpp::JsonBoolean, ChCpp::JsonBoolean);
USE_STRING_MAKE_FUNCTION_EXPLICIT_DECLARATION(ChCpp::JsonNull, ChCpp::JsonNull);
USE_STRING_MAKE_FUNCTION_EXPLICIT_DECLARATION(ChCpp::JsonNumber, ChCpp::JsonNumber);
USE_STRING_MAKE_FUNCTION_EXPLICIT_DECLARATION(ChCpp::JsonObject, ChCpp::JsonObject);
USE_STRING_MAKE_FUNCTION_EXPLICIT_DECLARATION(ChCpp::JsonString, ChCpp::JsonString);

template<> class ChCRT::WeakPtrPack<ChSystem::BaseSystem>;
template<> class ChCRT::WeakPtrPack<Ch3D::SavePolyData>;
template<> class ChCRT::WeakPtrPack<ChCpp::FrameList::FrameCreateMethodBase>;
template<> class ChCRT::WeakPtrPack<ChCpp::SaveDataClass>;
template<> class ChCRT::WeakPtrPack<ChCpp::SendDataClass>;
template<> class ChCRT::WeakPtrPack<ChCpp::BaseComponent>;
template<> class ChCRT::WeakPtrPack<ChCpp::BasicObject>;

