
#include"../../BaseIncluder/ChBase.h"

#include"ChBitBool.h"

using namespace ChCpp;

///////////////////////////////////////////////////////////////////////////////////////
//BitFlgObject 外部関数群
///////////////////////////////////////////////////////////////////////////////////////

void SetBitFlg0(BitBool::BitFlgObject& _this, const bool _flg) { _this.flg0 = _flg ? 1 : 0; }
void SetBitFlg1(BitBool::BitFlgObject& _this, const bool _flg) { _this.flg1 = _flg ? 1 : 0; }
void SetBitFlg2(BitBool::BitFlgObject& _this, const bool _flg) { _this.flg2 = _flg ? 1 : 0; }
void SetBitFlg3(BitBool::BitFlgObject& _this, const bool _flg) { _this.flg3 = _flg ? 1 : 0; }
void SetBitFlg4(BitBool::BitFlgObject& _this, const bool _flg) { _this.flg4 = _flg ? 1 : 0; }
void SetBitFlg5(BitBool::BitFlgObject& _this, const bool _flg) { _this.flg5 = _flg ? 1 : 0; }
void SetBitFlg6(BitBool::BitFlgObject& _this, const bool _flg) { _this.flg6 = _flg ? 1 : 0; }
void SetBitFlg7(BitBool::BitFlgObject& _this, const bool _flg) { _this.flg7 = _flg ? 1 : 0; }

///////////////////////////////////////////////////////////////////////////////////////

unsigned char GetBitFlg0(BitBool::BitFlgObject& _this) { return _this.flg0; }
unsigned char GetBitFlg1(BitBool::BitFlgObject& _this) { return _this.flg1; }
unsigned char GetBitFlg2(BitBool::BitFlgObject& _this) { return _this.flg2; }
unsigned char GetBitFlg3(BitBool::BitFlgObject& _this) { return _this.flg3; }
unsigned char GetBitFlg4(BitBool::BitFlgObject& _this) { return _this.flg4; }
unsigned char GetBitFlg5(BitBool::BitFlgObject& _this) { return _this.flg5; }
unsigned char GetBitFlg6(BitBool::BitFlgObject& _this) { return _this.flg6; }
unsigned char GetBitFlg7(BitBool::BitFlgObject& _this) { return _this.flg7; }

///////////////////////////////////////////////////////////////////////////////////////


void(*BitBool::setBitFlgFunc[])(BitBool::BitFlgObject&, const bool)
{
	&SetBitFlg0,
	&SetBitFlg1,
	&SetBitFlg2,
	&SetBitFlg3,
	&SetBitFlg4,
	&SetBitFlg5,
	&SetBitFlg6,
	&SetBitFlg7,
};

///////////////////////////////////////////////////////////////////////////////////////

unsigned char (*BitBool::getBitFlgFunc[])(BitBool::BitFlgObject&)
{
	& GetBitFlg0,
	& GetBitFlg1,
	& GetBitFlg2,
	& GetBitFlg3,
	& GetBitFlg4,
	& GetBitFlg5,
	& GetBitFlg6,
	& GetBitFlg7,
};

///////////////////////////////////////////////////////////////////////////////////////
//BitFlgObjectメソッド
///////////////////////////////////////////////////////////////////////////////////////

void BitBool::BitFlgObject::SetFlg(const unsigned long _num, const bool _flg)
{
	setBitFlgFunc[_num](*this,_flg);
}

///////////////////////////////////////////////////////////////////////////////////////

bool BitBool::BitFlgObject::GetFlg(const unsigned long _num)
{
	return getBitFlgFunc[_num](*this);
}

///////////////////////////////////////////////////////////////////////////////////////
//ChBitBoolメソッド
///////////////////////////////////////////////////////////////////////////////////////

void BitBool::SetBitFlg(const unsigned char _argsNum, const ChStd::Bool _flg)
{
	if (_argsNum >= flgs.size() * 8)return;

	flgs[_argsNum / 8].SetFlg(_argsNum, _flg);
}

///////////////////////////////////////////////////////////////////////////////////////

void BitBool::SetBitTrue(const unsigned char _argsNum)
{
	if (_argsNum >= flgs.size() * 8)return;

	flgs[_argsNum / 8].SetFlg(_argsNum ,true);

}

///////////////////////////////////////////////////////////////////////////////////////

void BitBool::SetBitFalse(const unsigned char _argsNum)
{
	if (_argsNum >= flgs.size() * 8)return;

	flgs[_argsNum / 8].SetFlg(_argsNum, false);
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

	return flgs[static_cast<size_t>(_argsNum / 8)].GetFlg(_argsNum % 8);
}
