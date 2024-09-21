#define CRT

#include"ChVectorPack.h"

using namespace ChCRT;

//templateÇÃñæé¶ìIêÈåæ//

#define EXPLICIT_DECLARATION(_type)\
template VectorPack<##_type##>::VectorPack();\
template VectorPack<##_type##>::~VectorPack();\
template _type##& VectorPack<##_type##>::operator[] (const size_t _num);\
template const _type##& VectorPack<##_type##>::operator [](const size_t _num)const;\
template size_t VectorPack<##_type##>::GetSize()const;\
template bool VectorPack<##_type##>::IsEmpty()const;\
template void VectorPack<##_type##>::Push(const _type##& _val);\
template void VectorPack<##_type##>::Pop();\
template void VectorPack<##_type##>::Remove(const size_t& _num);\
template void VectorPack<##_type##>::Clear();\

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

template<class T>
VectorPack<T>::VectorPack() { value = new VectorPackCRT(); }

template<class T>
VectorPack<T>::~VectorPack() { delete value; }

template<class T>
T& VectorPack<T>::operator[](const size_t _num) { return value->pack[_num]; }

template<class T>
const T& VectorPack<T>::operator[](const size_t _num)const { return value->pack[_num]; }

template<class T>
size_t VectorPack<T>::GetSize()const { return value->pack.size(); }

template<class T>
bool VectorPack<T>::IsEmpty()const { return value->pack.empty(); }

template<class T>
void VectorPack<T>::Push(const T& _val) { value->pack.push_back(_val); }

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
