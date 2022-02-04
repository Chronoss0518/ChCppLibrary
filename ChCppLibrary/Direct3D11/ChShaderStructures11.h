
//SStruct = ShaderStructure//
#ifndef Ch_D3D11_SStruct_h
#define Ch_D3D11_SStruct_h

namespace ChD3D11
{
	class Texture11;

	struct ShaderUseMaterial11
	{
		ChVec4 diffuse = ChVec4(1.0f, 1.0f, 1.0f, 1.0f);
		ChVec4 specular = ChVec4(1.0f, 1.0f, 1.0f, 1.0f);
		ChVec4 ambient = ChVec4(0.3f, 0.3f, 0.3f, 1.0f);
		ChMat_11 frameMatrix;
	};

	struct Material11
	{
		ShaderUseMaterial11 material;


		ConstantBuffer mBuffer = nullptr;
		std::string materialName;
		std::vector<ChPtr::Shared<Texture11>>textureList;
	};

	struct Vertex11
	{
		ChVec3 pos;
		ChVec2 uvPos;
		ChVec4 color = ChVec4(1.0f, 1.0f, 1.0f, 1.0f);
	};

	struct MeshVertex11: public Vertex11
	{
		ChVec3 normal = ChVec3(0.0f, 0.0f, -1.0f);
	};

	struct PrimitiveVertex11 : public MeshVertex11
	{
		ChVec3 faceNormal = ChVec3(0.0f,0.0f,-1.0f);
		ChUIMat blendIndex;
		ChLMat blendPow;
		unsigned long blendNum = 0;
	};

	class ShaderObjectBase11 :public ChCp::Releaser, public ChCp::Initializer
	{
	public:

		///////////////////////////////////////////////////////////////////////////////////////
		//InitAndRelease//

		inline void Init() { SetInitFlg(true); }

		inline void Release()override
		{
			SetInitFlg(false);
			if (ChPtr::NullCheck(buf))return;
			buf->Release();
			buf = nullptr;
		};

		///////////////////////////////////////////////////////////////////////////////////////
		//AddFunction//

		//Flgメソッド//
		inline void AddCPUAccessFlg(const D3D11_CPU_ACCESS_FLAG& _flg)
		{
			cpuAccessFlg |= _flg;
		}

		///////////////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		//Flgメソッド//
		inline void SetUsageFlg(const D3D11_USAGE& _flg)
		{
			usage = _flg;
		}

		//Flgメソッド//
		inline void SetCPUAccessFlg(const D3D11_CPU_ACCESS_FLAG& _flg)
		{
			cpuAccessFlg = _flg;
		}

		template<class T>
		inline void SetDynamicBuffer(ID3D11DeviceContext* _dc, const T* _buf, const unsigned long _bufferCount)
		{
			if (!(usage & D3D11_USAGE::D3D11_USAGE_DYNAMIC))return;

			D3D11_MAPPED_SUBRESOURCE map;
			ZeroMemory(&map, sizeof(D3D11_MAPPED_SUBRESOURCE));

			//  Disable GPU access to the vertex buffer data.
			_dc->Map(buf, 0, D3D11_MAP_WRITE_DISCARD, 0, &map);
			//  Update the vertex buffer here.
			memcpy(map.pData, _buf, sizeof(T) * _bufferCount);
			//  Reenable GPU access to the vertex buffer data.
			_dc->Unmap(buf, 0);
		}

		///////////////////////////////////////////////////////////////////////////////////////
		//UpdateFunction//

		template<class T>
		inline void UpdateResouce(
			ID3D11DeviceContext* _dc,
			const T* _content)
		{

			if (!*this)return;
			if (ChPtr::NullCheck(_dc))return;
			if (ChPtr::NullCheck(_content))return;

			_dc->UpdateSubresource(buf, 0, nullptr, &_content, 0, 0);
		}

	protected:

		///////////////////////////////////////////////////////////////////////////////////
		//CreateFunction//

