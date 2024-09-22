#include"ChBitBool.h"

using namespace ChCpp;

///////////////////////////////////////////////////////////////////////////////////////
//ChBitBoolÉÅÉ\ÉbÉh
///////////////////////////////////////////////////////////////////////////////////////

void ChCpp::BitBool::SetAllDownFlg()
{
	for (size_t i = 0; i < flgs.GetSize(); i++)
	{
		flgs[i] = 0;
	}
}

void ChCpp::BitBool::SetSize(const unsigned char _byteCount)
{
	if (_byteCount <= 0)return;
	flgs.Resize(_byteCount);
}

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

void BitBool::SetValue(const unsigned char _value, const unsigned char _byteCount)
{
	if (_byteCount >= GetSize())return;

	GetFlgs(_byteCount) = _value;
}

unsigned long  ChCpp::BitBool::GetSize()
{
	return static_cast<unsigned long>(flgs.GetSize() * 8);
}

unsigned char& ChCpp::BitBool::GetFlgs(const unsigned char _argsNum)
{
	return flgs[_argsNum];
}

unsigned char ChCpp::BitBool::GetValue(const unsigned char _num)
{
	if (flgs.GetSize() < _num)return 0;
	return flgs[_num];
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