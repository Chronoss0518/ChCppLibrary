#ifndef Ch_CPP_TexObj_h
#define Ch_CPP_TexObj_h

#include<vector>
#include<string>

#include"../../BasePack/ChStd.h"

namespace ChCpp
{
	template<typename CharaType>
	class TextObject
	{
	public:

		std::basic_string<CharaType> operator[](unsigned long _index)const
		{
			if (textLines.size() <= _index)return ChStd::GetZeroChara<CharaType>();
			return textLines[_index];
		}

	public://GetFunction//

		//Text全体を読み取る//
		std::basic_string<CharaType> GetText()const;

		//Textから一行読み取る//
		std::basic_string<CharaType> GetTextLine(const size_t _index = 0)const;

		//指定した文字数分から文字列を取得//
		std::basic_string<CharaType> GetSubStr(
			const unsigned int _startPos = 0,
			const unsigned int _endPos = std::basic_string<CharaType>::npos)const
		{
			return GetText().substr(_startPos, _endPos);
		}

		//指定した文字数分から文字列を取得//
		TextObject<CharaType> GetSubStrToFileObject(
			const unsigned int _startPos = 0,
			const unsigned int _endPos = std::basic_string<CharaType>::npos)const
		{
			TextObject<CharaType> res;
			std::basic_string<CharaType> str = GetText().substr(_startPos, _endPos);

			res.SetText(str);
			return res;
		}

		//Textの中に指定した文字列を先頭より探し//
		//初めに見つけた行の要素数を取得//
		size_t GetFindLine(
			const std::basic_string<CharaType>& _findStr,
			const size_t _startPos = 0)const;

		//Textの中に指定した文字列を先頭より探し//
		//初めに見つけた位置を取得//
		inline size_t GetFind(
			const std::basic_string<CharaType>& _findStr,
			const size_t _startPos = 0)const
		{
			return GetText().find(_findStr, _startPos);
		}

	public://SetFunction//

		//分割する文字を指定する//
		void SetCutChar(const std::basic_string<CharaType>& _cutChar);

		//Text全体を書き込む//
		void SetText(const std::basic_string<CharaType>& _str);

		//Textに一行書き込む//
		void SetTextLine(
			const std::basic_string<CharaType>& _str,
			const unsigned int _setIndex = 0);

	public://Other Functions//
	
		size_t Length()const { return GetText().length(); }

		size_t Count()const { return GetText().length(); }

		size_t LineCount()const { return textLines.size(); }

		typename std::vector<std::basic_string<CharaType>>::iterator begin() { return textLines.begin(); }

		typename std::vector<std::basic_string<CharaType>>::iterator end() { return textLines.end(); }

	private:

		std::basic_string<CharaType> cutChar = ChStd::GetCRLFChara<CharaType>();
		std::vector<std::basic_string<CharaType>> textLines;
	};
}

#endif