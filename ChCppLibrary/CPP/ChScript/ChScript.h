#ifndef Ch_CPP_Script_h
#define Ch_CPP_Script_h

namespace ChCpp
{
	class ScriptBase;

	//スクリプト全体を管理するクラス//
	//これを各地に配置して利用する//
	class ScriptController:public ChCp::Releaser
	{

	public:

		///////////////////////////////////////////////////////////////////////////////////
		//InitAndRelease//

		void Release()override
		{
			scriptList.clear();
		}

		///////////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		//登録しているScriptをセットする。//
		template<class Script>
		auto SetScript()->typename std::enable_if<std::is_base_of<ScriptBase, Script>::value, ChPtr::Shared<Script>>::type
		{
			ChPtr::Shared<ScriptBase> script = ChPtr::Make_S<Script>();
			script->Init(this);
			scriptList.push_back(script);
			return ChPtr::SharedSafeCast<Script>(script);
		}

		///////////////////////////////////////////////////////////////////////////////////
		//GetFunction//

		unsigned long GetNowScriptNum()
		{

			if (nowScript.lock() == nullptr)return ULONG_MAX;

			return nowScript.lock()->myNum;

		}


		///////////////////////////////////////////////////////////////////////////////////
		//UpdateFunction//

		void Update()
		{
			if (nowScript.lock() == nullptr)return;
			nowScript.lock()->update();
			Chenge();
		}
		///////////////////////////////////////////////////////////////////////////////////

		void ClearScript()
		{
			scriptList.clear();
		}

	protected:

		void Change();

		std::vector<ChPtr::Shared<ScriptBase>>scriptList;

		unsigned long nowScriptNo = 0;

	};

	class ScriptBase
	{
	public:

		void Init(ScriptController* _controller,ChPtr::Weak<ScriptBase> _upScript = ChPtr::Shared<ScriptBase>());

	public:

		virtual void Update() = 0;

	protected:

		void NextScript();

		ChPtr::Weak<ScriptBase> upScript;

	private:

		ScriptController* controller = nullptr;

	};

	class ScriptIfBase : public ScriptBase
	{
	public:

		virtual bool UseFunction() = 0;

	private:

		void Update()override final{}

	};

	class ScriptIfTrue :public ScriptIfBase
	{
	public:

		virtual bool IfFunction() { return true; }
		
		bool UseFunction()override final;

	};

	class ScriptIfFalse :public ScriptIfBase
	{
	public:

		virtual bool IfFunction() { return true; }

		bool UseFunction()override final;
	};

	class ScriptSequence :public ScriptBase
	{
	public:

		void SetScript(ChPtr::Shared<ScriptBase> _script);

	protected:

		void Update()override;

	private:

		std::vector<ChPtr::Shared<ScriptBase>> scriptList;

	};

	class ScriptLoop final :public ScriptSequence
	{
	public:

		void SetScript(ChPtr::Shared<ScriptBase> _script);

		void Break();

	private:

		void Update()override final;


	};
}


#endif
