#ifndef COMDEF_H
#define COMDEF_H

#define ZMIMPORT
#define ZMEXPORT

#define ZMDLL_EXPORT __declspec(dllexport)

//�������Ͷ���
typedef char				int8;
typedef short				int16;
typedef long				int32;
typedef __int64				int64;
typedef unsigned char		uint8;
typedef unsigned short		uint16;
typedef unsigned long		uint32;
typedef unsigned __int64	uint64;
typedef wchar_t				wchar;


enum SiteType
{
	kSiteDeskCity
};

//////////////////////////////////////////////////////////////////////////
class TPicshowPageAttri
{
public:
	wstring picName;
	string picUrl;
};

class TSiteInfo;
// ����ʵ�ʱ�ֽ���ӵ���ҳ(pageLevel1)�ؼ���
class TPicshowPageKey 
{
public:
	string picNameKey; // ��ֽ���ƹؼ���
	string picNameL;
	string picNameR;
	string picUrlKey;  // ��ֽUrl�ؼ���
	string picUrlL;
	string picUrlR;

	void Log(const string& siteName) const;
};

//////////////////////////////////////////////////////////////////////////
// �������pageLevel1ҳ�����ӵ���ҳ(pageLevel2)�ؼ�����Ϣ
class TPackagePageKey
{
public:
	string nameKey;  // ��ֽ�ϼ�Ŀ¼���ƹؼ���
	string nameL;
	string nameR;
	string urlKey;  // ������ֽҳ�����ӹؼ���
	string urlL;
	string urlR;

	void Log(const string& siteName) const;
};

class TPackagePageAttri
{
public:
	wstring  packageName;  // ��ֽ�ϼ�����
	vector<string> urlArr;
};

//////////////////////////////////////////////////////////////////////////
// �������pageLevel2ҳ�����ӵ���ҳ(pageLevel3)�ؼ�����Ϣ
class TPackagesPageKey
{

};

class TSiteInfo
{
public:
	TPicshowPageKey picshowPageKey;
	TPackagePageKey packagePageKey;
	//string nextChildKey;
	string mainUrl;
	string siteName;
};

typedef vector<TSiteInfo> TSiteList;

typedef struct _ZMTIME
{
	_ZMTIME()
	{
		memset(this,0,sizeof(_ZMTIME));
	}
	uint16 wYear;						//[0--]
	uint8 wMonth;						//[1--12]
	uint8 wDay;							//[1--31]
	uint8 wHour;						//[0--23]
	uint8 wMinute;						//[0--59]
	uint8 wSecond;						//[0--59]
	uint16 wMilliseconds;				//[0--999]
}ZMTIME,*LPZMTIME;



#endif