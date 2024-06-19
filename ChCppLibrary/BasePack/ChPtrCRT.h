#ifndef Ch_CPP_PTR_CRT_h
#define Ch_CPP_PTR_CRT_h

#include"ChPtr.h"
#include<memory>

template<typename T, class... _Types>
T* ChPtr::Instantiate(_Types&&... _args)
{
	return new T(_args...);
}

template<typename T>
T* ChPtr::InstantiateArray(unsigned long _num)
{
	return new T[_num];
}

template<typename T>
void ChPtr::Release(T*& _release)
{
	if(NullCheck(_release))return;
	delete[] _release;
	_release = nullptr;
}


//ChLibraryで利用するポインタに対して利用する関数、変数群のまとまり//
namespace ChPtr
{
	//SharedPtrの簡略版//
	template<class T>
	using Shared = std::shared_ptr<T>;

	//UniquePtrの簡略版//
	template<class T>
	using Unique = std::unique_ptr<T>;

	//WeakPtrの簡略版//
	template<class T>
	using Weak = std::weak_ptr<T>;

	//SharedPtr用ダウンキャスト//
	template<class C, class C2>
	static inline auto SharedSafeCast(Shared<C2> _sPtr)
		-> typename std::enable_if<std::is_base_of<C2, C>::value &&
		!std::is_same<C2, C>::value, Shared<C>>::type
	{
		return std::dynamic_pointer_cast<C, C2>(_sPtr);
	}

		template<class C, class C2>
	static inline auto SharedSafeCast(Shared<C2> _sPtr)
		-> typename  std::enable_if<std::is_same<C2, C>::value, Shared<C>>::type
	{
		return _sPtr;
	}

	//*Ptr用ダウンキャスト//
	template<class C, class C2>
	static inline auto SafeCast(C2* _ptr)
		-> typename  std::enable_if<std::is_base_of<C2, C>::value &&
		!std::is_same<C2, C>::value, C*>::type
	{
		return dynamic_cast<C*>(_ptr);
	}

	template<class C, class C2>
	static inline auto SafeCast(C2* _ptr)
		-> typename  std::enable_if<std::is_same<C2, C>::value, C*>::type
	{
		return (_ptr);
	}

	//make_sharedを短縮するための関数//
	template<class T, class... _Types>
	static inline Shared<T> Make_S(_Types&&... _args)
	{
		return std::make_shared<T>(_args...);
	}

	//make_uniqueを短縮するための関数//
	template<class T, class... _Types>
	static inline Unique<T> Make_U(_Types&&... _args)
	{
		return std::make_unique<T>(_args...);
	}

	//move_ptrを短縮するための関数//
	template<class T>
	static inline T Move(T _obj)
	{
		return std::move<T>(_obj);
	}

}

#endif