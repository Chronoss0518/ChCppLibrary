
#ifndef Ch_CPP_BaCom_h
#define Ch_CPP_BaCom_h

namespace ChCpp
{
	class BaseObject;

	//ChBaseObject�ɑ΂���R���|�[�l���g�V�X�e��//
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

		inline void SetUsing(const ChStd::Bool _Flg) { useFlg = _Flg; }

	public://Is Functions//

		inline ChStd::Bool IsDeth() { return dFlg; }

		inline ChStd::Bool IsUseFlg() { return useFlg; }

	protected:

		///////////////////////////////////////////////////////////////////////////////////
		//LookFunction//

		//���ږ{�̂ɐG�肽���Ƃ��ɌĂԊ֐�//
		template<class Class = BaseObject>
		ChStd::Bool LookObj(typename std::enable_if<
			std::is_base_of<BaseObject, Class>::value,
			Class*>::type _out)
			
		{
			auto&& testObj = ChPtr::SafeCast<Class>(obj);

			if (ChPtr::NullCheck(testObj))return false;

			_out = testObj;

			return true;

		}

		//���ږ{�̂ɐG�肽���Ƃ��ɌĂԊ֐�//
		template<class Class = BaseObject>
		auto LookObj()->typename std::enable_if<
			std::is_base_of<BaseObject, Class>::value,
			Class*>::type
		{
			return ChPtr::SafeCast<Class>(obj);
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

		//�Z�b�g�����ۂɌĂ΂��//
		void BaseInit(BaseObject* _obj);

		///////////////////////////////////////////////////////////////////////////////////

		ChStd::Bool useFlg = true;

		BaseObject* obj = nullptr;

		ChStd::Bool dFlg = false;


	};

}

#endif