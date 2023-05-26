#ifndef Ch_CPP_Script_h
#define Ch_CPP_Script_h

namespace ChCpp
{
	//Scriptを作成・操作するクラス
	typedef class Script:public ChCp::Releaser
	{
	private:

		struct BaseValueData
		{
			std::string valueName = "";
			
		};


	public://Initialize And Release//


		void Release()override
		{
			scriptList.clear();
		}

	public://Set Function//

		//一時的に利用する値の保持//
		void SetTmpValue(void* _value);

	public://Get Function//

		//一時的に利用する値の取得//
		void* GetTmpValue();

		std::function<bool(std::string)> GetDefaultValueSetFunction();

		std::function<bool(std::string)> GetDefaultValueSumFunction();

		std::function<bool(std::string)> GetDefaultValueSetSumFunction();

		std::function<bool(std::string)> GetDefaultValueSubFunction();

		std::function<bool(std::string)> GetDefaultValueSubSumFunction();

		std::function<bool(std::string)> GetDefaultValueMulFunction();

		std::function<bool(std::string)> GetDefaultValueMulSumFunction();

		std::function<bool(std::string)> GetDefaultValueDivFunction();

		std::function<bool(std::string)> GetDefaultValueDivSumFunction();

		std::function<bool(std::string)> GetDefaultValueEqualFunction();

		std::function<bool(std::string)> GetDefaultValueUnEqualFunction();

	public://Update Function//

		void Update();

	public://Other Function//

		void Compile(const std::string _str);

	private:

		std::vector<unsigned char> scriptList;

		std::map<std::string, ChPtr::Shared<BaseValueData>>valueMaps;
		std::map<std::string, std::string>structMaps;
		std::vector<std::string>functionStack;
		std::map<std::string, std::function<bool(std::string)>>functionMethod;

		Cumulative<std::string> blockCumulative = Cumulative<std::string>("{", "}");
		Cumulative<std::string> argumentCumulative = Cumulative<std::string>("(", ")");
		Cumulative<std::string> priorityCumulative = Cumulative<std::string>("(", ")");
		Cumulative<std::string> arrayCumulative = Cumulative<std::string>("[", "]");
		Cumulative<std::string> typeCumulative = Cumulative<std::string>("<", ">");
		Cumulative<std::string> commentCumulative = Cumulative<std::string>("/*", "*/");
		
		std::vector<std::string>stringTestCharactors;

		//一時的に作成した値//
		void* tmpValue = nullptr;

		enum class OpeCode : unsigned char
		{
			Set,			//value = target//
			Sum,			//value + target//
			Sub,			//value - target//
			Mul,			//value * target//
			Div,			//value / target//
			Sur,			//value % target//
			Equal,			//value == target//
			UnEqual,		//value != target//
			Greater,		//value > target//
			More,			//value >= target//
			Less,			//value <= target//
			Smaller,		//value < target//
			Create,			//type value//
			New,			//new type//
			Release,		//delete value//
			Constructor,	//value.Constructor//
			Destructor,		//value.Destructor//
			StartBlock,		//{//
			EndBlock,		//}//
			StartArg,		//(//
			EndArg,			//)//
			StartArray,		//[//
			EndArray,		//]//
			StartType,		//<//
			EndType,		//>//
			StartComment,	///*//
			EndComment,		//*///
			StartString,	//"//
			EndString,		//"//
			StartChar,		//'//
			EndChar,		//'//
		};

		bool inBlockFlg = true;

		Cumulative<OpeCode> blockOpeCodeCumulative = Cumulative<OpeCode>(OpeCode::StartBlock, OpeCode::EndBlock);
		Cumulative<OpeCode> argumentOpeCodeCumulative = Cumulative<OpeCode>(OpeCode::StartArg, OpeCode::EndArg);
		Cumulative<OpeCode> arrayOpeCodeCumulative = Cumulative<OpeCode>(OpeCode::StartArray, OpeCode::EndArray);
		Cumulative<OpeCode> typeOpeCodeCumulative = Cumulative<OpeCode>(OpeCode::StartType, OpeCode::EndType);
		Cumulative<OpeCode> commentOpeCodeCumulative = Cumulative<OpeCode>(OpeCode::StartComment, OpeCode::EndComment);


	}ChScCon;


}


#endif
