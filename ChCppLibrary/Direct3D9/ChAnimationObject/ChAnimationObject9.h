
#ifndef Ch_D3D9_AnCon_h
#define Ch_D3D9_AnCon_h

class ChAnimationSupporter9;

typedef class ChAnimationObject9
{
private:

	struct AniObject
	{
		AniObject()
		{
			sca = 1.0f;
		}

		void Lerp(const AniObject _sAni, const AniObject _eAni, const float nowTime)
		{
			pos.Lerp(_sAni.pos, _eAni.pos, nowTime);

			sca.Lerp(_sAni.sca, _eAni.sca, nowTime);

			rot.Lerp(_sAni.rot, _eAni.rot, nowTime);

		}

		ChVec3_9 pos;
		ChVec3_9 sca;
		ChQua_9 rot;
#ifdef CRT
		std::function<void()>frameFunc = nullptr;
#endif
	};

public:

	virtual ~ChAnimationObject9()
	{
		Release();
	}

public://Init And Release//

	inline virtual void Release()
	{
		ClearAnimation();
	}

public://Set Functions//

#ifdef CRT
	inline void SetAnimationFunction(
		const std::function<void()>& _func,
		const size_t _aniFrameNum)
	{
		if (_aniFrameNum > GetAniCnt()) {

			//ChSystem::ErrerMessage("関数がセットできませんでした", "警告");

			aniList[_aniFrameNum]->frameFunc = _func;

			return;
		}
	}

#endif

	//現在の行列からアニメーションへ移行する//
	void SetStartMat(const ChMat_9& _startMat)
	{
		tmpStartMat = (ChMat_9*)&_startMat;
	}

	void SetOneFrameTime(const float _fps)
	{
		oneFrameTime = 1.0f / _fps;
	}

	void SetAniObject(
		const ChVec3_9& _pos,
		const ChVec3_9& _sca,
		const ChQua_9& _rot);

	void SetAniObject(const ChMat_9& _mat);

public://Get Functions//

	unsigned long GetAniCnt();

	//現在の初期行列//
	ChMat_9 GetNowStartMat()
	{
		ChMat_9 tmpAni;
		if (nowFrame >= GetAniCnt())tmpAni;
		auto ani = GetAnimation(nowFrame);
		tmpAni.Scaling(ani.sca);
		tmpAni *= ani.rot;
		tmpAni = ani.pos;
		return tmpAni;
	}

	//最初期行列//
	ChMat_9 GetFirstMat()
	{
		ChMat_9 tmpAni;
		if (nowFrame >= GetAniCnt())tmpAni;
		auto ani = GetAnimation(0);
		tmpAni.Scaling(ani.sca);
		tmpAni *= ani.rot;
		tmpAni = ani.pos;
		return tmpAni;
	}

protected:

	AniObject GetAnimation(unsigned long _num);

public://Update Functions//

	ChMat_9 Update();

	void Play(const size_t _startFrame = -1)
	{
		if (GetAniCnt() < 2)return;

		if (nowFrame + 1 >= GetAniCnt())
		{
			nowFrame = 0;
			if (_startFrame >= 0&& _startFrame + 1 < GetAniCnt())nowFrame = _startFrame;
		}

		nowTime = 0.0f;
		aniPlayFlg = true;
	}

	void Pause()
	{
		aniPlayFlg = false;
	}

	void Stop()
	{
		aniPlayFlg = false;
		nowTime = 0.0f;
		nowFrame = 0;
	}

	void RunFunction(AniObject& _aniObj);

	void ClearAnimation();

	friend ChAnimationSupporter9;

private:

	enum class Flg
	{
		UseFunc, AniPlay
	};

	ChCpp::BitBool flgs;

	ChMat_9* tmpStartMat;


	ChMat_9 lastPlayMat;

	bool funcFlg = false;
	//1フレーム間の進む時間//
	float oneFrameTime = 1.0f / 60.0f;

	bool aniPlayFlg = true;

	float nowTime = 0.0f;
	size_t nowFrame = 0;
#ifdef CRT
	std::vector<ChPtr::Shared<AniObject>> aniList;

	std::map<std::string, std::function<std::string(const std::string& _FileName)>>openFuncList;
#endif

}ChAniObj9;

