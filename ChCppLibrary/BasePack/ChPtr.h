#ifndef Ch_CPP_Ptr_h
#define Ch_CPP_Ptr_h

#ifdef CRT
#include<memory>
#endif

#ifndef SAFE_CAST_TRUE
#define SAFE_CAST_TRUE(BaseClass,TargetClass)\
->typename std::enable_if<std::is_base_of<BaseClass, TargetClass>::value && \
!std::is_same<BaseClass, TargetClass>::value, Shared<TargetClass>>::type
#endif 

#ifndef SAFE_CAST_FALSE
#define SAFE_CAST_FALSE(BaseClass,TargetClass)\
->typename  std::enable_if<std::is_same<BaseClass, TargetClass>::value, Shared<TargetClass>>::type
#endif 

#ifndef POINTER_TEST
#define POINTER_TEST(TargetClass)\
->typename std::enable_if<std::is_pointer<TargetClass>::value, bool>::type
#endif

//ChLibraryで利用するポインタに対して利用する関数、変数群のまとまり//
namespace ChPtr
{
#ifdef CRT
	//SharedPtrの簡略版//
	template<class T>
	using Shared = std::shared_ptr<T>;
#endif

#ifdef CRT
	//UniquePtrの簡略版//
	template<class T>
	using Unique = std::unique_ptr<T>;
#endif

#ifdef CRT
	//WeakPtrの簡略版//
	template<class T>
	using Weak = std::weak_ptr<T>;
#endif

#ifdef CRT
	//SharedPtr用ダウンキャスト//
	template<class C, class C2>
	static inline auto SharedSafeCast(Shared<C2> _sPtr)SAFE_CAST_TRUE(C2,C)
	{
		return std::dynamic_pointer_cast<C, C2>(_sPtr);
	}
#endif

#ifdef CRT
	template<class C, class C2>
	static inline auto SharedSafeCast(Shared<C2> _sPtr)SAFE_CAST_FALSE(C2,C)
	{
		return _sPtr;
	}
#endif

#ifdef CRT
	//*Ptr用ダウンキャスト//
	template<class C, class C2>
	static inline auto SafeCast(C2*_ptr)SAFE_CAST_TRUE(C2, C)
	{
		return dynamic_cast<C*>(_ptr);
	}
#endif

#ifdef CRT
	template<class C, class C2>
	static inline auto SafeCast(C2* _ptr)SAFE_CAST_FALSE(C2, C)
	{
		return (_ptr);
	}
#endif

#ifdef CRT
	//クラスがNULLまたはnullptrかをチェックする関数//
	template<class C>
	static inline auto NullCheck(const C& _class)POINTER_TEST(C)
	{
		return (_class == NULL || _class == nullptr);
	}
#endif

#ifdef CRT
	//クラスがNULLとnullptrのどちらでもないかをチェックする関数//
	template<class C>
	static inline auto NotNullCheck(const C& _class)POINTER_TEST(C)
	{
		return (_class != NULL && _class != nullptr);
	}
#endif

#ifdef CRT
	//make_sharedを短縮するための関数//
	template<class T, class... _Types>
	static inline Shared<T> Make_S(_Types&&... _args)
	{
		return std::make_shared<T>(_args...);
	}
#endif

#ifdef CRT
	//make_uniqueを短縮するための関数//
	template<class T, class... _Types>
	static inline Unique<T> Make_U(_Types&&... _args)
	{
		return std::make_unique<T>(_args...);
	}
#endif

#ifdef CRT
	//move_ptrを短縮するための関数//
	template<class T>
	static inline T Move(T _obj)
	{
		return std::move<T>(_obj);
	}
#endif
}
#endif
