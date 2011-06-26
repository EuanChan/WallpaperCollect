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
class TPicShowPageAttri
{
public:
	wstring picName;
	string picUrl;
};

class TSiteInfo;
// ����ʵ�ʱ�ֽ���ӵ���ҳ(pageLevel1)�ؼ���
class TPicShowPageKey 
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
class TPicsShowPageKey
{
public:
	string nameKey;  // ��ֽ��Ŀ¼���ƹؼ���
	string nameL;
	string nameR;
	string urlKey;  // ������ֽҳ�����ӹؼ���
	string urlL;
	string urlR;

	void Log(const string& siteName) const;
};

class TPicsShowPageAttri
{
public:
	wstring  name;  // ��ֽ�ϼ�����
	vector<string> urlArr;
};

//////////////////////////////////////////////////////////////////////////
// �������pageLevel2ҳ�����ӵ���ҳ(pageLevel3)�ؼ�����Ϣ
class TPackagePageKey
{
public:
	string nameKey;  // ��ֽ�ϼ�Ŀ¼���ƹؼ���
	string nameL;
	string nameR;
	string urlKey;   // ��ֽ��ҳ�����ӹؼ���
	string urlL;
	string urlR;
};
class TPackagePageAttri
{
public:
	wstring name;
	vector<string> urlArr;
};

//////////////////////////////////////////////////////////////////////////
// ��һҳ����һҳ�ؼ�����Ϣ
class TPaginationKey
{
public:
	string divKey;
	string indexKey;
	string indexL;
	string indexR;
	string currentKey;
	string currentL;
	string currentR;
};

class TPaginationAttri
{
public:
	TPaginationAttri():minPage(1), maxPage(1), curPage(1){}
	string pageUrlBase;
	string extentStr;
	size_t minPage;
	size_t curPage;
	size_t maxPage;
};

//////////////////////////////////////////////////////////////////////////
// Ƶ��Ŀ¼ �ؼ���
class TChannelKey
{
public:
	string srcPageUrl;
};

typedef pair<string, string> TChannelNodeChild;  // pair<name, url>
typedef pair<string, vector<TChannelNodeChild> > TChannelNode;
typedef vector<TChannelNode> TChannelTree;  // vector<pair<rootName, childVec> >
// vector<pair<rootName, childTreeNodeVector>>
class TChannelAttri
{
public:
	string siteName;
	TChannelTree tree;
};
class TChannelStrInfo
{
public:
	int num;
	string channelName;
	string channelUrl;
	TChannelStrInfo()
		: num(0)
	{		
	}
	TChannelStrInfo(const TChannelStrInfo& strInfo)
	{
		num = strInfo.num;
		channelName = strInfo.channelName;
		channelUrl  = strInfo.channelUrl;
	}
};

//////////////////////////////////////////////////////////////////////////
// վ�����йؼ�����Ϣ
class TSiteInfo
{
public:
	TPicShowPageKey  picShowPageKey;
	TPicsShowPageKey picsShowPageKey;
	TPackagePageKey  packagePageKey;
	TPaginationKey   paginationKey;
	TChannelKey      channelKey;
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