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
	wchar_t szPath[MAX_PATH] = {0};
	wstring cachePath;
	::GetModuleFileName(NULL, szPath, sizeof(szPath));
	wcscpy(wcsrchr(szPath, '\\'), _T("\\Cache\\"));
	cachePath = szPath;

	CWallpaperCollect wpCol;

	wpCol.SetSite("http://www.deskcity.com/");
	wpCol.SetSaveDir(cachePath);
	wpCol.ColFromPicViewPage("http://www.deskcity.com/details/show/4074/83985.html");
}