class ChAnimationSupporter9
{
public:

#ifdef CRT
	inline std::map<std::string, ChPtr::Shared<ChAnimationObject9>>
		CreateKeyFrame(const std::string& _fileName)
	{
		if (!cFlg)
		{
			CreateFunction();
			cFlg = true;
		}

		std::string tmpType = _fileName;
		size_t tmp = tmpType.rfind(".");

		tmpType = tmpType.substr(tmp);

		return (creaters[tmpType](_fileName));

	}
#endif

private:

	static const char animationCheck[];

	static const char animation[];

	static const char aniKey[];

	bool cFlg = false;

#ifdef CRT
	std::vector<ChPtr::Shared<ChQua_9>>Create4D
	(const std::string& _str, size_t& _fPos ,const bool _rFlg);

	std::vector<ChPtr::Shared<ChVec3_9>> Create3D
	(const std::string& _str, size_t& _fPos, const bool _rFlg);


	std::map<std::string, std::function
		<std::map<std::string, ChPtr::Shared<ChAnimationObject9>>(const std::string&)>>creaters;
#endif

private:

	void CreateFunction();

	ChAnimationSupporter9() {}

public:

	static ChAnimationSupporter9& GetIns()
	{
		static ChAnimationSupporter9 ins;
		return ins;
	}

};

inline ChAnimationSupporter9& ChANiSupport() { return ChAnimationSupporter9::GetIns(); }

#ifdef CRT

void ChAniObj9::SetAniObject(
	const ChVec3_9& _pos,
	const ChVec3_9& _sca,
	const ChQua_9& _rot)
{
	auto ani = ChPtr::Make_S<AniObject>();

	ani->pos = _pos;
	ani->sca = _sca;
	ani->rot = _rot;

	aniList.push_back(ani);
}

void ChAniObj9::SetAniObject(const ChMat_9& _Mat)
{
	auto tmpMat = _Mat;

	auto ani = ChPtr::Make_S<AniObject>();

	ani->pos = tmpMat;

	ani->rot = tmpMat;

	ani->sca = tmpMat.GetScaleSize();

	aniList.push_back(ani);
}

unsigned long ChAnimationObject9::GetAniCnt() { return aniList.size(); }

ChAnimationObject9::AniObject ChAnimationObject9::GetAnimation(unsigned long _num)
{
	if (aniList.size() <= _num)return AniObject();
	return *aniList[_num];
}

void ChAnimationSupporter9::CreateFunction()
{
	if (cFlg)return;

	creaters[".x"] =
		[this](const std::string& _FileName)
		{
			std::string Datas;
			{
				ChCpp::CharFile file;
				file.FileOpen(_FileName);
				Datas = file.FileReadText();
				file.FileClose();
			}

			std::map<std::string, ChPtr::Shared<ChAnimationObject9>>animations;

			if (Datas.find(animationCheck) == std::string::npos)return std::move(animations);

			size_t fPos = 0;
			std::vector<ChPtr::Shared<ChVec3_9>>posList;
			std::vector<ChPtr::Shared<ChVec3_9>>sclList;
			std::vector<ChPtr::Shared<ChQua_9>>rotList;

			while ((fPos = Datas.find(animation, fPos)) != std::string::npos)
			{
				if (Datas.find(aniKey, fPos) == std::string::npos)break;


				fPos += std::strlen(animation);
				std::string BoneName;

				BoneName = Datas.substr(Datas.find("{", fPos) + 1, Datas.find("}", fPos) - Datas.find("{", fPos) - 1);

				{
					ChCpp::BitBool BreakFlg;

					while (1)
					{
						size_t tmpPos = Datas.find(aniKey, fPos);
						if (tmpPos == std::string::npos)break;
						tmpPos += std::strlen(aniKey);

						fPos = Datas.find(";", tmpPos);
						std::string Test;
						Test = Datas.substr(fPos - 2, 2);
						int tmp = std::atoi(Datas.substr(fPos - 2, 2).c_str());

						switch (tmp)
						{
						case 0:

							rotList = (Create4D(Datas, fPos, false));
							for (auto&& qua : rotList)
							{
								qua->w *= -1.0f;
							}
							BreakFlg.SetBitTrue(0);
							break;
						case 1:

							sclList = (Create3D(Datas, fPos, false));
							BreakFlg.SetBitTrue(1);
							break;
						case 2:

							posList = (Create3D(Datas, fPos, false));
							BreakFlg.SetBitTrue(2);

							break;
						default:
							break;
						}

						if (BreakFlg.GetBitFlg(0)
							&& BreakFlg.GetBitFlg(1)
							&& BreakFlg.GetBitFlg(2))break;

					}
				}

				size_t min = rotList.size(), max = rotList.size();

				if (max < sclList.size())max = sclList.size();
				if (max < posList.size())max = posList.size();


				if (min > sclList.size())min = sclList.size();
				if (min < posList.size())min = posList.size();

				for (size_t Cnt = 0; Cnt < max - min; Cnt++)
				{
					if (rotList.size() < max)
					{
						auto rot = ChPtr::Make_S<ChQua_9>();
						if (rotList.size() > 0)
						{
							*rot = *rotList[rotList.size() - 1];

						}
						rotList.push_back(rot);
					}
					if (sclList.size() < max)
					{
						auto scl = ChPtr::Make_S<ChVec3_9>();
						if (sclList.size() > 0)
						{
							*scl = *sclList[sclList.size() - 1];
						}
						sclList.push_back(scl);
					}
					if (posList.size() < max)
					{
						auto pos = ChPtr::Make_S<ChVec3_9>();
						if (posList.size() > 0)
						{
							*pos = *posList[posList.size() - 1];
						}
						*pos = *posList[posList.size() - 1];
						posList.push_back(pos);
					}
				}

				auto ani = ChPtr::Make_S<ChAnimationObject9>();

				for (size_t Cnt = 0; Cnt < max; Cnt++)
				{
					ani->SetAniObject
					(
						*posList[Cnt]
						, *sclList[Cnt]
						, *rotList[Cnt]
					);

				}

				animations[BoneName] = ani;

			}

			return (animations);
			//SizeTest//
		};

	cFlg = true;
}

