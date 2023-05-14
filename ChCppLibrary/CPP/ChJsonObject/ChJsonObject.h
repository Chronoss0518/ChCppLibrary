#ifndef Ch_CPP_JsonObject_h
#define Ch_CPP_JsonObject_h

#include"../ChBaseObject/ChBaseObject.h"

namespace ChCpp
{
	class JsonObject:protected BaseObject
	{
	public:

		std::string GetText();

	private:
		std::string text;
	};

	class JsonArray :public JsonObject
	{
	public:

		std::string GetText();

		std::vector<ChPtr::Shared<JsonObject>>GetArray();
	};

	class JsonNumber :public JsonObject
	{

		double GetValue();

	private:
	};

	class JsonString :public JsonObject
	{

	private:
		std::string value = "";
	};

	class JsonBoolean :public JsonObject
	{

	private:
		bool value = false;
	};
}



#endif
