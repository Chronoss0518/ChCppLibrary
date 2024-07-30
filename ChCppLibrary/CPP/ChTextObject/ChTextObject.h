#ifndef Ch_CPP_TexObj_h
#define Ch_CPP_TexObj_h

#ifdef CRT

#include<string>
#include<vector>
#include<iterator>

#endif

#include"../../BasePack/ChStd.h"

namespace ChCpp
{
	template<typename CharaType>
	class TextObject
	{
	public:

#ifdef CRT
		std::basic_string<CharaType> operator[](unsigned long _index)const
		{
			if (textLines.size() <= _index)return ChStd::GetZeroChara<CharaType>();
			return textLines[_index];
		}
#endif
	public://GetFunction//

#ifdef CRT
		//Text全体を読み取る//
		std::basic_string<CharaType> GetText()const;

		//Textから一行読み取る//
		std::basic_string<CharaType> GetTextLine(const unsigned long _index = 0)const;
#endif
	public://SetFunction//

		//分割する文字を指定する//
		void SetCutChar(const CharaType* _cutChar);

		//Text全体を書き込む//
		void SetText(const CharaType* _str);

		//Textに一行書き込む//
		void SetTextLine(
			const CharaType* _str,
			const unsigned int _setIndex = 0);

	public://Other Functions//
	
#ifdef CRT
		//指定した文字数分から文字列を取得//
		std::basic_string<CharaType> SubStr(
			const unsigned int _startPos = 0,
			const unsigned int _endPos = std::basic_string<CharaType>::npos)const
		{
			return GetText().substr(_startPos, _endPos);
		}

		//指定した文字数分から文字列を取得//
		TextObject<CharaType> SubStrToFileObject(
			const unsigned int _startPos = 0,
			const unsigned int _endPos = std::basic_string<CharaType>::npos)const
		{
			TextObject<CharaType> res;
			std::basic_string<CharaType> str = GetText().substr(_startPos, _endPos);

			res.SetText(str);
			return res;
		}
#endif

		unsigned long Length()const { return GetText().length(); }

		unsigned long Count()const { return GetText().length(); }

#ifdef CRT
		unsigned long LineCount()const { return textLines.size(); }

		typename std::vector<std::basic_string<CharaType>>::iterator begin() { return textLines.begin(); }

		typename std::vector<std::basic_string<CharaType>>::iterator end() { return textLines.end(); }

#endif

		//Textの中に指定した文字列を先頭より探し//
		//初めに見つけた行の要素数を取得//
		unsigned long FindLine(
			const CharaType* _findStr,
			const unsigned long _startPos = 0)const;

		//Textの中に指定した文字列を先頭より探し//
		//初めに見つけた位置を取得//
		unsigned long Find(
			const CharaType* _findStr,
			const unsigned long _startPos = 0)const
		{
			return GetText().find(_findStr, _startPos);
		}

	private:

#ifdef CRT
		std::basic_string<CharaType> cutChar = ChStd::GetCRLFChara<CharaType>();
		std::vector<std::basic_string<CharaType>> textLines;
#endif
	};
}

#ifdef CRT

template<typename CharaType>
std::basic_string<CharaType> ChCpp::TextObject<CharaType>::GetText()const
{
	if (textLines.empty())return ChStd::GetZeroChara<CharaType>();
	std::basic_string<CharaType> res = ChStd::GetZeroChara<CharaType>();

	for (auto&& text : textLines) { res += text + cutChar; }

	res.pop_back();
	return res;
}

template<typename CharaType>
std::basic_string<CharaType> ChCpp::TextObject<CharaType>::GetTextLine(const unsigned long _index)const
{
	unsigned long tmp = _index;
	if (tmp >= textLines.size())return ChStd::GetZeroChara<CharaType>();

	return textLines[tmp];
}

template<typename CharaType>
void ChCpp::TextObject<CharaType>::SetCutChar(const CharaType* _cutChar)
{
	if (cutChar == _cutChar)return;
	std::basic_string<CharaType> val = GetText();
	cutChar = _cutChar;
	SetText(val.c_str());
}

template<typename CharaType>
void ChCpp::TextObject<CharaType>::SetText(const CharaType* _str)
{
	std::basic_string<CharaType> testText = _str;
	textLines.clear();
	if (testText.find(cutChar) == std::basic_string<CharaType>::npos)
	{
		textLines.push_back(testText);
		return;
	}

	unsigned long tmpPos = 0;
	unsigned long testPos = 0;

	while (true)
	{
		testPos = testText.find(cutChar, tmpPos);

		if (testPos == testText.npos)break;

		textLines.push_back(testText.substr(tmpPos, testPos - tmpPos));
		tmpPos = testPos + 1;
	}
	textLines.push_back(testText.substr(tmpPos));
}

template<typename CharaType>
void ChCpp::TextObject<CharaType>::SetTextLine(
	const CharaType* _str,
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
unsigned long ChCpp::TextObject<CharaType>::FindLine(
	const CharaType* _findStr,
	const unsigned long _startPos)const
{
	std::basic_string<CharaType> str = GetText();

	unsigned long tmp = _startPos;
	unsigned long base = str.find(_findStr);

	if (base == str.npos)return 0;
	unsigned long count = 1;
	while (true)
	{
		tmp = str.find(cutChar, tmp);
		if (tmp >= base)return count;

		count++;
		tmp++;
	}
}

#endif

#endif