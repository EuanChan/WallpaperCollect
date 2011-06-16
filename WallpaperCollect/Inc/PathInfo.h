#ifndef CPATHINFO_H
#define CPATHINFO_H

#include "MyMacro.h"

class CPathInfo
{
public:
	CPathInfo();
	virtual ~CPathInfo();

	void InitPathInfo();   // ��ʼ������·��
	const wchar_t* ModulePath();

	wstring modulePath;
};

//����·������
MakeObjPtrFun( CPathInfo, GetObjPtr_ZMPathInfo )
#define gPathInfoPtr ((CPathInfo*&)GetObjPtr_ZMPathInfo())
#define gPathInfo (*(CPathInfo*&)GetObjPtr_ZMPathInfo())

#endif