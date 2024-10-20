
#ifndef Ch_D3D9_AnCon_h
#define Ch_D3D9_AnCon_h

#include<functional>
#include<vector>
#include<map>
#include<string>

#include"../../BasePack/ChPtr.h"
#include"../../CPP/ChBitBool/ChBitBool.h"

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

		std::function<void()>frameFunc = nullptr;
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

	size_t GetAniCnt();

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

	AniObject GetAnimation(size_t _num);

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

	std::vector<ChPtr::Shared<AniObject>> aniList;

	std::map<std::string, std::function<std::string(const std::string& _FileName)>>openFuncList;


}ChAniObj9;

class ChAnimationSupporter9
{
public:

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

private:

	static const char animationCheck[];

	static const char animation[];

	static const char aniKey[];

	bool cFlg = false;

	std::vector<ChPtr::Shared<ChQua_9>>Create4D
	(const std::string& _str, size_t& _fPos, const bool _rFlg);

	std::vector<ChPtr::Shared<ChVec3_9>> Create3D
	(const std::string& _str, size_t& _fPos, const bool _rFlg);


	std::map<std::string, std::function
		<std::map<std::string, ChPtr::Shared<ChAnimationObject9>>(const std::string&)>>creaters;
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

#endif
