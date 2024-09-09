#ifndef Ch_CPP_BiBo_h
#define Ch_CPP_BiBo_h

namespace ChCpp
{

	class BitBool
	{
	public://Constructor Destructor//

		BitBool();

		BitBool(const unsigned char _size);

		virtual ~BitBool();


	private://Init And Release//

		void CRTInit();

		void CRTRelease();

	public://Set Functions//

		//第一引数はアドレス内の一番小さいビットから数えた数値を入力//
		//例)アドレス位置が1000番,選択箇所1001番の場合は1を選択//
		void SetBitFlg(const unsigned char _argsNum, const bool _flg);

		//引数で選択された位置のビットをtrueをセットする//
		//第一引数はアドレス内の一番小さいビットから数えた数値を入力//
		//例)アドレス位置が1000番,選択箇所1001番の場合は1を選択//
		void SetBitTrue(const unsigned char _argsNum);

		//引数で選択された位置のビットをfalseをセットする//
		//第一引数はアドレス内の一番小さいビットから数えた数値を入力//
		//例)アドレス位置が1000番,選択箇所1001番の場合は1を選択//
		void SetBitFalse(const unsigned char _argsNum);

		//引数で選択された位置のByteをセットする//
		//第一引数はセットする値//
		//第二引数はアドレス内の一番小さいビットから数えた数値を入力//
		void SetValue(const unsigned char _value, const unsigned char _byteCount = 0);

		void SetAllDownFlg();

		//1バイトごとでフラグ数を変更する//
		//(1以下にはならない)//
		void SetSize(const unsigned char _byteCount);

	public://Get Functions//

		//引数で選択された数値のビットの値によって//
		//ChStd::TrueかChStd::Falseを返す//
		bool GetBitFlg(const unsigned char _argsNum);

		//使用可能サイズ//
		unsigned long  GetSize();

		unsigned char GetValue(const unsigned char _byteCount = 0);

		//フラグ数の指定でのTrueの個数取得//
		inline unsigned long GetTrueCnt(const unsigned long& _cnt)
		{
			unsigned char cnt = 0;

			for (unsigned char i = 0; i < _cnt; i++)
			{
				if (!GetBitFlg(i))continue;
				cnt++;
			}

			return cnt;
		}

		inline unsigned long GetTrueCnt()
		{
			return GetTrueCnt(GetSize());
		}

	protected://get Functions//

		unsigned char GetMask(const unsigned char _argsNum);

		unsigned char& GetFlgs(const unsigned char _argsNum);

	private:

		struct BitBoolCRT
		{
#ifdef CRT
			std::vector<unsigned char> flgs = { 0 };
#endif
		};

		BitBoolCRT* value = nullptr;

	protected://Member Value//

		BitBoolCRT& ValueIns() { return *value; }
	};

}

#ifdef CRT
ChCpp::BitBool::BitBool()
{
	flgs.resize(1);
	CRTInit();
}

ChCpp::BitBool::BitBool(const unsigned char _size)
{
	SetSize(_size);
	CRTInit();
}

ChCpp::BitBool::~BitBool()
{
	flgs.clear();
	CRTRelease();
}

void ChCpp::BitBool::CRTInit()
{
	value = new BitBoolCRT();
}

void ChCpp::BitBool::CRTRelease()
{
	delete value;
}

void ChCpp::BitBool::SetAllDownFlg()
{
	for (auto&& flg : ValueIns().flgs)
	{
		flg = 0;
	}
}

void ChCpp::BitBool::SetSize(const unsigned char _byteCount)
{
	if (_byteCount <= 0)return;
	ValueIns().flgs.resize(_byteCount);
}

unsigned long  ChCpp::BitBool::GetSize()
{
	return static_cast<unsigned long>(ValueIns().flgs.size() * 8);
}

unsigned char& ChCpp::BitBool::GetFlgs(const unsigned char _argsNum)
{
	return ValueIns().flgs[_argsNum];
}

unsigned char ChCpp::BitBool::GetValue(const unsigned char _num)
{
	if (ValueIns().flgs.size() < _num)return 0;
	return ValueIns().flgs[_num];
}

#endif

#endif