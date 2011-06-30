#ifndef CHTMLPARSE_H
#define CHTMLPARSE_H

#include "ComDef.h"

class CHtmlParse
{
public:
	CHtmlParse(const string& htmlSource);
	~CHtmlParse(void);
	void ResetSrc(const string& htmlSource);

	// ����htmlSource, ���Ƶ���б���Ϣ
	bool GetChannelInfo(const TSiteInfo& siteInfo, TChannelInfo *channelInfo);

	// ����htmlSource������siteInfo�ؼ��ʻ�ȡҳ�������Ϣ
	bool GetPageIndexInfo(const TSiteInfo& siteInfo, TPaginationInfo *paginationInfo);

	// ����������� pageLevel2 url����ҳԴ��  pageLevel3
	bool GetLevel2PageUrls(const TSiteInfo& siteInfo, TPackagePageInfo* packagePageInfo);
	
	// ����������� pageLevel1 url����ҳԴ�� pageLevel2
	bool GetLevel1PageUrls(const TSiteInfo& siteInfo, TPicsShowPageInfo* picsShowPageInfo);

	// �������� ��ֽͼƬurl�� ��ҳԴ�� pageLevel1
	bool GetWallpaperImgUrl(const TSiteInfo& siteInfo, TPicShowPageInfo* picShowPageInfo);

private:
	string   htmlSrc;
};

#endif