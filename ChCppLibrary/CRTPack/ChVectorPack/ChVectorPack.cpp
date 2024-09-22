#define CRT

#include"ChVectorPack.h"

using namespace ChCRT;

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
bool VectorPack<T>::IsFind(T& _val)const { return !value->pack.empty() ? std::find(value->pack.begin(), value->pack.end(), _val) != value->pack.end() : false; }

template<class T>
void VectorPack<T>::Push(const T& _val) { value->pack.push_back(_val); }

template<class T>
void VectorPack<T>::Pop() { value->pack.pop_back(); }

template<class T>
void VectorPack<T>::Resize(const size_t _num) { value->pack.resize(_num); }

template<class T>
void VectorPack<T>::Remove(const size_t& _num)
{
	if (value->pack.size() <= _num)return;
	value->pack.erase(value->pack.begin() + _num);
}

template<class T>
bool VectorPack<T>::RemoveObj(const T& _val)
{
	auto&& it = std::find(value->pack.begin(), value->pack.end(), _val);
	if (it == value->pack.end())return false;
	value->pack.erase(it);
	return true;
}

template<class T>
void VectorPack<T>::Clear() { value->pack.clear(); }

//templateÇÃñæé¶ìIêÈåæ//

#include"../ChStringPack/ChStringPack.h"
#include"../ChSmartPtrPack/ChSmartPtrPack.h"
#include"../../BasePack/ChMath3D.h"
#include"../../BasePack/Ch3D.h"
#include"../../CPP/ChBaseFrame/ChBaseFrame.h"
#include"../../CPP/ChBaseObject/ChBaseComponent.h"
#include"../../CPP/ChBaseObject/ChBaseObject.h"

template ChCRT::VectorPack<float>;
template ChCRT::VectorPack<unsigned char>;
template ChCRT::VectorPack<ChVec3*>;

template ChCRT::VectorPack<ChCRT::SharedPtrPack<Ch3D::SavePolyData>>;
template ChCRT::VectorPack<ChCRT::SharedPtrPack<ChCpp::FrameList::FrameCreateMethodBase>>;
template ChCRT::VectorPack<ChCRT::SharedPtrPack<ChCpp::BaseComponent>>;
template ChCRT::VectorPack<ChCRT::SharedPtrPack<ChCpp::BasicObject>>;

template ChCRT::VectorPack<ChCRT::StringPack<char>>;
template ChCRT::VectorPack < ChCRT::StringPack<wchar_t>>;
template ChCRT::VectorPack<ChCRT::StringPack<char8_t>>;
template ChCRT::VectorPack<ChCRT::StringPack<char16_t>>;
template ChCRT::VectorPack<ChCRT::StringPack<char32_t>>;
