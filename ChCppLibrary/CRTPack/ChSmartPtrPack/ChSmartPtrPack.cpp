#define CRT

#include"ChSmartPtrPack.h"

using namespace ChCRT;

//templateÇÃñæé¶ìIêÈåæ//

#define EXPLICIT_DECLARATION(_type)\
template SharedPtrPack<##_type##>::operator _type##* ();\
template SharedPtrPack<##_type##>::operator const _type##* ()const;\
template SharedPtrPack<##_type##>::SharedPtrPack(##_type##* _val);\
template SharedPtrPack<##_type##>::SharedPtrPack();\
template SharedPtrPack<##_type##>::~SharedPtrPack();\
template void SharedPtrPack<##_type##>::Set(##_type##* _val);\
template const _type##* SharedPtrPack<##_type##>::Get() const;\
template void SharedPtrPack<##_type##>::Make();\
template WeakPtrPack<##_type##>::WeakPtrPack();\
template WeakPtrPack<##_type##>::~WeakPtrPack();\
template void WeakPtrPack<##_type##>::Set(const SharedPtrPack<##_type##>& _val);\
template bool WeakPtrPack<##_type##>::IsExpired()const;\
template SharedPtrPack<##_type##> WeakPtrPack<##_type##>::LockChPtr()const;

#include"../../BasePack/Ch3D.h"

EXPLICIT_DECLARATION(Ch3D::SavePolyData);



template<class T>
SharedPtrPack<T>::operator T* () { return value->pack.get(); }

template<class T>
SharedPtrPack<T>::operator const T* ()const{ value->pack.get(); }

template<class T>
SharedPtrPack<T>::SharedPtrPack(T* _val) { value = new SharedPtrPackCRT(); value->pack.reset(_val); }

template<class T>
SharedPtrPack<T>::SharedPtrPack(){ value = new SharedPtrPackCRT(); }

template<class T>
SharedPtrPack<T>::~SharedPtrPack() { delete value; }

template<class T>
void SharedPtrPack<T>::Set(T* _val) { value->pack = nullptr; value->pack.reset(_val); }

template<class T>
const T* SharedPtrPack<T>::Get() const { return value->pack.get(); }

template<class T>
void SharedPtrPack<T>::Make() { value->pack = std::make_shared<T>(); }

template<class T>
WeakPtrPack<T>::WeakPtrPack() { value = new WeakPtrPackCRT(); }

template<class T>
WeakPtrPack<T>::~WeakPtrPack() { delete value; }

template<class T>
void WeakPtrPack<T>::Set(const SharedPtrPack<T>& _val) { value->pack = _val.GetPack(); }

template<class T>
bool WeakPtrPack<T>::IsExpired()const { return value->pack.expired(); }

template<class T>
SharedPtrPack<T> WeakPtrPack<T>::LockChPtr()const { return SharedPtrPack<T>(value->pack.lock()); }
