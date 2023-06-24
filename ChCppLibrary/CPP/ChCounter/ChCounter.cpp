#include"../../BaseIncluder/ChBase.h"
#include"ChCounter.h"

using namespace ChCpp;

//Šm”F‚µ‚½‚¢’l‚ð“ü‚ê‚é//
long Counter::Update(const std::function<bool()>& _addMethod, const std::function<bool()>& _subMethod)
{
	count = (_addMethod && _addMethod()) ? count + 1 : (_subMethod && _subMethod()) ? count - 1 : count;
	return count;
}