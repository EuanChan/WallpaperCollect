// PaperCol.cpp : ���� DLL Ӧ�ó������ڵ㡣
//

#include  <atlbase.h>

#include "stdafx.h"
#include "WallpaperCollect.h"
#include "WebServer.h"
#include "HtmlParse.h"
#include "tinyxml.h"
#include "Log.h"
#include "Tool.h"
#include "PathInfo.h"

TSiteList gSiteList;
CLogXml Log;
bool bGlobalValueInit = false;

#define WallpaperCollect_EXPORTS


CWallpaperCollect::CWallpaperCollect(void)
{
	if (!bGlobalValueInit)
	{
		Log.Init(L"log");
		LoadConfigFile();
		if (gPathInfoPtr == NULL)
		{
			gPathInfoPtr = new CPathInfo();
			gPathInfo.InitPathInfo();
		}
	}
}

CWallpaperCollect::~CWallpaperCollect(void)
{
}

bool CWallpaperCollect::LoadConfigFile()
{
	char szPath[MAX_PATH] = {0};
	string configFile;
	::GetModuleFileNameA(NULL, szPath, sizeof(szPath));
	strcpy(strrchr(szPath,'\\'), "\\config.xml");
	configFile = szPath;

	TiXmlDocument xmlDoc;
	if (xmlDoc.LoadFile(configFile.c_str()))
	{
		TiXmlElement *root = xmlDoc.RootElement();
		if (!root)
			return false;

		string strRoot = root->Value();
		if (0 != strcmp(strRoot.c_str(), "WallpaperCollection"))
			return false;

		TiXmlElement *secNode = root->FirstChildElement();
		while (secNode)
		{
			string strNodeV = secNode->Value();
			if (0 == strcmp(strNodeV.c_str(), "WallpaperSite"))
			{
				TSiteInfo  siteInfo;
				TiXmlElement *thdNode = secNode->FirstChildElement();
				while (thdNode)
				{
					string thdNodeStr = thdNode->Value();
					if ("Name" == thdNodeStr)
						siteInfo.siteName = thdNode->GetText() ? thdNode->GetText() : "";
					else if ("Site" == thdNodeStr)
						siteInfo.mainUrl = thdNode->GetText() ? thdNode->GetText() : "";
					else if ("Level1PageKey" == thdNodeStr)
					{
						TPicshowPageKey picShowPageKey;
						TiXmlElement *siteElm = thdNode->FirstChildElement();
						while (siteElm)
						{
							string childnode = siteElm->Value();
							if ("Name" == childnode)
								siteInfo.siteName = siteElm->GetText() ? siteElm->GetText() : "";
							else if ("Site" == childnode)
								siteInfo.mainUrl = siteElm->GetText() ? siteElm->GetText() : "";
							else if ("HtmlPicNameKey" == childnode)
								picShowPageKey.picNameKey = siteElm->GetText() ? siteElm->GetText() : "";
							else if ("HtmlPicNameL" == childnode)
								picShowPageKey.picNameL = siteElm->GetText() ? siteElm->GetText() : "";
							else if ("HtmlPicNameR" == childnode)
								picShowPageKey.picNameR = siteElm->GetText() ? siteElm->GetText() : "";
							else if ("HtmlPicUrlKey" == childnode)
								picShowPageKey.picUrlKey = siteElm->GetText() ? siteElm->GetText() : "";
							else if ("HtmlPicUrlL" == childnode)
								picShowPageKey.picUrlL = siteElm->GetText() ? siteElm->GetText() : "";
							else if ("HtmlPicUrlR" == childnode)
								picShowPageKey.picUrlR = siteElm->GetText() ? siteElm->GetText() : "";

							siteElm = siteElm->NextSiblingElement();
						}
						siteInfo.picshowPageKey = picShowPageKey;
					}
					else if ("Level2PageKey" == thdNodeStr)
					{
						TPackagePageKey packagePageKey;
						TiXmlElement *siteElm = thdNode->FirstChildElement();
						while (siteElm)
						{
							string childnode = siteElm->Value();
							if ("Name" == childnode)
								siteInfo.siteName = siteElm->GetText() ? siteElm->GetText() : "";
							else if ("Site" == childnode)
								siteInfo.mainUrl = siteElm->GetText() ? siteElm->GetText() : "";
							else if ("PackageNameKey" == childnode)
								packagePageKey.nameKey = siteElm->GetText() ? siteElm->GetText() : "";
							else if ("PackageNameL" == childnode)
								packagePageKey.nameL = siteElm->GetText() ? siteElm->GetText() : "";
							else if ("PackageNameR" == childnode)
								packagePageKey.nameR = siteElm->GetText() ? siteElm->GetText() : "";
							else if ("PicPageUrlKey" == childnode)
								packagePageKey.urlKey = siteElm->GetText() ? siteElm->GetText() : "";
							else if ("PicPageUrlL" == childnode)
								packagePageKey.urlL = siteElm->GetText() ? siteElm->GetText() : "";
							else if ("PicPageUrlR" == childnode)
								packagePageKey.urlR = siteElm->GetText() ? siteElm->GetText() : "";

							siteElm = siteElm->NextSiblingElement();
						}
						siteInfo.packagePageKey = packagePageKey;
					}
					thdNode = thdNode->NextSiblingElement();
				}

				gSiteList.push_back(siteInfo);
				Log.AddLog(siteInfo.siteName.c_str());
			}
			else
			{

			}
			secNode = root->NextSiblingElement();
		}
		bGlobalValueInit = true;
		Log.Save();
	}
	return true;
}

