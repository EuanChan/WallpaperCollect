// Main.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "Main.h"

#include "WallpaperCollect.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Ψһ��Ӧ�ó������

CWinApp theApp;

using namespace std;

void test();

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

	// ��ʼ�� MFC ����ʧ��ʱ��ʾ����
	if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0))
	{
		// TODO: ���Ĵ�������Է���������Ҫ
		_tprintf(_T("����: MFC ��ʼ��ʧ��\n"));
		nRetCode = 1;
	}
	else
	{
		test(); 
	}

	return nRetCode;
}

void test()
{
	char szPath[MAX_PATH] = {0};
	string strPath;
	::GetModuleFileName(NULL, szPath, sizeof(szPath));
	strcpy(strrchr(szPath,'\\'), "\\Cache\\");
	strPath = szPath;

	CWallpaperCollect wpCol;

	wpCol.SetSite("http://www.deskcity.com");
	wpCol.SetSaveDir(strPath);
	wpCol.ColFromPicViewPage("http://www.deskcity.com/details/show/4074/83985.html");
}