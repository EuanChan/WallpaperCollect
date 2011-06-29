#pragma once

class CPicWallView :
	public CWindowImpl<CPicWallView, CListViewCtrl>
{
public:
	// Ĭ��λ�ڳ�������Ŀ¼��Cache\Thumbnail�ļ�����
	CPicWallView(const wstring &cacheFilePath = _T(""));
	virtual ~CPicWallView(void);

	BEGIN_MSG_MAP(CChannelTreeCtrl)    
		MESSAGE_HANDLER(WM_RBUTTONDOWN, OnRBtnClicked)
		DEFAULT_REFLECTION_HANDLER() 
	END_MSG_MAP() 

	LRESULT OnRBtnClicked(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);

public:
	bool InitWithPageUrl(const string &pageUrl);

private:
	bool InitWithImgInfoList();
private:
	CImageList *imgList;      // 


// 	string pageUrl;
	wstring cachePathRoot;   // ��ʱ�ļ���Ÿ�Ŀ¼

	vector<TCollectInfo> thumbnailInfoList;
};
