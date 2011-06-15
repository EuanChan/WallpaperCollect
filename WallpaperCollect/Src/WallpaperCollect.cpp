// PaperCol.cpp : ���� DLL Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "WallpaperCollect.h"
#include "WebServer.h"
#include "HtmlParse.h"

#define WallpaperCollect_EXPORTS

// CWinApp theApp;
// 
// int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
// {
// 	int nRetCode = 0;
// 
// 	// ��ʼ�� MFC ����ʧ��ʱ��ʾ����
// 	if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0))
// 	{
// 		// TODO: ���Ĵ�������Է���������Ҫ
// 		_tprintf(_T("����: MFC ��ʼ��ʧ��\n"));
// 		nRetCode = 1;
// 	}
// 	else
// 	{
// 		// TODO: �ڴ˴�ΪӦ�ó������Ϊ��д���롣
// 	}
// 
// 	return nRetCode;
// }


CWallpaperCollect::CWallpaperCollect(void)
{
}

CWallpaperCollect::~CWallpaperCollect(void)
{
}

void CWallpaperCollect::SetSite(const string& url)
{
	siteUrl = url;
	if ((*siteUrl.rbegin()) != '/')
		this->siteUrl.append("/");
}

void CWallpaperCollect::SetSaveDir(const string& saveDir)
{
	this->saveDir = saveDir;
	if ((*saveDir.rbegin()) != '\\')
		this->saveDir.append("\\");
}

// ����ҳ�����ݣ�ÿȡ�ð������ű�ֽ��ҳ��󣬵���ColFromPicViewPage����
bool CWallpaperCollect::ColFromPicListPage(const string& pageUrl)
{
	return false;
}

// ����ҳ�����ݣ�ȡ�õ��ű�ֽ��url������url����ͼƬ
bool CWallpaperCollect::ColFromPicViewPage(const string& pageUrl)
{
	CWebServer webServ;
	string pageHtml = webServ.ColPageSourceHtml(pageUrl);

	// ������ñ�ֽ�����ӡ���ֽ�����Ϣ
	CHtmlParse parser(pageHtml);
	HtmlKeyStruct htmlKey;
	HtmlPicStruct htmlPic;
	htmlKey.picNameKey = "imginfo";
	htmlKey.picNameL = "<strong>";
	htmlKey.picNameR = "</strong>";
	htmlKey.picUrlKey = "s_img";
	htmlKey.picUrlL = "src=\"";
	htmlKey.picUrlR = ".jpg";
	htmlPic = parser.GetWallpaperImgUrl(htmlKey);

	// �����õ�ͼƬurl
	htmlPic.picUrl.insert(0, siteUrl.c_str());

	string filePath = saveDir + htmlPic.picName + htmlKey.picUrlR;

	// ����ͼƬ���浽ָ��Ŀ¼
	webServ.DownLoadFile(htmlPic.picUrl, filePath);

	return true;
}