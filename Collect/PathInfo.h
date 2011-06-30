#ifndef CPATHINFO_H
#define CPATHINFO_H

#include "MyMacro.h"
#include <hash_set>
using stdext::hash_set;


struct htraits 
{
	// comparisons
	bool operator()(const string& lhs,const string& rhs) const 
	{
		return !(lhs.compare(rhs) == 0); 
	}
	// hashing function
	size_t operator()(const string& key) const 
	{
		unsigned long __h = 0;
		for (size_t i = 0 ; i < key.size() ; i ++)
			__h = 5*__h + key[i];
		return size_t(__h);
	}
	// bucket information
	static const size_t bucket_size = 10u;
	static const size_t min_buckets = 20u;
};
typedef hash_set<string, htraits> TStrHashSet;


class __declspec(dllexport) CPathInfo
{
public:
	static CPathInfo* GetInstance();
	void InitPathInfo();   // ��ʼ������·��
	void LoadUrlMap();     // �ӱ����ļ������Ѽ��ص�url��hashmap
	void SaveUrlMap();     // �����Ѽ���url��hashmap�������ļ�
	void InsertUrlToFile(const string& url);     // ��url����hashmap��
	bool PageLoaded(const string& url); // �жϵ�ǰurl�Ƿ��Ѵ���
	wstring ModulePath();
	wstring CachePath();
	wstring ThumbnailCachePath();
	wstring GetSavePathRoot();
	void SetSavePathRoot(const wstring& path);
protected:
	CPathInfo();
	virtual ~CPathInfo();

private:
	static CPathInfo *instance;
	wstring modulePath;
	wstring savePathRoot;
	wstring cachePath;
	wstring thumbnailCachePath;
};

//����·������
#define gPathInfo CPathInfo::GetInstance()
// MakeObjPtrFun( CPathInfo, GetObjPtr_ZMPathInfo )
// #define gPathInfoPtr ((CPathInfo*&)GetObjPtr_ZMPathInfo())
// #define gPathInfo (*(CPathInfo*&)GetObjPtr_ZMPathInfo())

#endif