		template<class T>
		inline D3D11_BUFFER_DESC CreateBufferDesc(const unsigned long _num)
		{

			D3D11_BUFFER_DESC desc;
			ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
			desc.ByteWidth = sizeof(T) * _num;
			desc.Usage = usage;
			desc.BindFlags = bindFlg;
			desc.CPUAccessFlags = cpuAccessFlg;
			desc.MiscFlags = 0;
			desc.StructureByteStride = 0;

			return desc;
		}


		inline D3D11_SUBRESOURCE_DATA CreateSubresourceData(void* _buf)
		{
			D3D11_SUBRESOURCE_DATA data;
			ZeroMemory(&data, sizeof(D3D11_SUBRESOURCE_DATA));
			data.pSysMem = _buf;
			data.SysMemPitch = 0;
			data.SysMemSlicePitch = 0;

			return data;
		}

		///////////////////////////////////////////////////////////////////////////////////

		ID3D11Buffer* buf = nullptr;

		unsigned int cpuAccessFlg = 0;
		D3D11_USAGE usage = D3D11_USAGE::D3D11_USAGE_DEFAULT;
		D3D11_BIND_FLAG bindFlg = D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER;


	};

	class IndexBuffer11 : public ShaderObjectBase11
	{
	public:
		///////////////////////////////////////////////////////////////////////////////////////
		//CreateFunction//

		//Createを呼ぶ前に必要な場合はフラグ関係を操作するメソッドを呼びます//
		inline void CreateBuffer(
			ID3D11Device* _device,
			unsigned long* _indexBuffer,
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
			if (!*this)return;
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

		//Createを呼ぶ前に必要な場合はフラグ関係を操作するメソッドを呼びます//
		inline void CreateBuffer(
			ID3D11Device* _device,
			vertex* _vertexArray,
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

			if (!*this)return;
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

		//Createを呼ぶ前に必要な場合はフラグ関係を操作するメソッドを呼びます//
		inline void CreateBuffer(
			ID3D11Device* _device,
			const unsigned long _registerNo)
		{
			if (ChPtr::NullCheck(_device))return;

			Release();

			bindFlg = D3D11_BIND_CONSTANT_BUFFER;

			D3D11_BUFFER_DESC desc = CreateBufferDesc<content>(1);

			unsigned long makeUpBuffer = desc.ByteWidth % 16;

			desc.ByteWidth = makeUpBuffer == 0 ? desc.ByteWidth : desc.ByteWidth + (16 - makeUpBuffer);

			_device->CreateBuffer(&desc, nullptr, &buf);

			registerNo = _registerNo;

			Init();
		}

		///////////////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		inline void SetToVertexShader(
			ID3D11DeviceContext* _dc,
			const unsigned long updateCount = 1)
		{
			if (!(usage & D3D11_USAGE::D3D11_USAGE_DEFAULT))return;

			if (!*this)return;
			if (ChPtr::NullCheck(_dc))return;

			_dc->VSSetConstantBuffers(registerNo, updateCount, &buf);

		}

		///////////////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		inline void SetToPixelShader(
			ID3D11DeviceContext* _dc,
			const unsigned long updateCount = 1)
		{
			if (!*this)return;
			if (ChPtr::NullCheck(_dc))return;

			_dc->PSSetConstantBuffers(registerNo, updateCount, &buf);

		}

	protected:

		unsigned long registerNo = 0;
	};

	template<class vertex = Vertex11>
	struct PrimitiveData11
	{
		IndexBuffer11 indexs;
		VertexBuffer11<vertex> vertexs;


		typename std::enable_if<std::is_base_of<Vertex11, vertex>::value, vertex*>::type vertexArray = nullptr;
		unsigned long* indexArray = nullptr;

		unsigned long vertexNum = 0;
		unsigned long indexNum = 0;

		ChPtr::Shared<Material11> mate;

