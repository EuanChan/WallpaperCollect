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

#include "RawThread.h"
#include "RawCriSection.h"

enum ECmdType
{
	ECmdColPackagePages,  // ����ColFromPackagePages()
	ECmdColPicListPage    // ����ColFromPicListPage()
};

typedef struct  
{
	string url;
	wstring savePath;
	ECmdType cmdType;
}TCollectTaskInfo;

extern HANDLE ghNetEvent;
extern HANDLE ghWpCollEvent;
extern HWND   gWindowHandle;

// ��hNetEvent��hWpCollEvent��Ϊ���ź�״̬
__declspec(dllexport) bool SetWallpaperCollectEvent();

// ����Ҫ��Collect.dll�з�����Ϣ�����������Ϣ�Ĵ��ھ��
__declspec(dllexport) void SetMsgRecvWindowH(HWND windowHandle);

class WallpaperCollect_API CWallpaperCollect
{
public:
	CWallpaperCollect();
	~CWallpaperCollect(void);

	void SetSite(const char* url);
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


	//////////////////////////////////////////////////////////////////////////
	bool GetPicViewPageInfo(const string& pageUrl, const wstring& rootPath, TPicShowPageInfo& picPageInfo, wstring& savePath);

	// ��һ����������������ֽ��ҳ��(level1)��ȡ��ֽ����http://www.deskcity.com/details/show/4074/83985.html
	bool ColFromPicViewPage(const string& pageUrl, const wstring& rootPath);


public:
	//////////////////////////////////////////////////////////////////////////
	// ���½����߳��������������
	void AddTask(const string& url, const wstring& savePath, ECmdType type);
	void StartDownload();
	void StopDownload();

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

private:
	//////////////////////////////////////////////////////////////////////////
	static void ThreadFunc( void* aParam );
	void DoWork();

	vector<TCollectTaskInfo> taskInfoVec;
	vector<TCollectTaskInfo>::iterator iter;

	bool onWork;
	CRawThread    rawThread;
	CRawCriSection rawCrisection;
};
#endif