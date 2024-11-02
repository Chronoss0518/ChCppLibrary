
#include"../../BaseIncluder/ChBase.h"

#include"ChBaseFrame.h"


using namespace ChCpp;

///////////////////////////////////////////////////////////////////////////////////////
//BaseFrame9ƒƒ\ƒbƒh
///////////////////////////////////////////////////////////////////////////////////////

void ChCpp::FrameList::Release()
{
	saveData = nullptr;
	sendData = nullptr;

	nextFrame = nullptr;
	GetNowFrame() = nullptr;
}

void ChCpp::FrameList::Update()
{
	auto&& nowframe = GetNowFrame();
	if (nowframe == nullptr)return;
	nowframe->Update();

	Changes();
}

void ChCpp::FrameList::ChangeFrame(const unsigned long _frameNo)
{
	if (frameList.size() <= _frameNo)return;
	nextFrame = frameList[_frameNo]->CreateMethod();
	nextFrameNo = _frameNo;
	nextFrame->SetManager(this);
}

void ChCpp::FrameList::Changes()
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


CH_STRING_TYPE_EXPLICIT_DECLARATION(ChCpp::FrameManager);