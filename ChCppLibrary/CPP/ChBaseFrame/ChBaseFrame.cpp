
#include"../../BaseIncluder/ChBase.h"

#include"ChBaseFrame.h"


using namespace ChCpp;

///////////////////////////////////////////////////////////////////////////////////////
//BaseFrame9ƒƒ\ƒbƒh
///////////////////////////////////////////////////////////////////////////////////////

void ChCpp::FrameList::Release()
{
	saveData = ChCRT::NullPtr();
	sendData = ChCRT::NullPtr();

	nextFrame = ChCRT::NullPtr();
	GetNowFrame() = ChCRT::NullPtr();
}

void ChCpp::FrameList::Update()
{
	auto&& nowframe = GetNowFrame();
	if (nowframe == ChCRT::NullPtr())return;
	nowframe->Update();

	Changes();
}

void ChCpp::FrameList::ChangeFrame(const unsigned long _frameNo)
{
	if (frameList.GetSize() <= _frameNo)return;
	nextFrame = frameList[_frameNo]->CreateMethod();
	nextFrameNo = _frameNo;
	nextFrame->SetManager(this);
}

void ChCpp::FrameList::Changes()
{
	if (nextFrame == ChCRT::NullPtr())return;

	auto&& nowframe = GetNowFrame();
	if (nowframe != ChCRT::NullPtr())
	{
		nowframe->Release();
	}

	nowFrameNo = nextFrameNo;
	nowframe = nextFrame;

	nowframe->Init(sendData.Get());
	sendData = ChCRT::NullPtr();

	nextFrame = ChCRT::NullPtr();
	nextFrameNo = -1;
}