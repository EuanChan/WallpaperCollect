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
// 	std::string GetWebPage(const std::string& sUrl);
// 
	// ��ȡHTMLҳ��Դ��
	string ColPageSourceHtml(const string& pageUrl);

	bool DownLoadFile(const string& url, const string& filePath);
};
