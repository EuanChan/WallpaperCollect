#pragma once

#include <afxinet.h>

class CWebServer :	public CWnd
{
	DECLARE_DYNAMIC(CWebServer)

public:
	CWebServer();
	virtual ~CWebServer();

protected:
	DECLARE_MESSAGE_MAP()

public:
	// ��ȡָ��URL����������
// 	std::wstring GetWebPage(const std::wstring& sUrl);
// 
	// ��ȡHTMLҳ��Դ��
	bool ColPageSourceHtml(const string& pageUrl, string &htmlSrc);

	bool DownLoadFile(const string& url, const wstring& filePath);
	bool UpdateProgress(LONGLONG index, LONGLONG total);
	bool UpdateCurPicName(WPARAM wstrPt);
	bool NotifyThumbnailDownload(WPARAM urlPt, LPARAM savePathPt);
	
private:
	wstring curDownloadFile;
	CFile  *pfile;
};
