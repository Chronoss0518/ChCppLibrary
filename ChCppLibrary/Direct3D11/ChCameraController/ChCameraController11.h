#ifndef Ch_D3D11_Cam_h
#define Ch_D3D11_Cam_h

namespace ChD3D11
{
	class CameraController11
	{
	public://Get Functions//

		//ViewMatrix���쐬����ۂɁA�����ŏ�������v�Z���Ȃ��B//
		ChLMat GetViewMat(
			const ChVec3& _pos,
			const ChVec3& _dir,
			const ChVec3& _up = ChVec3(0.0f, 1.0f, 0.0f));

		//ViewMatrix���쐬����ۂɁA�����ŏ�������v�Z����B//
		ChLMat GetViewMat(
			const ChVec3& _pos,
			const ChVec3& _dir);

		//ViewMatrix���쐬����ۂɁA�����ŏ�������v�Z����B//
		ChLMat GetViewMat(
			const ChVec3& _pos,
			const ChQua& _rot);

		//�O��g�����f�[�^���g���܂킷//
		inline ChLMat GetViewMat() { return camMat; }

	public://Singleton//

		static CameraController11& GetIns()
		{
			static CameraController11 ins;

			return ins;
		}

	protected:

		CameraController11(){}
		
		~CameraController11(){}

	protected://Member Value//

		ChLMat camMat;

	};

	inline CameraController11& CamCon() { return CameraController11::GetIns(); }

}

#ifdef CRT


ChLMat ChD3D11::CameraController11::GetViewMat(
	const ChVec3& _pos,
	const ChVec3& _dir,
	const ChVec3& _up)
{
	ChVec3_11 dir;
	dir = _dir;
	ChVec3_11 up;
	up = _up;

	dir.Normalize();
	up.Normalize();

	ChMat_11 tmpMat;
	tmpMat.CreateViewMat(_pos, dir, up);
	camMat = tmpMat;
	return tmpMat;
}

ChLMat ChD3D11::CameraController11::GetViewMat(
	const ChVec3& _pos,
	const ChQua& _rot)
{

	ChMat_11 tmpMat;

	tmpMat.RotQua(_rot);

	ChVec3_11 dir;
	ChVec3_11 head;

	dir.MatNormal(tmpMat);
	head.MatNormal(tmpMat, ChVec3_11(0.0f, 1.0f, 0.0f));

	return GetViewMat(_pos, dir, head);
}

#endif

#endif