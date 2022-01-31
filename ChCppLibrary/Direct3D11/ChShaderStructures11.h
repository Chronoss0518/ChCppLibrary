
//SStruct = ShaderStructure//
#ifndef Ch_D3D11_SStruct_h
#define Ch_D3D11_SStruct_h

namespace ChD3D11
{
	class Texture11;

	struct ShaderUseMaterial11 :public Ch3D::Material
	{
		ChMat_11 frameMatrix;
	};

	struct Material11
	{
		ShaderUseMaterial11 material;

		std::string materialName;
		ChPtr::Shared<Texture11> diffuseMap = ChPtr::Make_S<Texture11>();
		ChPtr::Shared<Texture11> ambientMap = ChPtr::Make_S<Texture11>();
		ChPtr::Shared<Texture11> specularMap = ChPtr::Make_S<Texture11>();
		ChPtr::Shared<Texture11> specularHighLightMap = ChPtr::Make_S<Texture11>();
		ChPtr::Shared<Texture11> bumpMap = ChPtr::Make_S<Texture11>();
		ChPtr::Shared<Texture11> alphaMap = ChPtr::Make_S<Texture11>();
		ChPtr::Shared<Texture11> normalMap = ChPtr::Make_S<Texture11>();
		ChPtr::Shared<Texture11> metallicMap = ChPtr::Make_S<Texture11>();
	};

	struct Vertex11
	{
		ChVec3 pos;
		ChVec2 uvPos;
		ChVec4 color = ChVec4(1.0f, 1.0f, 1.0f, 1.0f);
	};

	struct MeshVertex11 : public Vertex11
	{
		ChVec3 normal = ChVec3(0.0f, 0.0f, -1.0f);
	};

	struct PrimitiveVertex11 : public MeshVertex11
	{
		ChVec3 faceNormal = ChVec3(0.0f, 0.0f, -1.0f);
	};

	struct SkinMeshVertex11 : public PrimitiveVertex11
	{
		float blendPow[96];
	};

	class ShaderObjectBase11 :public ChCp::Releaser, public ChCp::Initializer
	{
	public:

		///////////////////////////////////////////////////////////////////////////////////////
		//InitAndRelease//

		inline void Release()override
		{
			SetInitFlg(false);
			if (ChPtr::NullCheck(buf))return;
			buf->Release();
			buf = nullptr;
		};

		///////////////////////////////////////////////////////////////////////////////////////
		//AddFunction//

		inline void AddCPUAccessFlg(const D3D11_CPU_ACCESS_FLAG& _flg)
		{
			cpuAccessFlg |= _flg;
		}

		///////////////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		inline void SetCPUAccessFlg(const D3D11_CPU_ACCESS_FLAG& _flg)
		{
			cpuAccessFlg = _flg;
		}

		///////////////////////////////////////////////////////////////////////////////////
		//CreateFUnction//

		template<class T>
		inline D3D11_BUFFER_DESC CreateBufferDesc(const unsigned long _num)
		{

			D3D11_BUFFER_DESC desc;
			desc.ByteWidth = sizeof(T) * _num;
			desc.Usage = D3D11_USAGE_DEFAULT;
			desc.BindFlags = bindFlg;
			desc.CPUAccessFlags = cpuAccessFlg;
			desc.MiscFlags = 0;
			desc.StructureByteStride = 0;

			return desc;
		}

		template<class T>
		inline D3D11_SUBRESOURCE_DATA CreateSubresourceData(const T* _buf)
		{
			D3D11_SUBRESOURCE_DATA data;
			data.pSysMem = _buf;
			data.SysMemPitch = 0;
			data.SysMemSlicePitch = 0;

			return data;
		}

	protected:

		inline void Init() { SetInitFlg(true); }

		///////////////////////////////////////////////////////////////////////////////////

		ID3D11Buffer* buf = nullptr;

		unsigned int cpuAccessFlg = 0;
		unsigned int usage = 0;
		unsigned int bindFlg = 0;


	};

	class IndexBuffer11 : public ShaderObjectBase11
	{
	public:
		///////////////////////////////////////////////////////////////////////////////////////
		//CreateFunction//

