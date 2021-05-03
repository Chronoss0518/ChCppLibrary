#ifndef Ch_CPP_Cmp_Base_h
#define Ch_CPP_Cmp_Base_h

namespace ChCpp
{
	namespace Cmp
	{
		 class BaseCompressor
		{
		public:

			///////////////////////////////////////////////////////////////////////////////////
			
			//à≥èkä÷êî//
			virtual std::string Press(const std::string& _pressBase) = 0;

			///////////////////////////////////////////////////////////////////////////////////

			//âìÄä÷êî//
			virtual std::string Thaw(const std::string& _thawBase) = 0;

			///////////////////////////////////////////////////////////////////////////////////

		};

		 using BaseComp = BaseCompressor;

		 class Compressor :public ClassPerts::Initializer, public ClassPerts::Releaser
		{
		public:

			///////////////////////////////////////////////////////////////////////////////////
			//InitAndRelease//

			template<class T>
			inline auto Init()
				->typename std::enable_if<std::is_base_of<BaseCompressor, T>::value, void>::type
			{
				if (*this)return;

				compressor.Makes<T>();

				SetInitFlg(true);
			}

			template<class T>
			inline auto Init()
				->typename std::enable_if<!std::is_base_of<BaseCompressor, T>::value, void>::type
			{
				return;
			}

			inline void Release()override
			{

				compressor = nullptr;

				SetInitFlg(false);
			}

			///////////////////////////////////////////////////////////////////////////////////
			//SetFunction//

			template<class T>
			inline auto SetCompressor()
				->typename std::enable_if<std::is_base_of<BaseCompressor,T>::value,void>::type
			{
				if (!*this)return;
				Release();

				compressor = ChPtr::Make_S<T>();

				SetInitFlg(true);
			}

			template<class T>
			inline auto SetCompressor()
				->typename std::enable_if<!std::is_base_of<BaseCompressor, T>::value, void>::type
			{
				return;
			}

			///////////////////////////////////////////////////////////////////////////////////

			//à≥èkä÷êî//
			inline std::string Press(const std::string& _pressBase)
			{
				if (!*this)return "";
				if (!compressor)return "";
				if (_pressBase.size() <= 0)return "";

				return compressor->Press(_pressBase);

			}

			///////////////////////////////////////////////////////////////////////////////////

			//âìÄä÷êî//
			inline std::string Thaw(const std::string& _thawBase)
			{
				if (!*this)return "";
				if (!compressor)return "";
				if (_thawBase.size() <= 0)return "";

				return compressor->Thaw(_thawBase);

			}

		private:

			ChPtr::Shared<BaseComp>compressor = nullptr;
		};

	}
}

#endif
