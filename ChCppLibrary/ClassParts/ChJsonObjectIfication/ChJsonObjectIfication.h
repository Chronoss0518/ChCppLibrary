#ifndef Ch_CPP_JsonObject_h
#define Ch_CPP_JsonObject_h


namespace ChCp
{
#ifdef _UNICODE

	using TextType = std::wstring;

#else

	using TextType = std::string;

#endif


	enum class JsonType
	{
		Object,
		Array,
		Number,
		String,
		Boolean
	};

	//継承して利用する//
	//AddValueでJsonパラメータとして利用する値を登録する//
	//Serializeで文字列化Deserializeでオブジェクト化を行う//
	class JsonObjectIfication
	{
	protected://Add Functions//

		template<typename BaseType>
		void AddValue(BaseType* _value, const std::string& _parameterName);

		void AddValue(bool* _value, const std::string& _parameterName);

		void AddValue(std::wstring* _value, const std::string& _parameterName);

		void AddValue(JsonObjectIfication* _value, const std::string& _parameterName);

		template<typename BaseType>
		void AddValue(std::vector<BaseType>* _value, const std::string& _parameterName);

		void AddValue(std::vector<bool>* _value, const std::string& _parameterName);

		void AddValue(std::vector<std::wstring>* _value, const std::string& _parameterName);

		void AddValue(std::vector<ChPtr::Shared<JsonObjectIfication>>* _value, const std::string& _parameterName);

	public:

		TextType Serialize()
		{
			return

#ifdef _UNICODE
				SerializeFromWCharText();
#else
				SerializeFromCharText();
#endif

		};

		void Deserialize(const TextType& _str)
		{

#ifdef _UNICODE
			DeserializeFromWCharText(_str);
#else
			DeserializeFromCharText(_str);
#endif
		};

		std::string SerializeFromCharText();
		std::wstring SerializeFromWCharText();

		void DeserializeFromCharText(const std::string& _text);
		void DeserializeFromWCharText(const std::wstring& _text);

	public:


		struct JsonClassBase :private ChCp::Initializer
		{
		protected:

			void Init(JsonType _type)
			{
				if (*this)return;
				type = type;
				SetInitFlg(true);
			}

			TextType Serialize()
			{
				return

#ifdef _UNICODE
					SerializeFromWCharText();
#else
					SerializeFromCharText();
#endif

			};

			void Deserialize(const TextType& _str)
			{

#ifdef _UNICODE
				DeserializeFromWCharText(_str);
#else
				DeserializeFromCharText(_str);
#endif
			};


			virtual std::string SerializeFromCharText() = 0;

			virtual std::wstring SerializeFromWCharText() = 0;

			virtual void DeserializeFromCharText(const std::string& _text) = 0;

			virtual void DeserializeFromWCharText(const std::wstring& _text) = 0;

		private:

			JsonType type;

		};


	private:

		std::map<std::string, ChPtr::Shared<JsonClassBase>>jsonValues;

	};
}



#endif
