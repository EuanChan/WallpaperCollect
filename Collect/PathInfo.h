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
		return !(lhs.compare(rhs) == 0); //ע��������߼�
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
// struct str_hash
// {
// 	const static size_t bucket_size = 4;
// 	const static size_t min_buckets = 8;
// 	size_t operator()(const string& str) const
// 	{
// 		unsigned long __h = 0;
// 		for (size_t i = 0 ; i < str.size() ; i ++)
// 			__h = 5*__h + str[i];
// 		return size_t(__h);
// 	}
// 	bool operator()(const string& s1, const string& s2) {
// 		return (s1.compare(s2) == 0);
// 	}   
// };

typedef hash_set<string, htraits> TStrHashSet;


class CPathInfo
{
public:
	CPathInfo();
	virtual ~CPathInfo();

	void InitPathInfo();   // ��ʼ������·��
	void LoadUrlMap();     // �ӱ����ļ������Ѽ��ص�url��hashmap
	void SaveUrlMap();     // �����Ѽ���url��hashmap�������ļ�
	void InsertUrlToFile(const string& url);     // ��url����hashmap��
	bool pageLoaded(const string& url); // �жϵ�ǰurl�Ƿ��Ѵ���
	const wchar_t* ModulePath();

	wstring modulePath;
};

//����·������
MakeObjPtrFun( CPathInfo, GetObjPtr_ZMPathInfo )
#define gPathInfoPtr ((CPathInfo*&)GetObjPtr_ZMPathInfo())
#define gPathInfo (*(CPathInfo*&)GetObjPtr_ZMPathInfo())

#endif