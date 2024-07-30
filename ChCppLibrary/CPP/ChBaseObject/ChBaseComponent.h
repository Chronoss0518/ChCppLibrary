
#ifndef Ch_CPP_BaCom_h
#define Ch_CPP_BaCom_h

namespace ChCpp
{
	class BasicObject;

	//ChBaseObject�ɑ΂���R���|�[�l���g�V�X�e��//
	 class BaseComponent
	{
	public:

		friend BasicObject;

	public://Constructor Destructor//

		virtual ~BaseComponent() { Release(); }

		BaseComponent() {}

	protected://Init and Release

		//�Z�b�g�����ۂɎ����I�ɌĂ΂��//
		virtual void Init() {};

		//���������ۂɎ����I�ɌĂ΂��//
		virtual void Release() {};

	public://Destroy Functions//

		//���g�����������Ƃ��ɌĂ�//
		void Destroy();

		//���g�̖{�̂��̂Ă������ɑ��点��֐�//
		void DestroyObject();

	public://Set Function//

		void SetUsing(const bool _Flg) { useFlg = _Flg; }

	public://Is Functions//

		bool IsDeth() { return dFlg; }

		bool IsUseFlg() { return useFlg; }

	protected:

#ifdef CRT

		//���ږ{�̂ɐG�肽���Ƃ��ɌĂԊ֐�//
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

		//���ږ{�̂ɐG�肽���Ƃ��ɌĂԊ֐�//
		template<class Class = BasicObject>
		auto LookObj()->typename std::enable_if<
			std::is_base_of<BasicObject, Class>::value,
			Class*>::type
		{
			return ChPtr::SafeCast<Class>(obj);
		}

#endif

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

		//�Z�b�g�����ۂɌĂ΂��//
		void BaseInit(BasicObject* _obj);

	private://Member Value//

		bool useFlg = true;

		BasicObject* obj = nullptr;

		bool dFlg = false;


	};

}

#endif