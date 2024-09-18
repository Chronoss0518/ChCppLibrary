
#ifndef Ch_CPP_CP_Init_h
#define Ch_CPP_CP_Init_h

namespace ChCp
{
	//�p�����ė��p����//
	//���������������Ă��邩�m�F�ł���悤�ɂȂ�//
	//������������Ƃ���SetInitFlg(true);��//
	//�������Ƃ��ɂ�SetInitFlg(false);���ĂԎ�//
	class Initializer
	{
	public://Operator Functions//

		inline explicit operator bool()const { return initFlg; }

		inline bool IsInit()const { return initFlg; }

	protected://Set Functions//

		//������(Initialize)����ۂɌĂԂ��Ƃ�K�{�Ƃ���֐�//
		//Initialize�����Ƃ������������ɍs�����Ƃ��Ȃ����ߕK�v�Ƃ��Ă���//
		inline void SetInitFlg(const bool _flg) { initFlg = _flg; }

	protected://Constructor Destructor//
		
		Initializer() {}

	private://Member Value//

		bool initFlg = false;

	};



}
#endif
