#ifndef CPATHINFO_H
#define CPATHINFO_H

#include "MyMacro.h"
#include <hash_set>
using stdext::hash_set;

// struct htraits 
// {
// 	// comparisons
// 	bool operator()(const string& lhs,const string& rhs) const 
// 	{
// 		return !(lhs.compare(rhs) == 0); 
// 	}
// 	// hashing function
// 	size_t operator()(const string& key) const 
// 	{
// 		// hash _Keyval to size_t value by pseudorandomizing transform
// 		size_t _Val = 2166136261U;
// 		size_t _First = 0;
// 		size_t _Last = key.size();
// 		size_t _Stride = 1 + _Last / 10;
// 
// 		if (_Stride < _Last)
// 			_Last -= _Stride;
// 		for(; _First < _Last; _First += _Stride)
// 			_Val = 16777619U * _Val ^ (size_t)key[_First];
// 		return (_Val);
// 	}
// 	// bucket information
// 	static const size_t bucket_size = 4u;
// 	static const size_t min_buckets = 8u;
// };
// 
// typedef hash_set<string, htraits> TStrHashSet1;
typedef hash_set<string> TStrHashSet;


class __declspec(dllexport) CPathInfo
{
public:
	static CPathInfo* GetInstance();
	void ReleaseInstance();
	void InitPathInfo();   // ��ʼ������·��

	//////////////////////////////////////////////////////////////////////////
	const wchar_t* GetModulePath();
	const wchar_t* GetCachePath();
	const wchar_t* GetThumbnailCachePath();
	const wchar_t* GetSavePathRoot();
	void SetSavePathRoot(const wstring& path);


	//////////////////////////////////////////////////////////////////////////
	void LoadTaskedPicsPageUrl();     // �ӱ����ļ������Ѽ��ص�������������� ��ֽ��url
	void SaveTaskedPicsPageUrl();     // �����Ѽ��ص�������������� ��ֽ��url �������ļ�
	void InsertTaskedPicsPageUrl(const string& url)
	{
		taskedUrlList.insert(url);
	}
	void EraserTaskedPicsPageUrl(const string& url)
	{
		taskedUrlList.erase(url);
	}
	bool CurPicsPageUrlTasked(const string& url) // �жϵ�ǰurl�Ƿ�����һ�γ�������ʱ��ӵ�����������
	{
		TStrHashSet::const_iterator iter = taskedUrlList.begin();
		iter = taskedUrlList.find(url);
		return iter != taskedUrlList.end();
	}

	//////////////////////////////////////////////////////////////////////////
	void LoadFinishedPicsPageUrl();   // �ӱ����ļ��������������ص� ��ֽ��url
	void SaveFinishedPicsPageUrl();   // �������������ص� ��ֽ��url �������ļ�
	void InsertFinishedPicsPageUrl(const string& url)
	{
		finishedPackageUrlList.insert(url);
	}
	bool CurPicsPageUrlFinished(const string& url) // �жϵ�ǰurl�Ƿ����������
	{
		TStrHashSet::const_iterator iter = finishedPackageUrlList.begin();
		iter = finishedPackageUrlList.find(url);
		return iter != finishedPackageUrlList.end();
	}

	//////////////////////////////////////////////////////////////////////////
	void LoadUnfinishedPicTask(vector<TPicTaskInfo>& taskVec); // ����δ��ɱ�ֽ��������
	void SaveUnfinishedPicTask(vector<TPicTaskInfo>& taskVec); // ����δ��ɱ�ֽ��������


protected:
	CPathInfo();
	virtual ~CPathInfo();

	void DoLoadHashSet(TStrHashSet& strList, wstring filePath);
	void DoSaveHashSet(TStrHashSet& strList, wstring filePath);

private:
	static CPathInfo *instance;
	wstring modulePath;
	wstring savePathRoot;
	wstring cachePath;
	wstring thumbnailCachePath;
	TStrHashSet taskedUrlList;            // ��ҳ����������м���һ�ζ���ӵ����������У�δ����Ƿ����
	TStrHashSet finishedPackageUrlList;   // �Ѽ��ȷ����ҳ����������м�����������
};

//����·������
#define gPathInfo CPathInfo::GetInstance()
// MakeObjPtrFun( CPathInfo, GetObjPtr_ZMPathInfo )
// #define gPathInfoPtr ((CPathInfo*&)GetObjPtr_ZMPathInfo())
// #define gPathInfo (*(CPathInfo*&)GetObjPtr_ZMPathInfo())

#endif