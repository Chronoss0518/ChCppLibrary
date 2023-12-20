
#include"../../BaseIncluder/ChBase.h"

#include"ChBaseFrame.h"


using namespace ChCpp;

///////////////////////////////////////////////////////////////////////////////////////
//BaseFrame9ƒƒ\ƒbƒh
///////////////////////////////////////////////////////////////////////////////////////

void FrameList::Update()
{

	auto&& nowframe = GetNowFrame();
	if (nowframe == nullptr)return;
	nowframe->Update();

	Changes();
}

void FrameList::ChangeFrame(const unsigned long _frameNo)
{
	if (frameList.size() <= _frameNo)return;

	nextFrame = frameList[_frameNo]();

	nextFrameNo = _frameNo;

	nextFrame->SetManager(this);
}

void FrameList::Changes()
{
	if (nextFrame == nullptr)return;

	auto&& nowframe = GetNowFrame();
	if (nowframe != nullptr)
	{
		nowframe->Release();
	}

	nowFrameNo = nextFrameNo;
	nowframe = nextFrame;

	nowframe->Init(sendData);
	sendData = nullptr;

	nextFrame = nullptr;
	nextFrameNo = -1;
}

void FrameManager::ChangeFrame(const std::string& _frameName)
{
	if (frameNames.find(_frameName) == frameNames.end())return;

	FrameList::ChangeFrame(frameNames[_frameName]);
}

std::string FrameManager::GetNowFrameName() 
{
	if (frameNames.empty())return "";

	if (frameNames.size() <= nowFrameNo)return "";

	for (auto&& name : frameNames)
	{
		if (name.second != nowFrameNo)continue;

		return name.first;
	}

	return "";
}
