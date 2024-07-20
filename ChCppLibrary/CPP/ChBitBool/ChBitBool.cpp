#include"ChBitBool.h"

using namespace ChCpp;

///////////////////////////////////////////////////////////////////////////////////////
//ChBitBoolƒƒ\ƒbƒh
///////////////////////////////////////////////////////////////////////////////////////

void BitBool::SetBitFlg(const unsigned char _argsNum, const bool _flg)
{
	if (_argsNum >= GetSize())return;

	_flg ? SetBitTrue(_argsNum) : SetBitFalse(_argsNum);
}

void BitBool::SetBitTrue(const unsigned char _argsNum)
{
	if (_argsNum >= GetSize())return;

	unsigned char mask = BitBool::GetMask(_argsNum);
	mask &= 0xff;
	
	GetFlgs(_argsNum / 8) |= mask;

}

void BitBool::SetBitFalse(const unsigned char _argsNum)
{
	if (_argsNum >= GetSize())return;

	unsigned char mask = BitBool::GetMask(_argsNum);
	static unsigned char byteCount = 0;
	byteCount = _argsNum / 8;
	mask &= GetFlgs(byteCount);

	GetFlgs(byteCount) -= mask;
}

void BitBool::SetValue(const unsigned char _value, const unsigned long _byteCount)
{
	if (_byteCount >= GetSize())return;

	GetFlgs(_byteCount) = _value;
}

bool BitBool::GetBitFlg(const unsigned char _argsNum)
{
	if (_argsNum >= GetSize())return false;

	return GetFlgs(_argsNum / 8) & GetMask(_argsNum);
}

unsigned char BitBool::GetMask(const unsigned char _argsNum)
{
	return 1 << (_argsNum % 8);
}