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

		//Ray�̊�{������Z����+����//
		inline void SetRayPZ() { rayDir = ChVec3(0.0f, 0.0f, 1.0f); }

		//Ray�̊�{������Z����-����//
		inline void SetRayMZ() { rayDir = ChVec3(0.0f, 0.0f, -1.0f); }

		//Ray�̊�{������X����+����//
		inline void SetRayPX() { rayDir = ChVec3(1.0f, 0.0f, 0.0f); }

		//Ray�̊�{������X����-����//
		inline void SetRayMX() { rayDir = ChVec3(-1.0f, 0.0f, 0.0f); }

		//Ray�̊�{������Y����+����//
		inline void SetRayPY() { rayDir = ChVec3(0.0f, 1.0f, 0.0f); }

		//Ray�̊�{������Y����-����//
		inline void SetRayMY() { rayDir = ChVec3(0.0f, -1.0f, 0.0f); }

		inline ChVec3 GetRayDir() { return rayDir; }

		inline float GetMaxLen() { return maxLen; }

	private:

		ChVec3 rayDir = ChVec3(0.0f, 0.0f, 1.0f);

		float maxLen = ChMath::GetMaxFloat();
	};
}

#endif