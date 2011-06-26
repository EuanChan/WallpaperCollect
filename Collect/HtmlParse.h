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
	TChannelAttri GetChannelInfo(const TSiteInfo& siteInfo);

	// ����htmlSource������siteInfo�ؼ��ʻ�ȡҳ�������Ϣ
	TPaginationAttri GetPageIndexInfo(const TSiteInfo& siteInfo);

	// ����������� pageLevel2 url����ҳԴ��  pageLevel3
	TPackagePageAttri GetLevel2PageUrls(const TSiteInfo& siteInfo);
	
	// ����������� pageLevel1 url����ҳԴ�� pageLevel2
	TPicsShowPageAttri GetLevel1PageUrls(const TSiteInfo& siteInfo);

	// �������� ��ֽͼƬurl�� ��ҳԴ�� pageLevel1
	TPicShowPageAttri GetWallpaperImgUrl(const TSiteInfo& siteInfo);

private:
	string   htmlSrc;
};

#endif