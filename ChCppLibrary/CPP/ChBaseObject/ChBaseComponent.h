
#ifndef Ch_CPP_BaCom_h
#define Ch_CPP_BaCom_h

namespace ChCpp
{
	class BasicObject;

	//ChBaseObjectに対するコンポーネントシステム//
	class BaseComponent
	{
	public:

		friend BasicObject;

	protected://Constructor Destructor//

		virtual ~BaseComponent() { Release(); }

		BaseComponent() {}

	protected://Init and Release

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

		void SetUsing(const bool _Flg) { useFlg = _Flg; }

	public://Is Functions//

		bool IsDeth() { return dFlg; }

		bool IsUseFlg() { return useFlg; }

	protected:

		//直接本体に触りたいときに呼ぶ関数//
		template<class Class = BasicObject>
		bool LookObj(typename std::enable_if<
			std::is_base_of<BasicObject, Class>::value,
			Class*>::type _out)
		{
			auto&& testObj = ChPtr::SafeCast<Class>(obj);
			if (ChPtr::NullCheck(testObj))return false;
			_out = testObj;

			return true;
		}

		//直接本体に触りたいときに呼ぶ関数//
		template<class Class = BasicObject>
		typename std::enable_if<
			std::is_base_of<BasicObject, Class>::value,
			Class*>::type LookObj()
		{
			return ChPtr::SafeCast<Class>(obj);
		}

		inline BasicObject* LookObj() { return obj; }

	protected:

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
		void BaseInit(BasicObject* _obj);

	private://Member Value//

		bool useFlg = true;

		BasicObject* obj = nullptr;

		bool dFlg = false;
	};
}

#endif