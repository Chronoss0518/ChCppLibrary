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

		//�������̓A�h���X���̈�ԏ������r�b�g���琔�������l�����//
		//��)�A�h���X�ʒu��1000��,�I���ӏ�1001�Ԃ̏ꍇ��1��I��//
		void SetBitFlg(const unsigned char _argsNum, const bool _flg);

		//�����őI�����ꂽ�ʒu�̃r�b�g��true���Z�b�g����//
		//�������̓A�h���X���̈�ԏ������r�b�g���琔�������l�����//
		//��)�A�h���X�ʒu��1000��,�I���ӏ�1001�Ԃ̏ꍇ��1��I��//
		void SetBitTrue(const unsigned char _argsNum);

		//�����őI�����ꂽ�ʒu�̃r�b�g��false���Z�b�g����//
		//�������̓A�h���X���̈�ԏ������r�b�g���琔�������l�����//
		//��)�A�h���X�ʒu��1000��,�I���ӏ�1001�Ԃ̏ꍇ��1��I��//
		void SetBitFalse(const unsigned char _argsNum);

		//�����őI�����ꂽ�ʒu��Byte���Z�b�g����//
		//�������̓Z�b�g����l//
		//�������̓A�h���X���̈�ԏ������r�b�g���琔�������l�����//
		void SetValue(const unsigned char _value, const unsigned char _byteCount = 0);

		void SetAllDownFlg();

		//1�o�C�g���ƂŃt���O����ύX����//
		//(1�ȉ��ɂ͂Ȃ�Ȃ�)//
		void SetSize(const unsigned char _byteCount);

	public://Get Functions//

		//�����őI�����ꂽ���l�̃r�b�g�̒l�ɂ����//
		//ChStd::True��ChStd::False��Ԃ�//
		bool GetBitFlg(const unsigned char _argsNum);

		//�g�p�\�T�C�Y//
		unsigned long  GetSize();

		unsigned char GetValue(const unsigned char _byteCount = 0);

		//�t���O���̎w��ł�True�̌��擾//
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

	};

}

#ifdef CRT
ChCpp::BitBool::BitBool()
{
	CRTInit();
	value->flgs.resize(1);
}

ChCpp::BitBool::BitBool(const unsigned char _size)
{
	CRTInit();
	SetSize(_size);
}

ChCpp::BitBool::~BitBool()
{
	value->flgs.clear();
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
	for (auto&& flg : value->flgs)
	{
		flg = 0;
	}
}

void ChCpp::BitBool::SetSize(const unsigned char _byteCount)
{
	if (_byteCount <= 0)return;
	value->flgs.resize(_byteCount);
}

unsigned long  ChCpp::BitBool::GetSize()
{
	return static_cast<unsigned long>(value->flgs.size() * 8);
}

unsigned char& ChCpp::BitBool::GetFlgs(const unsigned char _argsNum)
{
	return value->flgs[_argsNum];
}

unsigned char ChCpp::BitBool::GetValue(const unsigned char _num)
{
	if (value->flgs.size() < _num)return 0;
	return value->flgs[_num];
}

#endif

#endif