		inline void CreateBuffer(
			ID3D11Device* _device,
			const unsigned long* _indexBuffer,
			const unsigned long _indexNum)
		{
			if (ChPtr::NullCheck(_device))return;

			Release();

			bindFlg = D3D11_BIND_INDEX_BUFFER;

			D3D11_BUFFER_DESC desc = CreateBufferDesc<unsigned long>(_indexNum);

			D3D11_SUBRESOURCE_DATA data = CreateSubresourceData(_indexBuffer);

			_device->CreateBuffer(&desc, &data, &buf);

			Init();
		}

		///////////////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		inline void SetIndexBuffer(ID3D11DeviceContext* _dc)
		{
			if (*this)return;
			if (ChPtr::NullCheck(_dc))return;

			_dc->IASetIndexBuffer(buf, DXGI_FORMAT_R32_UINT, 0);
		}

	};

	template<class vertex = Vertex11>
	class VertexBuffer11 : public ShaderObjectBase11
	{
	public:

		///////////////////////////////////////////////////////////////////////////////////////
		//CreateFunction//

		inline void CreateBuffer(
			ID3D11Device* _device,
			const vertex* _vertexArray,
			const unsigned long _vertexNum)
		{
			if (ChPtr::NullCheck(_device))return;
			if (ChPtr::NullCheck(_vertexArray))return;

			Release();

			bindFlg = D3D11_BIND_VERTEX_BUFFER;

			D3D11_BUFFER_DESC desc = CreateBufferDesc<vertex>(_vertexNum);

			D3D11_SUBRESOURCE_DATA data = CreateSubresourceData(_vertexArray);

			_device->CreateBuffer(&desc, &data, &buf);

			Init();
		}

		///////////////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		inline void SetVertexBuffer(
			ID3D11DeviceContext* _dc,
			const unsigned int _offset)
		{

			if (*this)return;
			if (ChPtr::NullCheck(_dc))return;

			unsigned int strides = sizeof(vertex);

			_dc->IASetVertexBuffers(0, 1, &buf, &strides, &_offset);
		}

	};

	template<class content>
	class ConstantBuffer11 :public ShaderObjectBase11
	{
	public:
		///////////////////////////////////////////////////////////////////////////////////////
		//CreateFunction//

		inline void CreateBuffer(
			ID3D11Device* _device,
			const unsigned long _registerNo)
		{
			if (ChPtr::NullCheck(_device))return;

			Release();

			bindFlg = D3D11_BIND_CONSTANT_BUFFER;

			D3D11_BUFFER_DESC desc = CreateBufferDesc<content>(1);

			_device->CreateBuffer(&desc, nullptr, &buf);

			registerNo = _registerNo;

			Init();
		}

		///////////////////////////////////////////////////////////////////////////////////////
		//UpdateFunction//

		inline void UpdateResouce(
			ID3D11DeviceContext* _dc,
			const content* _content)
		{

			if (*this)return;
			if (ChPtr::NullCheck(_dc))return;
			if (ChPtr::NullCheck(_content))return;

			_dc->UpdateSubresource(buf, 0, nullptr, &_content, 0, 0);
		}

		///////////////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		inline void SetToVertexShader(
			ID3D11DeviceContext* _dc,
			const unsigned long updateCount = 1)
		{
			if (*this)return;
			if (ChPtr::NullCheck(_dc))return;

			_dc->VSSetConstantBuffers(registerNo, updateCount, &buf);

		}

		///////////////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		inline void SetToPixelShader(
			ID3D11DeviceContext* _dc,
			const unsigned long updateCount = 1)
		{
			if (*this)return;
			if (ChPtr::NullCheck(_dc))return;

			_dc->PSSetConstantBuffers(registerNo, updateCount, &buf);

		}

	protected:

		unsigned long registerNo = 0;
	};

	template<class vertex = Vertex11>
	struct PrimitiveData11
	{
		IndexBuffer11 indexBuffer;
		VertexBuffer11<vertex> vertexBuffer;

		typename std::enable_if<std::is_base_of<Vertex11, vertex>::value, vertex*>::type vertexArray = nullptr;
		unsigned long* indexArray = nullptr;

		unsigned long vertexNum = 0;
		unsigned long indexNum = 0;

		ChPtr::Shared<Material11> mate = nullptr;

	};

	struct BoneData11
	{
		unsigned long skinWeightCount = 0;
		ChMath::Vector3Base<unsigned long> tmpBuffer;
		ChMat_11 animationMat[96];

	};


}

#endif