		inline void Release()
		{

			//if (ChPtr::NotNullCheck(indexs))
			//{
			//	indexs->Release();
			//	indexs = nullptr;
			//}

			//if (ChPtr::NotNullCheck(vertexs))
			//{
			//	vertexs->Release();
			//	vertexs = nullptr;
			//}

			if (ChPtr::NotNullCheck(vertexArray))
			{
				delete[] vertexArray;
				vertexArray = nullptr;
			}

			if (ChPtr::NotNullCheck(indexArray))
			{
				delete[] indexArray;
				indexArray = nullptr;
			}

			if (mate != nullptr)
			{

				if (ChPtr::NotNullCheck(mate->mBuffer))
				{
					mate->mBuffer->Release();
					mate->mBuffer = nullptr;
				}
			}

		}

		inline ~PrimitiveData11()
		{
			Release();
		}
	};

	template<class Vertex = Vertex11>
	class ShaderObject:public ChCp::Releaser
	{
	public:

		///////////////////////////////////////////////////////////////////////////////////////
		//InitAndRelease//

		virtual void Release()override {};

		///////////////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		virtual void SetDrawData(ID3D11DeviceContext* _cd) = 0;

		///////////////////////////////////////////////////////////////////////////////////////

		auto CreateVertexBuffer(PrimitiveData11<Vertex>& _prim)
			->typename std::enable_if<std::is_base_of<Vertex11, Vertex>::value, void>::type
		{

			_prim.vertexs.CreateBuffer(device, _prim.vertexArray, _prim.vertexNum);

			return;

			D3D11_BUFFER_DESC desc;

			desc.ByteWidth = sizeof(Vertex) * _prim.vertexNum;
			desc.Usage = D3D11_USAGE_DEFAULT;
			desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
			desc.CPUAccessFlags = 0;
			desc.MiscFlags = 0;
			desc.StructureByteStride = 0;

			D3D11_SUBRESOURCE_DATA data;
			data.pSysMem = _prim.vertexArray;
			data.SysMemPitch = 0;
			data.SysMemSlicePitch = 0;

			//device->CreateBuffer(&desc, &data, &_prim.vertexs);

		}

		///////////////////////////////////////////////////////////////////////////////////

		auto CreateIndexBuffer(PrimitiveData11<Vertex>& _prim)
			->typename std::enable_if<std::is_base_of<Vertex11, Vertex>::value, void>::type
		{
			_prim.indexs.CreateBuffer(device, _prim.indexArray, _prim.indexNum);

			return;


			D3D11_BUFFER_DESC desc;
			desc.ByteWidth = sizeof(unsigned long) * _prim.indexNum;
			desc.Usage = D3D11_USAGE_DEFAULT;
			desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
			desc.CPUAccessFlags = 0;
			desc.MiscFlags = 0;
			desc.StructureByteStride = 0;

			D3D11_SUBRESOURCE_DATA data;
			data.pSysMem = _prim.indexArray;
			data.SysMemPitch = 0;
			data.SysMemSlicePitch = 0;

			//device->CreateBuffer(&desc, &data, &_prim.indexs);

		}

		template<class T>
		void CreateContentBuffer(ConstantBuffer* _buffer)
		{

			D3D11_BUFFER_DESC desc;
			ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));

			desc.ByteWidth = sizeof(T);
			desc.Usage = D3D11_USAGE_DEFAULT;
			desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
			desc.CPUAccessFlags = 0;
			desc.MiscFlags = 0;
			desc.StructureByteStride = 0;

			device->CreateBuffer(&desc, nullptr, _buffer);
		}

	protected:

		///////////////////////////////////////////////////////////////////////////////////

		ID3D11Device* GetDevice() { return device; }

		///////////////////////////////////////////////////////////////////////////////////

		void SetDevice(ID3D11Device* _device) { device = _device; }

		///////////////////////////////////////////////////////////////////////////////////

	private:


		ID3D11Device* device = nullptr;



	};

}

#endif