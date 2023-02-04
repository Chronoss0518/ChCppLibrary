
#include"../../BaseIncluder/ChBase.h"

#include"ChBitBool.h"

using namespace ChCpp;

///////////////////////////////////////////////////////////////////////////////////////
//ChBitBoolƒƒ\ƒbƒh
///////////////////////////////////////////////////////////////////////////////////////

void BitBool::SetBitFlg(const unsigned char _argsNum, const ChStd::Bool _flg)
{
	if (_argsNum >= flgs.size() * 8)return;

	_flg ? SetBitTrue(_argsNum) : SetBitFalse(_argsNum);
}

///////////////////////////////////////////////////////////////////////////////////////

void BitBool::SetBitTrue(const unsigned char _argsNum)
{
	if (_argsNum >= flgs.size() * 8)return;

	unsigned char mask = BitBool::GetMask(_argsNum % 8);
	mask &= 0xff;
	
	flgs[_argsNum / 8] |= mask;

}

///////////////////////////////////////////////////////////////////////////////////////

void BitBool::SetBitFalse(const unsigned char _argsNum)
{
	if (_argsNum >= flgs.size() * 8)return;

	unsigned char mask = BitBool::GetMask(_argsNum % 8);
	mask &= flgs[_argsNum / 8];

	flgs[_argsNum / 8] |= mask;
}

///////////////////////////////////////////////////////////////////////////////////////

void BitBool::SetValue(const unsigned char _value, const unsigned long _byteCount)
{
	if (_byteCount >= flgs.size())return;

	flgs[_byteCount] = _value;
}

///////////////////////////////////////////////////////////////////////////////////////

ChStd::Bool BitBool::GetBitFlg(const unsigned char _argsNum)
{
	if (_argsNum >= flgs.size() * 8)return false;

	return flgs[static_cast<size_t>(_argsNum / 8)] & GetMask(_argsNum);
}

unsigned char BitBool::GetMask(const unsigned char _argsNum)
{
	return 1 << (_argsNum % 8);
}