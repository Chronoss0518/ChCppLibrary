#ifndef Ch_CPP_RCollider_h
#define Ch_CPP_RCollider_h

#include"ChCollider.h"

namespace ChCpp
{
	class HitTestRay :public HitTestObject
	{
	public://SetFunction//

		void SetMaxLength(const float _maxLen = ChMath::GetMaxFloat()) { maxLen = _maxLen; }

		inline void SetRayDir(const ChVec3& _dir) { rayDir = _dir; rayDir.Normalize(); }

		//Rayの基本方向をZ軸の+方向//
		inline void SetRayPZ() { rayDir = ChVec3(0.0f, 0.0f, 1.0f); }

		//Rayの基本方向をZ軸の-方向//
		inline void SetRayMZ() { rayDir = ChVec3(0.0f, 0.0f, -1.0f); }

		//Rayの基本方向をX軸の+方向//
		inline void SetRayPX() { rayDir = ChVec3(1.0f, 0.0f, 0.0f); }

		//Rayの基本方向をX軸の-方向//
		inline void SetRayMX() { rayDir = ChVec3(-1.0f, 0.0f, 0.0f); }

		//Rayの基本方向をY軸の+方向//
		inline void SetRayPY() { rayDir = ChVec3(0.0f, 1.0f, 0.0f); }

		//Rayの基本方向をY軸の-方向//
		inline void SetRayMY() { rayDir = ChVec3(0.0f, -1.0f, 0.0f); }

		inline ChVec3 GetRayDir() { return rayDir; }

		inline float GetMaxLen() { return maxLen; }

	private:

		ChVec3 rayDir = ChVec3(0.0f, 0.0f, 1.0f);

		float maxLen = ChMath::GetMaxFloat();
	};
}

#endif