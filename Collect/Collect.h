// Collect.h : Collect DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CCollectApp
// �йش���ʵ�ֵ���Ϣ������� Collect.cpp
//

class CCollectApp : public CWinApp
{
public:
	CCollectApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