void CWallpaperCollect::SetSite( const string& url )
{
	siteUrl = url;
	if ((*siteUrl.rbegin()) != '/')
		this->siteUrl.append("/");

	// ����url�е���Ϣ��sitelist���ҵ�ƥ��վ����Ϣ
	pCurSite = NULL;

	string siteName = url;
	size_t posL = siteName.find("www.");
	posL += 4;
	size_t posR = siteName.find(".", posL);
	siteName = siteName.substr(posL, posR - posL);

	size_t len = gSiteList.size();
	for (size_t i = 0; i < len; i++)
	{
		if (0 == strcmp(siteName.c_str(), gSiteList[i].siteName.c_str()))
		{
			pCurSite = &gSiteList[i];
			break;
		}
	}
}

void CWallpaperCollect::SetSaveDir(const wstring& saveDir)
{
	this->saveDir = saveDir;
	if ((*saveDir.rbegin()) != '\\')
		this->saveDir.append(_T("\\"));

	MakeSurePathExists(saveDir.c_str(), false);
}

// ����ҳ�����ݣ�ÿȡ�ð������ű�ֽ��ҳ��󣬵���ColFromPicViewPage����
// ��http://www.deskcity.com/details/picture/4074.html
bool CWallpaperCollect::ColFromPicListPage( const string& pageUrl )
{
	if (!pCurSite) return false;

	// ��ȡ��ҳԴ����
	CWebServer webServ;
	string pageHtml = webServ.ColPageSourceHtml(pageUrl);

	// �����õ���ʾ��ֽҳ���url����������
	CHtmlParse parser(pageHtml);
	TPackagePageAttri package;
	package = parser.GetWallpaperPagesUrl(*pCurSite);	

	// ����packageName,���ñ�ֽ�����ļ�����
	package.packageName = splitFirstString(package.packageName);
	saveDir.append(package.packageName + _T("\\"));
	MakeSurePathExists(saveDir.c_str(), false);
	
	// ����ColFromPicViewPage����ͼƬ
	size_t count = package.urlArr.size();
	for (size_t i = 0; i < count; i++)
	{
		ColFromPicViewPage(package.urlArr[i]);
	}
	return false;
}

// ����ҳ�����ݣ�ȡ�õ��ű�ֽ��url������url����ͼƬ
// ��http://www.deskcity.com/details/show/4074/83985.html
bool CWallpaperCollect::ColFromPicViewPage( const string& pageUrl )
{
	if (!pCurSite) return false;

	// ��ȡ��ҳԴ����
	CWebServer webServ;
	string pageHtml = webServ.ColPageSourceHtml(pageUrl);

	// ������ñ�ֽ�����ӡ���ֽ�����Ϣ
	CHtmlParse parser(pageHtml);
	TPicshowPageAttri picShowPageAttri;
	picShowPageAttri = parser.GetWallpaperImgUrl(*pCurSite);

	USES_CONVERSION;
	wchar *picNameExt = A2W(pCurSite->picshowPageKey.picUrlR.c_str());
	wstring filePath = saveDir + picShowPageAttri.picName + picNameExt;

	// TODO:����ͼƬ�Ѵ���

	// ����ͼƬ���浽ָ��Ŀ¼
	webServ.DownLoadFile(picShowPageAttri.picUrl, filePath);

	return true;
}