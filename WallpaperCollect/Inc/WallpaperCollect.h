#ifndef WALLPAPERCOLLECT_H
#define WALLPAPERCOLLECT_H

#ifdef WallpaperCollect_EXPORTS
#define WallpaperCollect_API __declspec(dllexport)
#else
#define WallpaperCollect_API __declspec(dllimport)
#endif

#include <string>
using std::string;
class WallpaperCollect_API CWallpaperCollect
{
public:
	CWallpaperCollect(void);
	~CWallpaperCollect(void);

	void SetSite(const string& url);
	void SetSaveDir(const string& saveDir);
	// bool ParseAndCollect(const char* url);


	// ��һ��չʾ�����ֽ��ҳ���ȡ��ֽ��
	// ��http://www.deskcity.com/details/picture/4074.html
	bool ColFromPicListPage(const string& pageUrl);

	// ��һ����������������ֽ��ҳ���ȡ��ֽ��
	// ��http://www.deskcity.com/details/show/4074/83985.html
	bool ColFromPicViewPage(const string& pageUrl);

private:
	bool LoadConfigFile();

private:
// 	CWebServer* webServ;
// 	CHtmlParse* parser;
	string     siteUrl;  // ������
	string     saveDir;  // ��ֽ����·��
};
#endif