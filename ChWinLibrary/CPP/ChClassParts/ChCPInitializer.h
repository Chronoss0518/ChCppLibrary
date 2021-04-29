
#ifndef Ch_CPP_CP_Init_h
#define Ch_CPP_CP_Init_h

namespace ChCpp
{
	namespace ChCp
	{
		//継承して利用する//
		//初期化が完了しているか確認できるようになる//
		//初期化をするときにSetInitFlg(true);を//
		//解放するときにはSetInitFlg(false);を呼ぶ事//
		class Initializer
		{
		protected:

			///////////////////////////////////////////////////////////////////////////////////

			//初期化(Initialize)する際に呼ぶことを必須とする関数//
			//Initializeしたという判定を勝手に行うことがないため必要としている//
			inline void SetInitFlg(const ChStd::Bool _Flg) { InitFlg = _Flg; }

			///////////////////////////////////////////////////////////////////////////////////

		public:

			///////////////////////////////////////////////////////////////////////////////////

			inline explicit operator bool()const { return InitFlg; }

			///////////////////////////////////////////////////////////////////////////////////

			inline ChStd::Bool IsInit() { return InitFlg; }

			///////////////////////////////////////////////////////////////////////////////////

		protected:


			///////////////////////////////////////////////////////////////////////////////////
			//ConstructorDestructor//
			Initializer(){}


		private:

			ChStd::Bool InitFlg = false;

		};
		


	}
}

#endif
