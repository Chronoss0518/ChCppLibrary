#define CRT

#include"ChVectorPack.h"

using namespace ChCRT;

template<class T>
VectorPack<T>::VectorPack() { value = new VectorPackCRT(); }

template<class T>
VectorPack<T>::~VectorPack() { delete value; }

template<class T>
VectorPack<T>::operator T*() { return &value->pack[0]; }

template<class T>
VectorPack<T>::operator const T* () const { return &value->pack[0]; }

template<class T>
size_t VectorPack<T>::GetSize() { return value->pack.size(); }

template<class T>
bool VectorPack<T>::IsEmpty() { return value->pack.empty(); }

template<class T>
void VectorPack<T>::Push(T& _val) { value->pack.push_back(_val); }

template<class T>
void VectorPack<T>::Pop() { value->pack.pop_back(); }

template<class T>
void VectorPack<T>::Remove(const size_t& _num)
{
	if (value->pack.size() <= _num)return;
	value->pack.erase(value->pack.begin() + _num);
}

template<class T>
void VectorPack<T>::Clear() { value->pack.clear(); }

//templateÇÃñæé¶ìIêÈåæ//

#define EXPLICIT_DECLARATION(_type)\
template VectorPack<##_type##>::VectorPack();\
template VectorPack<##_type##>::VectorPack();\
template VectorPack<##_type##>::operator _type##*();\
template VectorPack<##_type##>::operator const _type##*()const;\
template size_t VectorPack<##_type##>::GetSize();\
template bool VectorPack<##_type##>::IsEmpty();\
template void VectorPack<##_type##>::Push(_type##& _val);\
template void VectorPack<##_type##>::Pop();\

#include"../ChStringPack/ChStringPack.h"
#include"../ChSmartPtrPack/ChSmartPtrPack.h"
#include"../../BasePack/Ch3D.h"

EXPLICIT_DECLARATION(float);

EXPLICIT_DECLARATION(ChCRT::SharedPtrPack<Ch3D::SavePolyData>);

EXPLICIT_DECLARATION(ChCRT::StringPack<char>);
EXPLICIT_DECLARATION(ChCRT::StringPack<wchar_t>);
EXPLICIT_DECLARATION(ChCRT::StringPack<char8_t>);
EXPLICIT_DECLARATION(ChCRT::StringPack<char16_t>);
EXPLICIT_DECLARATION(ChCRT::StringPack<char32_t>);
