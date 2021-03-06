
#ifndef Ch_CPP_BaCom_h
#define Ch_CPP_BaCom_h

namespace ChCpp
{
	class BaseObject;

	//ChBaseObjectに対するコンポーネントシステム//
	 class BaseComponent :public  std::enable_shared_from_this<BaseComponent>
	{
	public:

		friend BaseObject;

		///////////////////////////////////////////////////////////////////////////////////
		//ConstructerDestructer//

		virtual ~BaseComponent() { Release(); }

		BaseComponent() {}

	protected:

		///////////////////////////////////////////////////////////////////////////////////
		//InitAndRelease//

		//セットされる際に自動的に呼ばれる//
		virtual void Init() {};

		//消去される際に自動的に呼ばれる//
		virtual void Release() {};

	public://Destroy Functions//

		//自身を消したいときに呼ぶ//
		void Destroy();

		//自身の本体を捨てたい時に走らせる関数//
		void DestroyObject();

	public://Set Function//

		inline void SetUsing(const ChStd::Bool _Flg) { useFlg = _Flg; }

	public://Is Functions//

		inline ChStd::Bool IsDeth() { return dFlg; }

		inline ChStd::Bool IsUseFlg() { return useFlg; }

	protected:

		///////////////////////////////////////////////////////////////////////////////////
		//LookFunction//

		//直接本体に触りたいときに呼ぶ関数//
		template<class Class = BaseObject>
		ChStd::Bool LookObj(typename
			std::enable_if<std::is_base_of<BaseObject, Class>::value, ChPtr::Shared<Class>>::type _out)
			
		{
			auto testObj = ChPtr::SharedSafeCast<Class>(obj.lock());

			if (testObj == nullptr)return false;

			_out = testObj;

			return true;

		}

		//直接本体に触りたいときに呼ぶ関数//
		template<class Class = BaseObject>
		auto LookObj()->
			typename std::enable_if<std::is_base_of<BaseObject, Class>::value, ChPtr::Shared<Class>>::type
		{
			return ChPtr::SharedSafeCast<Class>(obj.lock());
		}

		///////////////////////////////////////////////////////////////////////////////////
		//UpdateFuncsions//
		virtual void UpdateBegin() {};
		virtual void Update() {};
		virtual void UpdateEnd() {};

		//MoveFuncsions//
		virtual void MoveBegin() {};
		virtual void Move() {};
		virtual void MoveEnd() {};

		//DrawFuncsions//
		virtual void DrawBegin() {}
		virtual void Draw3D() {}
		virtual void Draw2D() {}
		virtual void DrawEnd() {}

	private:

		//セットされる際に呼ばれる//
		void BaseInit(ChPtr::Shared<BaseObject> _obj);

		///////////////////////////////////////////////////////////////////////////////////

		ChStd::Bool useFlg = true;

		ChPtr::Weak<BaseObject> obj = ChPtr::Shared<BaseObject>();

		ChStd::Bool dFlg = false;


	};

}

#endif