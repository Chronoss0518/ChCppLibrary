#include"ChFile.h"

namespace ChStd
{
	CH_TO_NUMBER_FUNCTION(CH_ERROR_TEXT_TYPE_FUNCTION, ".txt");
}

template<typename CharaType>
unsigned long ChCpp::File<CharaType>::GetLength()
{
	unsigned long out = 0;

	if (!stream.is_open())return out;

	auto istream = dynamic_cast<std::basic_istream<CharaType>*>(&stream);
	istream->seekg(0, std::ios::end);

	out = static_cast<unsigned long>(istream->tellg());

	istream->seekg(0, std::ios::beg);

	return out;
}

template<typename CharaType>
bool ChCpp::File<CharaType>::IsOpenModeTest(bool _isReadFlg, bool _isBinaryFlg)
{

	if (!stream.is_open())return false;

	if (((flg & std::ios::in) > 0) == _isReadFlg)return false;
	if (((flg & std::ios::out) <= 0) != _isReadFlg)return false;

	if (((flg & std::ios::binary) > 0) != _isBinaryFlg)return false;

	if (!_isReadFlg)return true;

	if ((flg & std::ios::app))return true;

	stream.close();
	stream.open(openFileName.c_str(), std::ios::out | std::ios::trunc);

	stream.close();
	stream.open(openFileName.c_str(), flg);

	return true;
}
