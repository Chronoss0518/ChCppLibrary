#ifndef Ch_CPP_BiBo_h
#define Ch_CPP_BiBo_h

namespace ChCpp
{

	class BitBool
	{
	public:

		struct BitFlgObject
		{
			union
			{
				unsigned char value = 0;
				struct
				{
					unsigned char flg0 : 1;
					unsigned char flg1 : 1;
					unsigned char flg2 : 1;
					unsigned char flg3 : 1;
					unsigned char flg4 : 1;
					unsigned char flg5 : 1;
					unsigned char flg6 : 1;
					unsigned char flg7 : 1;
				};
			};

			BitFlgObject(){}
			BitFlgObject(const unsigned char _val) { value = _val; }
			~BitFlgObject(){}

			BitFlgObject& operator = (const unsigned char& _val) { value = _val; return *this; }

			operator unsigned char&() { return value; }
			operator unsigned char () const { return value; }


			void SetFlg(const unsigned long _num, const bool _flg);

			bool GetFlg(const unsigned long _num);

		};

	private:

		static void(*setBitFlgFunc[])(BitFlgObject&, const bool);

		static unsigned char (*getBitFlgFunc[])(BitFlgObject&);

	public:

		///////////////////////////////////////////////////////////////////////////////////
		//ConstructerDestructer//

		BitBool()
		{
			flgs.resize(1);
		}

		BitBool(const unsigned char _size)
		{
			SetSize(_size);
		}

		virtual ~BitBool()
		{
			flgs.clear();
		}

		///////////////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		//第一引数はアドレス内の一番小さいビットから数えた数値を入力//
		//例)アドレス位置が1000番,選択箇所1001番の場合は1を選択//
		void SetBitFlg(const unsigned char _argsNum, const ChStd::Bool _flg);

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
		void SetValue(const unsigned char _value, const unsigned long _byteCount = 0);

		inline void SetAllDownFlg()
		{
			for (auto&& flg : flgs)
			{
				flg = 0;
			}
		}

		//1バイトごとでフラグ数を変更する//
		//(1以下にはならない)//
		inline void SetSize(const unsigned char _byteCount)
		{
			if (_byteCount <= 0)return;
			flgs.resize(_byteCount);
		}

		//////////////////////////////////////////////////////////////////////////////////////
		//GetFunction//

		//引数で選択された数値のビットの値によって//
		//ChStd::TrueかChStd::Falseを返す//
		ChStd::Bool GetBitFlg(const unsigned char _argsNum);

		//使用可能サイズ//
		inline unsigned long  GetSize()
		{
			return static_cast<unsigned long>(flgs.size() * 8);
		}

		inline unsigned char GetValue(const unsigned char _byteCount = 0)
		{
			if (_byteCount >= flgs.size())return 0;
			return flgs[_byteCount];
		}

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
			return GetTrueCnt(flgs.size() * 8);
		}

	protected:

		std::vector<BitFlgObject> flgs = { 0 };

	};
}


#endif