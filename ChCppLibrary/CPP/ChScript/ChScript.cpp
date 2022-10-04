
#include"../../BaseIncluder/ChBase.h"

#include"ChScript.h"

using namespace ChCpp;

///////////////////////////////////////////////////////////////////////////////////
//ChScriptControllerƒƒ\ƒbƒh
///////////////////////////////////////////////////////////////////////////////////

void ScriptController::Chenge()
{
	if (nextScript == nullptr)return;

	nowScript = nextScript;

	nowScript->Init(this);

	nextScript = nullptr;
}
