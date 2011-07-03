#include "StdAfx.h"
#include "PicWallView.h"
#include "PathInfo.h"

// 加载图片文件到HBITMAP
HBITMAP LoadImageFile(const wstring& fileName)
{
	// Use IPicture stuff to use JPG / GIF files
	IPicture* p;
	IStream* s;
	//IPersistStream* ps;
	HGLOBAL hG;
	void* pp;
	FILE* fp;


	// Read file in memory
	fp = _wfopen(fileName.c_str(), _T("rb"));
	if (!fp)
		return NULL;

	fseek(fp,0,SEEK_END);
	int fs = ftell(fp);
	fseek(fp,0,SEEK_SET);
	hG = GlobalAlloc(GPTR,fs);
	if (!hG)
	{
		fclose(fp);
		return NULL;
	}
	pp = (void*)hG;
	fread(pp,1,fs,fp);
	fclose(fp);

	// Create an IStream so IPicture can 
	CreateStreamOnHGlobal(hG,false,&s);
	if (!s)
	{
		GlobalFree(hG);
		return NULL;
	}

	OleLoadPicture(s,0,false,IID_IPicture,(void**)&p);

	if (!p)
	{
		s->Release();
		GlobalFree(hG);
		return NULL;
	}
	s->Release();
	GlobalFree(hG);

	HBITMAP hB = 0;
	p->get_Handle((unsigned int*)&hB);

	// Copy the image. Necessary, because upon p's release,
	// the handle is destroyed.
	HBITMAP hBB = (HBITMAP)CopyImage(hB,IMAGE_BITMAP,0,0,
		LR_COPYRETURNORG);

	p->Release();
	return hBB;
}

//////////////////////////////////////////////////////////////////////////
CPicWallView::CPicWallView()
: imgList(NULL)
{
}

CPicWallView::~CPicWallView(void)
{
	if (imgList)
		imgList->Destroy();
}

bool CPicWallView::InitWithCollectInfo( const TPackagePageInfo *packagePageInfo )
{
	collectName = packagePageInfo->name;
	thumbnailInfoList.erase(thumbnailInfoList.begin(), thumbnailInfoList.end());
	size_t size = packagePageInfo->collectInfoVec.size();
	for (size_t i = 0; i < size; i++)
	{
		TCollectInfo* collectInfo = const_cast<TCollectInfo*>(&packagePageInfo->collectInfoVec[i]);
		thumbnailInfoList.push_back(static_cast<TCollectInfo *const&>(collectInfo));
	}

	InitWithImgInfoList();
	return true;
}

bool CPicWallView::InitWithImgInfoList()
{
	SetRedraw(false);

	int count = GetItemCount();
	while (count-- > 0)
		DeleteItem(0);

	vector<TCollectInfo*>::iterator iter = thumbnailInfoList.begin();
	if (imgList)
	{
		imgList->Destroy();
	}
	imgList = new CImageList();
	// TODO: 分辨率
	imgList->Create(160, 100, TRUE | ILC_COLOR32, thumbnailInfoList.size(), 5);
	this->SetImageList(imgList->m_hImageList, LVSIL_NORMAL);
	for (; iter != thumbnailInfoList.end(); ++iter)
	{
		HBITMAP bm = LoadImageFile((*iter)->thumbSavePath);
		int i = imgList->Add(bm, (HBITMAP)NULL);
		if (i == -1)
		{
			;
		}
		// 已下载辑不再显示
		if (gPathInfo->CurPicsPageUrlFinished((*iter)->linkUrl))
			continue;

		InsertItem(LVIF_TEXT|LVIF_IMAGE|LVIF_PARAM, (*iter)->index, 
			(LPCTSTR)(*iter)->displayName.c_str(), 0, 0, (*iter)->index, (LPARAM)(*iter));
	}

	SetRedraw(true);
	Invalidate();
	UpdateWindow();

	return true;
}

bool CPicWallView::UpdateItem(const string& thumbnailUrl)
{
	int i = 0;
	// TODO: 刷新有问题，需要修改
	vector<TCollectInfo*>::iterator iter = thumbnailInfoList.begin();
	for (; iter != thumbnailInfoList.end(); ++iter, ++i)
	{
		if ((*iter)->thumbUrl == thumbnailUrl)
		{
			HBITMAP bm = LoadImageFile((*iter)->thumbSavePath);
			if (imgList->Add(bm, (HBITMAP)NULL))
				SetImageList(imgList->m_hImageList, LVSIL_NORMAL);
			RedrawItems(i, i);
			break;
		}
	}
	return true;
}