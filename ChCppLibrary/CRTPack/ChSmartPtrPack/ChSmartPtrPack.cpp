#define CRT

#include"ChSmartPtrPack.h"

using namespace ChCRT;

template<class T>
SharedPtrPack<T>& SharedPtrPack<T>::operator =(const NullPtr& _val) { value->pack = nullptr; return *this; }

template<class T>
bool SharedPtrPack<T>::operator ==(const SharedPtrPack<T>& _val)const { return reinterpret_cast<size_t>(value->pack.get()) == reinterpret_cast<size_t>(_val.value->pack.get()); }

template<class T>
bool SharedPtrPack<T>::operator !=(const SharedPtrPack<T>& _val)const { return reinterpret_cast<size_t>(value->pack.get()) != reinterpret_cast<size_t>(_val.value->pack.get()); }

template<class T>
SharedPtrPack<T>& SharedPtrPack<T>::operator =(const SharedPtrPack<T>& _val) { if (this != &_val)value->pack = _val.value->pack; return *this; }

template<class T>
bool SharedPtrPack<T>::operator ==(const NullPtr& _val)const { return value->pack == nullptr; }

template<class T>
bool SharedPtrPack<T>::operator !=(const NullPtr& _val)const { return value->pack != nullptr; }

template<class T>
T* SharedPtrPack<T>::operator ->()const { return value->pack.get(); }

template<class T>
T& SharedPtrPack<T>::operator * ()const { return *value->pack.get(); }

template<class T>
SharedPtrPack<T>::SharedPtrPack(){ value = new SharedPtrPackCRT(); }

template<class T>
SharedPtrPack<T>::SharedPtrPack(const SharedPtrPack& _val) { value = new SharedPtrPackCRT(); value->pack = _val.value->pack; }

template<class T>
SharedPtrPack<T>::SharedPtrPack(SharedPtrPack&& _val){ value = new SharedPtrPackCRT(); value->pack = _val.value->pack; }

template<class T>
SharedPtrPack<T>::SharedPtrPack(const NullPtr& _val){ value = new SharedPtrPackCRT(); value->pack = nullptr; }

template<class T>
SharedPtrPack<T>::~SharedPtrPack() { delete value; }

template<class T>
T* SharedPtrPack<T>::Get() const { return value->pack.get(); }

template<class T>
long SharedPtrPack<T>::GetUseCount()const { return value->pack.use_count(); }

template<class T>
WeakPtrPack<T>& WeakPtrPack<T>::operator =(const WeakPtrPack<T>& _val) { if (this != &_val)value->pack = _val.value->pack; return *this; }

template<class T>
WeakPtrPack<T>& WeakPtrPack<T>::operator =(const SharedPtrPack<T>& _val) { value->pack = _val.GetPack(); return *this; }

template<class T>
WeakPtrPack<T>::WeakPtrPack(const SharedPtrPack<T>& _pack) { value = new WeakPtrPackCRT(); value->pack = _pack.GetPack(); }

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
//templateÇÃñæé¶ìIêÈåæ//

#include"../../BasePack/Ch3D.h"
#include"../../CPP/ChBaseFrame/ChBaseFrame.h"
#include"../../CPP/ChBaseObject/ChBaseComponent.h"
#include"../../CPP/ChBaseObject/ChBaseObject.h"
#include"../../BaseSystem/ChBaseSystem/ChBaseSystem.h"

template ChCRT::SharedPtrPack<ChSystem::BaseSystem>;
template ChCRT::SharedPtrPack<Ch3D::SavePolyData>;
template ChCRT::SharedPtrPack<ChCpp::FrameList::FrameCreateMethodBase>;
template ChCRT::SharedPtrPack<ChCpp::SaveDataClass>;
template ChCRT::SharedPtrPack<ChCpp::SendDataClass>;
template ChCRT::SharedPtrPack<ChCpp::BaseComponent>;
template ChCRT::SharedPtrPack<ChCpp::BasicObject>;
;
template ChCRT::WeakPtrPack<ChSystem::BaseSystem>;
template ChCRT::WeakPtrPack<Ch3D::SavePolyData>;
template ChCRT::WeakPtrPack<ChCpp::FrameList::FrameCreateMethodBase>;
template ChCRT::WeakPtrPack<ChCpp::SaveDataClass>;
template ChCRT::WeakPtrPack<ChCpp::SendDataClass>;
template ChCRT::WeakPtrPack<ChCpp::BaseComponent>;
template ChCRT::WeakPtrPack<ChCpp::BasicObject>;
