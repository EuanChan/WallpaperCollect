#ifndef WALLPAPERCOLLECT_H
#define WALLPAPERCOLLECT_H

#ifdef WallpaperCollect_EXPORTS
#define WallpaperCollect_API __declspec(dllexport)
#else
#define WallpaperCollect_API __declspec(dllimport)
#endif

using std::wstring;
using std::string;

class TiXmlElement;
class TSiteInfo;
class TChannelInfo;
class CNet;
class WallpaperCollect_API CWallpaperCollect
{
public:
	CWallpaperCollect(void);
	~CWallpaperCollect(void);

	void SetSite(const string& url);
// 	void SetSaveDir(const wstring& saveDir);
	// bool ParseAndCollect(const char* url);

	// ��ȡƵ����Ϣ�����浽TChannelAttri��
	bool ColChannelTree(TChannelInfo* channelInfo);

	// �������������⣬����ͬColFromPackagePages
	bool GetPackagePagesInfo(const string& pageUrl,  TPackagePageInfo* collectInfo);
	// �������������⣬����ͬColFromPackagePage
	bool GetPackagePageInfo(const string& pageUrl,  TPackagePageInfo* collectInfo);

	// ��һ���ϼ�(�������level2����)ҳ���ȡ��ֽ, ��http://www.deskcity.com/details/index/152.html
	bool ColFromPackagePage(const string& pageUrl, const wstring& rootPath);
	// ����Ϊ��ҳ��ȫ����ȡ
	bool ColFromPackagePages(const string& pageUrl, const wstring& rootPath);

	bool GetPaginationInfo(const string &pageUrl, TPaginationInfo& paginationInfo);

	// ��һ�����ֽչʾ(�������level1����)ҳ��(level2)��ȡ��ֽ�� ��http://www.deskcity.com/details/picture/4074.html
	bool ColFromPicListPage(const string& pageUrl, const wstring& rootPath);

	// ��һ����������������ֽ��ҳ��(level1)��ȡ��ֽ����http://www.deskcity.com/details/show/4074/83985.html
	bool ColFromPicViewPage(const string& pageUrl, const wstring& rootPath);

private:
	bool LoadConfigFile();

	void InitLevel1PageKeyInfo( TiXmlElement * thdNode, TSiteInfo &siteInfo );
	void InitLevel2PageKeyInfo( TiXmlElement * thdNode, TSiteInfo &siteInfo );
	void InitLevel3PageKeyInfo( TiXmlElement * thdNode, TSiteInfo &siteInfo );
	void InitPaginationKeyInfo( TiXmlElement * thdNode, TSiteInfo &siteInfo );
	void InitChannelKeyInfo   ( TiXmlElement * thdNode, TSiteInfo &siteInfo );

private:
	CNet*      net;
	TSiteInfo* curSiteInfo;  // ����siteUrl�����
};
#endif