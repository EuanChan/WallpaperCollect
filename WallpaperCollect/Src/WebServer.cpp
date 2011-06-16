
#include  <atlbase.h>

#include "stdafx.h"
#include "WebServer.h"

IMPLEMENT_DYNAMIC(CWebServer, CWnd)

CWebServer::CWebServer(void)
{
	afxCurrentAppName = _T("WallpaperCollect.dll");
}

CWebServer::~CWebServer(void)
{
}

BEGIN_MESSAGE_MAP(CWebServer, CWnd)
END_MESSAGE_MAP()



string CWebServer::ColPageSourceHtml( const string& pageUrl )
{
	wstring htmlWStr;
	string htmlStr;
	USES_CONVERSION;
	CString theUrl = A2W(pageUrl.c_str());
	CInternetSession session;
	CInternetFile* file = NULL;

	try
	{	
		file = (CInternetFile*) session.OpenURL(theUrl); 
	}
	catch (CInternetException* m_pException)
	{
		file = NULL; 
		m_pException->Delete();
		return FALSE;
	}

	if (file)
	{
		CString  somecode;	//Ҳ�ɲ���LPTSTR���ͣ�������ɾ���ı��е�\n�س���

		// ��д��ҳ�ļ���ֱ��Ϊ��
		// �������LPTSTR���ͣ���ȡ������nMax��0��ʹ�������ַ�ʱ����
		while (file->ReadString(somecode) != NULL) 
		{
			somecode += "\n";
			htmlWStr += somecode;
		}
		htmlStr = W2A(htmlWStr.c_str());

		file->Close();
		delete file;
	}

	//////////////////////////////////////////////////////////////////////////
	wchar szPath[MAX_PATH] = {0};
	CString strPath;
	::GetModuleFileName(NULL,szPath,sizeof(szPath));
	wcscpy(wcsrchr(szPath, _T('\\')), _T("\\1.html"));
	strPath = szPath;

	CStdioFile data;
	if (data.Open(strPath, CFile::modeCreate | CFile::modeWrite | 
		CFile::shareDenyWrite | CFile::typeText))
	{
		data.WriteString(htmlWStr.c_str());
		data.Close();
	}
	//////////////////////////////////////////////////////////////////////////

	return htmlStr;
}


bool CWebServer::DownLoadFile( const string& url, const wstring& filePath )
{
	bool ret = false;

	USES_CONVERSION;
	wstring wUrl = A2W(url.c_str());
	CInternetSession netSess;
	CHttpFile *pHttpFile = NULL;
	try
	{
		DWORD dwFlag = INTERNET_FLAG_TRANSFER_BINARY|INTERNET_FLAG_DONT_CACHE|INTERNET_FLAG_RELOAD;
		pHttpFile = (CHttpFile *)netSess.OpenURL(wUrl.c_str(), 1, dwFlag);
		if (NULL != pHttpFile)
		{
			DWORD bufSize = 1024;
			DWORD readCount = 0;
			BYTE buf[1024];
			int len = 0;
			CFile file;
			if (file.Open(filePath.c_str(), CFile::modeCreate | CFile::modeWrite | CFile::typeBinary))
			{
				memset(buf, 0, bufSize);
				while (true)
				{
					readCount = pHttpFile->Read(buf, bufSize);
					file.Write(buf, readCount);
					if (readCount < bufSize)
						break;
				}
				file.Close();
				ret = true;
			}
			pHttpFile->Close();
			delete pHttpFile;
			pHttpFile = NULL;
		}
	}
	catch (...)
	{
		if(NULL != pHttpFile)
		{
			pHttpFile->Close();
			delete pHttpFile;
			pHttpFile = NULL;
		}
	}
	netSess.Close();
	return ret;
}