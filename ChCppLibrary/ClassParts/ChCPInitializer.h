
#ifndef Ch_CPP_CP_Init_h
#define Ch_CPP_CP_Init_h

namespace ChCp
{
	//継承して利用する//
	//初期化が完了しているか確認できるようになる//
	//初期化をするときにSetInitFlg(true);を//
	//解放するときにはSetInitFlg(false);を呼ぶ事//
	class Initializer
	{
	public://Operator Functions//

		inline explicit operator bool()const { return initFlg; }

		inline bool IsInit()const { return initFlg; }

	protected://Set Functions//

		//初期化(Initialize)する際に呼ぶことを必須とする関数//
		//Initializeしたという判定を勝手に行うことがないため必要としている//
		inline void SetInitFlg(const bool _flg) { initFlg = _flg; }

	protected://Constructor Destructor//
		
		Initializer() {}

	private://Member Value//

		bool initFlg = false;

	};



}
#endif
