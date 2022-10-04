#ifndef Ch_CPP_JsonObject_h
#define Ch_CPP_JsonObject_h

#include"../ChBaseObject/ChBaseObject.h"

namespace ChCpp
{
	class JsonObject:protected BaseObject
	{

	private:

		std::map<std::string, ChPtr::Shared<JsonObject>>value;

	};

	class JsonArray :public JsonObject
	{
	private:

		std::vector<ChPtr::Shared<JsonObject>>value;

	};

	class JsonNumber :public JsonObject
	{

	private:

		double value = 0.0;

	};

	class JsonString :public JsonObject
	{

	private:

		std::string value = "";

	};

	class JsonBoolean :public JsonObject
	{

	private:

		bool value = false;;

	};
}



#endif
