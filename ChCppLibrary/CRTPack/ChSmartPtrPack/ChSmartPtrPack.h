#ifndef Ch_CRT_SmartPtr
#define Ch_CRT_SmartPtr

#include"../ChCRTBase.h"

#ifdef CRT
#include<memory>
#endif

namespace ChCRT
{
	class NullPtr final { public: NullPtr() {} };

	template<class T>
	class SharedPtrPack final
	{
		struct SharedPtrPackCRT
		{
#ifdef CRT
			std::shared_ptr<T>pack = nullptr;
#endif
		};

	public:

		Ch_CRT_Operator_Functions_To_Pack(SharedPtrPack, std::shared_ptr<T>);

#ifdef CRT
		operator std::weak_ptr<T> () { return value->pack; }
#endif
		
		SharedPtrPack& operator =(const SharedPtrPack& _val);
		bool operator ==(const SharedPtrPack& _val)const;
		bool operator !=(const SharedPtrPack& _val)const;

		SharedPtrPack& operator =(const NullPtr& _val);

		bool operator ==(const NullPtr& _val)const;

		bool operator !=(const NullPtr& _val)const;

		T*  operator->()const;

		T& operator * ()const;

	public:

		Ch_CRT_ConstructorDestructor_Functions(SharedPtrPack, std::shared_ptr<T>);

#ifdef CRT
		template<class Y>
		SharedPtrPack(Y* _val) { value = new SharedPtrPackCRT(); value->pack.reset(_val); }
#endif
		SharedPtrPack(const SharedPtrPack& _val);

		SharedPtrPack(SharedPtrPack&& _val);

		SharedPtrPack(const NullPtr& _val);
		
		SharedPtrPack();

		~SharedPtrPack();

	public:

#ifdef CRT
		template<class Y>
		void Set(Y* _val) { value->pack = nullptr; value->pack.reset(_val); }

		inline void SetPack(const std::shared_ptr<T>& _val) { value->pack = _val; }
#endif

	public:

		T* Get()const;

		long GetUseCount()const;

#ifdef CRT
		inline std::shared_ptr<T> GetPack()const { return value->pack; }
#endif

	public:

#ifdef CRT
		template<class Y>
		void Make() { value->pack = std::make_shared<Y>(); }
#endif

	private:

		SharedPtrPackCRT* value = nullptr;
	};



	template<class T>
	class WeakPtrPack final
	{

		struct WeakPtrPackCRT
		{
#ifdef CRT
			std::weak_ptr<T>pack;
#endif
		};

	public:

		Ch_CRT_Operator_Functions_To_Pack(WeakPtrPack, std::weak_ptr<T>);

		WeakPtrPack& operator =(const WeakPtrPack& _val);

		WeakPtrPack& operator =(const SharedPtrPack<T>& _val);
	public:

		Ch_CRT_ConstructorDestructor_Functions(WeakPtrPack, std::weak_ptr<T>);

		Ch_CRT_ConstructorDestructor_Functions(WeakPtrPack, std::shared_ptr<T>);

		WeakPtrPack(const SharedPtrPack<T>& _pack);

		WeakPtrPack();

		~WeakPtrPack();

	public:

		void Set(const SharedPtrPack<T>& _val);

#ifdef CRT
		void SetPack(const std::weak_ptr<T>& _val) { value->pack = _val; }

		void SetPack(const std::shared_ptr<T>& _val) { value->pack = _val; }
#endif
	public:

#ifdef CRT
		std::weak_ptr<T> GetPack() const { return value->pack; }
#endif

	public:

		bool IsExpired()const;

		SharedPtrPack<T> LockChPtr()const;

#ifdef CRT
		std::shared_ptr<T> LockPtr()const { return value->pack.lock(); }
#endif
	private:

		WeakPtrPackCRT* value = nullptr;
	};
}

#endif