
#include"../../BaseIncluder/ChBase.h"
#include"ChTextObject.h"

using namespace ChCpp;

template<typename CharaType>
std::basic_string<CharaType> ChCpp::TextObject<CharaType>::GetText()const
{
	if (textLines.empty())return ChStd::GetZeroChara<CharaType>();
	std::basic_string<CharaType> res = ChStd::GetZeroChara<CharaType>();

	for (size_t i = 0; i < textLines.size(); i++)
	{
		res += textLines[i] + cutChar;
	}

	res.pop_back();
	return res;
}

template<typename CharaType>
std::basic_string<CharaType> ChCpp::TextObject<CharaType>::GetTextLine(const size_t _index)const
{
	size_t tmp = _index;
	if (tmp >= textLines.size())return ChStd::GetZeroChara<CharaType>();

	return textLines[tmp];
}

template<typename CharaType>
void ChCpp::TextObject<CharaType>::SetCutChar(const std::basic_string<CharaType>& _cutChar)
{
	if (cutChar == _cutChar)return;
	std::basic_string<CharaType> val = GetText();
	cutChar = _cutChar;
	SetText(val);
}

template<typename CharaType>
void ChCpp::TextObject<CharaType>::SetText(const std::basic_string<CharaType>& _str)
{
	std::basic_string<CharaType> testText = _str;
	textLines.clear();
	if (testText.find(cutChar) == std::basic_string<CharaType>::npos)
	{
		textLines.push_back(testText);
		return;
	}

	size_t tmpPos = 0;
	size_t testPos = 0;

	while (true)
	{
		testPos = testText.find(cutChar, tmpPos);

		if (testPos == std::basic_string<CharaType>::npos)break;

		textLines.push_back(testText.substr(tmpPos, testPos - tmpPos));
		tmpPos = testPos + 1;
	}
	textLines.push_back(testText.substr(tmpPos));
}

template<typename CharaType>
void ChCpp::TextObject<CharaType>::SetTextLine(
	const std::basic_string<CharaType>& _str,
	const unsigned int _setIndex)
{
	if (_setIndex > textLines.size())return;

	TextObject<CharaType> tmp;
	tmp.SetText(_str);

	if (_setIndex == textLines.size())
	{
		for (unsigned long i = 0; i < tmp.Count(); i++)
		{
			textLines.push_back(tmp.GetTextLine(i));
		}
		return;
	}

	for (unsigned long i = 0; i < tmp.Count(); i++)
	{
		textLines.insert(textLines.begin() + (textLines.size() - _setIndex - 1 + i), tmp.GetTextLine(i));
	}
}

template<typename CharaType>
size_t ChCpp::TextObject<CharaType>::GetFindLine(
	const std::basic_string<CharaType>& _findStr,
	const size_t _startPos)const
{
	std::basic_string<CharaType> str = GetText();

	size_t tmp = _startPos;
	size_t base = str.find(_findStr);

	if (base == std::basic_string<CharaType>::npos)return 0;
	size_t count = 1;
	while (true)
	{
		tmp = str.find(cutChar, tmp);
		if (tmp >= base)return count;

		count++;
		tmp++;
	}
}

CH_STRING_TYPE_EXPLICIT_DECLARATION(ChCpp::TextObject);