#ifndef Ch_D3DOBJ_WICBitmap_h
#define Ch_D3DOBJ_WICBitmap_h

struct IWICImagingFactory;
struct IWICBitmap;

namespace ChD3D
{
	class WICBitmapCreator;

	class WICBitmapObject
	{
	public:

		friend WICBitmapCreator;

	public:

		void Release();

	public:

		IWICBitmap* const GetBitmap() const { return bitmap; }

	private:

		IWICBitmap* bitmap = nullptr;
	};

	class WICBitmapCreator
	{
	public:

		struct WICBitmapCreatorCRT
		{
#ifdef CRT
			std::vector<IWICBitmap*>bitmapList;
#endif
		};

	public:

		friend WICBitmapObject;

	public:

		WICBitmapCreator();

		virtual ~WICBitmapCreator();

	public:

		void Init();

		void Release();

	public:

		WICBitmapObject CreateBitmapObject(unsigned long _width, unsigned long _height);

	private:

		IWICBitmap* GetBitmap(size_t _num);

		size_t GetBitmapCount();

		void AddBitmap(IWICBitmap*);

		void ClearBitmapList();

	public:

		static WICBitmapCreator& GetIns()
		{
			static WICBitmapCreator ins;
			return ins;
		}

	private:

		IWICImagingFactory* factory = nullptr;

		WICBitmapCreatorCRT* value = nullptr;
	};

	inline WICBitmapCreator& WICBitmapCreatorObj()
	{
		return WICBitmapCreator::GetIns();
	}

}

#ifdef CRT

void ChD3D::WICBitmapObject::Release()
{
	auto&& list = WICBitmapCreatorObj().value->bitmapList;

	auto&& bitmapIterator = std::find(list.begin(), list.end(), bitmap);

	list.erase(bitmapIterator);

	if (ChPtr::NotNullCheck(bitmap))
	{
		bitmap->Release();
		bitmap = nullptr;
	}
}

ChD3D::WICBitmapCreator::WICBitmapCreator()
{
	value = new WICBitmapCreatorCRT();
}

ChD3D::WICBitmapCreator::~WICBitmapCreator()
{
	Release();
	delete value;
}

IWICBitmap* ChD3D::WICBitmapCreator::GetBitmap(size_t _num)
{
	return value->bitmapList[_num];
}

size_t ChD3D::WICBitmapCreator::GetBitmapCount()
{
	return value->bitmapList.size();
}

void ChD3D::WICBitmapCreator::AddBitmap(IWICBitmap* _bmp)
{
	return value->bitmapList.push_back(_bmp);
}

void ChD3D::WICBitmapCreator::ClearBitmapList()
{
	if (value->bitmapList.empty())return;
	value->bitmapList.clear();
}

#endif

#endif