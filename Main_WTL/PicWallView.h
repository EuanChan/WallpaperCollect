#pragma once

class CPicWallView :
	public CWindowImpl<CPicWallView, CListViewCtrl>
{
public:
	// Ĭ��λ�ڳ�������Ŀ¼��Cache\Thumbnail�ļ�����
	CPicWallView();
	virtual ~CPicWallView(void);

	BEGIN_MSG_MAP(CChannelTreeCtrl)    
		MESSAGE_HANDLER(WM_RBUTTONDOWN, OnRBtnClicked)
		DEFAULT_REFLECTION_HANDLER() 
	END_MSG_MAP() 

	LRESULT OnRBtnClicked(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);

public:
	bool InitWithCollectInfo(const TPackagePageInfo *packagePageInfo);

private:
	bool InitWithImgInfoList();

private:
	CImageList *imgList;      // 
	vector<TCollectInfo*> thumbnailInfoList;
};
