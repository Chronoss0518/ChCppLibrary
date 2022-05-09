
#include"../../BaseIncluder/ChBase.h"

#include"ChBaseFrame.h"


using namespace ChCpp;

///////////////////////////////////////////////////////////////////////////////////////
//BaseFrame9���\�b�h
///////////////////////////////////////////////////////////////////////////////////////

void BaseFrameManager::Update()
{
	if (nowFrame == nullptr)return;
	nowFrame->Update();

	Chenges();
}

///////////////////////////////////////////////////////////////////////////////////

void BaseFrameManager::ChengeFrame(const std::string& _frameName)
{
	if (frameList.find(_frameName) == frameList.end())return;

	nextFrame = frameList[_frameName]();


}

///////////////////////////////////////////////////////////////////////////////////

void BaseFrameManager::Chenges()
{

	if (nextFrame == nullptr)return;

	if (nowFrame != nullptr)
	{
		nowFrame->Release();
	}

	nowFrame = nextFrame;

	nowFrame->Init();

	nextFrame = nullptr;
}
