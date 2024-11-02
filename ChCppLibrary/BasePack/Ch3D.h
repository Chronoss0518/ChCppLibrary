#ifndef Ch_CPP_3D_h
#define Ch_CPP_3D_h

#include<vector>
#include<string>
#include<map>
#include<memory>

#include"ChMath3D.h"
#include"ChPtr.h"

namespace Ch3D
{
	enum class ShaderAxisType:unsigned char
	{
		LeftHand,
		RightHand
	};

	struct Position
	{
		ChVec3 pos;
	};

	inline void SetPosition(Position* _pos, const ChVec3& _val)
	{
		if (ChPtr::NullCheck(_pos))return;
		_pos->pos = _val;
	}

	//ç∂è„Ç™0.0,0.0ÇÃç¿ïWån//
	struct UV
	{
		ChVec2 uv;
	};

	inline void SetUV(UV* _uv, const ChVec2& _val)
	{
		if (ChPtr::NullCheck(_uv))return;
		_uv->uv = _val;
	}

	struct Color
	{
		ChVec4 color = ChVec4(1.0f, 1.0f, 1.0f, 1.0f);
	};

	inline void SetColor(Color* _color, const ChVec4& _val)
	{
		if (ChPtr::NullCheck(_color))return;
		_color->color = _val;
	}

	struct Normal
	{
		ChVec3 normal = ChVec3(0.0f,1.0f,0.0f);
	};

	inline void SetNormal(Normal* _normal, const ChVec3& _val)
	{
		if (ChPtr::NullCheck(_normal))return;
		_normal->normal = _val;
	}

	struct FaceNormal
	{
		ChVec3 faceNormal = ChVec3(0.0f, 1.0f, 0.0f);
	};

	inline void SetFaceNormal(FaceNormal* _faceNormal, const ChVec3& _val)
	{
		if (ChPtr::NullCheck(_faceNormal))return;
		_faceNormal->faceNormal = _val;
	}

	template<unsigned long Num>
	struct Bone
	{
		Bone() {
			for (unsigned long i = 0; i < Num; i++)
			{
				blendPows[i] = 0.0f;
			}
		}
		unsigned long boneNum = 0;

		float blendPows[Num];

	};

	struct BoneData
	{
		std::vector<float> blendPow;
	};

	struct Vertex:
		public Position,
		public UV,
		public Color
	{};

	struct PolyVertex :
		public Vertex,
		public Normal
	{};

	struct MeshVertex :
		public PolyVertex,
		public FaceNormal
	{};

	template<unsigned long Num>
	struct SkinMeshVertex :
		public MeshVertex,
		public Bone<Num>
	{};

	struct SavePolyVertex :
		public Position,
		public Color,
		public Normal,
		public BoneData
	{};

	struct Material
	{
		ChVec4 diffuse = 1.0f;
		ChVec3 specularColor = 0.0f;
		float specularPower = 1.0f;
		ChVec4 ambient = 0.3f;
	};

	enum class TextureType:unsigned char
	{
		Diffuse,
		Ambient,
		Specular,
		SpecularHighLight,
		Bump,
		Alpha,
		Normal,
		Metallic,
		Other,
		None
	};


	template<typename CharaType>
	struct MaterialData
	{
		Material mate;
		std::basic_string<CharaType> mateName;
		std::map<TextureType, std::basic_string<CharaType>>textures;
	};

	struct Transform
	{
		ChVec3 pos;
		ChQua rot;
		ChVec3 scl = 1.0f;

		inline ChLMat& GetLeftHandMatrix()
		{
			static ChLMat res;
			res.SetPosition(pos);
			res.SetRotation(rot);
			res.SetScalling(scl);
			return res;
		}

		inline ChRMat& GetRightHandMatrix()
		{
			static ChRMat res;
			res.SetPosition(pos);
			res.SetRotation(rot);
			res.SetScalling(scl);
			return res;
		}
	};

	struct SavePolyData :public UV
	{
		unsigned long vertexNo = 0;
	};

	//MaterialÇ…ëŒâûÇ∑ÇÈñ Çä«óùÇ∑ÇÈ//
	struct Primitive:public FaceNormal
	{
		unsigned long mateNo = 0;
		std::vector<ChPtr::Shared<SavePolyData>> vertexData;
	};
}

#endif