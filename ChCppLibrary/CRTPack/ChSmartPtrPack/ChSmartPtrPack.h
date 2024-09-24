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
	class SharedPtrPack;

	template<class T>
	class WeakPtrPack;

	template<class T, class Y>
	SharedPtrPack<Y> UpCast(const SharedPtrPack<T>& _castBase);

	template<class T, class Y>
	void UpCast(SharedPtrPack<Y>& _out,const SharedPtrPack<T>& _castBase);

	template<class T, class Y>
	WeakPtrPack<Y> CreateWeak(const SharedPtrPack<T>& _castBase);

	template<class T, class Y>
	void CreateWeak(WeakPtrPack<Y>& _out,const SharedPtrPack<T>& _castBase);

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

		template<class Y>
		inline bool operator ==(const std::shared_ptr<Y>& _val)const{ return reinterpret_cast<size_t>(value->pack.get()) == reinterpret_cast<size_t>(_val.get()); }

		template<class Y>
		inline bool operator !=(const std::shared_ptr<Y>& _val)const{ return reinterpret_cast<size_t>(value->pack.get()) != reinterpret_cast<size_t>(_val.get()); }

#endif

#ifdef CRT

		template<class Y>
		operator std::weak_ptr<Y> () { return value->pack; }

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

		SharedPtrPack(T* _val);

		template<class Y>
		inline SharedPtrPack(typename std::enable_if<std::is_base_of<Y, T>::value, const SharedPtrPack<Y>&>::type _val)
		{
			CRTInit();
			ChCRT::UpCast<T,Y>(*this,_val);
		}

		SharedPtrPack(const SharedPtrPack& _val);

		SharedPtrPack(SharedPtrPack&& _val);

		SharedPtrPack(const NullPtr& _val);
		
		SharedPtrPack();

		~SharedPtrPack();

	private:

		void CRTInit();

	public:

		void Set(T* _val);

#ifdef CRT
		inline void SetPack(const std::shared_ptr<T>& _val) { value->pack = _val; }
#endif

	public:

		T* Get()const;

		long GetUseCount()const;

#ifdef CRT
		inline std::shared_ptr<T> GetPack()const { return value->pack; }
#endif

	public:

	private:

		SharedPtrPackCRT* value = nullptr;
	};


	template<class T>
	SharedPtrPack<T> Make();

	template<class T, class Y>
	SharedPtrPack<Y> Cast(const SharedPtrPack<T>& _castBase);

	template<class T, class Y>
	SharedPtrPack<Y> DownCast(const SharedPtrPack<T>& _castBase)
	{
		return ChCRT::Cast<T, Y>(_castBase);
	}


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

		template<class Y>
		WeakPtrPack& operator =(const SharedPtrPack<Y>& _val);
	public:

		Ch_CRT_ConstructorDestructor_Functions(WeakPtrPack, std::weak_ptr<T>);

		Ch_CRT_ConstructorDestructor_Functions(WeakPtrPack, std::shared_ptr<T>);

		WeakPtrPack(const ChCRT::SharedPtrPack<T>& _pack);

		template<class Y>
		WeakPtrPack(const ChCRT::SharedPtrPack<Y>& _val)
		{
			CRTInit();
			ChCRT::CreateWeak<Y, Y>(*this, _val);
		}

		WeakPtrPack();

		~WeakPtrPack();

	private:

		void CRTInit();

	public:

		void Set(const ChCRT::SharedPtrPack<T>& _val);

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