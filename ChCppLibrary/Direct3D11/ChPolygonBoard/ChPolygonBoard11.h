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
	public://InitAndRelease//

		void Init();

		void Init(ID3D11Device* _device);

		void Release();

	public://Set Functions//

#ifdef CRT
		void SetVertexList(const std::vector<ChPtr::Shared<Ch3D::PolyVertex>>& _vertexList)
		{
			if (!vertexs.empty())vertexs.clear();

			for (auto ver : _vertexList)
			{
				vertexs.push_back(ver);
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
			return vertexs;
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

#ifdef CRT

		std::vector<ChPtr::Shared<Ch3D::PolyVertex>> vertexs;

#endif

	};
}

#ifdef CRT

void ChD3D11::PolygonBoard11::Release()
{
	if (!vertexs.empty())vertexs.clear();
}

void ChD3D11::PolygonBoard11::SetInitTri()
{
	SetInitSquare();
	vertexs.pop_back();
}

void ChD3D11::PolygonBoard11::SetPos(const unsigned char _posNames, const  ChVec3& _posData)
{
	if (_posNames >= vertexs.size())return;
	vertexs[_posNames]->pos = _posData;
}

void ChD3D11::PolygonBoard11::SetUV(const unsigned char _posNames, const ChVec2& _posData)
{
	if (_posNames >= vertexs.size())return;
	vertexs[_posNames]->uv = _posData;
}

void ChD3D11::PolygonBoard11::SetInitSquare()
{
	if (!vertexs.empty())vertexs.clear();

	{
		auto vertex = ChPtr::Make_S<Ch3D::PolyVertex>();

		vertex->pos = ChVec3(-0.5f, 0.5f, 0.0f);
		vertex->uv = ChVec2(0.0f, 0.0f);
		vertex->color = ChVec4(1.0f, 1.0f, 1.0f, 1.0f);

		vertexs.push_back(vertex);
	}

	{
		auto vertex = ChPtr::Make_S<Ch3D::PolyVertex>();

		vertex->pos = ChVec3(0.5f, 0.5f, 0.0f);
		vertex->uv = ChVec2(1.0f, 0.0f);
		vertex->color = ChVec4(1.0f, 1.0f, 1.0f, 1.0f);

		vertexs.push_back(vertex);
	}

	{
		auto vertex = ChPtr::Make_S<Ch3D::PolyVertex>();

		vertex->pos = ChVec3(0.5f, -0.5f, 0.0f);
		vertex->uv = ChVec2(1.0f, 1.0f);
		vertex->color = ChVec4(1.0f, 1.0f, 1.0f, 1.0f);

		vertexs.push_back(vertex);
	}

	{
		auto vertex = ChPtr::Make_S<Ch3D::PolyVertex>();


		vertex->pos = ChVec3(-0.5f, -0.5f, 0.0f);
		vertex->uv = ChVec2(0.0f, 1.0f);
		vertex->color = ChVec4(1.0f, 1.0f, 1.0f, 1.0f);

		vertexs.push_back(vertex);
	}

}

Ch3D::PolyVertex ChD3D11::PolygonBoard11::GetVertex(unsigned long _num)const
{
	if (vertexs.size() <= _num)return Ch3D::PolyVertex();
	return *vertexs[_num];
}

unsigned long ChD3D11::PolygonBoard11::GetVertexSize()const
{
	return vertexs.size();
}

ChVec3 ChD3D11::PolygonBoard11::GetPos(const unsigned char _num)
{
	if (_num >= vertexs.size())return ChVec3();
	return vertexs[_num]->pos;
}

ChVec2 ChD3D11::PolygonBoard11::GetUVPos(const unsigned char _num)
{
	if (_num >= vertexs.size())return ChVec2();
	return vertexs[_num]->uv;
}

void ChD3D11::PolygonBoard11::AddVertex(const Ch3D::PolyVertex& _vertexs)
{
	auto vertex = ChPtr::Make_S<Ch3D::PolyVertex>();
	vertex->pos = _vertexs.pos;
	vertex->uv = _vertexs.uv;
	vertex->color = _vertexs.color;
	vertex->normal = _vertexs.normal;
	vertexs.push_back(vertex);
}

#endif

#endif
