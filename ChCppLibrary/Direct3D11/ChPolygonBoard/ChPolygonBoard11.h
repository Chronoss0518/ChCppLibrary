#ifndef Ch_D3D11_PolyBoard_h
#define Ch_D3D11_PolyBoard_h

#include"../ChShaderStructures11.h"

#include"../../BasePack/Ch3D.h"
#include"../../BasePack/ChPtr.h"

#ifdef CRT

#include<vector>

#endif

namespace ChD3D11
{
	class PolygonBoard11
	{
	public:

		struct PolygonBoard11CRT
		{
#ifdef CRT
			std::vector<ChPtr::Shared<Ch3D::PolyVertex>> vertexs;
#endif
		};

	public:

		PolygonBoard11();
		
		virtual ~PolygonBoard11();

	public://InitAndRelease//

		void Init();

		void Init(ID3D11Device* _device);

		void Release();

	public://Set Functions//

#ifdef CRT
		void SetVertexList(const std::vector<ChPtr::Shared<Ch3D::PolyVertex>>& _vertexList)
		{
			if (!ValueIns().vertexs.empty())ValueIns().vertexs.clear();

			for (auto ver : _vertexList)
			{
				ValueIns().vertexs.push_back(ver);
			}
		}
#endif

		void SetPos(const unsigned char _posNo, const ChVec3& _posData);

		void SetUV(const unsigned char _posNo, const ChVec2& _posData);

		void SetInitTri();

		void SetInitSquare();

	public://Get Functions//

#ifdef CRT
		inline const std::vector<ChPtr::Shared<Ch3D::PolyVertex>>& GetVertexs()
		{
			return ValueIns().vertexs;
		}
#endif

		Ch3D::PolyVertex GetVertex(unsigned long _num)const;

		unsigned long GetVertexSize()const;

		inline Ch3D::Material GetMaterial()const { return material; }

		ChVec3 GetPos(const unsigned char _num);

		ChVec2 GetUVPos(const unsigned char _num);

	public://Add Functions//

		inline void AddVertex()
		{
			Ch3D::PolyVertex vertex;
			AddVertex(vertex);
		}

		void AddVertex(const Ch3D::PolyVertex& _vertexs);

	protected:

		Ch3D::Material material;

		PolygonBoard11CRT& ValueIns() { return *value; }

	private:

		PolygonBoard11CRT* value = nullptr;

	};
}

#ifdef CRT

ChD3D11::PolygonBoard11::PolygonBoard11()
{
	value = new PolygonBoard11CRT();
}

ChD3D11::PolygonBoard11::~PolygonBoard11()
{
	delete value;
}

void ChD3D11::PolygonBoard11::Release()
{
	if (!ValueIns().vertexs.empty())ValueIns().vertexs.clear();
}

void ChD3D11::PolygonBoard11::SetInitTri()
{
	SetInitSquare();
	ValueIns().vertexs.pop_back();
}

void ChD3D11::PolygonBoard11::SetPos(const unsigned char _posNames, const  ChVec3& _posData)
{
	if (_posNames >= ValueIns().vertexs.size())return;
	ValueIns().vertexs[_posNames]->pos = _posData;
}

void ChD3D11::PolygonBoard11::SetUV(const unsigned char _posNames, const ChVec2& _posData)
{
	if (_posNames >= ValueIns().vertexs.size())return;
	ValueIns().vertexs[_posNames]->uv = _posData;
}

void ChD3D11::PolygonBoard11::SetInitSquare()
{
	if (!ValueIns().vertexs.empty())ValueIns().vertexs.clear();

	{
		auto vertex = ChPtr::Make_S<Ch3D::PolyVertex>();

		vertex->pos = ChVec3(-0.5f, 0.5f, 0.0f);
		vertex->uv = ChVec2(0.0f, 0.0f);
		vertex->color = ChVec4(1.0f, 1.0f, 1.0f, 1.0f);

		ValueIns().vertexs.push_back(vertex);
	}

	{
		auto vertex = ChPtr::Make_S<Ch3D::PolyVertex>();

		vertex->pos = ChVec3(0.5f, 0.5f, 0.0f);
		vertex->uv = ChVec2(1.0f, 0.0f);
		vertex->color = ChVec4(1.0f, 1.0f, 1.0f, 1.0f);

		ValueIns().vertexs.push_back(vertex);
	}

	{
		auto vertex = ChPtr::Make_S<Ch3D::PolyVertex>();

		vertex->pos = ChVec3(0.5f, -0.5f, 0.0f);
		vertex->uv = ChVec2(1.0f, 1.0f);
		vertex->color = ChVec4(1.0f, 1.0f, 1.0f, 1.0f);

		ValueIns().vertexs.push_back(vertex);
	}

	{
		auto vertex = ChPtr::Make_S<Ch3D::PolyVertex>();


		vertex->pos = ChVec3(-0.5f, -0.5f, 0.0f);
		vertex->uv = ChVec2(0.0f, 1.0f);
		vertex->color = ChVec4(1.0f, 1.0f, 1.0f, 1.0f);

		ValueIns().vertexs.push_back(vertex);
	}

}

Ch3D::PolyVertex ChD3D11::PolygonBoard11::GetVertex(unsigned long _num)const
{
	if (ValueIns().vertexs.size() <= _num)return Ch3D::PolyVertex();
	return *ValueIns().vertexs[_num];
}

unsigned long ChD3D11::PolygonBoard11::GetVertexSize()const
{
	return ValueIns().vertexs.size();
}

ChVec3 ChD3D11::PolygonBoard11::GetPos(const unsigned char _num)
{
	if (_num >= ValueIns().vertexs.size())return ChVec3();
	return ValueIns().vertexs[_num]->pos;
}

ChVec2 ChD3D11::PolygonBoard11::GetUVPos(const unsigned char _num)
{
	if (_num >= ValueIns().vertexs.size())return ChVec2();
	return ValueIns().vertexs[_num]->uv;
}

void ChD3D11::PolygonBoard11::AddVertex(const Ch3D::PolyVertex& _vertexs)
{
	auto vertex = ChPtr::Make_S<Ch3D::PolyVertex>();
	vertex->pos = _vertexs.pos;
	vertex->uv = _vertexs.uv;
	vertex->color = _vertexs.color;
	vertex->normal = _vertexs.normal;
	ValueIns().vertexs.push_back(vertex);
}

#endif

#endif