std::vector<ChPtr::Shared<ChQua_9>>
ChAnimationSupporter9::Create4D(const std::string& _Str, size_t& _fPos, const bool _rFlg)
{

	std::vector<ChPtr::Shared<ChQua_9>> tmpQua;
	std::string cutStart = ";4;";
	std::string cutEnd = ";;";
	std::string end = ";;;";

	size_t tmpFPos = 0;
	while (_Str.find(end, _fPos - 1) >= _fPos)
	{
		if ((tmpFPos = _Str.find(cutStart, _fPos)) >= _Str.find(end, _fPos))break;
		_fPos = tmpFPos;
		_fPos += cutStart.length();

		auto qua = ChPtr::Make_S<ChQua_9>();

		{
			ChQua tmpQua;
			tmpQua.Deserialize(_Str, _fPos);

			*qua = tmpQua;
		}

		if (_rFlg)*qua *= -1.0f;
		_fPos = _Str.find(cutEnd, _fPos);

		tmpQua.push_back(qua);
	}

	_fPos = _Str.find(end, _fPos);

	return tmpQua;
}

std::vector<ChPtr::Shared<ChVec3_9>>
ChAnimationSupporter9::Create3D(const std::string& _Str, size_t& _fPos, const bool _rFlg)
{
	std::vector<ChPtr::Shared<ChVec3_9>> tmpVec;
	std::string CutStart = ";3;";
	std::string CutEnd = ";;";
	std::string End = ";;;";

	size_t tmpFPos = 0;
	while (_Str.find(End, _fPos - 1) >= _fPos)
	{

		if ((tmpFPos = _Str.find(CutStart, _fPos)) >= _Str.find(End, _fPos))break;
		_fPos = tmpFPos;
		_fPos += CutStart.length();

		auto Vec = ChPtr::Make_S<ChVec3_9>();

		{
			ChVec3 tmpVec;
			tmpVec.Deserialize(_Str, _fPos);
			*Vec = tmpVec;
		}

		if (_rFlg)*Vec *= -1.0f;
		tmpVec.push_back(Vec);
		_fPos = _Str.find(CutEnd, _fPos);
	}

	return tmpVec;
}

void ChAnimationObject9::RunFunction(AniObject& _aniObj)
{
	if (funcFlg)return;
	if (_aniObj.frameFunc == nullptr)return;

	_aniObj.frameFunc();

	funcFlg = true;
}

void ChAnimationObject9::ClearAnimation()
{
	aniList.clear();
}

#endif

#endif
