#pragma once

class CPicWallView :
	public CWindowImpl<CPicWallView, CListViewCtrl>
{
public:
	CPicWallView();
	virtual ~CPicWallView(void);

	BEGIN_MSG_MAP(CPicWallView)
		DEFAULT_REFLECTION_HANDLER() 
	END_MSG_MAP() 

public:
	bool InitWithCollectInfo(const TPackagePageInfo *packagePageInfo);

	bool UpdateItem(const string& thumbnailUrl);
	TCollectInfo* GetDataByIndex(int index)
	{
		if (index >= thumbnailInfoList.size() - 1)
			return NULL;
		return thumbnailInfoList[index];
	}
private:
	bool InitWithImgInfoList();

private:
	CImageList *imgList;      // 
	vector<TCollectInfo*> thumbnailInfoList;
	wstring  collectName;     // ��ǰ�ϼ���
	int      indexFlag;       // ������������ͼ�����и���ͼƬ���ؽ��б�ʱ������Ϊimagelist::count, ÿ�θ���itemindexʱ���£�
};
