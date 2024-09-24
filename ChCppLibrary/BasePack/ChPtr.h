#ifndef Ch_CPP_Ptr_h
#define Ch_CPP_Ptr_h

#include<memory>

#ifndef CH_SAFE_CAST_TRUE
#define CH_SAFE_CAST_TRUE(BaseClass,TargetClass)\
->typename std::enable_if<std::is_base_of<BaseClass, TargetClass>::value && \
!std::is_same<BaseClass, TargetClass>::value, Shared<TargetClass>>::type
#endif 

#ifndef CH_SAFE_CAST_FALSE
#define CH_SAFE_CAST_FALSE(BaseClass,TargetClass)\
->typename  std::enable_if<std::is_same<BaseClass, TargetClass>::value, Shared<TargetClass>>::type
#endif 

#ifndef CH_POINTER_TEST
#define CH_POINTER_TEST(TargetClass)\
->typename std::enable_if<std::is_pointer<TargetClass>::value, bool>::type
#endif

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

	//SharedPtr用ダウンキャスト//
	template<class C, class C2>
	static inline typename std::enable_if<std::is_base_of<C2, C>::value && !std::is_same<C2, C>::value, Shared<C>>::type
		SharedSafeCast(Shared<C2> _sPtr)
	{
		return std::dynamic_pointer_cast<C, C2>(_sPtr);
	}

	template<class C, class C2>
	static inline typename std::enable_if<std::is_same<C2, C>::value, Shared<C>>::type
		SharedSafeCast(Shared<C2> _sPtr)
	{
		return _sPtr;
	}

	//*Ptr用ダウンキャスト//
	template<class C, class C2>
	static inline typename std::enable_if<std::is_base_of<C2, C>::value && !std::is_same<C2, C>::value, C*>::type
		SafeCast(C2* _ptr)
	{
		return dynamic_cast<C*>(_ptr);
	}

	template<class C, class C2>
	static inline typename std::enable_if<std::is_same<C2, C>::value, C*>::type
		SafeCast(C2* _ptr)
	{
		return (_ptr);
	}

	//クラスがNULLまたはnullptrかをチェックする関数//
	template<class C>
	static inline auto NullCheck(const C& _class)CH_POINTER_TEST(C)
	{
		return (_class == NULL || _class == nullptr);
	}

	//クラスがNULLとnullptrのどちらでもないかをチェックする関数//
	template<class C>
	static inline auto NotNullCheck(const C& _class)CH_POINTER_TEST(C)
	{
		return (_class != NULL && _class != nullptr);
	}
}
#endif
