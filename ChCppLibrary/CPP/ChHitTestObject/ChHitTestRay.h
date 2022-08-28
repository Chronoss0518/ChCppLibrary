#ifndef Ch_CPP_HTR_h
#define Ch_CPP_HTR_h

#include"ChHitTestObject.h"

namespace ChCpp
{
	
	class HitTestRay :public HitTestObject
	{
	public:
		///////////////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		inline void SetMaxLength(const float _maxLen = FLT_MAX) { maxLen = _maxLen; }

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

		///////////////////////////////////////////////////////////////////////////////////////
		//IsFunction//

		//�Ώۂ̃I�u�W�F�N�g���I�u�W�F�N�g�O����Փ˂��Ă��邩�̔���//
		ChStd::Bool IsHit(
			HitTestPanel* _target)override;

		//�Ώۂ̃I�u�W�F�N�g���I�u�W�F�N�g�O����Փ˂��Ă��邩�̔���//
		ChStd::Bool IsHit(
			HitTestBox* _target)override;

		//�Ώۂ̃I�u�W�F�N�g���I�u�W�F�N�g�O����Փ˂��Ă��邩�̔���//
		ChStd::Bool IsHit(
			HitTestSphere* _target)override;

		//�Ώۂ̃I�u�W�F�N�g���I�u�W�F�N�g�O����Փ˂��Ă��邩�̔���//
		ChStd::Bool IsHit(
			HitTestPolygon* _target)override;

		//�Ώۂ̃I�u�W�F�N�g���I�u�W�F�N�g������Փ˂��Ă��邩�̔���//
		ChStd::Bool IsInnerHit(
			HitTestBox* _target)override;

		//�Ώۂ̃I�u�W�F�N�g���I�u�W�F�N�g������Փ˂��Ă��邩�̔���//
		ChStd::Bool IsInnerHit(
			HitTestSphere* _target)override;

	private:

		float CreateDat(const ChVec3& _vec1, const ChVec3& _vec2, const ChVec3& _vec3);

		ChStd::Bool HitTestTri(const ChVec3& _vec1, const ChVec3& _vec2, const ChVec3& _vec3, const HitTestObject* _target);


		ChVec3 rayDir = ChVec3(0.0f, 0.0f, 1.0f);
		float maxLen = FLT_MAX;

	};




}

#endif