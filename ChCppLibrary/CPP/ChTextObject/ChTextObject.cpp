
#include"../../BaseIncluder/ChBase.h"
#include"ChTextObject.h"

using namespace ChCpp;


///////////////////////////////////////////////////////////////////////////////////////
//FileObjectƒƒ\ƒbƒh//
///////////////////////////////////////////////////////////////////////////////////////

std::string TextObject::GetText()const
{
	if (textLines.empty())return "";

	std::string out = "";

	for (auto text : textLines)
	{
		out += text + cutChar;
	}

	out.pop_back();

	return out;

}

std::string TextObject::GetTextLine(const size_t _index)const
{
	size_t tmp = _index;
	if (tmp >= textLines.size())return "";

	return textLines[tmp];
}

void TextObject::SetCutChar(char _cutChar)
{
	if (cutChar == _cutChar)return;
	std::string val = GetText();
	cutChar = _cutChar;
	SetText(val);
}

void TextObject::SetText(const std::string _str)
{
	textLines.clear();
	if (_str.find(cutChar) == _str.npos)
	{
		textLines.push_back(_str);
		return;
	}

	size_t tmpPos = 0;
	size_t testPos = 0;

	while (true)
	{
		testPos = _str.find(cutChar, tmpPos);

		if (testPos == _str.npos)break;

		textLines.push_back(_str.substr(tmpPos, testPos - tmpPos));
		tmpPos = testPos + 1;
	}

	textLines.push_back(_str.substr(tmpPos));
}

void TextObject::SetTextLine(
	const std::string _str
	, const unsigned int _setIndex)
{
	if (_setIndex > textLines.size())return;

	TextObject tmp;
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

unsigned long TextObject::FindLine(
	const std::string& _findStr
	, const size_t _startPos)const
{

	std::string str = GetText();

	size_t tmp = _startPos;
	size_t base = str.find(_findStr);

	if (base == str.npos)return 0;
	unsigned long count = 1;
	while (1)
	{
		tmp = str.find(cutChar, tmp);

		if (tmp >= base)return count;

		count++;

		tmp++;

	}

}
