
#ifndef Ch_CPP_ObjMa_h
#define Ch_CPP_ObjMa_h

#include"ChObjectList.h"

namespace ChCpp
{

	

	class ObjectManager :public ObjectList
	{
	private:

		///////////////////////////////////////////////////////////////////////////////////////
		//CostructerDestructer//

		ObjectManager() {}
		~ObjectManager() {}

	public:

		static ObjectManager& GetIns()
		{
			static ObjectManager Ins;
			return Ins;
		}

	};

	static const std::function<ObjectManager&()>ObjManager = ObjectManager::GetIns;

}


#endif